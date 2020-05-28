//============================================================================================
/**
 * @file	fnote_mem.c
 * @brief	�`���m�[�g�@�f�[�^�Ǘ�����
 * @author	Hiroyuki Nakamura
 * @date	2006.03.06
 */
//============================================================================================
#include "common.h"
#include "system/savedata.h"
#include "system/buflen.h"
#include "system/pm_rtc.h"
#include "savedata/mystatus.h"
#include "msgdata/msg_place_name.h"
#include "battle/trno_def.h"
#include "field/field_place_name.h"
#include "../field/mapdefine.h"
#include "../field/zonedata.h"
#include "../field/sysflag.h"

#define	FNOTE_MEM_H_GLOBAL
#include "savedata/fnote_mem.h"


//============================================================================================
//	�萔��`
//============================================================================================

// �Z�[�u�f�[�^�{��
struct _FNOTE_DATA {
	FNOTE_WK_START	hed;			// �J�n�f�[�^
// 4
	u32	action[FNOTE_ACTION_MAX];	// �s��
// 4+16
	FNOTE_WK_POKE	pokemon;		// �|�P����
// 4+16+4
	FNOTE_WK_TRAINER trainer;		// �g���[�i�[
// 4+16+4+4
	u8	sio[FNOTE_SIO_MAX][42];		// �ʐM
// 4+16+4+4+84 = 112
};

// ����Ȍ����f�[�^
typedef struct {
	u32	name;		// ���OID
	u32	type;		// �\���^�C�v
}EX_BUILD_DATA;

// �W���e�[�u��
typedef struct {
	u32	tr;			// �g���[�i�[ID
	u16	zone;		// �]�[��ID
	u16	badge;		// �o�b�W�t���O
}GYM_TBL;


//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================
static void FNOTE_StartDataSave( FNOTE_DATA * dat, FNOTE_WK_START * wk );
static void FNOTE_ActionDataSave( FNOTE_DATA * dat, FNOTE_WK_ACTION * wk );
static void FNOTE_PokemonDataSave( FNOTE_DATA * dat, FNOTE_WK_POKE * wk );
static void FNOTE_TrainerDataSave( FNOTE_DATA * dat, FNOTE_WK_TRAINER * wk );
static void FNOTE_SioDataSave( FNOTE_DATA * dat, FNOTE_WK_SIO * wk );

static u32 * FNOTE_ActionSavePosGet( u32 * action );
static u8 * FNOTE_SioSavePosGet( FNOTE_DATA * dat );
static void FNOTE_ActionIDDataSave( u32 * dat, FNOTE_WK_ACTION * wk );
static void FNOTE_ActionTrainerDataSave( u32 * dat, FNOTE_WK_ACTION * wk );
static void FNOTE_ActionSitennouDataSave( u32 * dat, FNOTE_WK_ACTION * wk );
static void FNOTE_ActionGymLeaderDataSave( u32 * dat, FNOTE_WK_ACTION * wk );
static void FNOTE_ActionMapDataSave( u32 * dat, FNOTE_WK_ACTION * wk );
static void FNOTE_ActionItemDataSave( u32 * dat, FNOTE_WK_ACTION * wk );
static void FNOTE_ActionSkillDataSave( u32 * dat, FNOTE_WK_ACTION * wk );
static void FNOTE_SioBattleDataSave( u8 * dat, FNOTE_WK_SIO * wk );
static void FNOTE_SioUnionGreetDataSave( u8 * dat, FNOTE_WK_SIO * wk );
static void FNOTE_SioPokeChgDataSave( u8 * dat, FNOTE_WK_SIO * wk );
static void FNOTE_SioIDDataSave( FNOTE_DATA * dat, FNOTE_WK_SIO * wk );
static void FNOTE_SioContestDataSave( u8 * dat, FNOTE_WK_SIO * wk );

static void FNOTE_StrCopy( const STRCODE * str, STRCODE * buf, u32 siz );

static void FNOTE_StartDataGet( FNOTE_DATA * dat, FNOTE_WK_START * wk );
static void FNOTE_ActionDataGet( FNOTE_DATA * dat, FNOTE_WK_ACTION * wk );
static void FNOTE_PokemonDataGet( FNOTE_DATA * dat, FNOTE_WK_POKE * wk );
static void FNOTE_TrainerDataGet( FNOTE_DATA * dat, FNOTE_WK_TRAINER * wk );
static void FNOTE_SioDataGet( FNOTE_DATA * dat, FNOTE_WK_SIO * wk );

static void FNOTE_ActionIDDataGet( u32 dat, FNOTE_WK_ACTION * wk );
static void FNOTE_ActionTrainerDataGet( u32 dat, FNOTE_WK_ACTION * wk );
static void FNOTE_ActionMapDataGet( u32 dat, FNOTE_WK_ACTION * wk );
static void FNOTE_ActionItemDataGet( u32 dat, FNOTE_WK_ACTION * wk );
static void FNOTE_ActionSkillDataGet( u32 dat, FNOTE_WK_ACTION * wk );
static void FNOTE_SioBattleDataGet( u8 * dat, FNOTE_WK_SIO * wk );
static void FNOTE_SioUnionGreetDataGet( u8 * dat, FNOTE_WK_SIO * wk );
static void FNOTE_SioPokeChgDataGet( u8 * dat, FNOTE_WK_SIO * wk );
static void FNOTE_SioIDDataGet( u8 * dat, FNOTE_WK_SIO * wk );
static void FNOTE_SioContestDataGet( u8 * dat, FNOTE_WK_SIO * wk );

static u8 GymCheck( MYSTATUS * my, u32 zone_id );
static u8 TrainerCheck( u32 tr );


//============================================================================================
//	�O���[�o���ϐ�
//============================================================================================
// ����Ȍ����e�[�u��
static const EX_BUILD_DATA BuildNameTable[] =
{
	{ MAPNAME_C1TV,				1 },	// �e���r�@�R�g�u�L
	{ MAPNAME_C1POKETCH,		0 },	// �|�P�b�`�J���p�j�[
	{ MAPNAME_C1GTC,			1 },	// �f�s�b
	{ MAPNAME_C1SCHOOL,			1 },	// �g���[�i�[�Y�X�N�[��
	{ MAPNAME_C3HAKUBUTUKAN,	0 },	// ���񂱂��͂��Ԃ���
	{ MAPNAME_T3FLOWER,			1 },	// �t�����[�@�V���v
	{ MAPNAME_C4BICYCLE,		1 },	// �T�C�N���@�V���b�v
	{ MAPNAME_C5CONTEST,		1 },	// �R���e�X�g�������傤
	{ MAPNAME_C5POFFINN,		1 },	// �|�t�B���n�E�X
//	{ MAPNAME_D11HIROBA,		0 },	// �ӂꂠ���Ђ��
	{ MAPNAME_C5BUILDING,		0 },	// ���Ԃ񂩂̂��Ă���
	{ MAPNAME_T4SODATEYA,		1 },	// �|�P���������Ă�
	{ MAPNAME_C7DEPARTMENT,		0 },	// �g�o���f�p�[�g
	{ MAPNAME_C7GAME,			1 },	// �Q�[���R�[�i�[
	{ MAPNAME_D26AZITO,			0 },	// �M���K����A�W�g
	{ MAPNAME_C7TOSYOKAN,		0 },	// �~�I�@�Ƃ��傩��
	{ MAPNAME_D20KISSAKI,		0 },	// �L�b�T�L����ł�
	{ MAPNAME_C8TODAI,			0 },	// �V���x�́@�Ƃ�����
	{ MAPNAME_C8ITIBA,			1 },	// �i�M�T�@������
	{ MAPNAME_D31TOWER,			1 },	// �o�g���^���[
	{ MAPNAME_R212YASIKI,		0 },	// �|�P�����₵��
	{ MAPNAME_R213ASIATO,		1 },	// �������Ƃ͂����̂���
//	{ MAPNAME_D10POKEPARK,		1 },	// �|�P�p�[�N
	{ MAPNAME_R210KISSATEN,		0 },	// �������Ă�
	{ MAPNAME_L02HOTEL,			0 },	// �O�����h���C�N
	{ MAPNAME_L02RESTAURANT,	0 },	// ���X�g����
	{ MAPNAME_D2HATUDEN,		0 },	// ���ɂ܂̂͂ł񂵂�
	{ MAPNAME_D4TATARA,			0 },	// �^�^�������Ă���
	{ MAPNAME_D25YOUKAN,		0 }		// ����̂悤����
};

// �W���e�[�u��
static const GYM_TBL GymTbl[] =
{
	{ LEADER1_01, ZONE_ID_C03GYM0101, BADGE_ID_C03 },	// �N���K�l�A���킭����
	{ LEADER2_01, ZONE_ID_C04GYM0101, BADGE_ID_C04 },	// �n�N�^�C�A����������
	{ LEADER3_01, ZONE_ID_C06GYM0101, BADGE_ID_C06 },	// �m���Z�A����΂炢
	{ LEADER4_01, ZONE_ID_C07GYM0101, BADGE_ID_C07 },	// �g�o���A������Ƃ�
	{ LEADER5_01, ZONE_ID_C05GYM0101, BADGE_ID_C05 },	// ���X�K�A�Ȃ݂̂�
	{ LEADER6_01, ZONE_ID_C09GYM0101, BADGE_ID_C09 },	// �L�b�T�L�A���b�N�N���C��
	{ LEADER7_01, ZONE_ID_C02GYM0101, BADGE_ID_C02 },	// �~�I�A�����肫
	{ LEADER8_01, ZONE_ID_C08GYM0101, BADGE_ID_C08 }	// �i�M�T�A�����̂ڂ�
};


//--------------------------------------------------------------------------------------------
/**
 * �`���m�[�g�p���[�N�̃T�C�Y�擾
 *
 * @param	none
 *
 * @return	���[�N�T�C�Y
 */
//--------------------------------------------------------------------------------------------
int FNOTE_GetWorkSize(void)
{
	return ( sizeof(FNOTE_DATA) * FNOTE_PAGE_MAX );
}

//--------------------------------------------------------------------------------------------
/**
 * �`���m�[�g�p���[�N������
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_Init( FNOTE_DATA * dat )
{
	memset( dat, 0, sizeof(FNOTE_DATA) );
}

//--------------------------------------------------------------------------------------------
/**
 * �`���m�[�g�p���[�N�������i�S�́j
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FNOTE_InitAll( FNOTE_DATA * dat )
{
	memset( dat, 0, sizeof(FNOTE_DATA)*FNOTE_PAGE_MAX );
}

//--------------------------------------------------------------------------------------------
/**
 * �Z�[�u�f�[�^����`���m�[�g�̃|�C���^���擾
 *
 * @param	sv		�Z�[�u�f�[�^
 *
 * @return	�`���m�[�g�f�[�^
 */
//--------------------------------------------------------------------------------------------
FNOTE_DATA * SaveData_GetFNote( SAVEDATA * sv )
{
	return SaveData_Get( sv, GMDATA_ID_FNOTE );
}

//--------------------------------------------------------------------------------------------
/**
 * �Z�[�u�y�[�W�擾
 *
 * @param	dat		�Z�[�u�f�[�^
 * @param	flg		�Z�[�u���t���O ( TRUE = ���� )
 *
 * @retval	"flg = TRUE : �Z�[�u�y�[�W"
 * @retval	"flg = FALSE : NULL"
 */
//--------------------------------------------------------------------------------------------
FNOTE_DATA * FNOTE_SavePageGet( FNOTE_DATA * dat, BOOL flg )
{
	RTCDate	rtc;
	s32	i;

	// �Z�[�u���`�F�b�N
	if( flg != TRUE ){ return NULL; }

	GF_RTC_GetDate( &rtc );

	if( dat[0].hed.month != 0 &&
		( dat[0].hed.year != rtc.year || dat[0].hed.month != rtc.month ||
		  dat[0].hed.day != rtc.day || dat[0].hed.week != rtc.week ) ){

		// �f�[�^�V�t�g
		for( i=FNOTE_PAGE_MAX-1; i>=1; i-- ){
			dat[i] = dat[i-1];
		}
		FNOTE_Init( &dat[0] );
	}
	return &dat[0];


/*
	// ���t����v����f�[�^���擾
	GF_RTC_GetDate( &rtc );
	for( i=0; i<FNOTE_PAGE_MAX; i++ ){
		if( dat[i].hed.year == rtc.year && dat[i].hed.month == rtc.month &&
			dat[i].hed.day == rtc.day && dat[i].hed.week == rtc.week ){

			return &dat[i];
		}
	}

	// �f�[�^�������ꏊ���擾
	for( i=0; i<FNOTE_PAGE_MAX; i++ ){
		if( dat[i].hed.month == 0 ){
			return &dat[i];
		}
	}

	// �󂫂������ꍇ�́A�V�t�g���Č��̃f�[�^���擾
	for( i=0; i<FNOTE_PAGE_MAX-1; i++ ){
		dat[i] = dat[i+1];
	}
	FNOTE_Init( &dat[i] );
	return &dat[i];
*/
}

//--------------------------------------------------------------------------------------------
/**
 * �Q�[���J�n���̖`���m�[�g�\���`�F�b�N
 *
 * @param	dat		�Z�[�u�f�[�^
 * @param	flg		�Z�[�u���t���O ( TRUE = ���� )
 *
 * @retval	"TRUE = �\��"
 * @retval	"FALSE = �\�����Ȃ�"
 */
//--------------------------------------------------------------------------------------------
BOOL FNOTE_GameStartOpenCheck( FNOTE_DATA * dat, BOOL flg )
{
	RTCDate	note;
	RTCDate	now;
	int	ofs;

	// �Z�[�u���`�F�b�N
	if( flg != TRUE ){ return FALSE; }

	// ���݂̎���
	GF_RTC_GetDate( &now );
	// �`���m�[�g�̍ŐV�̎���
	note.year  = dat[0].hed.year;
	note.month = dat[0].hed.month;
	note.day   = dat[0].hed.day;
	note.week  = dat[0].hed.week;

	ofs = GF_RTC_GetDaysOffset(&now) - GF_RTC_GetDaysOffset(&note);
	if( ofs == 0 ){
		if( now.year != note.year ){
			return TRUE;
		}
	}else if( ofs <= -2 ){
		return TRUE;
	}else if( ofs >= 2 ){
		return TRUE;
	}
	return FALSE;
}


//============================================================================================
//	�f�[�^�Z�[�u
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * ��z�Z�[�u
 *
 * @param	dat		�Z�[�u�f�[�^
 * @param	wk		�Z�[�u����f�[�^
 * @param	type	�L�^�^�C�v
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FNOTE_DataSave( FNOTE_DATA * dat, void * wk, u8 type )
{
	if( dat != NULL ){
		switch( type ){
		case FNOTE_TYPE_START:		// �J�n
			FNOTE_StartDataSave( dat, wk );
			break;

		case FNOTE_TYPE_ACTION:		// �s��
			FNOTE_ActionDataSave( dat, wk );
			break;

		case FNOTE_TYPE_POKEMON:	// �|�P����
			FNOTE_PokemonDataSave( dat, wk );
			break;

		case FNOTE_TYPE_TRAINER:	// �g���[�i�[
			FNOTE_TrainerDataSave( dat, wk );
			break;

		case FNOTE_TYPE_SIO:		// �ʐM
			FNOTE_SioDataSave( dat, wk );
			break;
		}
	}
	sys_FreeMemoryEz( wk );
}

//--------------------------------------------------------------------------------------------
/**
 * �J�n�f�[�^�Z�[�u
 *
 * @param	dat		�Z�[�u�f�[�^
 * @param	wk		�Z�[�u����f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_StartDataSave( FNOTE_DATA * dat, FNOTE_WK_START * wk )
{
	if( dat->hed.year == wk->year && dat->hed.month == wk->month &&
		dat->hed.day == wk->day && dat->hed.week == wk->week ){
		return;
	}
	dat->hed = *wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �s���f�[�^�Z�[�u
 *
 * @param	dat		�Z�[�u�f�[�^
 * @param	wk		�Z�[�u����f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_ActionDataSave( FNOTE_DATA * dat, FNOTE_WK_ACTION * wk )
{
	switch( wk->id ){
	case FNOTE_ID_MYHOUSE:			// �s���F����
	case FNOTE_ID_LABO:				// �s���F������
	case FNOTE_ID_POKECENTER:		// �s���F�|�P�����Z���^�[
	case FNOTE_ID_FDSHOP_BUY:		// �s���F�V���b�v�E����
	case FNOTE_ID_FDSHOP_BUY2:		// �s���F�V���b�v�E�����i�����j
	case FNOTE_ID_FDSHOP_SALE:		// �s���F�V���b�v�E����
	case FNOTE_ID_FDSHOP_SALE2:		// �s���F�V���b�v�E����i�����j
	case FNOTE_ID_FDSHOP_TRADE:		// �s���F�V���b�v�E����
	case FNOTE_ID_GAMECORNER:		// �s���F�Q�[���R�[�i�[
	case FNOTE_ID_SAFARIZONE:		// �s���F�T�t�@���]�[��
	case FNOTE_ID_UG_FOSSIL:		// �s���F�n���E���Ό@��
	case FNOTE_ID_UG_BASE:			// �s���F�n���E�閧��n
		FNOTE_ActionIDDataSave( dat->action, wk );
		break;

	case FNOTE_ID_GYMBEFORE:		// �s���F�W���i���[�_�[��|���O�j
	case FNOTE_ID_GYMAFTER:			// �s���F�W���i���[�_�[��|������j
		FNOTE_ActionGymLeaderDataSave( dat->action, wk );
		break;

	case FNOTE_ID_SITENNOU:			// �s���F�l�V��
		FNOTE_ActionSitennouDataSave( dat->action, wk );
		break;

	case FNOTE_ID_CHAMPION:			// �s���F�`�����s�I��
		FNOTE_ActionTrainerDataSave( dat->action, wk );
		break;

	case FNOTE_ID_CITY:				// �s���F�X
	case FNOTE_ID_DUNGEON:			// �s���F�_���W����
	case FNOTE_ID_BUILD:			// �s���F����
		FNOTE_ActionMapDataSave( dat->action, wk );
		break;

	case FNOTE_ID_ITEMGET:			// �s���F�A�C�e���擾
		FNOTE_ActionItemDataSave( dat->action, wk );
		break;

	case FNOTE_ID_IAIGIRI:			// �s���F�Z�E����������
	case FNOTE_ID_SORAWOTOBU:		// �s���F�Z�E������Ƃ�
	case FNOTE_ID_NAMINORI:			// �s���F�Z�E�Ȃ݂̂�
	case FNOTE_ID_KAIRIKI:			// �s���F�Z�E�����肫
	case FNOTE_ID_FLASH:			// �s���F�Z�E�t���b�V��
	case FNOTE_ID_KIRIBARAI:		// �s���F�Z�E����΂炢
	case FNOTE_ID_IWAKUDAKI:		// �s���F�Z�E���킭����
	case FNOTE_ID_TAKINOBORI:		// �s���F�Z�E�����̂ڂ�
	case FNOTE_ID_ROCKCLIMB:		// �s���F�Z�E���b�N�N���C��
	case FNOTE_ID_ANAWOHORU:		// �s���F�Z�E���Ȃ��ق�
	case FNOTE_ID_AMAIKAORI:		// �s���F�Z�E���܂�������
	case FNOTE_ID_TELEPORT:			// �s���F�Z�E�e���|�[�g
	case FNOTE_ID_TAMAGOUMI:		// �s���F�Z�E�^�}�S����
	case FNOTE_ID_MIRUKUNOMI:		// �s���F�Z�E�~���N�̂�
		FNOTE_ActionSkillDataSave( dat->action, wk );
		break;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �|�P�����f�[�^�Z�[�u
 *
 * @param	dat		�Z�[�u�f�[�^
 * @param	wk		�Z�[�u����f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_PokemonDataSave( FNOTE_DATA * dat, FNOTE_WK_POKE * wk )
{
	dat->pokemon = *wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �g���[�i�[�f�[�^�Z�[�u
 *
 * @param	dat		�Z�[�u�f�[�^
 * @param	wk		�Z�[�u����f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_TrainerDataSave( FNOTE_DATA * dat, FNOTE_WK_TRAINER * wk )
{
	dat->trainer = *wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �ʐM�f�[�^�Z�[�u
 *
 * @param	dat		�Z�[�u�f�[�^
 * @param	wk		�Z�[�u����f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_SioDataSave( FNOTE_DATA * dat, FNOTE_WK_SIO * wk )
{
	u8 * sio = FNOTE_SioSavePosGet( dat );

	switch( wk->id ){
	case FNOTE_ID_SB_SINGLE:		// �ʐM�F�ʐM�ΐ�E�V���O��
	case FNOTE_ID_SB_DOUBLE:		// �ʐM�F�ʐM�ΐ�E�_�u��
	case FNOTE_ID_SB_MULTI:			// �ʐM�F�ʐM�ΐ�E�}���`
	case FNOTE_ID_SB_MIX1:			// �ʐM�F�ʐM�ΐ�E�~�b�N�X1vs1
	case FNOTE_ID_SB_MIX2:			// �ʐM�F�ʐM�ΐ�E�~�b�N�X2vs2
	case FNOTE_ID_U_BATTLE:			// �ʐM�F���j�I�����[���E�ΐ�
		FNOTE_SioBattleDataSave( sio, wk );
		break;

	case FNOTE_ID_U_GREETING:		// �ʐM�F���j�I�����[���E���A
		FNOTE_SioUnionGreetDataSave( sio, wk );
		break;

	case FNOTE_ID_U_POKECHG:		// �ʐM�F���j�I�����[���E����
	case FNOTE_ID_U_MLTCHG:			// �ʐM�F���j�I�����[���E�����l����
	case FNOTE_ID_GTC:				// �ʐM�FGTC
		FNOTE_SioPokeChgDataSave( sio, wk );
		break;

	case FNOTE_ID_U_PICTURE:		// �ʐM�F���j�I�����[���E���G����
	case FNOTE_ID_U_TRANSCEIVER:	// �ʐM�F���j�I�����[���E�g�����V�[�o�[
	case FNOTE_ID_RECORD:			// �ʐM�F���R�[�h�R�[�i�[
	case FNOTE_ID_PORUTO:			// �ʐM�F�|���g�쐬
	case FNOTE_ID_BTLTOWER:			// �ʐM�F�o�g���^���[
		FNOTE_SioIDDataSave( dat, wk );
		break;

	case FNOTE_ID_CONTEST:			// �ʐM�F�R���e�X�g
		FNOTE_SioContestDataSave( sio, wk );
		break;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �s���f�[�^�̃Z�[�u�ʒu�擾
 *
 * @param	action	�Z�[�u�f�[�^
 *
 * @return	�Z�[�u�ʒu
 */
//--------------------------------------------------------------------------------------------
static u32 * FNOTE_ActionSavePosGet( u32 * action )
{
	u32	i;

	for( i=0; i<FNOTE_ACTION_MAX; i++ ){
		if( ( action[i] & 0x3f ) == 0 ){
			return &action[i];
		}
	}

	for( i=0; i<FNOTE_ACTION_MAX-1; i++ ){
		action[i]  = action[i+1];
	}
	action[i] = 0;
	return &action[i];
}

//--------------------------------------------------------------------------------------------
/**
 * �ʐM�f�[�^�̃Z�[�u�ʒu�擾
 *
 * @param	dat		�Z�[�u�f�[�^
 *
 * @return	�Z�[�u�ʒu
 */
//--------------------------------------------------------------------------------------------
static u8 * FNOTE_SioSavePosGet( FNOTE_DATA * dat )
{
	u32	i;

	for( i=0; i<FNOTE_SIO_MAX; i++ ){
		if( dat->sio[i][0] == 0 ){
			return &dat->sio[i][0];
		}
	}

	for( i=0; i<FNOTE_SIO_MAX-1; i++ ){
		memcpy( &dat->sio[i][0], &dat->sio[i+1][0], 42 );
	}
	memset( &dat->sio[i][0], 0, 42 );
	return &dat->sio[i][0];
}


//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�Z�[�u [ �s���FID�݂̂̂��� ]
 *
 * @param	dat		�Z�[�u�f�[�^
 * @param	wk		�Z�[�u���郏�[�N
 *
 * @return	none
 *
 * @li	*dat = ( id & 0x3f )
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_ActionIDDataSave( u32 * dat, FNOTE_WK_ACTION * wk )
{
	u32 * buf;
	u32	i;

	for( i=0; i<FNOTE_ACTION_MAX; i++ ){
		if( dat[i] == 0 ){
			break;
		}
	}
	if( i != 0 ){
		if( (dat[i-1]&0x3f) == wk->id ){ return; }
	}

	buf = FNOTE_ActionSavePosGet( dat );
	*buf = ( wk->id & 0x3f );
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�Z�[�u [ �s���F�`�����s�I�� ]
 *
 * @param	dat		�Z�[�u�f�[�^
 * @param	wk		�Z�[�u���郏�[�N
 *
 * @return	none
 *
 * @li	*dat = (map << 16) | ((trainer & 0x3ff) << 6) | (id & 0x3f)
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_ActionTrainerDataSave( u32 * dat, FNOTE_WK_ACTION * wk )
{
	u32 * buf = FNOTE_ActionSavePosGet( dat );
	*buf = (wk->map << 16) | ((wk->trainer & 0x3ff) << 6) | (wk->id & 0x3f);
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�Z�[�u [ �s���F�l�V�� ]
 *
 * @param	dat		�Z�[�u�f�[�^
 * @param	wk		�Z�[�u���郏�[�N
 *
 * @return	none
 *
 * @li	*dat = (map << 16) | ((trainer & 0x3ff) << 6) | (id & 0x3f)
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_ActionSitennouDataSave( u32 * dat, FNOTE_WK_ACTION * wk )
{
	u32 * buf;
	u16	map;
	u16	i;

	buf = NULL;

	for( i=0; i<FNOTE_ACTION_MAX; i++ ){
		if( ( dat[i] & 0x3f ) == FNOTE_ID_SITENNOU ){
			dat[i] = 0;
			for( i=i; i<FNOTE_ACTION_MAX-1; i++ ){
				dat[i] = dat[i+1];
			}
			break;
		}
	}

	buf = FNOTE_ActionSavePosGet( dat );
	*buf = (wk->map << 16) | ((wk->trainer & 0x3ff) << 6) | (wk->id & 0x3f);
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�Z�[�u [ �s���F�W�����[�_�[ ]
 *
 * @param	dat		�Z�[�u�f�[�^
 * @param	wk		�Z�[�u���郏�[�N
 *
 * @return	none
 *
 * @li	*dat = (map << 16) | ((trainer & 0x3ff) << 6) | (id & 0x3f)
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_ActionGymLeaderDataSave( u32 * dat, FNOTE_WK_ACTION * wk )
{
	u32 * buf;
	u16	map;
	u16	i;

	buf = NULL;

	for( i=0; i<FNOTE_ACTION_MAX; i++ ){
		if( (dat[i]&0x3f) == FNOTE_ID_GYMBEFORE && ((dat[i]>>16)&0xffff) == wk->map ){
			dat[i] = 0;
			for( i=i; i<FNOTE_ACTION_MAX-1; i++ ){
				dat[i] = dat[i+1];
			}
			break;
		}
	}

	buf = FNOTE_ActionSavePosGet( dat );
	*buf = (wk->map << 16) | ((wk->trainer & 0x3ff) << 6) | (wk->id & 0x3f);
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�Z�[�u [ �s���F�X�A�_���W�����A�����Ȃ� ]
 *
 * @param	dat		�Z�[�u�f�[�^
 * @param	wk		�Z�[�u���郏�[�N
 *
 * @return	none
 *
 * @li	*dat = (map << 16) | ( id & 0x3f )
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_ActionMapDataSave( u32 * dat, FNOTE_WK_ACTION * wk )
{
	u32 * buf;
	u32	i;

	for( i=0; i<FNOTE_ACTION_MAX; i++ ){
		if( dat[i] == 0 ){ break; }
	}
	if( i != 0 ){
		if( (dat[i-1]&0x3f) == wk->id && (dat[i-1]>>16) == wk->map ){
			return;
		}
	}
	buf = FNOTE_ActionSavePosGet( dat );
	*buf = (wk->map << 16) | (wk->id & 0x3f);
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�Z�[�u [ �s���F�A�C�e���擾 ]
 *
 * @param	dat		�Z�[�u�f�[�^
 * @param	wk		�Z�[�u���郏�[�N
 *
 * @return	none
 *
 * @li	*dat = (item << 16 ) | ( id & 0x3f )
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_ActionItemDataSave( u32 * dat, FNOTE_WK_ACTION * wk )
{
	u32 * buf;
	u32	i;

	for( i=0; i<FNOTE_ACTION_MAX; i++ ){
		if( dat[i] == 0 ){ break; }
	}
	if( i != 0 ){
		if( (dat[i-1]&0x3f) == wk->id && (dat[i-1]>>16) == wk->item ){
			return;
		}
	}
	buf = FNOTE_ActionSavePosGet( dat );
	*buf = (wk->item << 16) | (wk->id & 0x3f);
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�Z�[�u [ �s���F�Z ]
 *
 * @param	dat		�Z�[�u�f�[�^
 * @param	wk		�Z�[�u���郏�[�N
 *
 * @return	none
 *
 * @li	*dat = ( id & 0x3f )
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_ActionSkillDataSave( u32 * dat, FNOTE_WK_ACTION * wk )
{
	u32 * buf;
	u32	i;

	for( i=0; i<FNOTE_ACTION_MAX; i++ ){
		if( dat[i] == 0 ){ break; }
	}
	if( i != 0 ){
		if( (dat[i-1]&0x3f) == wk->id && (dat[i-1]>>16) == wk->map ){
			return;
		}
	}
	buf = FNOTE_ActionSavePosGet( dat );
	*buf = (wk->map << 16) | (wk->id & 0x3f);
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�Z�[�u [ �ʐM�F�ΐ� ]
 *
 * @param	dat		�Z�[�u�f�[�^
 * @param	wk		�Z�[�u���郏�[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_SioBattleDataSave( u8 * dat, FNOTE_WK_SIO * wk )
{
	dat[0] = wk->id;
	dat[1] = (wk->result<<2) | (wk->sex1<<1) | (wk->sex2);
	FNOTE_StrCopy( wk->name1, (STRCODE *)&dat[2], 8 );
	FNOTE_StrCopy( wk->name2, (STRCODE *)&dat[18], 8 );
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�Z�[�u [ �ʐM�F���j�I�����[���E���A ]
 *
 * @param	dat		�Z�[�u�f�[�^
 * @param	wk		�Z�[�u���郏�[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_SioUnionGreetDataSave( u8 * dat, FNOTE_WK_SIO * wk )
{
	dat[0] = wk->id;
	dat[1] = wk->sex1;
	FNOTE_StrCopy( wk->name1, (STRCODE *)&dat[2], 8 );
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�Z�[�u [ �ʐM�F���� ]
 *
 * @param	dat		�Z�[�u�f�[�^
 * @param	wk		�Z�[�u���郏�[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_SioPokeChgDataSave( u8 * dat, FNOTE_WK_SIO * wk )
{
	dat[0] = wk->id;
	dat[1] = (wk->sex1 << 2) | (wk->poke_sex);
	FNOTE_StrCopy( wk->name1, (STRCODE *)&dat[2], 8 );
	FNOTE_StrCopy( wk->nickname, (STRCODE *)&dat[18], 12 );
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�Z�[�u [ �ʐM�F�o�g���^���[ ]
 *
 * @param	dat		�Z�[�u�f�[�^
 * @param	wk		�Z�[�u���郏�[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_SioIDDataSave( FNOTE_DATA * dat, FNOTE_WK_SIO * wk )
{
	u32	i;
	u8 * buf;

	for( i=0; i<FNOTE_SIO_MAX; i++ ){
		if( dat->sio[i][0] == 0 ){
			break;
		}
	}
	if( i != 0 ){
		if( dat->sio[i-1][0] == wk->id ){ return; }
	}
	buf = FNOTE_SioSavePosGet( dat );
	buf[0] = wk->id;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�Z�[�u [ �ʐM�F�R���e�X�g ]
 *
 * @param	dat		�Z�[�u�f�[�^
 * @param	wk		�Z�[�u���郏�[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_SioContestDataSave( u8 * dat, FNOTE_WK_SIO * wk )
{
	dat[0] = wk->id;
	dat[1] = wk->result;
}


//============================================================================================
//	�f�[�^�쐬
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ ���t�E�J�n�ꏊ ]
 *
 * @param	start	�J�n�ꏊ
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 *
 * @li	���t��RTC����擾
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_StartDataMake( u16 start, u32 heap )
{
	FNOTE_WK_START * wk;
	RTCDate	rtc;

	wk = sys_AllocMemory( heap, sizeof(FNOTE_WK_START) );

	GF_RTC_GetDate( &rtc );

	wk->year  = rtc.year;
	wk->month = rtc.month;
	wk->day   = rtc.day;
	wk->week  = rtc.week;
	wk->start = start;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * ���ځE�s���p���[�N�m��
 *
 * @param	heap	�q�[�vID
 *
 * @return	�m�ۂ������[�N
 */
//--------------------------------------------------------------------------------------------
static FNOTE_WK_ACTION * FNOTE_ActionWorkAlloc( u32 heap )
{
	FNOTE_WK_ACTION * wk = sys_AllocMemory( heap, sizeof(FNOTE_WK_ACTION) );
	memset( wk, 0, sizeof(FNOTE_WK_ACTION) );
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �s���F���� ]
 *
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_ActionHouseDataMake( u32 heap )
{
	FNOTE_WK_ACTION * wk = FNOTE_ActionWorkAlloc( heap );
	wk->id = FNOTE_ID_MYHOUSE;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �s���F������ ]
 *
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_ActionLaboDataMake( u32 heap )
{
	FNOTE_WK_ACTION * wk = FNOTE_ActionWorkAlloc( heap );
	wk->id = FNOTE_ID_LABO;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �s���F�|�P�����Z���^�[ ]
 *
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_PokemonCenterDataMake( u32 heap )
{
	FNOTE_WK_ACTION * wk = FNOTE_ActionWorkAlloc( heap );
	wk->id = FNOTE_ID_POKECENTER;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �s���F�V���b�v�E���� ]
 *
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_ActionShopBuyDataMake( u32 heap )
{
	FNOTE_WK_ACTION * wk = FNOTE_ActionWorkAlloc( heap );
	wk->id = FNOTE_ID_FDSHOP_BUY;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �s���F�V���b�v�E�����i�����j ]
 *
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_ActionShopBuy2DataMake( u32 heap )
{
	FNOTE_WK_ACTION * wk = FNOTE_ActionWorkAlloc( heap );
	wk->id = FNOTE_ID_FDSHOP_BUY2;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �s���F�V���b�v�E���� ]
 *
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_ActionShopSaleDataMake( u32 heap )
{
	FNOTE_WK_ACTION * wk = FNOTE_ActionWorkAlloc( heap );
	wk->id = FNOTE_ID_FDSHOP_SALE;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �s���F�V���b�v�E����i�����j ]
 *
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_ActionShopSale2DataMake( u32 heap )
{
	FNOTE_WK_ACTION * wk = FNOTE_ActionWorkAlloc( heap );
	wk->id = FNOTE_ID_FDSHOP_SALE2;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �s���F�V���b�v�E���� ]
 *
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_ActionShopTradeDataMake( u32 heap )
{
	FNOTE_WK_ACTION * wk = FNOTE_ActionWorkAlloc( heap );
	wk->id = FNOTE_ID_FDSHOP_TRADE;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �s���F�W���i���[�_�[��|���O�j]
 *
 * @param	map		�}�b�vID
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_ActionGymBeforeDataMake( u16 map, u32 heap )
{
	FNOTE_WK_ACTION * wk = FNOTE_ActionWorkAlloc( heap );
	wk->id  = FNOTE_ID_GYMBEFORE;
	wk->map = map;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �s���F�W���i���[�_�[��|������j ]
 *
 * @param	map		�}�b�vID
 * @param	trainer	�g���[�i�[ID
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_ActionGymAfterDataMake( u16 map, u16 trainer, u32 heap )
{
	FNOTE_WK_ACTION * wk = FNOTE_ActionWorkAlloc( heap );
	wk->id      = FNOTE_ID_GYMAFTER;
	wk->map     = map;
	wk->trainer = trainer;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �s���F�l�V�� ]
 *
 * @param	trainer	�g���[�i�[ID
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_ActionSitenouDataMake( u16 trainer, u32 heap )
{
	FNOTE_WK_ACTION * wk = FNOTE_ActionWorkAlloc( heap );
	wk->id      = FNOTE_ID_SITENNOU;
	wk->trainer = trainer;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �s���F�`�����s�I�� ]
 *
 * @param	trainer	�g���[�i�[ID
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_ActionChampionDataMake( u16 trainer, u32 heap )
{
	FNOTE_WK_ACTION * wk = FNOTE_ActionWorkAlloc( heap );
	wk->id      = FNOTE_ID_CHAMPION;
	wk->trainer = trainer;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �s���F�X ]
 *
 * @param	map		�}�b�vID
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_ActionCityDataMake( u16 map, u32 heap )
{
	FNOTE_WK_ACTION * wk = FNOTE_ActionWorkAlloc( heap );
	wk->id  = FNOTE_ID_CITY;
	wk->map = map;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �s���F�_���W���� ]
 *
 * @param	map		�}�b�vID
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_ActionDungeonDataMake( u16 map, u32 heap )
{
	FNOTE_WK_ACTION * wk = FNOTE_ActionWorkAlloc( heap );
	wk->id  = FNOTE_ID_DUNGEON;
	wk->map = map;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �s���F���� ]
 *
 * @param	map		�}�b�vID
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_ActionBuildDataMake( u16 map, u32 heap )
{
	FNOTE_WK_ACTION * wk = FNOTE_ActionWorkAlloc( heap );
	wk->id  = FNOTE_ID_BUILD;
	wk->map = map;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �s���F�Q�[���R�[�i�[ ]
 *
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_ActionGameCornerDataMake( u32 heap )
{
	FNOTE_WK_ACTION * wk = FNOTE_ActionWorkAlloc( heap );
	wk->id  = FNOTE_ID_GAMECORNER;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �s���F�T�t�@���]�[�� ]
 *
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_ActionSafariDataMake( u32 heap )
{
	FNOTE_WK_ACTION * wk = FNOTE_ActionWorkAlloc( heap );
	wk->id  = FNOTE_ID_SAFARIZONE;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �s���F�A�C�e���擾 ]
 *
 * @param	item	�A�C�e��ID
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_ActionItemDataMake( u16 item, u32 heap )
{
	FNOTE_WK_ACTION * wk = FNOTE_ActionWorkAlloc( heap );
	wk->id   = FNOTE_ID_ITEMGET;
	wk->item = item;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �s���F�Z ]
 *
 * @param	waza	�t�B�[���h�Z�ԍ�
 * @param	map		�}�b�vID
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_ActionSkillDataMake( u8 waza, u16 map, u32 heap )
{
	FNOTE_WK_ACTION * wk = FNOTE_ActionWorkAlloc( heap );
	wk->id  = FNOTE_ID_IAIGIRI+waza;
	wk->map = map;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �s���F�n���E���Ό@�� ]
 *
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_ActionUGFossilDataMake( u32 heap )
{
	FNOTE_WK_ACTION * wk = FNOTE_ActionWorkAlloc( heap );
	wk->id = FNOTE_ID_UG_FOSSIL;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �s���F�n���E�閧��n ]
 *
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_ActionUGBaseDataMake( u32 heap )
{
	FNOTE_WK_ACTION * wk = FNOTE_ActionWorkAlloc( heap );
	wk->id = FNOTE_ID_UG_BASE;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * ���ځE�|�P�����p���[�N�m��
 *
 * @param	heap	�q�[�vID
 *
 * @return	�m�ۂ������[�N
 */
//--------------------------------------------------------------------------------------------
static FNOTE_WK_POKE * FNOTE_PokeWorkAlloc( u32 heap )
{
	FNOTE_WK_POKE * wk = sys_AllocMemory( heap, sizeof(FNOTE_WK_POKE) );
	memset( wk, 0, sizeof(FNOTE_WK_POKE) );
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �|�P�����F�ߊl ]
 *
 * @param	ptyme	�v���C����
 * @param	mons	�|�P����ID
 * @param	sex		����
 * @param	time	���ԑ�
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_PokemonGetDataMake( const PLAYTIME * ptime, u16 mons, u8 sex, u8 time, u32 heap )
{
	FNOTE_WK_POKE * wk;
	u8	min;
	
	wk = FNOTE_PokeWorkAlloc( heap );
	wk->id   = FNOTE_ID_POKEGET;
	wk->mons = mons;
	wk->sex  = sex;
	wk->time = time;

	min = PLAYTIME_GetMinute( ptime ) / 10;
	if( min == 0 || min == 2 || min == 4 ){
		wk->type = 0;
	}else if( min == 1 || min == 3 ){
		wk->type = 1;
	}else{
		wk->type = 2;
	}

	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �|�P�����F�|�� ]
 *
 * @param	ptyme	�v���C����
 * @param	mons	�|�P����ID
 * @param	sex		����
 * @param	time	���ԑ�
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_PokemonDownDataMake( const PLAYTIME * ptime, u16 mons, u8 sex, u8 time, u32 heap )
{
	FNOTE_WK_POKE * wk;
	u8	min;
	
	wk = FNOTE_PokeWorkAlloc( heap );
	wk->id   = FNOTE_ID_POKEDOWN;
	wk->mons = mons;
	wk->sex  = sex;
	wk->time = time;

	min = PLAYTIME_GetMinute( ptime ) / 10;
	if( min == 1 || min == 3 || min == 5 ){
		wk->type = 0;
	}else if( min == 2 || min == 4 ){
		wk->type = 1;
	}else{
		wk->type = 2;
	}

	return wk;
}


//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �g���[�i�[ ]
 *
 * @param	map		�}�b�vID
 * @param	trainer	�g���[�i�[ID
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_TrainerDataMake( u16 map, u16 trainer, u32 heap )
{
	FNOTE_WK_TRAINER * wk = sys_AllocMemory( heap, sizeof(FNOTE_WK_TRAINER) );
	wk->id   = 1;
	wk->map  = map;
	wk->trid = trainer;
	return wk;
}


//--------------------------------------------------------------------------------------------
/**
 * ���ځE�ʐM�p���[�N�m��
 *
 * @param	heap	�q�[�vID
 *
 * @return	�m�ۂ������[�N
 */
//--------------------------------------------------------------------------------------------
static FNOTE_WK_SIO * FNOTE_SioWorkAlloc( u32 heap )
{
	FNOTE_WK_SIO * wk = sys_AllocMemory( heap, sizeof(FNOTE_WK_SIO) );
	memset( wk, 0, sizeof(FNOTE_WK_SIO) );
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * ������R�s�[
 *
 * @param	str		�R�s�[���镶����
 * @param	buf		�i�[��
 * @param	siz		������
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_StrCopy( const STRCODE * str, STRCODE * buf, u32 siz )
{
	u32	i;

	for( i=0; i<siz; i++ ){
		buf[i] = EOM_;
	}
	for( i=0; i<siz; i++ ){
		if( str[i] == EOM_ ){ break; }
		buf[i] = str[i];
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �ʐM�F�ʐM�ΐ�E�V���O�� ]
 *
 * @param	name	�ΐ푊��̖��O
 * @param	sex		�ΐ푊��̐���
 * @param	result	���s
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_SioSingleBtlDataMake( STRCODE * name, u8 sex, u8 result, u32 heap )
{
	FNOTE_WK_SIO * wk = FNOTE_SioWorkAlloc( heap );
	wk->id     = FNOTE_ID_SB_SINGLE;
	wk->result = result;
	wk->sex1   = sex;
	FNOTE_StrCopy( name, wk->name1, BUFLEN_PERSON_NAME );
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �ʐM�F�ʐM�ΐ�E�_�u�� ]
 *
 * @param	name	�ΐ푊��̖��O
 * @param	sex		�ΐ푊��̐���
 * @param	result	���s
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_SioDoubleBtlDataMake( STRCODE * name, u8 sex, u8 result, u32 heap )
{
	FNOTE_WK_SIO * wk = FNOTE_SioWorkAlloc( heap );
	wk->id     = FNOTE_ID_SB_DOUBLE;
	wk->result = result;
	wk->sex1   = sex;
	FNOTE_StrCopy( name, wk->name1, BUFLEN_PERSON_NAME );
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �ʐM�F�ʐM�ΐ�E�}���` ]
 *
 * @param	name1	�ΐ푊��P�̖��O
 * @param	name2	�ΐ푊��Q�̖��O
 * @param	sex1	�ΐ푊��P�̐���
 * @param	sex2	�ΐ푊��Q�̐���
 * @param	result	���s
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_SioMultiBtlDataMake(
		 STRCODE * name1, STRCODE * name2, u8 sex1, u8 sex2, u8 result, u32 heap )
{
	FNOTE_WK_SIO * wk = FNOTE_SioWorkAlloc( heap );
	wk->id     = FNOTE_ID_SB_MULTI;
	wk->result = result;
	wk->sex1   = sex1;
	wk->sex2   = sex2;
	FNOTE_StrCopy( name1, wk->name1, BUFLEN_PERSON_NAME );
	FNOTE_StrCopy( name2, wk->name2, BUFLEN_PERSON_NAME );
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �ʐM�F�ʐM�ΐ�E�~�b�N�X1vs1 ]
 *
 * @param	name	�ΐ푊��̖��O
 * @param	sex		�ΐ푊��̐���
 * @param	result	���s
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_SioMixBtl1DataMake( STRCODE * name, u8 sex, u8 result, u32 heap )
{
	FNOTE_WK_SIO * wk = FNOTE_SioWorkAlloc( heap );
	wk->id     = FNOTE_ID_SB_MIX1;
	wk->result = result;
	wk->sex1   = sex;
	FNOTE_StrCopy( name, wk->name1, BUFLEN_PERSON_NAME );
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �ʐM�F�ʐM�ΐ�E�~�b�N�X2vs2 ]
 *
 * @param	name1	�ΐ푊��P�̖��O
 * @param	name2	�ΐ푊��Q�̖��O
 * @param	sex1	�ΐ푊��P�̐���
 * @param	sex2	�ΐ푊��Q�̐���
 * @param	result	���s
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_SioMixBtl2DataMake(
		 STRCODE * name1, STRCODE * name2, u8 sex1, u8 sex2, u8 result, u32 heap )
{
	FNOTE_WK_SIO * wk = FNOTE_SioWorkAlloc( heap );
	wk->id     = FNOTE_ID_SB_MIX2;
	wk->result = result;
	wk->sex1   = sex1;
	wk->sex2   = sex2;
	FNOTE_StrCopy( name1, wk->name1, BUFLEN_PERSON_NAME );
	FNOTE_StrCopy( name2, wk->name2, BUFLEN_PERSON_NAME );
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �ʐM�F���j�I�����[���E���A ]
 *
 * @param	name	����̖��O
 * @param	sex		����̐���
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_SioUnionGreetDataMake( STRCODE * name, u8 sex, u32 heap )
{
	FNOTE_WK_SIO * wk = FNOTE_SioWorkAlloc( heap );
	wk->id   = FNOTE_ID_U_GREETING;
	wk->sex1 = sex;
	FNOTE_StrCopy( name, wk->name1, BUFLEN_PERSON_NAME );
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �ʐM�F���j�I�����[���E���� ]
 *
 * @param	name		��������̖��O
 * @param	sex			��������̐���
 * @param	nickname	�����ł����|�P�����̃j�b�N�l�[��
 * @param	poke_sex	�����ł����|�P�����̐���
 * @param	heap		�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_SioUnionChangeDataMake(
		STRCODE * name, u8 sex, STRCODE * nickname, u8 poke_sex, u32 heap )
{
	FNOTE_WK_SIO * wk = FNOTE_SioWorkAlloc( heap );
	wk->id       = FNOTE_ID_U_POKECHG;
	wk->sex1     = sex;
	wk->poke_sex = poke_sex;
	FNOTE_StrCopy( name, wk->name1, BUFLEN_PERSON_NAME );
	FNOTE_StrCopy( nickname, wk->nickname, BUFLEN_POKEMON_NAME );
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �ʐM�F���j�I�����[���E���G���� ]
 *
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_SioUnionPictureDataMake( u32 heap )
{
	FNOTE_WK_SIO * wk = FNOTE_SioWorkAlloc( heap );
	wk->id = FNOTE_ID_U_PICTURE;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �ʐM�F���j�I�����[���E�����l���� ]
 *
 * @param	nickname	�����ł����|�P�����̃j�b�N�l�[��
 * @param	poke_sex	�����ł����|�P�����̐���
 * @param	heap		�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_SioUnionMltChgDataMake( STRCODE * nickname, u8 poke_sex, u32 heap )
{
	FNOTE_WK_SIO * wk = FNOTE_SioWorkAlloc( heap );
	wk->id       = FNOTE_ID_U_MLTCHG;
	wk->poke_sex = poke_sex;
	FNOTE_StrCopy( nickname, wk->nickname, BUFLEN_POKEMON_NAME );
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �ʐM�F���j�I�����[���E�g�����V�[�o�[ ]
 *
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_SioUnionTransceiverDataMake( u32 heap )
{
	FNOTE_WK_SIO * wk = FNOTE_SioWorkAlloc( heap );
	wk->id = FNOTE_ID_U_TRANSCEIVER;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �ʐM�F���j�I�����[���E�ΐ� ]
 *
 * @param	name	�ΐ푊��̖��O
 * @param	sex		�ΐ푊��̐���
 * @param	result	���s
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_SioUnionBattleDataMake( STRCODE * name, u8 sex, u8 result, u32 heap )
{
	FNOTE_WK_SIO * wk = FNOTE_SioWorkAlloc( heap );
	wk->id     = FNOTE_ID_U_BATTLE;
	wk->result = result;
	wk->sex1   = sex;
	FNOTE_StrCopy( name, wk->name1, BUFLEN_PERSON_NAME );
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �ʐM�F���R�[�h�R�[�i�[ ]
 *
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_SioRecordDataMake( u32 heap )
{
	FNOTE_WK_SIO * wk = FNOTE_SioWorkAlloc( heap );
	wk->id = FNOTE_ID_RECORD;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �ʐM�F�R���e�X�g ]
 *
 * @param	result	����
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_SioContestDataMake( u8 result, u32 heap )
{
	FNOTE_WK_SIO * wk = FNOTE_SioWorkAlloc( heap );
	wk->id     = FNOTE_ID_CONTEST;
	wk->result = result;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �ʐM�F�|���g�쐬 ]
 *
 * @param	name	����̖��O
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_SioPorutoDataMake( u32 heap )
{
	FNOTE_WK_SIO * wk = FNOTE_SioWorkAlloc( heap );
	wk->id = FNOTE_ID_PORUTO;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �ʐM�FGTC ]
 *
 * @param	name		��������̖��O
 * @param	sex			��������̐���
 * @param	nickname	�����ł����|�P�����̃j�b�N�l�[��
 * @param	poke_sex	�����ł����|�P�����̐���
 * @param	heap		�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_SioGTCDataMake( STRCODE * name, u8 sex, STRCODE * nickname, u8 poke_sex, u32 heap )
{
	FNOTE_WK_SIO * wk = FNOTE_SioWorkAlloc( heap );
	wk->id       = FNOTE_ID_GTC;
	wk->sex1     = sex;
	wk->poke_sex = poke_sex;
	FNOTE_StrCopy( name, wk->name1, BUFLEN_PERSON_NAME );
	FNOTE_StrCopy( nickname, wk->nickname, BUFLEN_POKEMON_NAME );
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬 [ �ʐM�F�o�g���^���[ ]
 *
 * @param	name	����̖��O
 * @param	heap	�q�[�vID
 *
 * @return	�쐬�������[�N
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_SioBattleTowerDataMake( u32 heap )
{
	FNOTE_WK_SIO * wk = FNOTE_SioWorkAlloc( heap );
	wk->id = FNOTE_ID_BTLTOWER;
	return wk;
}


//============================================================================================
//	�f�[�^�擾
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * ��z�f�[�^�擾
 *
 * @param	dat		�Z�[�u�f�[�^
 * @param	wk		�擾�ꏊ
 * @param	type	�L�^�^�C�v
 * @param	page	�擾�y�[�W
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FNOTE_DataGet( FNOTE_DATA * dat, void * wk, u8 type, u8 page )
{
	switch( type ){
	case FNOTE_TYPE_START:		// �J�n
		FNOTE_StartDataGet( &dat[page], wk );
		break;

	case FNOTE_TYPE_ACTION:		// �s��
		FNOTE_ActionDataGet( &dat[page], wk );
		break;

	case FNOTE_TYPE_POKEMON:	// �|�P����
		FNOTE_PokemonDataGet( &dat[page], wk );
		break;

	case FNOTE_TYPE_TRAINER:	// �g���[�i�[
		FNOTE_TrainerDataGet( &dat[page], wk );
		break;

	case FNOTE_TYPE_SIO:		// �ʐM
		FNOTE_SioDataGet( &dat[page], wk );
		break;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �J�n�f�[�^�擾
 *
 * @param	dat		�Z�[�u�f�[�^
 * @param	wk		�擾�ꏊ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_StartDataGet( FNOTE_DATA * dat, FNOTE_WK_START * wk )
{
	*wk = dat->hed;
}

//--------------------------------------------------------------------------------------------
/**
 * �s���f�[�^�擾
 *
 * @param	dat		�Z�[�u�f�[�^
 * @param	wk		�擾�ꏊ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_ActionDataGet( FNOTE_DATA * dat, FNOTE_WK_ACTION * wk )
{
	u32	i;

	for( i=0; i<FNOTE_ACTION_MAX; i++ ){
		memset( &wk[i], 0, sizeof(FNOTE_WK_ACTION) );
		switch( dat->action[i] & 0x3f ){
		case FNOTE_ID_MYHOUSE:			// �s���F����
		case FNOTE_ID_LABO:				// �s���F������
		case FNOTE_ID_POKECENTER:		// �s���F�|�P�����Z���^�[
		case FNOTE_ID_FDSHOP_BUY:		// �s���F�V���b�v�E����
		case FNOTE_ID_FDSHOP_BUY2:		// �s���F�V���b�v�E�����i�����j
		case FNOTE_ID_FDSHOP_SALE:		// �s���F�V���b�v�E����
		case FNOTE_ID_FDSHOP_SALE2:		// �s���F�V���b�v�E����i�����j
		case FNOTE_ID_FDSHOP_TRADE:		// �s���F�V���b�v�E����
		case FNOTE_ID_GAMECORNER:		// �s���F�Q�[���R�[�i�[
		case FNOTE_ID_SAFARIZONE:		// �s���F�T�t�@���]�[��
		case FNOTE_ID_UG_FOSSIL:		// �s���F�n���E���Ό@��
		case FNOTE_ID_UG_BASE:			// �s���F�n���E�閧��n
			FNOTE_ActionIDDataGet( dat->action[i], &wk[i] );
			break;

		case FNOTE_ID_GYMBEFORE:		// �s���F�W���i���[�_�[��|���O�j
		case FNOTE_ID_GYMAFTER:			// �s���F�W���i���[�_�[��|������j
		case FNOTE_ID_SITENNOU:			// �s���F�l�V��
		case FNOTE_ID_CHAMPION:			// �s���F�`�����s�I��
			FNOTE_ActionTrainerDataGet( dat->action[i], &wk[i] );
			break;

		case FNOTE_ID_CITY:				// �s���F�X
		case FNOTE_ID_DUNGEON:			// �s���F�_���W����
		case FNOTE_ID_BUILD:			// �s���F����
			FNOTE_ActionMapDataGet( dat->action[i], &wk[i] );
			break;

		case FNOTE_ID_ITEMGET:			// �s���F�A�C�e���擾
			FNOTE_ActionItemDataGet( dat->action[i], &wk[i] );
			break;

		case FNOTE_ID_IAIGIRI:			// �s���F�Z�E����������
		case FNOTE_ID_SORAWOTOBU:		// �s���F�Z�E������Ƃ�
		case FNOTE_ID_NAMINORI:			// �s���F�Z�E�Ȃ݂̂�
		case FNOTE_ID_KAIRIKI:			// �s���F�Z�E�����肫
		case FNOTE_ID_FLASH:			// �s���F�Z�E�t���b�V��
		case FNOTE_ID_KIRIBARAI:		// �s���F�Z�E����΂炢
		case FNOTE_ID_IWAKUDAKI:		// �s���F�Z�E���킭����
		case FNOTE_ID_TAKINOBORI:		// �s���F�Z�E�����̂ڂ�
		case FNOTE_ID_ROCKCLIMB:		// �s���F�Z�E���b�N�N���C��
		case FNOTE_ID_ANAWOHORU:		// �s���F�Z�E���Ȃ��ق�
		case FNOTE_ID_AMAIKAORI:		// �s���F�Z�E���܂�������
		case FNOTE_ID_TELEPORT:			// �s���F�Z�E�e���|�[�g
		case FNOTE_ID_TAMAGOUMI:		// �s���F�Z�E�^�}�S����
		case FNOTE_ID_MIRUKUNOMI:		// �s���F�Z�E�~���N�̂�
			FNOTE_ActionSkillDataGet( dat->action[i], &wk[i] );
			break;
		}
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �|�P�����f�[�^�擾
 *
 * @param	dat		�Z�[�u�f�[�^
 * @param	wk		�擾�ꏊ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_PokemonDataGet( FNOTE_DATA * dat, FNOTE_WK_POKE * wk )
{
	*wk = dat->pokemon;
}

//--------------------------------------------------------------------------------------------
/**
 * �g���[�i�[�f�[�^�擾
 *
 * @param	dat		�Z�[�u�f�[�^
 * @param	wk		�擾�ꏊ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_TrainerDataGet( FNOTE_DATA * dat, FNOTE_WK_TRAINER * wk )
{
	*wk = dat->trainer;
}

//--------------------------------------------------------------------------------------------
/**
 * �ʐM�f�[�^�擾
 *
 * @param	dat		�Z�[�u�f�[�^
 * @param	wk		�擾�ꏊ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_SioDataGet( FNOTE_DATA * dat, FNOTE_WK_SIO * wk )
{
	u32	i;

	for( i=0; i<FNOTE_SIO_MAX; i++ ){
		memset( &wk[i], 0, sizeof(FNOTE_WK_SIO) );
		switch( dat->sio[i][0] ){
		case FNOTE_ID_SB_SINGLE:		// �ʐM�F�ʐM�ΐ�E�V���O��
		case FNOTE_ID_SB_DOUBLE:		// �ʐM�F�ʐM�ΐ�E�_�u��
		case FNOTE_ID_SB_MULTI:			// �ʐM�F�ʐM�ΐ�E�}���`
		case FNOTE_ID_SB_MIX1:			// �ʐM�F�ʐM�ΐ�E�~�b�N�X1vs1
		case FNOTE_ID_SB_MIX2:			// �ʐM�F�ʐM�ΐ�E�~�b�N�X2vs2
		case FNOTE_ID_U_BATTLE:			// �ʐM�F���j�I�����[���E�ΐ�
			FNOTE_SioBattleDataGet( &dat->sio[i][0], &wk[i] );
			break;

		case FNOTE_ID_U_GREETING:		// �ʐM�F���j�I�����[���E���A
			FNOTE_SioUnionGreetDataGet( &dat->sio[i][0], &wk[i] );
			break;

		case FNOTE_ID_U_POKECHG:		// �ʐM�F���j�I�����[���E����
		case FNOTE_ID_U_MLTCHG:			// �ʐM�F���j�I�����[���E�����l����
		case FNOTE_ID_GTC:				// �ʐM�FGTC
			FNOTE_SioPokeChgDataGet( &dat->sio[i][0], &wk[i] );
			break;

		case FNOTE_ID_U_PICTURE:		// �ʐM�F���j�I�����[���E���G����
		case FNOTE_ID_U_TRANSCEIVER:	// �ʐM�F���j�I�����[���E�g�����V�[�o�[
		case FNOTE_ID_RECORD:			// �ʐM�F���R�[�h�R�[�i�[
		case FNOTE_ID_PORUTO:			// �ʐM�F�|���g�쐬
		case FNOTE_ID_BTLTOWER:			// �ʐM�F�o�g���^���[
			FNOTE_SioIDDataGet( &dat->sio[i][0], &wk[i] );
			break;

		case FNOTE_ID_CONTEST:			// �ʐM�F�R���e�X�g
			FNOTE_SioContestDataGet( &dat->sio[i][0], &wk[i] );
			break;
		}
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�擾 [ �s���FID�݂̂̂��� ]
 *
 * @param	dat		�Z�[�u�f�[�^
 * @param	wk		�擾�ꏊ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_ActionIDDataGet( u32 dat, FNOTE_WK_ACTION * wk )
{
//	*dat = ( wk->id & 0x3f );
	wk->id = ( dat & 0x3f );
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�擾 [ �s���F�W�����[�_�[�A�l�V���A�`�����s�I�� ]
 *
 * @param	dat		�Z�[�u�f�[�^
 * @param	wk		�擾�ꏊ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_ActionTrainerDataGet( u32 dat, FNOTE_WK_ACTION * wk )
{
//	*dat = (wk->map << 16) | ((wk->trainer & 0x3ff) << 6) | (wk->id & 0x3f);
	wk->id      = ( dat & 0x3f );
	wk->trainer = ( dat >> 6 ) & 0x3ff;
	wk->map     = ( dat >> 16 ) & 0xffff;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�擾 [ �s���F�X�A�_���W�����A�����Ȃ� ]
 *
 * @param	dat		�Z�[�u�f�[�^
 * @param	wk		�擾�ꏊ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_ActionMapDataGet( u32 dat, FNOTE_WK_ACTION * wk )
{
//	*dat = (wk->map << 16) | (wk->id & 0x3f);
	wk->id  = ( dat & 0x3f );
	wk->map = ( dat >> 16 ) & 0xffff;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�擾 [ �s���F�A�C�e���擾 ]
 *
 * @param	dat		�Z�[�u�f�[�^
 * @param	wk		�擾�ꏊ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_ActionItemDataGet( u32 dat, FNOTE_WK_ACTION * wk )
{
//	*dat = (wk->item << 16) | (wk->id & 0x3f);
	wk->id   = ( dat & 0x3f );
	wk->item = ( dat >> 16 ) & 0xffff;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�擾 [ �s���F�Z ]
 *
 * @param	dat		�Z�[�u�f�[�^
 * @param	wk		�擾�ꏊ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_ActionSkillDataGet( u32 dat, FNOTE_WK_ACTION * wk )
{
//	*dat = (wk->map << 16) | (wk->id & 0x3f);
	wk->id  = ( dat & 0x3f );
	wk->map = ( dat >> 16 ) & 0xffff;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�擾 [ �ʐM�F�ΐ� ]
 *
 * @param	dat		�Z�[�u�f�[�^
 * @param	wk		�擾�ꏊ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_SioBattleDataGet( u8 * dat, FNOTE_WK_SIO * wk )
{
/*
	dat[0] = wk->id;
	dat[1] = (wk->result<<2) | (wk->sex1<<1) | (wk->sex2);
	FNOTE_StrCopy( wk->name1, (STRCODE *)&dat[2], 8 );
	FNOTE_StrCopy( wk->name2, (STRCODE *)&dat[18], 8 );
*/
	wk->id       = dat[0];
	wk->result   = ( dat[1] >> 2 ) & 0x1f;
	wk->sex1     = ( dat[1] >> 1 ) & 1;
	wk->sex2     = dat[1] & 1;
	FNOTE_StrCopy( (STRCODE *)&dat[2], wk->name1, 8 );
	FNOTE_StrCopy( (STRCODE *)&dat[18], wk->name2, 8 );
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�擾 [ �ʐM�F���j�I�����[���E���A ]
 *
 * @param	dat		�Z�[�u�f�[�^
 * @param	wk		�擾�ꏊ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_SioUnionGreetDataGet( u8 * dat, FNOTE_WK_SIO * wk )
{
/*
	dat[0] = wk->id;
	dat[1] = wk->sex1;
	FNOTE_StrCopy( wk->name1, (STRCODE *)&dat[2], 8 );
*/
	wk->id   = dat[0];
	wk->sex1 = dat[1];
	FNOTE_StrCopy( (STRCODE *)&dat[2], wk->name1, 8 );
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�擾 [ �ʐM�F���� ]
 *
 * @param	dat		�Z�[�u�f�[�^
 * @param	wk		�擾�ꏊ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_SioPokeChgDataGet( u8 * dat, FNOTE_WK_SIO * wk )
{
/*
	dat[0] = wk->id;
	dat[1] = (wk->sex1 << 2) | (wk->poke_sex);
	FNOTE_StrCopy( wk->name1, (STRCODE *)&dat[2], 8 );
	FNOTE_StrCopy( wk->nickname, (STRCODE *)&dat[18], 12 );
*/
	wk->id       = dat[0];
	wk->sex1     = ( dat[1] >> 2 ) & 1;
	wk->poke_sex = dat[1] & 3;
	FNOTE_StrCopy( (STRCODE *)&dat[2], wk->name1, 8 );
	FNOTE_StrCopy( (STRCODE *)&dat[18], wk->nickname, 12 );
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�擾 [ �ʐM�F�o�g���^���[ ]
 *
 * @param	dat		�Z�[�u�f�[�^
 * @param	wk		�擾�ꏊ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_SioIDDataGet( u8 * dat, FNOTE_WK_SIO * wk )
{
//	dat[0] = wk->id;
	wk->id = dat[0];
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�擾 [ �ʐM�F�R���e�X�g ]
 *
 * @param	dat		�Z�[�u�f�[�^
 * @param	wk		�擾�ꏊ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_SioContestDataGet( u8 * dat, FNOTE_WK_SIO * wk )
{
/*
	dat[0] = wk->id;
	dat[1] = wk->result;
*/
	wk->id     = dat[0];
	wk->result = dat[1];
}


//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬/�Z�[�u [ �s���F����A�������A�����A�_���W��������o�� ]
 *
 * @param	my		�v���[���[�f�[�^
 * @param	dat		�`���m�[�g�̃Z�[�u�f�[�^
 * @param	now		���݂̃}�b�v
 * @param	before	�O�ɂ����}�b�v
 * @param	heap	�q�[�vID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FNOTE_DataMakeSaveMapChg( MYSTATUS * my, FNOTE_DATA * dat, u32 now, u32 before, u32 heap )
{
	void * buf;
	u32	i;

	buf = NULL;

	// �_���W��������
	if( ZoneData_IsDungeon( before ) == TRUE ){
		// ���O��
		if( ZoneData_IsOutDoor( now ) == TRUE ){
//			buf = FNOTE_ActionDungeonDataMake( (u16)before, heap );
			buf = FNOTE_ActionDungeonDataMake( (u16)ZoneData_GetPlaceNameID(before), heap );
		}
	// ��������
	}else if( ZoneData_IsRoom( before ) == TRUE ){
		// ���O��
		if( ZoneData_IsOutDoor( now ) == TRUE ){
			// ����
			if( before == ZONE_ID_T01R0201 ){
				buf = FNOTE_ActionHouseDataMake( heap );
			// ������
			}else if( before == ZONE_ID_T02R0101 ){
				buf = FNOTE_ActionLaboDataMake( heap );
			// ���̑�
			}else{
				u32	name = ZoneData_GetPlaceNameID( before );
				for( i=0; i<NELEMS(BuildNameTable); i++ ){
					if( name != BuildNameTable[i].name ){ continue; }
//					buf = FNOTE_ActionBuildDataMake( (u16)before, heap );
					buf = FNOTE_ActionBuildDataMake( (u16)name, heap );
				}
			}
		}
	// ���O����
	}else if( ZoneData_IsOutDoor( before ) == TRUE ){
		// ������
		if( ZoneData_IsRoom( now ) == TRUE ){
			// �W��
			u8	gym = GymCheck( my, now );
			if( gym != 0xff ){
				buf = FNOTE_ActionGymBeforeDataMake( gym, heap );
			}
		}
	}

	if( buf != NULL ){
		FNOTE_DataSave( dat, buf, FNOTE_TYPE_ACTION );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * ����Ȍ����̕\���^�C�v�擾
 *
 * @param	name	���OID
 *
 * @return	�\���^�C�v
 */
//--------------------------------------------------------------------------------------------
u32 FNOTE_ExBuildPutTypeGet( u32 name )
{
	u32	i;

	for( i=0; i<NELEMS(BuildNameTable); i++ ){
		if( name != BuildNameTable[i].name ){ continue; }
		return BuildNameTable[i].type;
	}
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �W���`�F�b�N
 *
 * @param	my			�v���[���[�f�[�^
 * @param	zone_id		�]�[��ID
 *
 * @retval	"0xff != �W��ID"
 * @retval	"0xff = �W���ȊO"
 */
//--------------------------------------------------------------------------------------------
static u8 GymCheck( MYSTATUS * my, u32 zone_id )
{
	u8	i;

	for( i=0; i<NELEMS(GymTbl); i++ ){
		if( GymTbl[i].zone == zone_id ){
			if( MyStatus_GetBadgeFlag( my, GymTbl[i].badge ) == FALSE ){
				return i;
			}
			break;
		}
	}
	return 0xff;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬/�Z�[�u [ �s���F�X�ɓ��� ]
 *
 * @param	dat		�Z�[�u�f�[�^
 * @param	map		���݂̃}�b�v
 * @param	heap	�q�[�vID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FNOTE_DataMakeSaveCity( FNOTE_DATA * dat, u32 map, u32 heap )
{
	void * buf = FNOTE_ActionCityDataMake( (u16)map, heap );
	FNOTE_DataSave( dat, buf, FNOTE_TYPE_ACTION );
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�쐬/�Z�[�u [ �s���F�W�����[�_�[�A�`�����s�I���A�l�V�� & �g���[�i�[�F�g���[�i�[ ]
 *
 * @param	dat			�`���m�[�g�̃Z�[�u�f�[�^
 * @param	map			�]�[��ID
 * @param	trainer		�g���[�i�[ID
 * @param	heap		�q�[�vID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FNOTE_DataMakeSaveTrainer( FNOTE_DATA * dat, u16 map, u16 trainer, u32 heap )
{
	void * buf;
	u8	ret;
	
	ret = TrainerCheck( trainer );

	// �W�����[�_�[
	if( ret < 8 ){
		buf = FNOTE_ActionGymAfterDataMake( ret, trainer, heap );
		FNOTE_DataSave( dat, buf, FNOTE_TYPE_ACTION );
	// �l�V��
	}else if( ret == 8 ){
		buf = FNOTE_ActionSitenouDataMake( trainer, heap );
		FNOTE_DataSave( dat, buf, FNOTE_TYPE_ACTION );
	// �`�����s�I��
	}else if( ret == 9 ){
		buf = FNOTE_ActionChampionDataMake( trainer, heap );
		FNOTE_DataSave( dat, buf, FNOTE_TYPE_ACTION );
	// ���ʂ̃g���[�i�[
	}else{
		buf = FNOTE_TrainerDataMake( map, trainer, heap );
		FNOTE_DataSave( dat, buf, FNOTE_TYPE_TRAINER );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �g���[�i�[�^�C�v���擾
 *
 * @param	tr		�g���[�i�[ID
 *
 * @retval	"8 > �W�����[�_�[
 * @retval	"8 = �l�V��"
 * @retval	"9 = �`�����s�I��"
 * @retval	"10 = ���ʂ̃g���[�i�["
 */
//--------------------------------------------------------------------------------------------
static u8 TrainerCheck( u32 tr )
{
	u8	i;

	// �W�����[�_�[
	for( i=0; i<NELEMS(GymTbl); i++ ){
		if( GymTbl[i].tr == tr ){
			return i;
		}
	}
	// �l�V��
	if( tr == BIGFOUR1_01 || tr == BIGFOUR2_01 || tr == BIGFOUR3_01 || tr == BIGFOUR4_01 ){
		return 8;
	}
	// �`�����s�I��
	if( tr == CHAMPION_01 ){
		return 9;
	}
	return 10;
}

