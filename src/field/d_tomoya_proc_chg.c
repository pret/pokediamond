//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		d_tomoya_proc_chg.c
 *	@brief		�v���b�N�ύX����f�o�b�N�f�[�^
 *	@author		tomoya takahashi
 *	@data		2006.03.27
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifdef PM_DEBUG

#include "common.h"

#include "system/lib_pack.h"
#include "system/bmp_list.h"
#include "system/bmp_menu.h"
#include "fld_bmp.h"
#include "fieldmap.h"
#include "fieldsys.h"
#include "fieldmap_work.h"
#include "system/fontproc.h"

#include "d_tomoya.h"
#include "system/touchpanel_draw.h"
#include "field_light.h"
#include "fog_sys.h"
#include "weather_sys.h"
#include "field_glb_state.h"

#include "encount_effect.h"
#include "effect_uground.h"

#include "system/clact_util.h"
#include "system/render_oam.h"
#include "field_event.h"
#include "system/wipe.h"


#include "msgdata/msg.naix"
#include "msgdata/msg_debug_tomoya.h"

#include "include/application/imageClip/imc_playsys.h"
#include "include/application/imageClip/imc_sys.h"
#include "include/savedata/imageclip_data.h"
#include "include/application/imageClip/imc_preview.h"

#include "poketool/poke_tool.h"
#include "include/application/zukanlist/zkn_sys.h"

#include "src/field/ev_time.h"


#define	__D_TOMOYA_PROC_CHG_H_GLOBAL
#include "d_tomoya_proc_chg.h"

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

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------

// ���������悤�@�O���[�o���ϐ�
u32 D_Tomoya_MazeMaze_TeamWork;



// �J�n�|�P�����I��
//----------------------------------------------------------------------------
/**
 *	@brief	�J�n�|�P�����I��
 *
 *	@param	tcb
 *	@param	work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void MainEvPokeSelect_Check( TCB_PTR tcb, void* work )
{
	DT_SPRITE_CHECK* data = work;
	
	switch( data->seq ){
	case 0:		// �t�F�[�h�A�E�g
		WIPE_SYS_Start( 
				WIPE_PATTERN_FMAS,
				WIPE_TYPE_FADEOUT,
				WIPE_TYPE_FADEOUT,
				0,
				8,2,
				HEAPID_FIELD );
		data->tmp_seq = 2;
		data->seq++;
		break;

	case 1:	// �t�F�[�h�҂�	
		if( WIPE_SYS_EndCheck() ){

			data->seq = data->tmp_seq;
		}
		break;

	case 2:		// �I��������
		Field_EVPokeSelect_SetProc( data->p_fsys, data->p_pearent );
		data->seq++;	
		break;

	case 3:		// �I���I���҂�
		if( GameSystem_CheckSubProcExists( data->p_fsys ) == FALSE ){

			// �擾�����ް��\��
			{
				EV_POKESELECT_PEARENT_DATA* p_pearent;

				p_pearent = data->p_pearent;

#if 0
				switch( p_pearent->select_monsno ){
				case MONSNO_NAEGAME:
					OS_Printf( "�Ȃ�����\n" );
					break;
				case MONSNO_HINOKOZARU:
					OS_Printf( "�Ђ̂�����\n" );
					break;
				case MONSNO_UMIOUZI:
					OS_Printf( "���݂�����\n" );
					break;

				default:
					OS_Printf( "��������\n" );
					break; 
				}
#endif
			}
			
			// �t�B�[���h���A
			GameSystem_CreateFieldProc( data->p_fsys );
			data->seq++;
		}
		break;

	case 4:
		// �t�B�[���h���A�������������`�F�b�N
		if( GameSystem_CheckFieldProcExists(data->p_fsys) ){
/*		�t�B�[���h���͎����Ńt�F�[�h�C�����邽��
 *		�R�����g�A�E�g */
			WIPE_SYS_Start( 
					WIPE_PATTERN_FSAM,
					WIPE_TYPE_FADEIN,
					WIPE_TYPE_FADEIN,
					WIPE_FADE_OUTCOLOR,
					8,2,
					HEAPID_FIELD );
			// �t�F�[�h�C��
			data->seq = 1;
			data->tmp_seq = 5;//*/
/*			WIPE_SYS_Start( 
					WIPE_PATTERN_S,
					WIPE_TYPE_FADEIN,
					WIPE_TYPE_FADEIN,
					0,
					8,2,
					HEAPID_FIELD );
			// �t�F�[�h�C��
			data->seq = 1;
			data->tmp_seq = 5;//*/
		}
		break;

	case 5:		// �I��
		sys_FreeMemoryEz( data->p_pearent );
		// �^�X�N�I��
		TCB_Delete( tcb );
		sys_FreeMemoryEz( work );
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�ӎ��s
 *
 *	@param	TCB_PTR tcb
 *	@param	work 
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
void MainZukan_Check( TCB_PTR tcb, void* work ) 
{
	DT_SPRITE_CHECK* data = work;
	
	switch( data->seq ){
	case 0:		// �t�F�[�h�A�E�g
		WIPE_SYS_Start( 
				WIPE_PATTERN_FMAS,
				WIPE_TYPE_FADEOUT,
				WIPE_TYPE_FADEOUT,
				0,
				8,2,
				HEAPID_FIELD );
		data->tmp_seq = 2;
		data->seq++;
		break;

	case 1:	// �t�F�[�h�҂�	
		if( WIPE_SYS_EndCheck() ){

			data->seq = data->tmp_seq;
		}
		break;

	case 2:		// �}�ӏ�����
		FieldZukan_SetProc( data->p_fsys, data->p_pearent );
		data->seq++;	
		break;

	case 3:		// �}�ӏI���҂�
		if( GameSystem_CheckSubProcExists( data->p_fsys ) == FALSE ){

			// �t�B�[���h���A
			GameSystem_CreateFieldProc( data->p_fsys );
			data->seq++;
		}
		break;

	case 4:
		// �t�B�[���h���A�������������`�F�b�N
		if( GameSystem_CheckFieldProcExists(data->p_fsys) ){
/*		�t�B�[���h���͎����Ńt�F�[�h�C�����邽��
 *		�R�����g�A�E�g */
			WIPE_SYS_Start( 
					WIPE_PATTERN_FSAM,
					WIPE_TYPE_FADEIN,
					WIPE_TYPE_FADEIN,
					WIPE_FADE_OUTCOLOR,
					8,2,
					HEAPID_FIELD );
			// �t�F�[�h�C��
			data->seq = 1;
			data->tmp_seq = 5;//*/
/*			WIPE_SYS_Start( 
					WIPE_PATTERN_S,
					WIPE_TYPE_FADEIN,
					WIPE_TYPE_FADEIN,
					0,
					8,2,
					HEAPID_FIELD );
			// �t�F�[�h�C��
			data->seq = 1;
			data->tmp_seq = 5;//*/
		}
		break;

	case 5:		// �I��
		sys_FreeMemoryEz( data->p_pearent );
		// �^�X�N�I��
		TCB_Delete( tcb );
		sys_FreeMemoryEz( work );
		break;
	}
}




static inline void debug_savedata_print( IMC_TELEVISION_SAVEDATA* p_save_one )
{
	int i;
	
	OS_Printf( "�����X�^�[�i���o�[%d\n", ImcSaveData_GetTelevisionPokeMonsNo( p_save_one ) );
	OS_Printf( "�����X�^�[�D�揇��%d\n", ImcSaveData_GetTelevisionPokePri( p_save_one ) );
	OS_Printf( "�����X�^�[���Wx[%d] y[%d]\n", ImcSaveData_GetTelevisionPokeX( p_save_one ), ImcSaveData_GetTelevisionPokeY( p_save_one ) );

	for( i=0; i<IMC_SAVEDATA_TELEVISION_ACCE_NUM; i++ ){
	
		if( ImcSaveData_CheckTelevisionAcceDataSet( p_save_one, i ) ){
			OS_Printf( "�A�N�Z�T���i���o�[%d\n", ImcSaveData_GetTelevisionAcceNo( p_save_one, i ) );
			OS_Printf( "�A�N�Z�T��x[%d] y[%d]\n", ImcSaveData_GetTelevisionAcceMatX( p_save_one, i ), ImcSaveData_GetTelevisionAcceMatY( p_save_one, i ) );
			OS_Printf( "�A�N�Z�T���D�揇��%d\n", ImcSaveData_GetTelevisionAccePri( p_save_one, i ) );
		}
	}

	OS_Printf( "BG %d\n", ImcSaveData_GetTelevisionBgId( p_save_one ) );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief
 *
 *	@param	TCB_PTR tcb
 *	@param	work 
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
void MainSprite_Check( TCB_PTR tcb, void* work ) 
{
	DT_SPRITE_CHECK* data = work;
	
	switch( data->seq ){
	case 0:		// �t�F�[�h�A�E�g
		WIPE_SYS_Start( 
				WIPE_PATTERN_FMAS,
				WIPE_TYPE_FADEOUT,
				WIPE_TYPE_FADEOUT,
				0,
				8,2,
				HEAPID_FIELD );
		data->tmp_seq = 2;
		data->seq++;
		break;

	case 1:	// �t�F�[�h�҂�	
		if( WIPE_SYS_EndCheck() ){

			data->seq = data->tmp_seq;
		}
		break;

	case 2:		// �C���[�W�N���b�v������
		FieldImageClip_SetProc( data->p_fsys, data->p_pearent );
		data->seq++;	
		break;

	case 3:		// �C���[�W�N���b�v�I���҂�
		if( GameSystem_CheckSubProcExists( data->p_fsys ) == FALSE ){


			// �v���b�N�f�[�^�j��
			{
				IMC_PROC_WORK* imc_w = data->p_pearent;

				// �Z�[�u�f�[�^�\��
				debug_savedata_print( imc_w->p_imc_one_data );

				sys_FreeMemoryEz( imc_w->p_poke_para );
				sys_FreeMemoryEz( imc_w );
			}


			// �t�B�[���h���A
			GameSystem_CreateFieldProc( data->p_fsys );
			data->seq++;
		}
		break;

	case 4:
		// �t�B�[���h���A�������������`�F�b�N
		if( GameSystem_CheckFieldProcExists(data->p_fsys) ){
/*		�t�B�[���h���͎����Ńt�F�[�h�C�����邽��
 *		�R�����g�A�E�g */
			WIPE_SYS_Start( 
					WIPE_PATTERN_FSAM,
					WIPE_TYPE_FADEIN,
					WIPE_TYPE_FADEIN,
					WIPE_FADE_OUTCOLOR,
					8,2,
					HEAPID_FIELD );
			// �t�F�[�h�C��
			data->seq = 1;
			data->tmp_seq = 5;//*/
/*			WIPE_SYS_Start( 
					WIPE_PATTERN_S,
					WIPE_TYPE_FADEIN,
					WIPE_TYPE_FADEIN,
					0,
					8,2,
					HEAPID_FIELD );
			// �t�F�[�h�C��
			data->seq = 1;
			data->tmp_seq = 5;//*/
		}
		break;

	case 5:		// �I��
		// �^�X�N�I��
		TCB_Delete( tcb );
		sys_FreeMemoryEz( work );
		break;
	}
}



static inline void debug_contest_savedata_print( IMC_CONTEST_SAVEDATA* p_save_one )
{
	int i;
	
	OS_Printf( "�����X�^�[�i���o�[%d\n", ImcSaveData_GetContestPokeMonsNo( p_save_one ) );
	OS_Printf( "�����X�^�[�D�揇��%d\n", ImcSaveData_GetContestPokePri( p_save_one ) );
	OS_Printf( "�����X�^�[���Wx[%d] y[%d]\n", ImcSaveData_GetContestPokeX( p_save_one ), ImcSaveData_GetContestPokeY( p_save_one ) );

	for( i=0; i<IMC_SAVEDATA_CONTEST_ACCE_NUM; i++ ){
	
		if( ImcSaveData_CheckContestAcceDataSet( p_save_one, i ) ){
			OS_Printf( "�A�N�Z�T���i���o�[%d\n", ImcSaveData_GetContestAcceNo( p_save_one, i ) );
			OS_Printf( "�A�N�Z�T��x[%d] y[%d]\n", ImcSaveData_GetContestAcceMatX( p_save_one, i ), ImcSaveData_GetContestAcceMatY( p_save_one, i ) );
			OS_Printf( "�A�N�Z�T���D�揇��%d\n", ImcSaveData_GetContestAccePri( p_save_one, i ) );
		}
	}

	OS_Printf( "BG %d\n", ImcSaveData_GetContestBgId( p_save_one ) );
	OS_Printf( "�����N %d\n", ImcSaveData_GetContestRank( p_save_one ) );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief
 *
 *	@param	TCB_PTR tcb
 *	@param	work 
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
void MainSprite_Check_Contest( TCB_PTR tcb, void* work ) 
{
	DT_SPRITE_CHECK* data = work;
	
	switch( data->seq ){
	case 0:		// �t�F�[�h�A�E�g
		WIPE_SYS_Start( 
				WIPE_PATTERN_FMAS,
				WIPE_TYPE_FADEOUT,
				WIPE_TYPE_FADEOUT,
				0,
				8,2,
				HEAPID_FIELD );
		data->tmp_seq = 2;
		data->seq++;
		break;

	case 1:	// �t�F�[�h�҂�	
		if( WIPE_SYS_EndCheck() ){

			data->seq = data->tmp_seq;
		}
		break;

	case 2:		// �C���[�W�N���b�v������
		{
			// �I�[�o�[���CID�錾
			FS_EXTERN_OVERLAY(ol_imageclip);
			
			// �v���b�N�f�[�^
			static PROC_DATA IMC_SYS_Proc = {
				IMC_ProcContestInit,
				IMC_ProcContestMain,
				IMC_ProcContestEnd,
				FS_OVERLAY_ID(ol_imageclip),
			};

			GameSystem_StartSubProc(data->p_fsys,  &IMC_SYS_Proc, data->p_pearent );
		}
		data->seq++;	
		break;

	case 3:		// �C���[�W�N���b�v�I���҂�
		if( GameSystem_CheckSubProcExists( data->p_fsys ) == FALSE ){


			// �v���b�N�f�[�^�j��
			{
				IMC_CONTEST_PROC_WORK* imc_w = data->p_pearent;

				// �Z�[�u�f�[�^�\��
				debug_contest_savedata_print( imc_w->p_imc_one_data );

				sys_FreeMemoryEz( imc_w->p_comm_data );
				sys_FreeMemoryEz( imc_w->p_poke_para );
				sys_FreeMemoryEz( imc_w );
			}


			// �t�B�[���h���A
			GameSystem_CreateFieldProc( data->p_fsys );
			data->seq++;
		}
		break;

	case 4:
		// �t�B�[���h���A�������������`�F�b�N
		if( GameSystem_CheckFieldProcExists(data->p_fsys) ){
/*		�t�B�[���h���͎����Ńt�F�[�h�C�����邽��
 *		�R�����g�A�E�g */
			WIPE_SYS_Start( 
					WIPE_PATTERN_FSAM,
					WIPE_TYPE_FADEIN,
					WIPE_TYPE_FADEIN,
					WIPE_FADE_OUTCOLOR,
					8,2,
					HEAPID_FIELD );
			// �t�F�[�h�C��
			data->seq = 1;
			data->tmp_seq = 5;//*/
/*			WIPE_SYS_Start( 
					WIPE_PATTERN_S,
					WIPE_TYPE_FADEIN,
					WIPE_TYPE_FADEIN,
					0,
					8,2,
					HEAPID_FIELD );
			// �t�F�[�h�C��
			data->seq = 1;
			data->tmp_seq = 5;//*/
		}
		break;

	case 5:		// �I��
		// �^�X�N�I��
		TCB_Delete( tcb );
		sys_FreeMemoryEz( work );
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�h���X�A�b�v�ʏ�̃r���[�A�[
 *
 *	@param	tcb
 *	@param	work 
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
void MainSprite_CheckView( TCB_PTR tcb, void* work ) 
{
	DT_SPRITE_CHECK* data = work;
	
	switch( data->seq ){
	case 0:		// �t�F�[�h�A�E�g
		WIPE_SYS_Start( 
				WIPE_PATTERN_FMAS,
				WIPE_TYPE_FADEOUT,
				WIPE_TYPE_FADEOUT,
				0,
				8,2,
				HEAPID_FIELD );
		data->tmp_seq = 2;
		data->seq++;
		break;

	case 1:	// �t�F�[�h�҂�	
		if( WIPE_SYS_EndCheck() ){

			data->seq = data->tmp_seq;
		}
		break;

	case 2:		// �C���[�W�N���b�v������
		{
			// �I�[�o�[���CID�錾
			FS_EXTERN_OVERLAY(ol_imageclip);
			
			// �v���b�N�f�[�^
			static PROC_DATA IMC_SYS_PLAY_Proc = {
				IMC_Prev_ProcInit,
				IMC_Prev_ProcMain,
				IMC_Prev_ProcEnd,
				FS_OVERLAY_ID(ol_imageclip),
			};

			GameSystem_StartSubProc(data->p_fsys,  &IMC_SYS_PLAY_Proc, data->p_pearent );
		}
		data->seq++;	
		break;

	case 3:		// �C���[�W�N���b�v�I���҂�
		if( GameSystem_CheckSubProcExists( data->p_fsys ) == FALSE ){


			// �v���b�N�f�[�^�j��
			{
				IMC_PROC_PREV_WORK* imc_w = data->p_pearent;
				sys_FreeMemoryEz( imc_w );
			}

			// �t�B�[���h���A
			GameSystem_CreateFieldProc( data->p_fsys );
			data->seq++;
		}
		break;

	case 4:
		// �t�B�[���h���A�������������`�F�b�N
		if( GameSystem_CheckFieldProcExists(data->p_fsys) ){
/*		�t�B�[���h���͎����Ńt�F�[�h�C�����邽��
 *		�R�����g�A�E�g */
			WIPE_SYS_Start( 
					WIPE_PATTERN_FSAM,
					WIPE_TYPE_FADEIN,
					WIPE_TYPE_FADEIN,
					WIPE_FADE_OUTCOLOR,
					8,2,
					HEAPID_FIELD );
			// �t�F�[�h�C��
			data->seq = 1;
			data->tmp_seq = 5;//*/
		}
		break;

	case 5:		// �I��
		// �^�X�N�I��
		TCB_Delete( tcb );
		sys_FreeMemoryEz( work );
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�����ł��\�[�X
 */	
//-----------------------------------------------------------------------------
BOOL EventScr_D_FldTrade(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * p_fsys = FieldEvent_GetFieldSysWork(event);
	D_TOMOYA_EVENT_WORK* p_work = FieldEvent_GetSpecialWork(event);
	u16 monsno, monsno_chg;
	POKEPARTY* party = SaveData_GetTemotiPokemon( p_fsys->savedata );
	POKEMON_PARAM* pp = PokeParty_GetMemberPointer( party, 0 );

	switch( p_work->seq ){
	case 0:	// �����ł��邩�`�F�b�N
		monsno = FLD_TradeChangeMonsno( p_work->p_work );
		monsno_chg = PokeParaGet( pp, ID_PARA_monsno, NULL );
		if( monsno == monsno_chg ){
			p_work->seq++;
		}else{
			return TRUE;
		}
		break;

	case 1:	//����
		EventCmd_FldTrade( event, p_work->p_work, 0, HEAPID_BASE_DEBUG );
		p_work->seq++;
		break;

	case 2:	// �I��
		FLD_TradeDelete( p_work->p_work );
		sys_FreeMemoryEz( p_work );
		return TRUE;
	}
	return FALSE;
}

#endif // PM_DEBUG
