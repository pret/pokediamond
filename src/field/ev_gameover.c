//============================================================================================
/**
 * @file	ev_gameover.c
 * @brief
 * @date	2006.04.18
 * @author	tamada GAME FREAK inc.
 *
 * scr_tool.c,field_encount.c����Q�[���I�[�o�[�����������Ă��čč\������
 */
//============================================================================================

#include "common.h"
#include "fieldsys.h"
#include "field_event.h"

#include "ev_mapchange.h"

#include "system/snd_tool.h"
#include "fld_bgm.h"

#include "system/window.h"
#include "system/wipe.h"

#include "mapdata_warp.h"			//WARPDATA_GetRevivalLocation
#include "situation_local.h"		//Situation_Get�`
#include "system/brightness.h"
#include "script.h"
#include "scr_tool.h"
#include "mapdefine.h"
#include "..\fielddata\script\common_scr_def.h"		//SCRID_GAME_OVER_RECOVER_PC
#include "sysflag.h"
#include "fld_flg_init.h"			//FldFlgInit_GameOver

//==============================================================================================
//
//	�S�Ŋ֘A
//
//==============================================================================================
#include "system/fontproc.h"						
#include "system/msgdata.h"							//MSGMAN_TYPE_DIRECT
#include "system/wordset.h"							//WORDSET_Create

#include "fld_bmp.h"						

#include "msgdata/msg.naix"							//NARC_msg_??_dat
#include "msgdata/msg_gameover.h"					//msg_all_dead_??

#include "system/arc_util.h"
#include "system/font_arc.h"

//----------------------------------------------------------------------------------------------
//	�\���̐錾
//----------------------------------------------------------------------------------------------
typedef struct{
	int seq;

	FIELDSYS_WORK* fsys;

	GF_BGL_INI* bgl;								//BGL�f�[�^

	GF_BGL_BMPWIN bmpwin;							//BMP�E�B���h�E�f�[�^

	//STRBUF* msg_buf[EV_WIN_MENU_MAX];				//���b�Z�[�W�f�[�^�̃|�C���^
	MSGDATA_MANAGER* msgman;						//���b�Z�[�W�}�l�[�W���[
	WORDSET* wordset;								//�P��Z�b�g

	//PALETTE_FADE_PTR pfd;							//�p���b�g�t�F�[�h
}GAME_OVER_WORK;

#define GAME_OVER_MSG_BUF_SIZE		(1024)			//���b�Z�[�W�o�b�t�@�T�C�Y
#define GAME_OVER_FADE_SYNC			(8)				//�t�F�[�hsync��

//----------------------------------------------------------------------------------------------
//	BMP�E�B���h�E
//----------------------------------------------------------------------------------------------
enum{
	GAME_OVER_BMPWIN_FRAME	= GF_BGL_FRAME3_M,
	//GAME_OVER_BMPWIN_PX1	= 1,//2,
	//GAME_OVER_BMPWIN_PY1	= 1,//2,
	//GAME_OVER_BMPWIN_SX		= 29,//25,
	//GAME_OVER_BMPWIN_SY		= 19,//18,
	GAME_OVER_BMPWIN_PX1	= 4,
	GAME_OVER_BMPWIN_PY1	= 5,
	GAME_OVER_BMPWIN_SX		= 25,
	GAME_OVER_BMPWIN_SY		= 15,
	GAME_OVER_BMPWIN_PL		= FLD_SYSFONT_PAL,
	GAME_OVER_BMPWIN_CH		= 1,
};

static const BMPWIN_DAT	GameOverWinData = {
	GAME_OVER_BMPWIN_FRAME,						//�E�C���h�E�g�p�t���[��
	GAME_OVER_BMPWIN_PX1,GAME_OVER_BMPWIN_PY1,	//�E�C���h�E�̈�̍����X,Y���W�i�L�����P�ʂŎw��j
	GAME_OVER_BMPWIN_SX, GAME_OVER_BMPWIN_SY,	//�E�C���h�E�̈��X,Y�T�C�Y�i�L�����P�ʂŎw��j
	GAME_OVER_BMPWIN_PL,						//�E�C���h�E�̈�̃p���b�g�i���o�[	
	GAME_OVER_BMPWIN_CH							//�E�C���h�E�L�����̈�̊J�n�L�����N�^�i���o�[
};

//----------------------------------------------------------------------------------------------
//	�v���g�^�C�v�錾
//----------------------------------------------------------------------------------------------
static void GameOverCall( FIELDSYS_WORK* fsys, GMEVENT_CONTROL* event );
static BOOL GMEVENT_GameOver( GMEVENT_CONTROL* event );
static void scr_msg_print( GAME_OVER_WORK* wk, u16 msg_id, u8 x, u8 y );

static void SetBgHeader( GF_BGL_INI * ini );
static void BgExit( GF_BGL_INI * ini );


static void setup_bg_sys( GF_BGL_INI* bgl )
{
	static const GF_BGL_DISPVRAM SetBankData = {
		GX_VRAM_BG_128_B,				// ���C��2D�G���W����BG
		GX_VRAM_BGEXTPLTT_NONE,			// ���C��2D�G���W����BG�g���p���b�g
		GX_VRAM_SUB_BG_128_C,			// �T�u2D�G���W����BG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		// �T�u2D�G���W����BG�g���p���b�g
		GX_VRAM_OBJ_64_E,				// ���C��2D�G���W����OBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// ���C��2D�G���W����OBJ�g���p���b�g
		GX_VRAM_SUB_OBJ_16_I,			// �T�u2D�G���W����OBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// �T�u2D�G���W����OBJ�g���p���b�g
		GX_VRAM_TEX_0_A,				// �e�N�X�`���C���[�W�X���b�g
		GX_VRAM_TEXPLTT_01_FG			// �e�N�X�`���p���b�g�X���b�g
	};

	static const GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D,
	};

	static const GF_BGL_BGCNT_HEADER header = {
		0, 0, 0x800, 0,	// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x00000,
		GX_BG_EXTPLTT_01, 1, 0, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};

	GF_Disp_SetBank( &SetBankData );
	GF_BGL_InitBG( &BGsys_data );
	GF_BGL_BGControlSet( bgl, GAME_OVER_BMPWIN_FRAME, &header, GF_BGL_MODE_TEXT );

	ArcUtil_PalSet( ARC_FONT, NARC_font_system_ncrl, PALTYPE_MAIN_BG, 
		GAME_OVER_BMPWIN_PL*0x20, 0x20, HEAPID_WORLD );
}

//--------------------------------------------------------------
/**
 * @brief	�Q�[���I�[�o�[��ʌĂяo��
 *
 * @param	fsys	FIELDSYS_WORK�^�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void GameOverCall( FIELDSYS_WORK* fsys, GMEVENT_CONTROL* event )
{
	GAME_OVER_WORK* wk;

	wk = sys_AllocMemory( HEAPID_WORLD, sizeof(GAME_OVER_WORK) );
	if( wk == NULL ){
		GF_ASSERT( (0) && "�������m�ۂɎ��s���܂����I" );
	}
	memset( wk, 0, sizeof(GAME_OVER_WORK) );

	wk->seq			= 0;
	wk->fsys		= fsys;
	wk->bgl 		= GF_BGL_BglIniAlloc( HEAPID_WORLD );

	setup_bg_sys( wk->bgl );

	//���b�Z�[�W�f�[�^�}�l�[�W���[�쐬
	wk->msgman = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_gameover_dat, HEAPID_WORLD);
	wk->wordset = WORDSET_Create( HEAPID_WORLD );

	//�r�b�g�}�b�v�ǉ�
	GF_BGL_BmpWinAddEx( wk->bgl, &wk->bmpwin, &GameOverWinData );

	//��l�����Z�b�g
	WORDSET_RegisterPlayerName(wk->wordset, 0, SaveData_GetMyStatus(GameSystem_GetSaveData(fsys)));

	//�}�b�v�Ǘ��\����BGM�i���o�[��Ԃ�
	if( fsys->location->zone_id == ZONE_ID_T01R0201 ){
		OS_Printf( "05 zone_id = %d\n", fsys->location->zone_id );
		scr_msg_print( wk, msg_all_dead_05, 0, 0 );
	}else{
		OS_Printf( "04 zone_id = %d\n", fsys->location->zone_id );
		scr_msg_print( wk, msg_all_dead_04, 0, 0 );
	}

	GF_BGL_BmpWinOn( &wk->bmpwin );

	FieldEvent_Call( event, GMEVENT_GameOver, wk );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	�Q�[���I�[�o�[��ʃ��C��
 *
 * @param	tcb		TCB_PTR�^
 * @param	work	���[�N
 *
 * @retval	none
 */
//--------------------------------------------------------------
static BOOL GMEVENT_GameOver( GMEVENT_CONTROL* event )
{
	GAME_OVER_WORK * wk = FieldEvent_GetSpecialWork( event );

	switch( wk->seq ){

	case 0:

		WIPE_SYS_Start(WIPE_PATTERN_M, WIPE_TYPE_FADEIN, WIPE_TYPE_MAX,
				WIPE_FADE_BLACK, GAME_OVER_FADE_SYNC, WIPE_DEF_SYNC, HEAPID_EVENT);
		wk->seq++;
		break;

	case 1:
		if (WIPE_SYS_EndCheck()) {
			wk->seq++;
		}
		break;

	//�L�[�҂�
	case 2:
		if( (sys.trg & PAD_BUTTON_A) || (sys.trg & PAD_BUTTON_B) ){
			WIPE_SYS_Start(WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT,
					WIPE_FADE_BLACK, GAME_OVER_FADE_SYNC, WIPE_DEF_SYNC, HEAPID_EVENT);
			wk->seq++;
		}
		break;

	//���C����ʃu���b�N�A�E�g�҂�
	case 3:
		if (WIPE_SYS_EndCheck()) {

			GF_BGL_BmpWinDataFill( &wk->bmpwin, FBMP_COL_NULL );		//�h��Ԃ�

			wk->seq++;
		}
		break;

	//�I���J��
	case 4:
		BmpTalkWinClear( &wk->bmpwin, WINDOW_TRANS_ON );
		GF_BGL_BmpWinDel( &wk->bmpwin );

		WORDSET_Delete( wk->wordset );
		MSGMAN_Delete( wk->msgman );
		GF_BGL_BGControlExit( wk->bgl, GAME_OVER_BMPWIN_FRAME );
		sys_FreeMemoryEz( wk->bgl );

		sys_FreeMemoryEz( wk );

		return TRUE;
	};

	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	���b�Z�[�W�\��
 *
 * @param	wk			EV_WIN_WORK�^�̃A�h���X
 * @param	msg_id		���b�Z�[�WID
 * @param	x			�\���w���W
 * @param	y			�\���x���W
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void scr_msg_print( GAME_OVER_WORK* wk, u16 msg_id, u8 x, u8 y )
{
	STRBUF* tmp_buf = STRBUF_Create( GAME_OVER_MSG_BUF_SIZE, HEAPID_WORLD );
	STRBUF* tmp_buf2= STRBUF_Create( GAME_OVER_MSG_BUF_SIZE, HEAPID_WORLD );

	GF_BGL_BmpWinDataFill( &wk->bmpwin, FBMP_COL_NULL );			//�h��Ԃ�

	MSGMAN_GetString( wk->msgman, msg_id, tmp_buf );

	WORDSET_ExpandStr( wk->wordset, tmp_buf2, tmp_buf );
	GF_STR_PrintColor( &wk->bmpwin, FONT_SYSTEM, tmp_buf2, x, y, MSG_NO_PUT, 
					GF_PRINTCOLOR_MAKE(FBMP_COL_WHITE,FBMP_COL_BLK_SDW,FBMP_COL_NULL), NULL );

	STRBUF_Delete( tmp_buf );
	STRBUF_Delete( tmp_buf2 );
	return;
}


//============================================================================================
//============================================================================================
//-----------------------------------------------------------------------------
/**
 * @brief	�ʏ�퓬�F�S�ŃV�[�P���X
 * @param	event		�C�x���g���䃏�[�N�ւ̃|�C���^
 * @retval	TRUE		�C�x���g�I��
 * @retval	FALSE		�C�x���g�p����
 *
 */
//-----------------------------------------------------------------------------
BOOL GMEVENT_NormalGameOver(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys;
	int * seq;
	fsys = FieldEvent_GetFieldSysWork(event);
	seq = FieldEvent_GetSeqWork(event);

	switch (*seq) {
	case 0:
		//���[�vID�Ŏw�肳�ꂽ�߂���
		{
			LOCATION_WORK next;
			SITUATION * sit = SaveData_GetSituation(fsys->savedata);
			u16 warp_id = Situation_GetWarpID(sit);
			WARPDATA_GetRevivalLocation(warp_id, &next);
			//�G�X�P�[�v�|�C���g�����[�v�|�C���g�ɍĐݒ�
			WARPDATA_GetWarpLocation(warp_id,Situation_GetEscapeLocation(sit));
			//�}�b�v�`�F���W
			EventCmd_MapChangeByLocation(event, &next);
			//�Q�[���I�[�o�[���̃t���O�̃N���A
			FldFlgInit_GameOver(fsys);
		}
		(*seq) ++;
		break;

	case 1:
		//BGM�t�F�[�h�A�E�g
		Snd_BgmFadeOut( 0, 20 );
		(*seq) ++;
		break;

	case 2:
		//BGM�t�F�[�h�A�E�g�҂�
		if( Snd_FadeCheck() == 0 ){

			//�T�E���h�Q�[���I�[�o�[����
			Snd_GameOverSet();

			(*seq) ++;
		}
		break;

	case 3:
		//�x��BG�ȊO��\���I�t
		SetBrightness( BRIGHTNESS_BLACK, (PLANEMASK_ALL^PLANEMASK_BG3), MASK_MAIN_DISPLAY);
		SetBrightness( BRIGHTNESS_BLACK, PLANEMASK_ALL, MASK_SUB_DISPLAY);

		//�Q�[���I�[�o�[�x��
		GameOverCall( fsys, event );
		(*seq) ++;
		break;

	case 4:
		//�C�x���g�R�}���h�F�t�B�[���h�}�b�v�v���Z�X���A
		EventCmd_StartFieldMap(event);
		(*seq)++;
		break;

	case 5:
		//�\���I�t����
		SetBrightness( BRIGHTNESS_NORMAL, PLANEMASK_ALL, MASK_DOUBLE_DISPLAY);

		//�C�����Ă˃X�N���v�g
		
		//�b�������Ώۂ�OBJ���擾���鏈�����K�v�ɂȂ�
		//OS_Printf( "field_encount zone_id = %d\n", fsys->location->zone_id );
		if(	WARPDATA_GetInitializeID()
				== Situation_GetWarpID(SaveData_GetSituation(fsys->savedata))) {
			//�����l�̃��[�vID�����ŏ��̖߂��Ȃ̂Ŏ����̉�
			EventCall_Script( event, SCRID_GAME_OVER_RECOVER_MYHOME, NULL, NULL );
		}else{
			//����ȊO�����|�P�Z���̂͂�
			EventCall_Script( event, SCRID_GAME_OVER_RECOVER_PC, NULL, NULL );
		}
		(*seq) ++;
		break;

	case 6:
		//�T�E���h���X�^�[�g����(06/07/10����Ȃ��̂ō폜)
		//Snd_RestartSet( fsys );

		return TRUE;
	}
	return FALSE;
}


//-----------------------------------------------------------------------------
/**
 * @brief	�C�x���g�R�}���h�F�ʏ�S�ŏ���
 * @param	event		�C�x���g���䃏�[�N�ւ̃|�C���^
 */
//-----------------------------------------------------------------------------
void EventCmd_NormalLose(GMEVENT_CONTROL * event)
{
	FieldEvent_Call(event, GMEVENT_NormalGameOver, NULL);
}



