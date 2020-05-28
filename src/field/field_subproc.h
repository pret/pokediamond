//=============================================================================
/**
 * @file	field_subproc.h	
 * @brief	�t�B�[���h�����΂��T�u�v���Z�X
 * @author	GAME FREAK inc.
 */
//=============================================================================
#ifndef	__FIELD_SUBPROC_H__
#define	__FIELD_SUBPROC_H__

#include "field_common.h"
#include "system/procsys.h"
#include "field_event.h"
#include "application/trainer_card.h"
#include "application/poru_tool.h"
#include "application/box.h"
#include "application/wifi_p2pmatch.h"
#include "field/itemuse.h"
#include "field/field_skill.h"
#include "application/slot.h"

//==============================================================================
//	include
//==============================================================================


typedef enum {
	EVBAG_MODE_NORMAL_ONLY = 0,
	EVBAG_MODE_KINOMI_ONLY,
}EVBAG_MODE;

//==============================================================================
//==============================================================================

//�ʐM�����C�x���g�Ăяo��
extern void EventCmd_UnionTrade(GMEVENT_CONTROL * event);

extern void * FieldBag_SetProc( FIELDSYS_WORK * fsys, ITEMCHECK_WORK * icwk );
extern void FieldBag_SubProcSet( FIELDSYS_WORK * fsys, void * buf );
extern void * FieldPokeList_SetProc( FIELDSYS_WORK * fsys, SKILLCHECK_WORK * scwk, u8 pos );
extern void FieldPokeStatus_SetProc( FIELDSYS_WORK * fsys, void * psd );
extern void FieldTrCard_SetProc( FIELDSYS_WORK * fsys, TR_CARD_DATA *tcd );
extern void FieldNutsTag_SetProc( FIELDSYS_WORK * fsys, void * buf );
extern void FieldFantasyNote_SetProc( FIELDSYS_WORK * fsys, void * buf );
extern void * FieldConfig_SetProc( FIELDSYS_WORK * fsys );

extern void * DebugFieldBox_SetProc( FIELDSYS_WORK * fsys );
extern void FieldBox_SetProc( FIELDSYS_WORK * fsys, BOX_PROC_PARAM* param );

void EventCmd_ImcClipTvStart(GMEVENT_CONTROL * event, u16* result, SAVEDATA* p_save, u16 pos, u16 reference );
extern BOOL FieldImageClip_SetProc( FIELDSYS_WORK * fsys, void* buff );
extern BOOL FieldImageClipViewer_SetProc( FIELDSYS_WORK * fsys, void* buff );
extern BOOL FieldZukan_SetProc( FIELDSYS_WORK * fsys, void* p_pearent );
extern void NameInput_SetProc( FIELDSYS_WORK * fsys, void *param );
extern void * TradeList_SetProc( FIELDSYS_WORK * fsys );
extern void OekakiBoard_SetProc( FIELDSYS_WORK *fsys );
extern void * RecordCorner_SetProc( FIELDSYS_WORK *fsys );
extern void WifiNoteEntry_SetProc( FIELDSYS_WORK *fsys, SAVEDATA* pSaveData );
extern void WifiNote_SetProc( FIELDSYS_WORK *fsys, SAVEDATA* pSaveData );
extern BOOL WifiP2PMatch_SetProc( FIELDSYS_WORK *fsys,WIFIP2PMATCH_PROC_PARAM* pParam );
//WiFi�n���V�Ăяo��
extern void Field_WifiEarth_SetProc(FIELDSYS_WORK * fsys);

extern void EventCmd_NameIn(GMEVENT_CONTROL * event, int mode, int info, int wordmax, int pos, const STRCODE* str, u16* ret_work);


extern void * FieldBagEvent_SetProc( FIELDSYS_WORK * fsys, EVBAG_MODE mode );
extern u16 FieldBagEvent_GetSelectedItem(void * param);

//�|�P�����I���ďo��
extern void * FieldPokeListEvent_SetProc(int heap, FIELDSYS_WORK * fsys);
extern void * FieldPokeListEventNpcTrade_SetProc(int heap, FIELDSYS_WORK * fsys);
extern int FieldPokeListEvent_GetSelect(void * wk);
extern int FieldPokeListEvent_GetMode(void * wk);
extern void * UnionPokeListEvent_SetProc(int heap, FIELDSYS_WORK * fsys);
extern void * ContestPokeListEvent_SetProc(int heap, FIELDSYS_WORK * fsys, 
	int con_type, int con_rank, int sio_flag, int pos);

extern void * EventCmd_PokeListSelect(GMEVENT_CONTROL * event, int heapID);

//�����Ă�|�P�����I���ďo��
extern void * SodateyaPokeListEvent_SetProc(int heap, FIELDSYS_WORK * fsys, int pos);

//�|�P�����X�e�[�^�X��ʌĂяo��
extern void * ContestPokeStatusEvent_SetProc(int heap, FIELDSYS_WORK * fsys, int pos);
extern int FieldPokeStatusEvent_GetPos(void * wk);

//�킴�Y��I���ďo��
extern void * FieldWazaListEvent_SetProc(int heap, FIELDSYS_WORK * fsys, u8 pos);
extern int FieldWazaListEvent_GetSelect(void * wk);

//�Z�����E�v���o��
#include "application/waza_oshie.h"
extern void WazaOshie_ProcSet( FIELDSYS_WORK * fsys , WAZAOSHIE_DATA * wk );

//���[���Ăяo��
#include "savedata/mail_def.h"
#include "application/mail/mail_param.h"
/**
 *	@brief	���[���쐬��ʃt�B�[���h���j���[�Ăяo��
 *	
 *	@param	fsys FIELDSYS_WORK *
 *
 *	@retval	MAIL_PARAM* :�����m�ۂ����p�����[�^���[�N�ւ̃|�C���^
 *						�@�@�Ăяo�����������I�ɉ������K�v����
 */
extern MAIL_PARAM * FieldMailCreate_InitCall( FIELDSYS_WORK * fsys ,
		MAILBLOCK_ID blockID,u8 poke_pos,u8 design,int heapID);

/**
 *	@brief	���[���`���ʃt�B�[���h���j���[�Ăяo��
 *	
 *	@param	fsys FIELDSYS_WORK *
 *
 *	@retval	MAIL_PARAM* :�����m�ۂ����p�����[�^���[�N�ւ̃|�C���^
 *						�@�@�Ăяo�����������I�ɉ������K�v����
 */
extern MAIL_PARAM * FieldMailView_InitCall( FIELDSYS_WORK * fsys,
		MAILBLOCK_ID blockID,u8 dataID,int heapID);
/**
 *	@brief	���[���`���ʃt�B�[���h���j���[�Ăяo��(�|�P�������[��)
 *	
 *	@param	fsys FIELDSYS_WORK *
 *
 *	@retval	MAIL_PARAM* :�����m�ۂ����p�����[�^���[�N�ւ̃|�C���^
 *						�@�@�Ăяo�����������I�ɉ������K�v����
 *
 */
extern MAIL_PARAM * FieldMailViewPoke_InitCall( FIELDSYS_WORK * fsys,
		POKEMON_PARAM* poke,int heapID);

/**
 *	@brief	�|���g�P�[�X�Ăяo��
 */
extern PORUTO_PARAM* FieldPorutoCase_InitCall(FIELDSYS_WORK* fsys,int heapID);
/**
 *	@brief	�t�B�[���h �^���[�A�v���Ăяo��
 *
 *	@param	fsys FIELDSYS_WORK *
 *	@param	work	void*:���[�N�̈��p��
 *
 *	@retval	0:����
 *	@retval else	���s
 */
#include "application\btwr_app.h"
extern void BTowerApp_SetProc(FIELDSYS_WORK *fsys,BTOWER_APP_PARAM * ap);

//==============================================================================
// �ȈՉ�b���͉��
//==============================================================================
#include "application\pms_input.h"
extern void FieldProc_SetPmsInput( FIELDSYS_WORK* fsys, PMSI_PARAM* param );

//�C�x���g�R�}���h�F�ȈՉ�b�P����͌Ăяo��
extern void EventCmd_PMSInput(GMEVENT_CONTROL * event, u16 * result, u16 * pms1, u16 * pms2);

//==============================================================================
// �J�n�|�P�����I����ʉ��
//==============================================================================
#include "demo/ev_poke_select.h"
extern void Field_EVPokeSelect_SetProc( FIELDSYS_WORK * fsys, EV_POKESELECT_PEARENT_DATA* p_pearent );

// -----------------------------------------
//
//	�J�X�^���{�[�����
//
// -----------------------------------------
extern BOOL Field_CustomBall_SetProc( FIELDSYS_WORK * fsys, void* buff );

// �����T�C�����͉��
extern void Field_MySign_SetProc( FIELDSYS_WORK *fsys );

// ���E�����Ăяo��
extern void Field_WorldTrade_SetProc( FIELDSYS_WORK *fsys, int connect );

// WIFI�o�g���^���[�ڑ���ʌĂяo��
extern void* Field_WifiBattleTowerConnect_SetProc( FIELDSYS_WORK *fsys, int mode, int connect );



//==============================================================================
// �������X�g�`�����f���`
//==============================================================================
extern BOOL GMEVENT_UnionTradeList(GMEVENT_CONTROL * event);


//==============================================================================
// �a������f��
//==============================================================================
#include "demo\demo_dendou.h"
extern void Field_DendouDemo_SetProc( FIELDSYS_WORK * fsys, DEMO_DENDOU_PARAM* param );

//==============================================================================
//	�a������m�F
//==============================================================================
extern void * Field_DendouPC_Call( FIELDSYS_WORK* fsys );


//==============================================================================
// �G���f�B���O�f��
//==============================================================================
#include "demo\demo_ending.h"
extern void Field_EndingDemo_SetProc( FIELDSYS_WORK * fsys, ENDING_PROC_PARAM* param );

//==============================================================================
//	�^�}�S���܂��f��
//==============================================================================
void Field_EggDemo_Call(FIELDSYS_WORK * fsys);

//==============================================================================
//	�X���b�g
//==============================================================================
extern BOOL FieldSlot_SetProc( FIELDSYS_WORK *fsys, SLOT_PARAM *slotparam );

extern void EventCmd_SlotMachine(GMEVENT_CONTROL * event, int id);


//==============================================================================
//	�A�N�Z�T���[�V���b�v
//==============================================================================
extern void EventCmd_AcceShop(GMEVENT_CONTROL * event);

//==============================================================================
//	�\����
//==============================================================================
extern void* Syoujyou_SetProc( FIELDSYS_WORK * fsys, int heapID, int type );

//==============================================================================
// �^�E���}�b�v�֘A
//==============================================================================
extern void * FieldMenuTMap_SetProc( FIELDSYS_WORK * fsys );


#endif	//__FIELD_SUBPROC_H__
