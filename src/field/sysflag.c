//============================================================================================
/**
 * @file	sysflag.c
 * @bfief	�v���O�����A�X�N���v�g����A�N�Z�X�����V�X�e���t���O����
 * @author	Satoshi Nohara
 * @date	06.03.12
 */
//============================================================================================
#include "common.h"
#include "system/pm_rtc.h"			//GF_RTC_IsNightTime
#include "system/snd_tool.h"
#include "fieldsys.h"
#include "script.h"
#include "field/evwkdef.h"
#include "sysflag.h"
#include "contest/contest_def.h"
#include "mapdefine.h"				//ZONE_ID_C01


//============================================================================================
//
//	�v���g�^�C�v�錾
//
//============================================================================================
static void SysFlag_Set( EVENTWORK* ev, u16 flag );
static void SysFlag_Reset( EVENTWORK* ev, u16 flag );
static BOOL SysFlag_Check( EVENTWORK* ev, u16 flag );
static BOOL SysFlag_Common( EVENTWORK* ev, SYSFLAG_MODE mode, u32 flag_id);


//============================================================================================
//
//	�֐�
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �V�X�e���t���O�Z�b�g
 *
 * @param	ev			EVENTWORK�̃|�C���^
 * @param	flag		�t���O�i���o�[
 *
 * @retval	none
 *
 * �V�X�e���t���O�́A�X�N���v�g�̃Z�[�u�t���O���g�p���Ă���
 */
//--------------------------------------------------------------------------------------------
static void SysFlag_Set( EVENTWORK* ev, u16 flag )
{
	EventWork_SetEventFlag( ev, flag );
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * �V�X�e���t���O���Z�b�g
 *
 * @param	ev			EVENTWORK�̃|�C���^
 * @param	flag		�t���O�i���o�[
 *
 * @retval	none
 *
 * �V�X�e���t���O�́A�X�N���v�g�̃Z�[�u�t���O���g�p���Ă���
 */
//--------------------------------------------------------------------------------------------
static void SysFlag_Reset( EVENTWORK* ev, u16 flag )
{
	EventWork_ResetEventFlag( ev, flag );
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * �V�X�e���t���O�`�F�b�N
 *
 * @param	ev			EVENTWORK�̃|�C���^
 * @param	flag		�t���O�i���o�[
 *
 * @retval	"1 = �t���OON"
 * @retval	"0 = �t���OOFF"
 *
 * �V�X�e���t���O�́A�X�N���v�g�̃Z�[�u�t���O���g�p���Ă���
 */
//--------------------------------------------------------------------------------------------
static BOOL SysFlag_Check( EVENTWORK* ev, u16 flag )
{
	return EventWork_CheckEventFlag( ev, flag );
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
static BOOL SysFlag_Common( EVENTWORK* ev, SYSFLAG_MODE mode, u32 flag_id)
{
	switch (mode) {
	case SYSFLAG_MODE_SET:
		SysFlag_Set( ev, flag_id);
		break;
	case SYSFLAG_MODE_RESET:
		SysFlag_Reset( ev, flag_id);
		break;
	case SYSFLAG_MODE_CHECK:
		return SysFlag_Check( ev, flag_id);
	default:
		GF_ASSERT_MSG(0, "FLAG %d, NOT DEFINED MODE %d\n", flag_id, mode);
	}
	return FALSE;
}

//============================================================================================
//
//	�o�b�O�֘A
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �o�b�O����t���O�̃Z�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
void SysFlag_BagSet( EVENTWORK* ev )
{
	SysFlag_Set( ev, SYS_FLAG_BAG_GET );
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * �o�b�O����t���O�̃`�F�b�N
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	"1 = �t���OON"
 * @retval	"0 = �t���OOFF"
 */
//--------------------------------------------------------------------------------------------
BOOL SysFlag_BagCheck( EVENTWORK* ev )
{
	return SysFlag_Check( ev, SYS_FLAG_BAG_GET );
}

//============================================================================================
//
//	�J���i�M�̃M���K�c�C�x���g�֘A
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �J���i�M�̃M���K�c�C�x���g�t���O�̃Z�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
void SysFlag_T05GingaEventSet( EVENTWORK* ev )
{
	SysFlag_Set( ev, SYS_FLAG_T05_GINGA_EVENT );
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * �J���i�M�̃M���K�c�C�x���g�t���O�̃`�F�b�N
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	"1 = �t���OON"
 * @retval	"0 = �t���OOFF"
 */
//--------------------------------------------------------------------------------------------
BOOL SysFlag_T05GingaEventCheck( EVENTWORK* ev )
{
	return SysFlag_Check( ev, SYS_FLAG_T05_GINGA_EVENT );
}

//============================================================================================
//
//	�Q�[���N���A�֘A
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �Q�[���N���A�t���O�̃Z�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
void SysFlag_GameClearSet( EVENTWORK* ev )
{
	SysFlag_Set( ev, SYS_FLAG_GAME_CLEAR );
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * �Q�[���N���A�t���O�̃`�F�b�N
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	"1 = �t���OON"
 * @retval	"0 = �t���OOFF"
 */
//--------------------------------------------------------------------------------------------
BOOL SysFlag_GameClearCheck( EVENTWORK* ev )
{
	return SysFlag_Check( ev, SYS_FLAG_GAME_CLEAR );
}


//============================================================================================
//
//	�A������t���O�֘A
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �A������t���O�̃Z�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
void SysFlag_PairSet( EVENTWORK* ev )
{
	SysFlag_Set( ev, SYS_FLAG_PAIR );
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * �A������t���O�̃��Z�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
void SysFlag_PairReset( EVENTWORK* ev )
{
	SysFlag_Reset( ev, SYS_FLAG_PAIR );
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * �A������t���O�̃`�F�b�N
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	"1 = �t���OON"
 * @retval	"0 = �t���OOFF"
 */
//--------------------------------------------------------------------------------------------
BOOL SysFlag_PairCheck( EVENTWORK* ev )
{
	return SysFlag_Check( ev, SYS_FLAG_PAIR );
}


//============================================================================================
//
//	������������t���O�֘A
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * ������������t���O�̃Z�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
void SysFlag_OneStepSet( EVENTWORK* ev )
{
	SysFlag_Set( ev, SYS_FLAG_ONE_STEP );
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * ������������t���O�̃��Z�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
void SysFlag_OneStepReset( EVENTWORK* ev )
{
	SysFlag_Reset( ev, SYS_FLAG_ONE_STEP );
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * ������������t���O�̃`�F�b�N
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	"1 = �t���OON"
 * @retval	"0 = �t���OOFF"
 */
//--------------------------------------------------------------------------------------------
BOOL SysFlag_OneStepCheck( EVENTWORK* ev )
{
	return SysFlag_Check( ev, SYS_FLAG_ONE_STEP );
}


//============================================================================================
//
//	�o�g���T�[�`���[�̃o�b�e���[���g�p���Ă��邩�t���O�֘A
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �o�g���T�[�`���[�̃o�b�e���[���g�p���Ă��邩�t���O�̃Z�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
void SysFlag_BtlSearcherUseSet( EVENTWORK* ev )
{
	SysFlag_Set( ev, SYS_FLAG_BTL_SEARCHER_USE );
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * �o�g���T�[�`���[�̃o�b�e���[���g�p���Ă��邩�t���O�̃��Z�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
void SysFlag_BtlSearcherUseReset( EVENTWORK* ev )
{
	SysFlag_Reset( ev, SYS_FLAG_BTL_SEARCHER_USE );
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * �o�g���T�[�`���[�̃o�b�e���[���g�p���Ă��邩�t���O�̃`�F�b�N
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	"1 = �t���OON"
 * @retval	"0 = �t���OOFF"
 */
//--------------------------------------------------------------------------------------------
BOOL SysFlag_BtlSearcherUseCheck( EVENTWORK* ev )
{
	return SysFlag_Check( ev, SYS_FLAG_BTL_SEARCHER_USE );
}



//============================================================================================
//
//	�n���t���O�֘A
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �n���F�����t���O�̃Z�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
void SysFlag_UgArriveSet( EVENTWORK* ev )
{
	SysFlag_Set( ev, SYS_FLAG_UG_ARRIVE );
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * �n���F�����t���O�̃��Z�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
void SysFlag_UgArriveReset( EVENTWORK* ev )
{
	SysFlag_Reset( ev, SYS_FLAG_UG_ARRIVE );
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * �n���F�����t���O�̃`�F�b�N
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	"1 = �t���OON"
 * @retval	"0 = �t���OOFF"
 */
//--------------------------------------------------------------------------------------------
BOOL SysFlag_UgArriveCheck( EVENTWORK* ev )
{
	return SysFlag_Check( ev, SYS_FLAG_UG_ARRIVE );
}

//--------------------------------------------------------------------------------------------
/**
 * �n���F���΃t���O�̃Z�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
void SysFlag_UgDigSet( EVENTWORK* ev )
{
	SysFlag_Set( ev, SYS_FLAG_UG_DIG );
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * �n���F���΃t���O�̃��Z�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
void SysFlag_UgDigReset( EVENTWORK* ev )
{
	SysFlag_Reset( ev, SYS_FLAG_UG_DIG );
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * �n���F���΃t���O�̃`�F�b�N
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	"1 = �t���OON"
 * @retval	"0 = �t���OOFF"
 */
//--------------------------------------------------------------------------------------------
BOOL SysFlag_UgDigCheck( EVENTWORK* ev )
{
	return SysFlag_Check( ev, SYS_FLAG_UG_DIG );
}

//--------------------------------------------------------------------------------------------
/**
 * �n���F�ʃt���O�̃Z�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
void SysFlag_UgTamaSet( EVENTWORK* ev )
{
	SysFlag_Set( ev, SYS_FLAG_UG_TAMA );
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * �n���F�ʃt���O�̃��Z�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
void SysFlag_UgTamaReset( EVENTWORK* ev )
{
	SysFlag_Reset( ev, SYS_FLAG_UG_TAMA );
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * �n���F�ʃt���O�̃`�F�b�N
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	"1 = �t���OON"
 * @retval	"0 = �t���OOFF"
 */
//--------------------------------------------------------------------------------------------
BOOL SysFlag_UgTamaCheck( EVENTWORK* ev )
{
	return SysFlag_Check( ev, SYS_FLAG_UG_TAMA );
}

//--------------------------------------------------------------------------------------------
/**
 * �n���F��n�t���O�̃Z�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
void SysFlag_UgBaseSet( EVENTWORK* ev )
{
	SysFlag_Set( ev, SYS_FLAG_UG_BASE );
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * �n���F��n�t���O�̃��Z�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
void SysFlag_UgBaseReset( EVENTWORK* ev )
{
	SysFlag_Reset( ev, SYS_FLAG_UG_BASE );
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * �n���F��n�t���O�̃`�F�b�N
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	"1 = �t���OON"
 * @retval	"0 = �t���OOFF"
 */
//--------------------------------------------------------------------------------------------
BOOL SysFlag_UgBaseCheck( EVENTWORK* ev )
{
	return SysFlag_Check( ev, SYS_FLAG_UG_BASE );
}

//--------------------------------------------------------------------------------------------
/**
 * �n���F�͗l�ւ��t���O�̃Z�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
void SysFlag_UgGoodsSet( EVENTWORK* ev )
{
	SysFlag_Set( ev, SYS_FLAG_UG_GOODS );
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * �n���F�͗l�ւ��t���O�̃��Z�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
void SysFlag_UgGoodsReset( EVENTWORK* ev )
{
	SysFlag_Reset( ev, SYS_FLAG_UG_GOODS );
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * �n���F�͗l�ւ��t���O�̃`�F�b�N
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	"1 = �t���OON"
 * @retval	"0 = �t���OOFF"
 */
//--------------------------------------------------------------------------------------------
BOOL SysFlag_UgGoodsCheck( EVENTWORK* ev )
{
	return SysFlag_Check( ev, SYS_FLAG_UG_GOODS );
}

//--------------------------------------------------------------------------------------------
/**
 * �n���F���t���O�̃Z�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
void SysFlag_UgHataSet( EVENTWORK* ev )
{
	SysFlag_Set( ev, SYS_FLAG_UG_HATA );
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * �n���F���t���O�̃��Z�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
void SysFlag_UgHataReset( EVENTWORK* ev )
{
	SysFlag_Reset( ev, SYS_FLAG_UG_HATA );
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * �n���F���t���O�̃`�F�b�N
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	"1 = �t���OON"
 * @retval	"0 = �t���OOFF"
 */
//--------------------------------------------------------------------------------------------
BOOL SysFlag_UgHataCheck( EVENTWORK* ev )
{
	return SysFlag_Check( ev, SYS_FLAG_UG_HATA );
}


//============================================================================================
//
//	�R���e�X�g �}�X�^�[�����N�N���A�t���O�֘A
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �R���e�X�g �}�X�^�[�����N�N���A �t���O�̃Z�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 * @param	type	�R���e�X�g�^�C�v
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
void SysFlag_ConMasterSet( EVENTWORK* ev, int type )
{
	switch( type ){

	///�R���e�X�g�^�C�v�F�i�D�悳
	case  CONTYPE_STYLE:
		SysFlag_Set( ev, SYS_FLAG_CON_STYLE_MASTER );
		break;

	///�R���e�X�g�^�C�v�F������
	case CONTYPE_BEAUTIFUL:
		SysFlag_Set( ev, SYS_FLAG_CON_BEAUTIFUL_MASTER );
		break;

	///�R���e�X�g�^�C�v�F����
	case CONTYPE_CUTE:
		SysFlag_Set( ev, SYS_FLAG_CON_CUTE_MASTER );
		break;

	///�R���e�X�g�^�C�v�F����
	case CONTYPE_CLEVER:
		SysFlag_Set( ev, SYS_FLAG_CON_CLEVER_MASTER );
		break;

	///�R���e�X�g�^�C�v�F痂���
	case CONTYPE_STRONG:
		SysFlag_Set( ev, SYS_FLAG_CON_STRONG_MASTER );
		break;
	};

	return;
}

//--------------------------------------------------------------------------------------------
/**
 * �R���e�X�g �}�X�^�[�����N�N���A �t���O�̃��Z�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 * @param	type	�R���e�X�g�^�C�v
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
void SysFlag_ConMasterReset( EVENTWORK* ev, int type )
{
	switch( type ){

	///�R���e�X�g�^�C�v�F�i�D�悳
	case  CONTYPE_STYLE:
		SysFlag_Reset( ev, SYS_FLAG_CON_STYLE_MASTER );
		break;

	///�R���e�X�g�^�C�v�F������
	case CONTYPE_BEAUTIFUL:
		SysFlag_Reset( ev, SYS_FLAG_CON_BEAUTIFUL_MASTER );
		break;

	///�R���e�X�g�^�C�v�F����
	case CONTYPE_CUTE:
		SysFlag_Reset( ev, SYS_FLAG_CON_CUTE_MASTER );
		break;

	///�R���e�X�g�^�C�v�F����
	case CONTYPE_CLEVER:
		SysFlag_Reset( ev, SYS_FLAG_CON_CLEVER_MASTER );
		break;

	///�R���e�X�g�^�C�v�F痂���
	case CONTYPE_STRONG:
		SysFlag_Reset( ev, SYS_FLAG_CON_STRONG_MASTER );
		break;
	};

	return;
}

//--------------------------------------------------------------------------------------------
/**
 * �R���e�X�g �}�X�^�[�����N�N���A �t���O�̃`�F�b�N
 *
 * @param	ev		EVENTWORK�̃|�C���^
 * @param	type	�R���e�X�g�^�C�v
 *
 * @retval	"1 = �t���OON"
 * @retval	"0 = �t���OOFF"
 */
//--------------------------------------------------------------------------------------------
BOOL SysFlag_ConMasterCheck( EVENTWORK* ev, int type )
{
	int ret;

	switch( type ){

	///�R���e�X�g�^�C�v�F�i�D�悳
	case  CONTYPE_STYLE:
		ret = SysFlag_Check( ev, SYS_FLAG_CON_STYLE_MASTER );
		break;

	///�R���e�X�g�^�C�v�F������
	case CONTYPE_BEAUTIFUL:
		ret = SysFlag_Check( ev, SYS_FLAG_CON_BEAUTIFUL_MASTER );
		break;

	///�R���e�X�g�^�C�v�F����
	case CONTYPE_CUTE:
		ret = SysFlag_Check( ev, SYS_FLAG_CON_CUTE_MASTER );
		break;

	///�R���e�X�g�^�C�v�F����
	case CONTYPE_CLEVER:
		ret = SysFlag_Check( ev, SYS_FLAG_CON_CLEVER_MASTER );
		break;

	///�R���e�X�g�^�C�v�F痂���
	case CONTYPE_STRONG:
		ret = SysFlag_Check( ev, SYS_FLAG_CON_STRONG_MASTER );
		break;
	};

	return ret;
}


//============================================================================================
//
//	�o�g���T�[�`���[�F�t���O�֘A
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �o�g���T�[�`���[ �t���O�̃Z�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 * @param	lv		���x��
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
void SysFlag_BsLvSet( EVENTWORK* ev, int lv )
{
	switch( lv ){

	case  1:
		SysFlag_Set( ev, SYS_FLAG_BS_LV1 );
		break;

	case 2:
		SysFlag_Set( ev, SYS_FLAG_BS_LV2 );
		break;

	case 3:
		SysFlag_Set( ev, SYS_FLAG_BS_LV3 );
		break;

	case 4:
		SysFlag_Set( ev, SYS_FLAG_BS_LV4 );
		break;

	case 5:
		SysFlag_Set( ev, SYS_FLAG_BS_LV5 );
		break;
	};

	return;
}

//--------------------------------------------------------------------------------------------
/**
 * �o�g���T�[�`���[ �t���O�̃��Z�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 * @param	lv		���x��
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
void SysFlag_BsLvReset( EVENTWORK* ev, int lv )
{
	switch( lv ){

	case  1:
		SysFlag_Reset( ev, SYS_FLAG_BS_LV1 );
		break;

	case 2:
		SysFlag_Reset( ev, SYS_FLAG_BS_LV2 );
		break;

	case 3:
		SysFlag_Reset( ev, SYS_FLAG_BS_LV3 );
		break;

	case 4:
		SysFlag_Reset( ev, SYS_FLAG_BS_LV4 );
		break;

	case 5:
		SysFlag_Reset( ev, SYS_FLAG_BS_LV5 );
		break;
	};

	return;
}

//--------------------------------------------------------------------------------------------
/**
 * �o�g���T�[�`���[ �t���O�̃`�F�b�N
 *
 * @param	ev		EVENTWORK�̃|�C���^
 * @param	lv		���x��
 *
 * @retval	"1 = �t���OON"
 * @retval	"0 = �t���OOFF"
 */
//--------------------------------------------------------------------------------------------
BOOL SysFlag_BsLvCheck( EVENTWORK* ev, int lv )
{
	int ret = FALSE;

	switch( lv ){

	case  1:
		ret = SysFlag_Check( ev, SYS_FLAG_BS_LV1 );
		break;

	case 2:
		ret = SysFlag_Check( ev, SYS_FLAG_BS_LV2 );
		break;

	case 3:
		ret = SysFlag_Check( ev, SYS_FLAG_BS_LV3 );
		break;

	case 4:
		ret = SysFlag_Check( ev, SYS_FLAG_BS_LV4 );
		break;

	case 5:
		ret = SysFlag_Check( ev, SYS_FLAG_BS_LV5 );
		break;
	};

	return ret;
}


//============================================================================================
//
//	�C�x���gBGM�؂�ւ��F�t���O�֘A
//
//	�t���O����Ƃ͈Ӗ��������Ⴄ�̂ł����̃\�[�X�ɓ����͔̂����B�B�B
//
//	�t���O��`�͂��̃\�[�X�����ŎQ�Ƃ������A
//	case���͂Q�ӏ��ɏ��������Ȃ��A
//	����w�肪����A
//
//	�e�[�u������āA�]�[���A�t���O�ABGM���ABGM�����邢�������B
//	�e�[�u���u���ꏊ�́A�����ɂȂ�H(�t���O�͂��̃\�[�X�����ŎQ�Ƃ������̂�)
//	�B�B�B�Ƃ肠�����ۗ��B
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �C�x���gBGM�؂�ւ� �t���O�̃`�F�b�N�����āA�؂�ւ���BGM�i���o�[���擾
 *
 * @param	ev		EVENTWORK�̃|�C���^
 * @param	zone_id �]�[��ID
 *
 * @retval	"0		= �t���O�I�t�Ȃ̂ŉ����Ȃ�"
 * @retval	"0�ȊO	= �ύX����BGM�i���o�["
 */
//--------------------------------------------------------------------------------------------
u16 SysFlag_EventBgmGet( EVENTWORK* ev, int zone_id )
{
	u16 bgm = 0;

	switch( zone_id ){

	//���b�V��
	case  ZONE_ID_D28R0101:
		if( SysFlag_Check(ev,SYS_FLAG_BGM_D28) == 1 ){
			bgm = SEQ_D_LAKE;
		}
		break;

	case  ZONE_ID_D28R0103:
		if( SysFlag_Check(ev,SYS_FLAG_BGM_D28) == 1 ){
			bgm = SEQ_D_RYAYHY;
		}
		break;

	//d27
	case  ZONE_ID_D27R0102:
		if( SysFlag_Check(ev,SYS_FLAG_BGM_D27) == 1 ){
			bgm = SEQ_D_LAKE;
		}
		break;

	//d29
	case  ZONE_ID_D29R0102:
		if( SysFlag_Check(ev,SYS_FLAG_BGM_D29) == 1 ){
			bgm = SEQ_D_LAKE;
		}
		break;

	//d10r0101
	case  ZONE_ID_D10R0101:
		if( SysFlag_Check(ev,SYS_FLAG_BGM_D10) == 1 ){
			bgm = SEQ_D_SAFARI;
		}
		break;

	//t02
	case  ZONE_ID_T02R0101:
		if( SysFlag_Check(ev,SYS_FLAG_BGM_T02) == 1 ){
			bgm = SEQ_OPENING2;
		}
		break;
#if 0
	//c02
	case  ZONE_ID_C02R0101:
	case  ZONE_ID_C02R0102:
	case  ZONE_ID_C02R0103:
		if( SysFlag_Check(ev,SYS_FLAG_BGM_C02) == 1 ){
			bgm = SEQ_THE_EVENT01;
		}
		break;
#endif

	//�M���K�c�A�W�g
	//�M���K�c����
	case  ZONE_ID_D26R0101:
	case  ZONE_ID_D26R0102:
	case  ZONE_ID_D26R0103:
	case  ZONE_ID_D26R0104:
	case  ZONE_ID_D26R0105:
	case  ZONE_ID_D26R0106:
	case  ZONE_ID_D26R0107:
	case  ZONE_ID_D26R0108:

		//�M���K�c���󂵂Ă�����
		if( SysFlag_Check(ev,SYS_FLAG_BGM_GINGA) == 1 ){

			if( GF_RTC_IsNightTime() == FALSE ){			//FALSE=���ATRUE=��
				bgm = SEQ_CITY07_D;
			}else{
				bgm = SEQ_CITY07_N;
			}
			break;	//�K�v�I
		}

		//�M���K�c�A�W�g�N���}�b�v�̎�
		if( zone_id == ZONE_ID_D26R0101 ){
			if( SysFlag_Check(ev,SYS_FLAG_BGM_D26) == 1 ){
				bgm = SEQ_D_AGITO;
			}
		}
		break;

	//�M���K�c�x��
	case  ZONE_ID_C04R0201:
	case  ZONE_ID_C04R0202:
	case  ZONE_ID_C04R0203:
	case  ZONE_ID_C04R0204:
		if( SysFlag_Check(ev,SYS_FLAG_BGM_C04) == 1 ){
			if( GF_RTC_IsNightTime() == FALSE ){			//FALSE=���ATRUE=��
				bgm = SEQ_CITY04_D;
			}else{
				bgm = SEQ_CITY04_N;
			}
		}
		break;

	//���d��
	case  ZONE_ID_D02R0101:
		if( SysFlag_Check(ev,SYS_FLAG_BGM_D02) == 1 ){
			if( GF_RTC_IsNightTime() == FALSE ){			//FALSE=���ATRUE=��
				bgm = SEQ_ROAD_C_D;
			}else{
				bgm = SEQ_ROAD_C_N;
			}
		}
		break;

	//�\�m�I�̉Ԕ�
	case  ZONE_ID_D13R0101:
		if( SysFlag_Check(ev,SYS_FLAG_BGM_D13) == 1 ){
			if( GF_RTC_IsNightTime() == FALSE ){			//FALSE=���ATRUE=��
				bgm = SEQ_TOWN03_D;
			}else{
				bgm = SEQ_TOWN03_N;
			}
		}
		break;

	//R224�z�z�C�x���g
	case  ZONE_ID_R224:
		if( SysFlag_Check(ev,SYS_FLAG_BGM_R224) == 1 ){
			if( GF_RTC_IsNightTime() == FALSE ){			//FALSE=���ATRUE=��
				bgm = SEQ_TOWN03_D;
			}else{
				bgm = SEQ_TOWN03_N;
			}
		}
		break;

	//�`�����s�I���̕���
	case  ZONE_ID_C10R0111:
		if( SysFlag_Check(ev,SYS_FLAG_BGM_C10) == 1 ){
			bgm = SEQ_SILENCE_FIELD;
		}
		break;

	};


	return bgm;
}


//============================================================================================
//
//	�ʐM�J�E���^�[�ʉ߃t���O�֘A
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �ʐM�J�E���^�[�ʉ߃t���O�̃Z�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
void SysFlag_CommCounterSet( EVENTWORK* ev )
{
	SysFlag_Set( ev, SYS_FLAG_COMM_COUNTER );
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * �ʐM�J�E���^�[�ʉ߃t���O�̃��Z�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
void SysFlag_CommCounterReset( EVENTWORK* ev )
{
	SysFlag_Reset( ev, SYS_FLAG_COMM_COUNTER );
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * �ʐM�J�E���^�[�ʉ߃t���O�̃`�F�b�N
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	"1 = �t���OON"
 * @retval	"0 = �t���OOFF"
 */
//--------------------------------------------------------------------------------------------
BOOL SysFlag_CommCounterCheck( EVENTWORK* ev )
{
	return SysFlag_Check( ev, SYS_FLAG_COMM_COUNTER );
}

//============================================================================================
//
//	�|�P�����X�e�[�^�X�F�R���e�X�g�Z�t���O�֘A
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �|�P�����X�e�[�^�X�F�R���e�X�g�Z�t���O�̃Z�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
void SysFlag_PSTContestSet( EVENTWORK* ev )
{
	SysFlag_Set( ev, SYS_FLAG_PST );
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * �|�P�����X�e�[�^�X�F�R���e�X�g�Z�t���O�̃��Z�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
void SysFlag_PSTContestReset( EVENTWORK* ev )
{
	SysFlag_Reset( ev, SYS_FLAG_PST );
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * �|�P�����X�e�[�^�X�F�R���e�X�g�Z�t���O�̃`�F�b�N
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	"1 = �t���OON"
 * @retval	"0 = �t���OOFF"
 */
//--------------------------------------------------------------------------------------------
BOOL SysFlag_PSTContestCheck( EVENTWORK* ev )
{
	return SysFlag_Check( ev, SYS_FLAG_PST );
}


//============================================================================================
//
//	�n������C�x���g�t���O�֘A
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �n������C�x���g�t���O�̃Z�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
void SysFlag_UgFirstSet( EVENTWORK* ev )
{
	SysFlag_Set( ev, SYS_FLAG_UG_FIRST );
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * �n������C�x���g�t���O�̃��Z�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
void SysFlag_UgFirstReset( EVENTWORK* ev )
{
	SysFlag_Reset( ev, SYS_FLAG_UG_FIRST );
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * �n������C�x���g�t���O�̃`�F�b�N
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	"1 = �t���OON"
 * @retval	"0 = �t���OOFF"
 */
//--------------------------------------------------------------------------------------------
BOOL SysFlag_UgFirstCheck( EVENTWORK* ev )
{
	return SysFlag_Check( ev, SYS_FLAG_UG_FIRST );
}


//============================================================================================
//
//	GTC�I�[�v���t���O�֘A
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * GTC�I�[�v���t���O�̃Z�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
void SysFlag_GTCOpenSet( EVENTWORK* ev )
{
	SysFlag_Set( ev, SYS_FLAG_GTC_OPEN );
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * GTC�I�[�v���t���O�̃��Z�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
void SysFlag_GTCOpenReset( EVENTWORK* ev )
{
	SysFlag_Reset( ev, SYS_FLAG_GTC_OPEN );
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * GTC�I�[�v���t���O�̃`�F�b�N
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	"1 = �t���OON"
 * @retval	"0 = �t���OOFF"
 */
//--------------------------------------------------------------------------------------------
BOOL SysFlag_GTCOpenCheck( EVENTWORK* ev )
{
	return SysFlag_Check( ev, SYS_FLAG_GTC_OPEN );
}


//============================================================================================
//
//	�o�g���^���[�I�[�v���t���O�֘A
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �o�g���^���[�I�[�v���t���O�̃Z�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
void SysFlag_BTowerOpenSet( EVENTWORK* ev )
{
	SysFlag_Set( ev, SYS_FLAG_BTOWER_OPEN );
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * �o�g���^���[�I�[�v���t���O�̃��Z�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
void SysFlag_BTowerOpenReset( EVENTWORK* ev )
{
	SysFlag_Reset( ev, SYS_FLAG_BTOWER_OPEN );
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * �o�g���^���[�I�[�v���t���O�̃`�F�b�N
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	"1 = �t���OON"
 * @retval	"0 = �t���OOFF"
 */
//--------------------------------------------------------------------------------------------
BOOL SysFlag_BTowerOpenCheck( EVENTWORK* ev )
{
	return SysFlag_Check( ev, SYS_FLAG_BTOWER_OPEN );
}


//============================================================================================
//
//	�D���g����t���O�֘A
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �D���g����t���O�̃Z�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
void SysFlag_ShipSet( EVENTWORK* ev )
{
	SysFlag_Set( ev, SYS_FLAG_SHIP );
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * �D���g����t���O�̃��Z�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
void SysFlag_ShipReset( EVENTWORK* ev )
{
	SysFlag_Reset( ev, SYS_FLAG_SHIP );
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * �D���g����t���O�̃`�F�b�N
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	"1 = �t���OON"
 * @retval	"0 = �t���OOFF"
 */
//--------------------------------------------------------------------------------------------
BOOL SysFlag_ShipCheck( EVENTWORK* ev )
{
	return SysFlag_Check( ev, SYS_FLAG_SHIP );
}


//============================================================================================
//
//	���C�A�C�n�C�~�o�t���O�֘A
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * ���C�A�C�n�C�~�o�t���O�̃Z�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
void SysFlag_ReiAiHaiSet( EVENTWORK* ev )
{
	SysFlag_Set( ev, SYS_FLAG_REIAIHAI );
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * ���C�A�C�n�C�~�o�t���O�̃��Z�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
void SysFlag_ReiAiHaiReset( EVENTWORK* ev )
{
	SysFlag_Reset( ev, SYS_FLAG_REIAIHAI );
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * ���C�A�C�n�C�~�o�t���O�̃`�F�b�N
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	"1 = �t���OON"
 * @retval	"0 = �t���OOFF"
 */
//--------------------------------------------------------------------------------------------
BOOL SysFlag_ReiAiHaiCheck( EVENTWORK* ev )
{
	return SysFlag_Check( ev, SYS_FLAG_REIAIHAI );
}


//============================================================================================
//
//	�~�Y�L�t���O�֘A
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �~�Y�L�t���O�̃Z�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
void SysFlag_MizukiSet( EVENTWORK* ev )
{
	SysFlag_Set( ev, SYS_FLAG_MIZUKI );
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * �~�Y�L�t���O�̃��Z�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
void SysFlag_MizukiReset( EVENTWORK* ev )
{
	SysFlag_Reset( ev, SYS_FLAG_MIZUKI );
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * �~�Y�L�t���O�̃`�F�b�N
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	"1 = �t���OON"
 * @retval	"0 = �t���OOFF"
 */
//--------------------------------------------------------------------------------------------
BOOL SysFlag_MizukiCheck( EVENTWORK* ev )
{
	return SysFlag_Check( ev, SYS_FLAG_MIZUKI );
}


//============================================================================================
//
//	�|�P�b�`�}�~�֘A
//
//============================================================================================
//--------------------------------------------------------------------------------------------
///	�V�X�e���t���O�Z�b�g�F�|�P�b�`�}�~
//--------------------------------------------------------------------------------------------
void SysFlag_PoketchHookSet(EVENTWORK * ev)
{
	SysFlag_Set(ev, SYS_FLAG_POKETCH_HOOK);
}
//--------------------------------------------------------------------------------------------
///	�V�X�e���t���O���Z�b�g�F�|�P�b�`�}�~
//--------------------------------------------------------------------------------------------
void SysFlag_PoketchHookReset(EVENTWORK * ev)
{
	SysFlag_Reset(ev, SYS_FLAG_POKETCH_HOOK);
}
//--------------------------------------------------------------------------------------------
///	�V�X�e���t���O�擾�F�|�P�b�`�}�~
//--------------------------------------------------------------------------------------------
BOOL SysFlag_PoketchHookCheck(EVENTWORK * ev)
{
	return SysFlag_Check(ev, SYS_FLAG_POKETCH_HOOK);
}

//============================================================================================
//		�T�t�@�����[�h�֘A
//============================================================================================
//--------------------------------------------------------------------------------------------
/**
 * @brief	�T�t�@�����[�h�t���O�̃Z�b�g
 * @param	ev		EVENTWORK�̃|�C���^
 */
//--------------------------------------------------------------------------------------------
void SysFlag_SafariSet(EVENTWORK * ev)
{
	SysFlag_Set(ev, SYS_FLAG_SAFARI_MODE);
}
//--------------------------------------------------------------------------------------------
/**
 * @brief	�T�t�@�����[�h�t���O�̃��Z�b�g
 * @param	ev		EVENTWORK�̃|�C���^
 */
//--------------------------------------------------------------------------------------------
void SysFlag_SafariReset(EVENTWORK * ev)
{
	SysFlag_Reset(ev, SYS_FLAG_SAFARI_MODE);
}
//--------------------------------------------------------------------------------------------
/**
 * @brief	�T�t�@�����[�h�t���O�̃Z�b�g
 * @param	ev		EVENTWORK�̃|�C���^
 * @return	BOOL	�t���O�̒l
 */
//--------------------------------------------------------------------------------------------
BOOL SysFlag_SafariCheck(EVENTWORK * ev)
{
	return SysFlag_Check(ev, SYS_FLAG_SAFARI_MODE);
}

//============================================================================================
//		�|�P�p�[�N���[�h�֘A
//============================================================================================
//--------------------------------------------------------------------------------------------
/**
 * @brief	�|�P�p�[�N���[�h�t���O�̃Z�b�g
 * @param	ev		EVENTWORK�̃|�C���^
 */
//--------------------------------------------------------------------------------------------
void SysFlag_PokeParkSet(EVENTWORK * ev)
{
	SysFlag_Set(ev, SYS_FLAG_POKEPARK_MODE);
}
//--------------------------------------------------------------------------------------------
/**
 * @brief	�|�P�p�[�N���[�h�t���O�̃��Z�b�g
 * @param	ev		EVENTWORK�̃|�C���^
 */
//--------------------------------------------------------------------------------------------
void SysFlag_PokeParkReset(EVENTWORK * ev)
{
	SysFlag_Reset(ev, SYS_FLAG_POKEPARK_MODE);
}
//--------------------------------------------------------------------------------------------
/**
 * @brief	�|�P�p�[�N���[�h�t���O�̃Z�b�g
 * @param	ev		EVENTWORK�̃|�C���^
 * @return	BOOL	�t���O�̒l
 */
//--------------------------------------------------------------------------------------------
BOOL SysFlag_PokeParkCheck(EVENTWORK * ev)
{
	return SysFlag_Check(ev, SYS_FLAG_POKEPARK_MODE);
}

//============================================================================================
//
//		�T�C�N�����O���[�h�֘A
//
//============================================================================================
//--------------------------------------------------------------------------------------------
/**
 * @brief	�T�C�N�����O���[�h���[�h�t���O�̃Z�b�g
 * @param	ev		EVENTWORK�̃|�C���^
 * @return	BOOL	�t���O�̒l
 */
//--------------------------------------------------------------------------------------------
void SysFlag_CyclingRoadSet(EVENTWORK * ev)
{
	SysFlag_Set(ev, SYS_FLAG_CYCLINGROAD);
}
//--------------------------------------------------------------------------------------------
/**
 * @brief	�T�C�N�����O���[�h���[�h�t���O�̃��Z�b�g
 * @param	ev		EVENTWORK�̃|�C���^
 * @return	BOOL	�t���O�̒l
 */
//--------------------------------------------------------------------------------------------
void SysFlag_CyclingRoadReset(EVENTWORK * ev)
{
	SysFlag_Reset(ev, SYS_FLAG_CYCLINGROAD);
}
//--------------------------------------------------------------------------------------------
/**
 * @brief	�T�C�N�����O���[�h���[�h�t���O�̃`�F�b�N
 * @param	ev		EVENTWORK�̃|�C���^
 * @return	BOOL	�t���O�̒l
 */
//--------------------------------------------------------------------------------------------
BOOL SysFlag_CyclingRoadCheck(EVENTWORK * ev)
{
	return SysFlag_Check(ev, SYS_FLAG_CYCLINGROAD);
}

//============================================================================================
//
//	�Ђł�킴�֘A
//
//============================================================================================
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
BOOL SysFlag_Kairiki( EVENTWORK* ev, SYSFLAG_MODE mode)
{
	return SysFlag_Common( ev, mode, SYS_FLAG_KAIRIKI );
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
void SysFlag_FlashSet(EVENTWORK* ev)
{
	SysFlag_Set(ev, SYS_FLAG_FLASH);
}
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
void SysFlag_FlashReset(EVENTWORK* ev)
{
	SysFlag_Reset(ev, SYS_FLAG_FLASH);
}
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
BOOL SysFlag_FlashCheck(EVENTWORK* ev)
{
	return SysFlag_Check(ev, SYS_FLAG_FLASH);
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
void SysFlag_KiribaraiSet(EVENTWORK* ev)
{
	SysFlag_Set(ev, SYS_FLAG_KIRIBARAI);
}
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
void SysFlag_KiribaraiReset(EVENTWORK* ev)
{
	SysFlag_Reset(ev, SYS_FLAG_KIRIBARAI);
}
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
BOOL SysFlag_KiribaraiCheck(EVENTWORK* ev)
{
	return SysFlag_Check(ev, SYS_FLAG_KIRIBARAI);
}

//============================================================================================
//		�`���m�[�g�֘A
//============================================================================================
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
BOOL SysFlag_FNote( EVENTWORK* ev, SYSFLAG_MODE mode )
{
	return SysFlag_Common( ev, mode, SYS_FLAG_FNOTE_GET );
}

//============================================================================================
//
//		�����t���O�֘A
//
//============================================================================================
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
BOOL SysFlag_Arrive( EVENTWORK* ev, SYSFLAG_MODE mode, u32 arrive_id )
{
	GF_ASSERT( arrive_id < FLAG_ARRIVE_MAX );
	return SysFlag_Common( ev, mode, SYS_FLAG_ARRIVE_START + arrive_id );
}

//============================================================================================
//
//		�C�x���g�֘A
//
//============================================================================================
//--------------------------------------------------------------------------------------------
/**
 * WiFi�Ɍq����
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------------------------------------
void SysFlag_WifiUseSet( EVENTWORK* ev )
{
	SysFlag_Set(ev, SYS_FLAG_WIFI_USE);
}

//============================================================================================
//
//		�f�o�b�O�@�\�֘A
//
//============================================================================================
#ifdef PM_DEBUG

//�V�X�e���t���O�n���Q�b�g����
u32 DNumInput_SysFlagGet(SAVEDATA* sv,u32 param)
{
	EVENTWORK* ev = SaveData_GetEventWork(sv);
	return SysFlag_Check( ev,param);
}
//�V�X�e���t���O�n���Z�b�g����
void DNumInput_SysFlagSet(SAVEDATA* sv,u32 param,u32 value)
{
	EVENTWORK* ev = SaveData_GetEventWork(sv);
	if(value){
		SysFlag_Set(ev,param);
	}else{
		SysFlag_Reset(ev,param);
	}
}

#endif	//PM_DEBUG

