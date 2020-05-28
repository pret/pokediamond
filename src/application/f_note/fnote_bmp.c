//============================================================================================
/**
 * @file	fnote_bmp.c
 * @brief	�`���m�[�g�@BMP����
 * @author	Hiroyuki Nakamura
 * @date	2006.03.06
 */
//============================================================================================
#include "common.h"
#include "gflib/strbuf_family.h"
#include "savedata/fnote_mem.h"
#include "system/fontproc.h"
#include "system/msgdata.h"
#include "system/wordset.h"
#include "poketool/tr_tool.h"
#include "battle/trtype_def.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_fantasy_note.h"
#include "msgdata/msg_place_name.h"
#include "field/field_place_name.h"
#include "../../src/field/zonedata.h"

#define	FNOTE_BMP_H_GLOBAL
#include "fnote_main.h"
#include "fnote_bmp.h"


//============================================================================================
//	�萔��`
//============================================================================================
#define	WIN_TIME1_PX	( 2 )
#define	WIN_TIME1_PY	( 2 )
#define	WIN_TIME1_SX	( 24 )
#define	WIN_TIME1_SY	( 2 )
#define	WIN_TIME1_PAL	( 15 )
#define	WIN_TIME1_CGX	( 1 )

#define	WIN_STR1_PX		( 4 )
#define	WIN_STR1_PY		( 4 )
#define	WIN_STR1_SX		( 27 )
#define	WIN_STR1_SY		( 18 )
#define	WIN_STR1_PAL	( 15 )
#define	WIN_STR1_CGX	( WIN_TIME1_CGX + WIN_TIME1_SX * WIN_TIME1_SY )

#define	WIN_TIME2_PX	( 2 )
#define	WIN_TIME2_PY	( 2 )
#define	WIN_TIME2_SX	( 24 )
#define	WIN_TIME2_SY	( 2 )
#define	WIN_TIME2_PAL	( 15 )
#define	WIN_TIME2_CGX	( 1 )

#define	WIN_STR2_PX		( 4 )
#define	WIN_STR2_PY		( 4 )
#define	WIN_STR2_SX		( 27 )
#define	WIN_STR2_SY		( 18 )
#define	WIN_STR2_PAL	( 15 )
#define	WIN_STR2_CGX	( WIN_TIME2_CGX + WIN_TIME2_SX * WIN_TIME2_SY )

#define	COL_N_BLACK		( GF_PRINTCOLOR_MAKE( 1, 2, 0 ) )		// �t�H���g�J���[�F��

#define	WEEK_SPC_X	( 12 )		// �j���X�y�[�X

#define	ACTION_PY	( 16 )
#define	POKEMON_PY	( ACTION_PY * 4 + 16 )
#define	TRAINER_PY	( POKEMON_PY + 16 )
#define	SIO_PY		( TRAINER_PY + 16 )


//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================
static u8 FNOTE_HederPut( FNOTE_WORK * wk, GF_BGL_BMPWIN * time, GF_BGL_BMPWIN * info );
static void FNOTE_ActionPut( FNOTE_WORK * wk, GF_BGL_BMPWIN * info );
static void FNOTE_PokemonPut( FNOTE_WORK * wk, GF_BGL_BMPWIN * info );
static void FNOTE_TrainerPut( FNOTE_WORK * wk, GF_BGL_BMPWIN * info );
static void FNOTE_SioPut( FNOTE_WORK * wk, GF_BGL_BMPWIN * info );

static void FNOTE_ActionHouseDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos );
static void FNOTE_ActionLaboDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos );
static void FNOTE_ActionPokeCenterDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos );
static void FNOTE_ActionShopBuyDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos );
static void FNOTE_ActionShopBuy2DataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos );
static void FNOTE_ActionShopSaleDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos );
static void FNOTE_ActionShopSale2DataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos );
static void FNOTE_ActionShopTradeDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos );
static void FNOTE_ActionGymBeforeDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos );
static void FNOTE_ActionGymAfterDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos );
static void FNOTE_ActionSitennouDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos );
static void FNOTE_ActionChampionDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos );
static void FNOTE_ActionCityDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos );
static void FNOTE_ActionDungeonDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos );
static void FNOTE_ActionBuildDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos );
static void FNOTE_ActionGameCornerDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos );
static void FNOTE_ActionSafariDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos );
static void FNOTE_ActionItemGetDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos );
static void FNOTE_ActionIwakudakiDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos );
static void FNOTE_ActionIaigiriDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos );
static void FNOTE_ActionSorawotobuDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos );
static void FNOTE_ActionKiribaraiDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos );
static void FNOTE_ActionKairikiDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos );
static void FNOTE_ActionNaminoriDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos );
static void FNOTE_ActionRockckimbDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos );
static void FNOTE_ActionTakinoboriDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos );
static void FNOTE_ActionFlashDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos );
static void FNOTE_ActionTeleportDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos );
static void FNOTE_ActionAnawohoruDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos );
static void FNOTE_ActionAmiaikaoriDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos );
static void FNOTE_ActionTamagoumiDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos );
static void FNOTE_ActionMilknomiDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos );
static void FNOTE_ActionUGFossilDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos );
static void FNOTE_ActionUGBaseDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos );
static void FNOTE_PokeGetDataPut( FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_POKE * mem );
static void FNOTE_PokeDownDataPut( FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_POKE * mem );
static void FNOTE_SioBtlSingleDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_SIO * mem, u8 pos );
static void FNOTE_SioBtlDoubleDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_SIO * mem, u8 pos );
static void FNOTE_SioBtlMultiDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_SIO * mem, u8 pos );
static void FNOTE_SioBtlMix1DataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_SIO * mem, u8 pos );
static void FNOTE_SioBtlMix2DataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_SIO * mem, u8 pos );
static void FNOTE_SioUnionGreetDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_SIO * mem, u8 pos );
static void FNOTE_SioUnionChgDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_SIO * mem, u8 pos );
static void FNOTE_SioUnionPictureDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_SIO * mem, u8 pos );
static void FNOTE_SioUnionMultiChgDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_SIO * mem, u8 pos );
static void FNOTE_SioUnionTransceiverDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_SIO * mem, u8 pos );
static void FNOTE_SioUnionBtlDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_SIO * mem, u8 pos );
static void FNOTE_SioRecordDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_SIO * mem, u8 pos );
static void FNOTE_SioContestDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_SIO * mem, u8 pos );
static void FNOTE_SioPorutoDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_SIO * mem, u8 pos );
static void FNOTE_SioGtcDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_SIO * mem, u8 pos );
static void FNOTE_SioBtlTowerDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_SIO * mem, u8 pos );


//============================================================================================
//	�O���[�o���ϐ�
//============================================================================================
static const BMPWIN_DAT BmpData[] =
{
	{	// ���t�P
		GF_BGL_FRAME0_M, WIN_TIME1_PX, WIN_TIME1_PY,
		WIN_TIME1_SX, WIN_TIME1_SY, WIN_TIME1_PAL, WIN_TIME1_CGX
	},
	{	// ���P
		GF_BGL_FRAME0_M, WIN_STR1_PX, WIN_STR1_PY,
		WIN_STR1_SX, WIN_STR1_SY, WIN_STR1_PAL, WIN_STR1_CGX
	},
	{	// ���t�Q
		GF_BGL_FRAME1_M, WIN_TIME2_PX, WIN_TIME2_PY,
		WIN_TIME2_SX, WIN_TIME2_SY, WIN_TIME2_PAL, WIN_TIME2_CGX
	},
	{	// ���Q
		GF_BGL_FRAME1_M, WIN_STR2_PX, WIN_STR2_PY,
		WIN_STR2_SX, WIN_STR2_SY, WIN_STR2_PAL, WIN_STR2_CGX
	}
};


//--------------------------------------------------------------------------------------------
/**
 * BMP�ǉ�
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FantasyNote_BmpAdd( FNOTE_WORK * wk )
{
	u32	i;

	for( i=0; i<WIN_MAX; i++ ){
		GF_BGL_BmpWinAddEx( wk->bgl, &wk->win[i], &BmpData[i] );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * BMP�폜
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FantasyNote_BmpFree( FNOTE_WORK * wk )
{
	u32	i;

	for( i=0; i<WIN_MAX; i++ ){
		GF_BGL_BmpWinDel( &wk->win[i] );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * ������\��
 *
 * @param	wk		���[�N
 * @param	flg		�\������BMP�̃t���O
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FantasyNote_BmpPut( FNOTE_WORK * wk, u32 flg )
{
	GF_BGL_BMPWIN * time;
	GF_BGL_BMPWIN * info;

	if( flg == 0 ){
		time = &wk->win[WIN_TIME1];
		info = &wk->win[WIN_STR1];
	}else{
		time = &wk->win[WIN_TIME2];
		info = &wk->win[WIN_STR2];
	}

	GF_BGL_BmpWinDataFill( time, 0 );
	GF_BGL_BmpWinDataFill( info, 0 );

	if( FNOTE_HederPut( wk, time, info ) == TRUE ){
		FNOTE_ActionPut( wk, info );
		FNOTE_PokemonPut( wk, info );
		FNOTE_TrainerPut( wk, info );
		FNOTE_SioPut( wk, info );
	}

	GF_BGL_BmpWinOnVReq( time );
	GF_BGL_BmpWinOnVReq( info );
}


static u8 FNOTE_HederPut( FNOTE_WORK * wk, GF_BGL_BMPWIN * time, GF_BGL_BMPWIN * info )
{
	FNOTE_WK_START	mem;
	STRBUF * str;
	u32	siz;

	FNOTE_DataGet( wk->dat, &mem, FNOTE_TYPE_START, wk->page );

	if( mem.year == 0 && mem.month == 0 && mem.day == 0 ){
		return FALSE;
	}

	// ���t
	str = MSGMAN_AllocString( wk->mman, msg_fnote_001 );
	WORDSET_RegisterNumber(
		wk->wset, 0, mem.month, 2, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	WORDSET_RegisterNumber(
		wk->wset, 1, mem.day, 2, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
	STRBUF_Delete( str );
	GF_STR_PrintColor( time, FONT_SYSTEM, wk->msg_buf, 0, 0, MSG_NO_PUT, COL_N_BLACK, NULL );
	// �j��
	siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, wk->msg_buf, 0 );
	str = MSGMAN_AllocString( wk->mman, msg_fnote_010+mem.week );
	GF_STR_PrintColor(
		time, FONT_SYSTEM, str, siz+WEEK_SPC_X, 0, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );

	// �X�^�[�g�I
	str = MSGMAN_AllocString( wk->mman, msg_fnote_000 );
	WORDSET_RegisterPlaceName( wk->wset, 0, ZoneData_GetPlaceNameID(mem.start) );

	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
	GF_STR_PrintColor( info, FONT_SYSTEM, wk->msg_buf, 0, 0, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );

	return TRUE;
}

static void FNOTE_ActionPut( FNOTE_WORK * wk, GF_BGL_BMPWIN * info )
{
	FNOTE_WK_ACTION	mem[FNOTE_ACTION_MAX];
	u32	i;

	FNOTE_DataGet( wk->dat, &mem[0], FNOTE_TYPE_ACTION, wk->page );

	for( i=0; i<FNOTE_ACTION_MAX; i++ ){
		switch( mem[i].id ){
		case 0:						// �f�[�^�Ȃ�
			return;

		case FNOTE_ID_MYHOUSE:		// �s���F����
			FNOTE_ActionHouseDataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_LABO:			// �s���F������
			FNOTE_ActionLaboDataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_POKECENTER:	// �s���F�|�P�����Z���^�[
			FNOTE_ActionPokeCenterDataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_FDSHOP_BUY:	// �s���F�V���b�v�E����
			FNOTE_ActionShopBuyDataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_FDSHOP_BUY2:	// �s���F�V���b�v�E�����i�����j
			FNOTE_ActionShopBuy2DataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_FDSHOP_SALE:	// �s���F�V���b�v�E����
			FNOTE_ActionShopSaleDataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_FDSHOP_SALE2:	// �s���F�V���b�v�E����i�����j
			FNOTE_ActionShopSale2DataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_FDSHOP_TRADE:	// �s���F�V���b�v�E����
			FNOTE_ActionShopTradeDataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_GYMBEFORE:	// �s���F�W���i���[�_�[��|���O�j
			FNOTE_ActionGymBeforeDataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_GYMAFTER:		// �s���F�W���i���[�_�[��|������j
			FNOTE_ActionGymAfterDataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_SITENNOU:		// �s���F�l�V��
			FNOTE_ActionSitennouDataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_CHAMPION:		// �s���F�`�����s�I��
			FNOTE_ActionChampionDataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_CITY:			// �s���F�X
			FNOTE_ActionCityDataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_DUNGEON:		// �s���F�_���W����
			FNOTE_ActionDungeonDataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_BUILD:		// �s���F����
			FNOTE_ActionBuildDataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_GAMECORNER:		// �s���F�Q�[���R�[�i�[
			FNOTE_ActionGameCornerDataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_SAFARIZONE:		// �s���F�T�t�@���]�[��
			FNOTE_ActionSafariDataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_ITEMGET:		// �s���F�A�C�e���擾
			FNOTE_ActionItemGetDataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_IWAKUDAKI:	// �s���F�Z�E���킭����
			FNOTE_ActionIwakudakiDataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_IAIGIRI:		// �s���F�Z�E����������
			FNOTE_ActionIaigiriDataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_SORAWOTOBU:	// �s���F�Z�E������Ƃ�
			FNOTE_ActionSorawotobuDataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_KIRIBARAI:	// �s���F�Z�E����΂炢
			FNOTE_ActionKiribaraiDataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_KAIRIKI:		// �s���F�Z�E�����肫
			FNOTE_ActionKairikiDataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_NAMINORI:		// �s���F�Z�E�Ȃ݂̂�
			FNOTE_ActionNaminoriDataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_ROCKCLIMB:	// �s���F�Z�E���b�N�N���C��
			FNOTE_ActionRockckimbDataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_TAKINOBORI:	// �s���F�Z�E�����̂ڂ�
			FNOTE_ActionTakinoboriDataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_FLASH:		// �s���F�Z�E�t���b�V��
			FNOTE_ActionFlashDataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_TELEPORT:		// �s���F�Z�E�e���|�[�g
			FNOTE_ActionTeleportDataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_ANAWOHORU:	// �s���F�Z�E���Ȃ��ق�
			FNOTE_ActionAnawohoruDataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_AMAIKAORI:	// �s���F�Z�E���܂�������
			FNOTE_ActionAmiaikaoriDataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_TAMAGOUMI:	// �s���F�Z�E�^�}�S����
			FNOTE_ActionTamagoumiDataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_MIRUKUNOMI:	// �s���F�Z�E�~���N�̂�
			FNOTE_ActionMilknomiDataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_UG_FOSSIL:	// �s���F�n���E���Ό@��
			FNOTE_ActionUGFossilDataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_UG_BASE:		// �s���F�n���E�閧��n
			FNOTE_ActionUGBaseDataPut( wk, info, &mem[i], i );
			break;
		}
	}
}

static void FNOTE_PokemonPut( FNOTE_WORK * wk, GF_BGL_BMPWIN * info )
{
	FNOTE_WK_POKE	mem;

	FNOTE_DataGet( wk->dat, &mem, FNOTE_TYPE_POKEMON, wk->page );

	switch( mem.id ){
	case 0:						// �f�[�^�Ȃ�
		return;

	case FNOTE_ID_POKEGET:		// �|�P�����F�ߊl
		FNOTE_PokeGetDataPut( wk, info, &mem );
		break;

	case FNOTE_ID_POKEDOWN:		// �|�P�����F�|����
		FNOTE_PokeDownDataPut( wk, info, &mem );
		break;
	}
}

static void FNOTE_TrainerPut( FNOTE_WORK * wk, GF_BGL_BMPWIN * info )
{
	FNOTE_WK_TRAINER	mem;
	STRBUF * str;
	u32	i;

	FNOTE_DataGet( wk->dat, &mem, FNOTE_TYPE_TRAINER, wk->page );

	if( mem.id == 0 ){ return; }

	{
		STRBUF * str;
		
		// �n��
		str = MSGDAT_GetStrDirectAlloc(
				ARC_MSG, NARC_msg_place_name_dat,
				ZoneData_GetPlaceNameID(mem.map), HEAPID_FANTASYNOTE );
		i = STRBUF_GetLen( str );
		STRBUF_Delete( str );

		// �g���[�i�[��
		// ���C�o��
		if( TT_TrainerDataParaGet( mem.trid, ID_TD_tr_type ) == TRTYPE_RIVAL ){
			str = MSGMAN_AllocString( wk->mman, msg_fnote_304 );
			WORDSET_RegisterRivalName( wk->wset, 1, wk->sv );
			WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
			i += STRBUF_GetLen( wk->msg_buf );
			STRBUF_Delete( str );
		// ����ȊO
		}else{
			str = MSGDAT_GetStrDirectAlloc(
					ARC_MSG, NARC_msg_trname_dat, mem.trid, HEAPID_FANTASYNOTE );
			i += STRBUF_GetLen( str );
			STRBUF_Delete( str );
			WORDSET_RegisterTrainerName( wk->wset, 1, mem.trid );
		}
	}

	if( i <= 10 ){
		str = MSGMAN_AllocString( wk->mman, msg_fnote_300 );
	}else if( i <= 12 ){
		str = MSGMAN_AllocString( wk->mman, msg_fnote_301 );
	}else if( i <= 14 ){
		str = MSGMAN_AllocString( wk->mman, msg_fnote_302 );
	}else{
		str = MSGMAN_AllocString( wk->mman, msg_fnote_303 );
	}

	WORDSET_RegisterPlaceName( wk->wset, 0, ZoneData_GetPlaceNameID(mem.map) );
	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
	GF_STR_PrintColor(
		info, FONT_SYSTEM, wk->msg_buf, 0, TRAINER_PY, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

static void FNOTE_SioPut( FNOTE_WORK * wk, GF_BGL_BMPWIN * info )
{
	FNOTE_WK_SIO	mem[FNOTE_SIO_MAX];
	u32	i;

	FNOTE_DataGet( wk->dat, &mem[0], FNOTE_TYPE_SIO, wk->page );

	for( i=0; i<FNOTE_SIO_MAX; i++ ){
		switch( mem[i].id ){
		case 0:
			return;

		case FNOTE_ID_SB_SINGLE:		// �ʐM�F�ʐM�ΐ�E�V���O��
			FNOTE_SioBtlSingleDataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_SB_DOUBLE:		// �ʐM�F�ʐM�ΐ�E�_�u��
			FNOTE_SioBtlDoubleDataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_SB_MULTI:			// �ʐM�F�ʐM�ΐ�E�}���`
			FNOTE_SioBtlMultiDataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_SB_MIX1:			// �ʐM�F�ʐM�ΐ�E�~�b�N�X1vs1
			FNOTE_SioBtlMix1DataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_SB_MIX2:			// �ʐM�F�ʐM�ΐ�E�~�b�N�X2vs2
			FNOTE_SioBtlMix2DataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_U_GREETING:		// �ʐM�F���j�I�����[���E���A
			FNOTE_SioUnionGreetDataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_U_POKECHG:		// �ʐM�F���j�I�����[���E����
			FNOTE_SioUnionChgDataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_U_PICTURE:		// �ʐM�F���j�I�����[���E���G����
			FNOTE_SioUnionPictureDataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_U_MLTCHG:			// �ʐM�F���j�I�����[���E�����l����
			FNOTE_SioUnionMultiChgDataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_U_TRANSCEIVER:	// �ʐM�F���j�I�����[���E�g�����V�[�o�[
			FNOTE_SioUnionTransceiverDataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_U_BATTLE:			// �ʐM�F���j�I�����[���E�ΐ�
			FNOTE_SioUnionBtlDataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_RECORD:			// �ʐM�F���R�[�h�R�[�i�[
			FNOTE_SioRecordDataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_CONTEST:			// �ʐM�F�R���e�X�g
			FNOTE_SioContestDataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_PORUTO:			// �ʐM�F�|���g�쐬
			FNOTE_SioPorutoDataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_GTC:				// �ʐM�FGTC
			FNOTE_SioGtcDataPut( wk, info, &mem[i], i );
			break;

		case FNOTE_ID_BTLTOWER:			// �ʐM�F�o�g���^���[
			FNOTE_SioBtlTowerDataPut( wk, info, &mem[i], i );
			break;
		}
	}
}


// �s���F����
static void FNOTE_ActionHouseDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos )
{
	STRBUF * str = MSGMAN_AllocString( wk->mman, msg_fnote_100 );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, str, 0, ACTION_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �s���F������
static void FNOTE_ActionLaboDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos )
{
	STRBUF * str = MSGMAN_AllocString( wk->mman, msg_fnote_101 );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, str, 0, ACTION_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �s���F�|�P�����Z���^�[
static void FNOTE_ActionPokeCenterDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos )
{
	STRBUF * str = MSGMAN_AllocString( wk->mman, msg_fnote_110 );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, str, 0, ACTION_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �s���F�V���b�v�E����
static void FNOTE_ActionShopBuyDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos )
{
	STRBUF * str = MSGMAN_AllocString( wk->mman, msg_fnote_120 );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, str, 0, ACTION_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �s���F�V���b�v�E�����i�����j
static void FNOTE_ActionShopBuy2DataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos )
{
	STRBUF * str = MSGMAN_AllocString( wk->mman, msg_fnote_121 );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, str, 0, ACTION_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �s���F�V���b�v�E����
static void FNOTE_ActionShopSaleDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos )
{
	STRBUF * str = MSGMAN_AllocString( wk->mman, msg_fnote_122 );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, str, 0, ACTION_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �s���F�V���b�v�E����i�����j
static void FNOTE_ActionShopSale2DataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos )
{
	STRBUF * str = MSGMAN_AllocString( wk->mman, msg_fnote_123 );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, str, 0, ACTION_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �s���F�V���b�v�E����
static void FNOTE_ActionShopTradeDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos )
{
	STRBUF * str = MSGMAN_AllocString( wk->mman, msg_fnote_124 );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, str, 0, ACTION_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �s���F�W���i���[�_�[��|���O�j
static void FNOTE_ActionGymBeforeDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos )
{
	STRBUF * str = MSGMAN_AllocString( wk->mman, msg_fnote_130 );
	WORDSET_RegisterGymName( wk->wset, 0, mem->map );
	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->msg_buf, 0, ACTION_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �s���F�W���i���[�_�[��|������j
static void FNOTE_ActionGymAfterDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos )
{
	STRBUF * str = MSGMAN_AllocString( wk->mman, msg_fnote_131 );
	WORDSET_RegisterGymName( wk->wset, 0, mem->map );
	WORDSET_RegisterTrainerName( wk->wset, 1, mem->trainer );
	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->msg_buf, 0, ACTION_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �s���F�l�V��
static void FNOTE_ActionSitennouDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos )
{
	STRBUF * str = MSGMAN_AllocString( wk->mman, msg_fnote_132 );
	WORDSET_RegisterTrainerName( wk->wset, 0, mem->trainer );
	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->msg_buf, 0, ACTION_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �s���F�`�����s�I��
static void FNOTE_ActionChampionDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos )
{
	STRBUF * str = MSGMAN_AllocString( wk->mman, msg_fnote_133 );
	WORDSET_RegisterTrainerName( wk->wset, 0, mem->trainer );
	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->msg_buf, 0, ACTION_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �s���F�X
static void FNOTE_ActionCityDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos )
{
	STRBUF * str = MSGMAN_AllocString( wk->mman, msg_fnote_140 );
	WORDSET_RegisterPlaceName( wk->wset, 0, ZoneData_GetPlaceNameID(mem->map) );
	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->msg_buf, 0, ACTION_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �s���F�_���W����
static void FNOTE_ActionDungeonDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos )
{
	STRBUF * str;
	u32	name;

	name = mem->map;
	// �u���ɂ܂̂͂ł񂵂�v�u�L�b�T�L����ł�v�u�^�^�������Ă���v�͓���
	if( name == MAPNAME_D2HATUDEN || name == MAPNAME_D20KISSAKI || name == MAPNAME_D4TATARA ){
		str = MSGMAN_AllocString( wk->mman, msg_fnote_142 );
	}else{
		str = MSGMAN_AllocString( wk->mman, msg_fnote_141 );
	}
	WORDSET_RegisterPlaceName( wk->wset, 0, name );
	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->msg_buf, 0, ACTION_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �s���F����
static void FNOTE_ActionBuildDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos )
{
	STRBUF * str;
	u32	name;

	name = mem->map;
	if( FNOTE_ExBuildPutTypeGet( name ) == 0 ){
		str = MSGMAN_AllocString( wk->mman, msg_fnote_142 );
	}else{
		str = MSGMAN_AllocString( wk->mman, msg_fnote_143 );
	}
	WORDSET_RegisterPlaceName( wk->wset, 0, name );
	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->msg_buf, 0, ACTION_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �s���F�Q�[���R�[�i�[
static void FNOTE_ActionGameCornerDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos )
{
	STRBUF * str = MSGMAN_AllocString( wk->mman, msg_fnote_144 );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, str, 0, ACTION_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �s���F�T�t�@���]�[��
static void FNOTE_ActionSafariDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos )
{
	STRBUF * str = MSGMAN_AllocString( wk->mman, msg_fnote_145 );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, str, 0, ACTION_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �s���F�A�C�e���擾
static void FNOTE_ActionItemGetDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos )
{
	STRBUF * str = MSGMAN_AllocString( wk->mman, msg_fnote_150 );
	WORDSET_RegisterItemName( wk->wset, 0, mem->item );
	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->msg_buf, 0, ACTION_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �s���F�Z�E���킭����
static void FNOTE_ActionIwakudakiDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos )
{
	STRBUF * str = MSGMAN_AllocString( wk->mman, msg_fnote_165 );
	WORDSET_RegisterPlaceName( wk->wset, 0, ZoneData_GetPlaceNameID(mem->map) );
	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->msg_buf, 0, ACTION_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �s���F�Z�E����������
static void FNOTE_ActionIaigiriDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos )
{
	STRBUF * str = MSGMAN_AllocString( wk->mman, msg_fnote_160 );
	WORDSET_RegisterPlaceName( wk->wset, 0, ZoneData_GetPlaceNameID(mem->map) );
	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->msg_buf, 0, ACTION_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �s���F�Z�E������Ƃ�
static void FNOTE_ActionSorawotobuDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos )
{
	STRBUF * str = MSGMAN_AllocString( wk->mman, msg_fnote_161 );
	WORDSET_RegisterPlaceName( wk->wset, 0, ZoneData_GetPlaceNameID(mem->map) );
	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->msg_buf, 0, ACTION_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �s���F�Z�E����΂炢
static void FNOTE_ActionKiribaraiDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos )
{
	STRBUF * str = MSGMAN_AllocString( wk->mman, msg_fnote_168 );
	WORDSET_RegisterPlaceName( wk->wset, 0, ZoneData_GetPlaceNameID(mem->map) );
	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->msg_buf, 0, ACTION_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �s���F�Z�E�����肫
static void FNOTE_ActionKairikiDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos )
{
	STRBUF * str = MSGMAN_AllocString( wk->mman, msg_fnote_163 );
	WORDSET_RegisterPlaceName( wk->wset, 0, ZoneData_GetPlaceNameID(mem->map) );
	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->msg_buf, 0, ACTION_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �s���F�Z�E�Ȃ݂̂�
static void FNOTE_ActionNaminoriDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos )
{
	STRBUF * str = MSGMAN_AllocString( wk->mman, msg_fnote_162 );
	WORDSET_RegisterPlaceName( wk->wset, 0, ZoneData_GetPlaceNameID(mem->map) );
	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->msg_buf, 0, ACTION_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �s���F�Z�E���b�N�N���C��
static void FNOTE_ActionRockckimbDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos )
{
	STRBUF * str = MSGMAN_AllocString( wk->mman, msg_fnote_167 );
	WORDSET_RegisterPlaceName( wk->wset, 0, ZoneData_GetPlaceNameID(mem->map) );
	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->msg_buf, 0, ACTION_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �s���F�Z�E�����̂ڂ�
static void FNOTE_ActionTakinoboriDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos )
{
	STRBUF * str = MSGMAN_AllocString( wk->mman, msg_fnote_166 );
	WORDSET_RegisterPlaceName( wk->wset, 0, ZoneData_GetPlaceNameID(mem->map) );
	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->msg_buf, 0, ACTION_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �s���F�Z�E�t���b�V��
static void FNOTE_ActionFlashDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos )
{
	STRBUF * str = MSGMAN_AllocString( wk->mman, msg_fnote_164 );
	WORDSET_RegisterPlaceName( wk->wset, 0, ZoneData_GetPlaceNameID(mem->map) );
	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->msg_buf, 0, ACTION_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �s���F�Z�E�e���|�[�g
static void FNOTE_ActionTeleportDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos )
{
	STRBUF * str = MSGMAN_AllocString( wk->mman, msg_fnote_172 );
	WORDSET_RegisterPlaceName( wk->wset, 0, ZoneData_GetPlaceNameID(mem->map) );
	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->msg_buf, 0, ACTION_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �s���F�Z�E���Ȃ��ق�
static void FNOTE_ActionAnawohoruDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos )
{
	STRBUF * str = MSGMAN_AllocString( wk->mman, msg_fnote_170 );
	WORDSET_RegisterPlaceName( wk->wset, 0, ZoneData_GetPlaceNameID(mem->map) );
	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->msg_buf, 0, ACTION_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �s���F�Z�E���܂�������
static void FNOTE_ActionAmiaikaoriDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos )
{
	STRBUF * str = MSGMAN_AllocString( wk->mman, msg_fnote_171 );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, str, 0, ACTION_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �s���F�Z�E�^�}�S����
static void FNOTE_ActionTamagoumiDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos )
{
	STRBUF * str = MSGMAN_AllocString( wk->mman, msg_fnote_173 );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, str, 0, ACTION_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �s���F�Z�E�~���N�̂�
static void FNOTE_ActionMilknomiDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos )
{
	STRBUF * str = MSGMAN_AllocString( wk->mman, msg_fnote_174 );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, str, 0, ACTION_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �s���F�n���E���Ό@��
static void FNOTE_ActionUGFossilDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos )
{
	STRBUF * str = MSGMAN_AllocString( wk->mman, msg_fnote_146 );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, str, 0, ACTION_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �s���F�n���E�閧��n
static void FNOTE_ActionUGBaseDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_ACTION * mem, u8 pos )
{
	STRBUF * str = MSGMAN_AllocString( wk->mman, msg_fnote_147 );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, str, 0, ACTION_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}


static void FNOTE_PokeMonsNameSet( FNOTE_WORK * wk, u16 mons, u8 sex, u8 buf_id )
{
	POKEMON_PARAM * pp = PokemonParam_AllocWork( HEAPID_FANTASYNOTE );

	PokeParaSetSexChr( pp, mons, 1, POW_RND, sex, 0, 0 );
	WORDSET_RegisterPokeMonsName( wk->wset, buf_id, PPPPointerGet( pp ) );
	sys_FreeMemoryEz( pp );
}


// �|�P�����F�ߊl
static void FNOTE_PokeGetDataPut( FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_POKE * mem )
{
	STRBUF * str;

	switch( mem->type ){
	case 0:
		str = MSGMAN_AllocString( wk->mman, msg_fnote_200 );
		break;
	case 1:
		str = MSGMAN_AllocString( wk->mman, msg_fnote_201 );
		break;
	default:
		if( mem->sex == PARA_MALE ){
			str = MSGMAN_AllocString( wk->mman, msg_fnote_202 );
		}else if( mem->sex == PARA_FEMALE ){
			str = MSGMAN_AllocString( wk->mman, msg_fnote_203 );
		}else{
			str = MSGMAN_AllocString( wk->mman, msg_fnote_200 );
		}
	}

	FNOTE_PokeMonsNameSet( wk, mem->mons, mem->sex, 0 );
	WORDSET_RegisterTimeType( wk->wset, 1, mem->time );

	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->msg_buf, 0, POKEMON_PY, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �|�P�����F�|����
static void FNOTE_PokeDownDataPut( FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_POKE * mem )
{
	STRBUF * str;

	switch( mem->type ){
	case 0:
		str = MSGMAN_AllocString( wk->mman, msg_fnote_210 );
		break;
	case 1:
		str = MSGMAN_AllocString( wk->mman, msg_fnote_211 );
		break;
	default:
		if( mem->sex == PARA_MALE ){
			str = MSGMAN_AllocString( wk->mman, msg_fnote_212 );
		}else if( mem->sex == PARA_FEMALE ){
			str = MSGMAN_AllocString( wk->mman, msg_fnote_213 );
		}else{
			str = MSGMAN_AllocString( wk->mman, msg_fnote_210 );
		}
	}

	FNOTE_PokeMonsNameSet( wk, mem->mons, mem->sex, 0 );
	WORDSET_RegisterTimeType( wk->wset, 1, mem->time );

	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->msg_buf, 0, POKEMON_PY, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}



static void FNOTE_StrWordSet( FNOTE_WORK * wk, STRCODE * str, u8 sex, u8 buf_id )
{
	STRBUF * buf = STRBUF_Create( 32, HEAPID_FANTASYNOTE );

	STRBUF_SetStringCode( buf, str );
	WORDSET_RegisterWord( wk->wset, buf_id, buf, sex, TRUE, PM_LANG );
	STRBUF_Delete( buf );
}


// �ʐM�F�ʐM�ΐ�E�V���O��
static void FNOTE_SioBtlSingleDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_SIO * mem, u8 pos )
{
	STRBUF * str;
	
	switch( mem->result ){
	case FNOTE_RESULT_WIN:		// ����
		str = MSGMAN_AllocString( wk->mman, msg_fnote_400 );
		break;
	case FNOTE_RESULT_LOSE:		// ����
		str = MSGMAN_AllocString( wk->mman, msg_fnote_401 );
		break;
	case FNOTE_RESULT_DRAW:		// ��������
		str = MSGMAN_AllocString( wk->mman, msg_fnote_402 );
		break;
	}

	FNOTE_StrWordSet( wk, mem->name1, mem->sex1, 0 );
	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->msg_buf, 0, SIO_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �ʐM�F�ʐM�ΐ�E�_�u��
static void FNOTE_SioBtlDoubleDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_SIO * mem, u8 pos )
{
	STRBUF * str;
	
	switch( mem->result ){
	case FNOTE_RESULT_WIN:		// ����
		str = MSGMAN_AllocString( wk->mman, msg_fnote_403 );
		break;
	case FNOTE_RESULT_LOSE:		// ����
		str = MSGMAN_AllocString( wk->mman, msg_fnote_404 );
		break;
	case FNOTE_RESULT_DRAW:		// ��������
		str = MSGMAN_AllocString( wk->mman, msg_fnote_405 );
		break;
	}

	FNOTE_StrWordSet( wk, mem->name1, mem->sex1, 0 );
	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->msg_buf, 0, SIO_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �ʐM�F�ʐM�ΐ�E�}���`
static void FNOTE_SioBtlMultiDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_SIO * mem, u8 pos )
{
	STRBUF * str;
	
	switch( mem->result ){
	case FNOTE_RESULT_WIN:		// ����
		str = MSGMAN_AllocString( wk->mman, msg_fnote_406 );
		break;
	case FNOTE_RESULT_LOSE:		// ����
		str = MSGMAN_AllocString( wk->mman, msg_fnote_407 );
		break;
	case FNOTE_RESULT_DRAW:		// ��������
		str = MSGMAN_AllocString( wk->mman, msg_fnote_408 );
		break;
	}

	FNOTE_StrWordSet( wk, mem->name1, mem->sex1, 0 );
	FNOTE_StrWordSet( wk, mem->name2, mem->sex2, 1 );
	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->msg_buf, 0, SIO_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �ʐM�F�ʐM�ΐ�E�~�b�N�X1vs1
static void FNOTE_SioBtlMix1DataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_SIO * mem, u8 pos )
{
	STRBUF * str;
	
	switch( mem->result ){
	case FNOTE_RESULT_WIN:		// ����
		str = MSGMAN_AllocString( wk->mman, msg_fnote_409 );
		break;
	case FNOTE_RESULT_LOSE:		// ����
		str = MSGMAN_AllocString( wk->mman, msg_fnote_410 );
		break;
	case FNOTE_RESULT_DRAW:		// ��������
		str = MSGMAN_AllocString( wk->mman, msg_fnote_411 );
		break;
	}

	FNOTE_StrWordSet( wk, mem->name1, mem->sex1, 0 );
	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->msg_buf, 0, SIO_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �ʐM�F�ʐM�ΐ�E�~�b�N�X2vs2
static void FNOTE_SioBtlMix2DataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_SIO * mem, u8 pos )
{
	STRBUF * str;
	
	switch( mem->result ){
	case FNOTE_RESULT_WIN:		// ����
		str = MSGMAN_AllocString( wk->mman, msg_fnote_412 );
		break;
	case FNOTE_RESULT_LOSE:		// ����
		str = MSGMAN_AllocString( wk->mman, msg_fnote_413 );
		break;
	case FNOTE_RESULT_DRAW:		// ��������
		str = MSGMAN_AllocString( wk->mman, msg_fnote_414 );
		break;
	}

	FNOTE_StrWordSet( wk, mem->name1, mem->sex1, 0 );
	FNOTE_StrWordSet( wk, mem->name2, mem->sex2, 1 );
	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->msg_buf, 0, SIO_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �ʐM�F���j�I�����[���E���A
static void FNOTE_SioUnionGreetDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_SIO * mem, u8 pos )
{
	STRBUF * str = MSGMAN_AllocString( wk->mman, msg_fnote_420 );
	FNOTE_StrWordSet( wk, mem->name1, mem->sex1, 0 );
	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->msg_buf, 0, SIO_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �ʐM�F���j�I�����[���E����
static void FNOTE_SioUnionChgDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_SIO * mem, u8 pos )
{
	STRBUF * str = MSGMAN_AllocString( wk->mman, msg_fnote_421 );
	FNOTE_StrWordSet( wk, mem->name1, mem->sex1, 0 );
	FNOTE_StrWordSet( wk, mem->nickname, mem->poke_sex, 1 );
	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->msg_buf, 0, SIO_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �ʐM�F���j�I�����[���E���G����
static void FNOTE_SioUnionPictureDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_SIO * mem, u8 pos )
{
	STRBUF * str = MSGMAN_AllocString( wk->mman, msg_fnote_422 );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, str, 0, SIO_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �ʐM�F���j�I�����[���E�����l����
static void FNOTE_SioUnionMultiChgDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_SIO * mem, u8 pos )
{
	STRBUF * str = MSGMAN_AllocString( wk->mman, msg_fnote_423 );
	FNOTE_StrWordSet( wk, mem->nickname, mem->poke_sex, 0 );
	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->msg_buf, 0, SIO_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �ʐM�F���j�I�����[���E�g�����V�[�o�[
static void FNOTE_SioUnionTransceiverDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_SIO * mem, u8 pos )
{
	STRBUF * str = MSGMAN_AllocString( wk->mman, msg_fnote_424 );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, str, 0, SIO_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �ʐM�F���j�I�����[���E�ΐ�
static void FNOTE_SioUnionBtlDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_SIO * mem, u8 pos )
{
	STRBUF * str;
	
	switch( mem->result ){
	case FNOTE_RESULT_WIN:		// ����
		str = MSGMAN_AllocString( wk->mman, msg_fnote_425 );
		break;
	case FNOTE_RESULT_LOSE:		// ����
		str = MSGMAN_AllocString( wk->mman, msg_fnote_426 );
		break;
	case FNOTE_RESULT_DRAW:		// ��������
		str = MSGMAN_AllocString( wk->mman, msg_fnote_427 );
		break;
	}

	FNOTE_StrWordSet( wk, mem->name1, mem->sex1, 0 );
	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->msg_buf, 0, SIO_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �ʐM�F���R�[�h�R�[�i�[
static void FNOTE_SioRecordDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_SIO * mem, u8 pos )
{
	STRBUF * str = MSGMAN_AllocString( wk->mman, msg_fnote_440 );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, str, 0, SIO_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �ʐM�F�R���e�X�g
static void FNOTE_SioContestDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_SIO * mem, u8 pos )
{
	STRBUF * str = MSGMAN_AllocString( wk->mman, msg_fnote_450 );
	WORDSET_RegisterNumber(
		wk->wset, 0, mem->result, 1, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->msg_buf, 0, SIO_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �ʐM�F�|���g�쐬
static void FNOTE_SioPorutoDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_SIO * mem, u8 pos )
{
	STRBUF * str = MSGMAN_AllocString( wk->mman, msg_fnote_460 );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, str, 0, SIO_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �ʐM�FGTC
static void FNOTE_SioGtcDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_SIO * mem, u8 pos )
{
	STRBUF * str = MSGMAN_AllocString( wk->mman, msg_fnote_470 );
	FNOTE_StrWordSet( wk, mem->name1, mem->sex1, 0 );
	FNOTE_StrWordSet( wk, mem->nickname, mem->poke_sex, 1 );
	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->msg_buf, 0, SIO_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}

// �ʐM�F�o�g���^���[
static void FNOTE_SioBtlTowerDataPut(
				FNOTE_WORK * wk, GF_BGL_BMPWIN * win, FNOTE_WK_SIO * mem, u8 pos )
{
	STRBUF * str = MSGMAN_AllocString( wk->mman, msg_fnote_480 );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, str, 0, SIO_PY+pos*16, MSG_NO_PUT, COL_N_BLACK, NULL );
	STRBUF_Delete( str );
}
























/*
void Debug_FNOTE_BmpPut( FNOTE_WORK * wk, u32 flg )
{
	GF_BGL_BMPWIN * time;
	GF_BGL_BMPWIN * info;
	STRBUF * str;

	if( flg == 0 ){
		time = &wk->win[WIN_TIME1];
		info = &wk->win[WIN_STR1];

		GF_BGL_BmpWinDataFill( time, 0 );
		GF_BGL_BmpWinDataFill( info, 0 );

		// ���t
		str = MSGMAN_AllocString( wk->mman, msg_fnote_001 );
		WORDSET_RegisterNumber(
			wk->wset, 0, 7, 2, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		WORDSET_RegisterNumber(
			wk->wset, 1, 18, 2, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
		STRBUF_Delete( str );
		GF_STR_PrintColor( time, FONT_SYSTEM, wk->msg_buf, 0, 0, MSG_NO_PUT, COL_N_BLACK, NULL );
		// �X�^�[�g�I
		str = MSGMAN_AllocString( wk->mman, msg_fnote_000 );
		GF_STR_PrintColor( info, FONT_SYSTEM, str, 0, 0, MSG_NO_PUT, COL_N_BLACK, NULL );
		STRBUF_Delete( str );
		// �s���P
		str = MSGMAN_AllocString( wk->mman, msg_fnote_100 );
		GF_STR_PrintColor( info, FONT_SYSTEM, str, 0, 16, MSG_NO_PUT, COL_N_BLACK, NULL );
		STRBUF_Delete( str );
		// �s���Q
		str = MSGMAN_AllocString( wk->mman, msg_fnote_121 );
		GF_STR_PrintColor( info, FONT_SYSTEM, str, 0, 32, MSG_NO_PUT, COL_N_BLACK, NULL );
		STRBUF_Delete( str );
		// �s���R
		str = MSGMAN_AllocString( wk->mman, msg_fnote_144 );
		GF_STR_PrintColor( info, FONT_SYSTEM, str, 0, 48, MSG_NO_PUT, COL_N_BLACK, NULL );
		STRBUF_Delete( str );
		// �s���S
		str = MSGMAN_AllocString( wk->mman, msg_fnote_171 );
		GF_STR_PrintColor( info, FONT_SYSTEM, str, 0, 64, MSG_NO_PUT, COL_N_BLACK, NULL );
		STRBUF_Delete( str );
		// �|�P����
		str = MSGMAN_AllocString( wk->mman, msg_fnote_200 );
		GF_STR_PrintColor( info, FONT_SYSTEM, str, 0, 80, MSG_NO_PUT, COL_N_BLACK, NULL );
		STRBUF_Delete( str );
		// �g���[�i�[
		str = MSGMAN_AllocString( wk->mman, msg_fnote_300 );
		GF_STR_PrintColor( info, FONT_SYSTEM, str, 0, 96, MSG_NO_PUT, COL_N_BLACK, NULL );
		STRBUF_Delete( str );
		// �ʐM
		str = MSGMAN_AllocString( wk->mman, msg_fnote_460 );
		GF_STR_PrintColor( info, FONT_SYSTEM, str, 0, 112, MSG_NO_PUT, COL_N_BLACK, NULL );
		STRBUF_Delete( str );

	}else{
		time = &wk->win[WIN_TIME2];
		info = &wk->win[WIN_STR2];

		GF_BGL_BmpWinDataFill( time, 0 );
		GF_BGL_BmpWinDataFill( info, 0 );

		// ���t
		str = MSGMAN_AllocString( wk->mman, msg_fnote_001 );
		WORDSET_RegisterNumber(
			wk->wset, 0, 11, 2, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		WORDSET_RegisterNumber(
			wk->wset, 1, 3, 2, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
		STRBUF_Delete( str );
		GF_STR_PrintColor( time, FONT_SYSTEM, wk->msg_buf, 0, 0, MSG_NO_PUT, COL_N_BLACK, NULL );
		// �X�^�[�g�I
		str = MSGMAN_AllocString( wk->mman, msg_fnote_000 );
		GF_STR_PrintColor( info, FONT_SYSTEM, str, 0, 0, MSG_NO_PUT, COL_N_BLACK, NULL );
		STRBUF_Delete( str );
		// �s���P
		str = MSGMAN_AllocString( wk->mman, msg_fnote_101 );
		GF_STR_PrintColor( info, FONT_SYSTEM, str, 0, 16, MSG_NO_PUT, COL_N_BLACK, NULL );
		STRBUF_Delete( str );
		// �s���Q
		str = MSGMAN_AllocString( wk->mman, msg_fnote_110 );
		GF_STR_PrintColor( info, FONT_SYSTEM, str, 0, 32, MSG_NO_PUT, COL_N_BLACK, NULL );
		STRBUF_Delete( str );
		// �s���R
		str = MSGMAN_AllocString( wk->mman, msg_fnote_145 );
		GF_STR_PrintColor( info, FONT_SYSTEM, str, 0, 48, MSG_NO_PUT, COL_N_BLACK, NULL );
		STRBUF_Delete( str );
		// �s���S
		str = MSGMAN_AllocString( wk->mman, msg_fnote_173 );
		GF_STR_PrintColor( info, FONT_SYSTEM, str, 0, 64, MSG_NO_PUT, COL_N_BLACK, NULL );
		STRBUF_Delete( str );
		// �|�P����
		str = MSGMAN_AllocString( wk->mman, msg_fnote_203 );
		GF_STR_PrintColor( info, FONT_SYSTEM, str, 0, 80, MSG_NO_PUT, COL_N_BLACK, NULL );
		STRBUF_Delete( str );
		// �g���[�i�[
		str = MSGMAN_AllocString( wk->mman, msg_fnote_302 );
		GF_STR_PrintColor( info, FONT_SYSTEM, str, 0, 96, MSG_NO_PUT, COL_N_BLACK, NULL );
		STRBUF_Delete( str );
		// �ʐM
		str = MSGMAN_AllocString( wk->mman, msg_fnote_480 );
		GF_STR_PrintColor( info, FONT_SYSTEM, str, 0, 112, MSG_NO_PUT, COL_N_BLACK, NULL );
		STRBUF_Delete( str );
	}

	GF_BGL_BmpWinOnVReq( time );
	GF_BGL_BmpWinOnVReq( info );
}
*/
