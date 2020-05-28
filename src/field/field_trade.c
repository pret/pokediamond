//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		field_trade.c
 *	@brief		�Q�[��������
 *	@author		tomoya takahashi
 *	@data		2006.05.15
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "common.h"
#include "system/arc_util.h"
#include "include/msgdata/msg_fld_trade.h"
#include "include/msgdata/msg.naix"
#include "include/gflib/strbuf_family.h"
#include "fieldsys.h"
#include "field_event.h"
#include "ev_mapchange.h"
#include "ev_time.h"
#include "savedata/zukanwork.h"
#include "savedata/get_poke.h"
#include "include/poketool/poke_memo.h"
#include "zonedata.h"

#define  __FIELD_TRADE_H_GLOBAL
#include "field_trade.h"

//-----------------------------------------------------------------------------
/**
 *					�R�[�f�B���O�K��
 *		���֐���
 *				�P�����ڂ͑啶������ȍ~�͏������ɂ���
 *		���ϐ���
 *				�E�ϐ�����
 *						const�ɂ� c_ ��t����
 *						static�ɂ� s_ ��t����
 *						�|�C���^�ɂ� p_ ��t����
 *						�S�č��킳��� csp_ �ƂȂ�
 *				�E�O���[�o���ϐ�
 *						�P�����ڂ͑啶��
 *				�E�֐����ϐ�
 *						�������Ɓh�Q�h�Ɛ������g�p���� �֐��̈���������Ɠ���
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
#define FLD_TRADE_GET_POKE_GMM(x)	(x)
#define FLD_TRADE_GET_OYA_GMM(x)	(TRADE_OYA_00+x)


//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�����|�P�����f�[�^
//=====================================
typedef struct {
	u32 monsno;			// �����X�^�[�i���o�[
	u32 hp_rnd;			// HP����
	u32 at_rnd;			// �U������
	u32 df_rnd;			// �h�䗐��
	u32 sp_rnd;			// ��������
	u32 sa_rnd;			// ���U����
	u32 sd_rnd;			// ���h����
	u32 speabino;		// ����\��
	u32	mons_id;		// ID
	u32 style;			// �������悳
	u32 beautiful;		// ��������
	u32 cute;			// ���킢��
	u32 clever;			// ��������
	u32 strong;			// �����܂���
	u32 mons_rnd;		// �ő̗���
	u32 item;			// �A�C�e��
	u32 oya_sex;		// �e����
	u32 fur;			// �щ�
	u32 world_code;		// �e�̍��R�[�h
	u32 change_monsno;	// �������郂���X�^�[�i���o�[
} FLD_TRADE_POKEDATA;


typedef struct _FLD_TRADE_WORK {
	FLD_TRADE_POKEDATA* p_pokedata;		// �����|�P�����f�[�^

	POKEMON_PARAM*		p_pp;			// �����|�P����
	MYSTATUS*			p_myste;		// ��������p�����[�^
	u32 trade_no;						// �����i���o�[
	u32 heapID;
};

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
static STRBUF* FLD_TradeGetGmm( u32 heapID, u32 idx );
static void FLD_TradeSetPokeParam( POKEMON_PARAM* p_pp, FLD_TRADE_POKEDATA* p_data, u32 lev, u32 trade_no, u32 heapID, u32 zone_id );



//----------------------------------------------------------------------------
/**
 *	@brief	���[�N�m��
 *
 *	@param	heapID		�q�[�vID
 *	@param	trade_no	�����ԍ�
 *
 *	@return	���[�N
 */
//-----------------------------------------------------------------------------
FLD_TRADE_WORK* FLD_TradeAlloc( u32 heapID, u32 trade_no )
{
	FLD_TRADE_WORK* p_work;
	STRBUF* str;
	STRCODE str_arry[ 128 ];

	GF_ASSERT( trade_no < FLD_TRADE_NUM );
	
	p_work = sys_AllocMemory( heapID, sizeof(FLD_TRADE_WORK) );
	memset( p_work, 0, sizeof(FLD_TRADE_WORK) );

	// �����f�[�^�ǂݍ���
	p_work->p_pokedata = ArcUtil_Load( ARC_FIELD_TRADE_POKE, trade_no, FALSE, heapID, ALLOC_TOP );

	
	p_work->heapID = heapID;
	p_work->trade_no = trade_no;

	// �����|�P�����f�[�^�쐬
	p_work->p_pp = PokemonParam_AllocWork( heapID );

	// �e�f�[�^�쐬
	p_work->p_myste = MyStatus_AllocWork( heapID );
	MyStatus_Init( p_work->p_myste );
	str = FLD_TradeGetGmm( heapID, FLD_TRADE_GET_OYA_GMM( trade_no ) );
	STRBUF_GetStringCode( str, str_arry, 128 );
	STRBUF_Delete(str);
	MyStatus_SetMyName( p_work->p_myste, str_arry );
	MyStatus_SetMySex( p_work->p_myste, p_work->p_pokedata->oya_sex );
	
	return p_work;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���[�N�j��
 *
 *	@param	p_work		
 */
//-----------------------------------------------------------------------------
void FLD_TradeDelete( FLD_TRADE_WORK* p_work )
{
	sys_FreeMemoryEz( p_work->p_pokedata );
	sys_FreeMemoryEz( p_work->p_pp );
	sys_FreeMemoryEz( p_work->p_myste );
	sys_FreeMemoryEz( p_work );
}

//----------------------------------------------------------------------------
/**
 *	@brief	��������|�P�����i���o�[�擾
 *
 *	@param	cp_work		���[�N
 *
 *	@return	�|�P�����i���o�[
 */
//-----------------------------------------------------------------------------
u32 FLD_TradeMonsno( const FLD_TRADE_WORK* cp_work )
{
	return cp_work->p_pokedata->monsno;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�����ɕK�v�ȃ|�P�����i���o�[�擾
 *
 *	@param	cp_work		���[�N
 *
 *	@return	�|�P�����i���o�[
 */
//-----------------------------------------------------------------------------
u32 FLD_TradeChangeMonsno( const FLD_TRADE_WORK* cp_work )
{
	return cp_work->p_pokedata->change_monsno;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�e���ʁ@�擾
 *
 *	@param	cp_work		���[�N
 *
 *	@return	����
 */
//-----------------------------------------------------------------------------
u32 FLD_TradeOyaSex( const FLD_TRADE_WORK* cp_work )
{
	return cp_work->p_pokedata->oya_sex;
}

//----------------------------------------------------------------------------
/**
 *	@brief	����
 *
 *	@param	p_fsys		�t�B�[���h�V�X�e��
 *	@param	p_work		�������[�N
 *	@param	party_pos	�p�[�e�B�[�|�W�V����
 */
//-----------------------------------------------------------------------------
void FLD_Trade( FIELDSYS_WORK * p_fsys, FLD_TRADE_WORK* p_work, int party_pos )
{
	POKEPARTY * party = SaveData_GetTemotiPokemon( p_fsys->savedata );

	// �������s
	PokeParty_SetMemberData( party, party_pos, p_work->p_pp );

	// �}�ӂɓo�^
	SaveData_GetPokeRegister( p_fsys->savedata, p_work->p_pp );
}

void FLD_TradeDemoDataMake( FIELDSYS_WORK * p_fsys, FLD_TRADE_WORK* p_work, int party_pos, DEMO_TRADE_PARAM* p_demo, POKEMON_PARAM* sendPoke, POKEMON_PARAM* recvPoke )
{
	POKEPARTY * party = SaveData_GetTemotiPokemon( p_fsys->savedata );
	POKEMON_PARAM* p_chg_poke;
	STRBUF* str;
	u32 lev;		// ���x��
	int time_zone;

	// ��������|�P����
	p_chg_poke = PokeParty_GetMemberPointer( party, party_pos );
	lev = PokeParaGet( p_chg_poke, ID_PARA_level, NULL );
	
	// �����|�P�����̍쐬
	FLD_TradeSetPokeParam( p_work->p_pp, p_work->p_pokedata, lev, p_work->trade_no, p_work->heapID, p_fsys->location->zone_id );

	// �f���p�̃|�P�����p�����[�^�Ɋi�[
	PokeCopyPPtoPP( p_chg_poke, sendPoke );
	PokeCopyPPtoPP( p_work->p_pp, recvPoke );

	// �f���f�[�^�쐬
	p_demo->sendPoke	= PPPPointerGet( sendPoke );
	p_demo->recvPoke	= PPPPointerGet( recvPoke );
	p_demo->partner	= p_work->p_myste;
	p_demo->seqFlag	= DEMO_TRADE_SEQ_FULL;
	p_demo->config		= SaveData_GetConfig( p_fsys->savedata );
	time_zone = EVTIME_GetTimeZone( p_fsys );
	if( (time_zone == TIMEZONE_MORNING) || 
		(time_zone == TIMEZONE_NOON) ){
		p_demo->bgType		= DEMO_TRADE_BGTYPE_MORNING;
	}else if( time_zone == TIMEZONE_EVENING ){
		p_demo->bgType		= DEMO_TRADE_BGTYPE_EVENING;
	}else{
		p_demo->bgType		= DEMO_TRADE_BGTYPE_NIGHT;
	}
}




//----------------------------------------------------------------------------
/**
 *	@brief	���b�Z�[�W�擾
 *	�j�����K�v
 */
//-----------------------------------------------------------------------------
static STRBUF* FLD_TradeGetGmm( u32 heapID, u32 idx )
{
	STRBUF* str;
	
	MSGDATA_MANAGER* msg_data = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_fld_trade_dat, heapID);
	str = MSGMAN_AllocString(msg_data, idx);
	MSGMAN_Delete(msg_data);
	return str;
}


//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����p�����Ƀf�[�^�̐ݒ�
 *
 *	@param	p_pp		�|�P�����p����
 *	@param	p_data		�f�[�^
 *	@param	lev			���x��
 *	@param	trade_no	trade�i���o�[
 */
//-----------------------------------------------------------------------------
static void FLD_TradeSetPokeParam( POKEMON_PARAM* p_pp, FLD_TRADE_POKEDATA* p_data, u32 lev, u32 trade_no, u32 heapID, u32 zone_id )
{
	STRBUF* str;
	u8 nickname_flg;
	u32 placeid;

	
	// �����X�^�[�i���o�[�@���x���@�ő̗����@ID�ݒ�
	PokeParaSet( p_pp, 
			p_data->monsno,
			lev, POW_RND, 
			RND_SET, p_data->mons_rnd,
			ID_SET, p_data->mons_id );

	// �j�b�N�l�[��
	str = FLD_TradeGetGmm( heapID, FLD_TRADE_GET_POKE_GMM(trade_no) );
	PokeParaPut( p_pp, ID_PARA_nickname_buf, str );
	STRBUF_Delete(str);

	// �j�b�N�l�[���t���O
	nickname_flg = 1;
	PokeParaPut( p_pp, ID_PARA_nickname_flag, &nickname_flg );

	// �e�헐���ݒ�
	PokeParaPut( p_pp, ID_PARA_hp_rnd, &p_data->hp_rnd );
	PokeParaPut( p_pp, ID_PARA_pow_rnd, &p_data->at_rnd );
	PokeParaPut( p_pp, ID_PARA_def_rnd, &p_data->df_rnd );
	PokeParaPut( p_pp, ID_PARA_agi_rnd, &p_data->sp_rnd );
	PokeParaPut( p_pp, ID_PARA_spepow_rnd, &p_data->sa_rnd );
	PokeParaPut( p_pp, ID_PARA_spedef_rnd, &p_data->sd_rnd );

	// ����
//	PokeParaPut( p_pp, ID_PARA_speabino, &p_data->speabino );

	// �������悳�Ȃ�
	PokeParaPut( p_pp, ID_PARA_style, &p_data->style );
	PokeParaPut( p_pp, ID_PARA_beautiful, &p_data->beautiful );
	PokeParaPut( p_pp, ID_PARA_cute, &p_data->cute );
	PokeParaPut( p_pp, ID_PARA_clever, &p_data->clever );
	PokeParaPut( p_pp, ID_PARA_strong, &p_data->strong );
	
	// �A�C�e��
	PokeParaPut( p_pp, ID_PARA_item, &p_data->item );

	// �e�̖��O
	str = FLD_TradeGetGmm( heapID, FLD_TRADE_GET_OYA_GMM(trade_no) );
	PokeParaPut( p_pp, ID_PARA_oyaname_buf, str );
	STRBUF_Delete(str);

	// �e�̐���	
	PokeParaPut( p_pp, ID_PARA_oyasex, &p_data->oya_sex );

	// ���R�[�h
	PokeParaPut( p_pp, ID_PARA_country_code, &p_data->world_code );

	// �g���[�i�[�����ݒ�
	placeid = ZoneData_GetPlaceNameID( zone_id );
	TrainerMemoSetPP( p_pp, NULL, TRMEMO_OFFTRADE_PLACESET, placeid, heapID );

	// �v�Z���Ȃ���
	PokeParaCalc( p_pp );

	// ���A�ɂȂ�Ȃ��悤�ɂ���
	GF_ASSERT( PokeRareGet( p_pp ) == FALSE );
}
