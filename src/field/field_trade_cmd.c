//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		field_trade_cmd.c
 *	@brief		�Q�[���������@�풓�@�C�x���g�R�}���h
 *	@author		tomoya takahashi
 *	@data		2006.05.16
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "common.h"
#include "fieldsys.h"
#include "field_event.h"
#include "ev_mapchange.h"
#include "ev_time.h"


#define __FIELD_TRADE_CMD_H_GLOBAL
#include "field_trade_cmd.h"

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

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
typedef struct {
	FLD_TRADE_WORK* p_trade;
	u32 seq;
	int party_pos;
	DEMO_TRADE_PARAM demo;

	POKEMON_PARAM*   sendPoke;	///< �����炩�瑗�����|�P����
	POKEMON_PARAM*   recvPoke;	///< �����炩�瑗���Ă����|�P����
} FIELD_TRADE_EVENT_WORK;


//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
static BOOL GMEVENT_FldTrade( GMEVENT_CONTROL * event );
static void FLD_TradeStartDemo( GMEVENT_CONTROL * event );

// �f���J�n
void FLD_TradeStartDemo( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * p_fsys = FieldEvent_GetFieldSysWork(event);
	FIELD_TRADE_EVENT_WORK* p_work = FieldEvent_GetSpecialWork(event);

	{
		FS_EXTERN_OVERLAY(demo_trade);

		static const PROC_DATA  TradeDemoProcData = {
			TradeDemoProc_Init,
			TradeDemoProc_Main,
			TradeDemoProc_Quit,
			FS_OVERLAY_ID(demo_trade),
		};
		EventCmd_CallSubProc(event, &TradeDemoProcData, &p_work->demo );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	�������s
 *	@param	event �C�x���g
 *	@return
 */
//-----------------------------------------------------------------------------
static BOOL GMEVENT_FldTrade( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * p_fsys = FieldEvent_GetFieldSysWork(event);
	FIELD_TRADE_EVENT_WORK* p_work = FieldEvent_GetSpecialWork(event);

	switch( p_work->seq ){
	case 0:	// �����f���f�[�^�쐬
		FLD_TradeDemoDataMake( p_fsys, p_work->p_trade, p_work->party_pos, &p_work->demo, p_work->sendPoke, p_work->recvPoke );

		// �f�[�^��������
		FLD_Trade( p_fsys, p_work->p_trade, p_work->party_pos );
		p_work->seq++;
		break;

	case 1:	// �t�F�[�h�A�E�g
		EventCmd_FieldFadeOut( event );
		p_work->seq++;
		break;

	case 2:	// �t�B�[���h�j��
		EventCmd_FinishFieldMap(event);
		p_work->seq++;
		break;

	case 3:	//�����f��
		FLD_TradeStartDemo( event );
		p_work->seq++;
		break;

	case 4:	// �t�B�[���h���A
		EventCmd_StartFieldMap( event );
		p_work->seq++;
		break;

	case 5:	// �t�F�[�h�C��
		EventCmd_FieldFadeIn( event );
		p_work->seq++;
		break;

	case 6:	// �I��
		sys_FreeMemoryEz( p_work->sendPoke );
		sys_FreeMemoryEz( p_work->recvPoke );
		sys_FreeMemoryEz( p_work );
		return TRUE;
	}
	return FALSE;
}


//----------------------------------------------------------------------------
/**
 *	@brief	�������s
 *
 *	@param	event		�C�x���g���[�N
 *	@param	p_work		�����p���[�N
 *	@param	party_pos	�p�[�e�B�[�i���o�[
 *	@param	heapID
 */
//-----------------------------------------------------------------------------
void EventCmd_FldTrade(GMEVENT_CONTROL * event, FLD_TRADE_WORK* p_work, int party_pos, u32 heapID )
{
	FIELD_TRADE_EVENT_WORK* p_data = sys_AllocMemory( heapID, sizeof(FIELD_TRADE_EVENT_WORK) );
	memset( p_data, 0, sizeof(FIELD_TRADE_EVENT_WORK) );
	p_data->seq =  0;
	p_data->p_trade = p_work;
	p_data->party_pos = party_pos;

	// �|�P�����f�[�^�ۑ��p�̈���쐬
	p_data->sendPoke = PokemonParam_AllocWork( heapID );
	p_data->recvPoke = PokemonParam_AllocWork( heapID );
	
	FieldEvent_Call(event, GMEVENT_FldTrade, p_data);
}
