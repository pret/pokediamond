//==============================================================================================
/**
 * @file	d_nohara.c
 * @brief	�f�o�b�N�\�[�X
 * @author	Satoshi Nohara
 * @date	2005.07.26
 */
//==============================================================================================
#include "common.h"
#include "system/lib_pack.h"
#include "system/bmp_list.h"
#include "system/fontproc.h"
#include "system/pm_str.h"
#include "system/get_text.h"

#include "system/snd_tool.h"
#include "system/snd_perap.h"

#include "system/savedata.h"
#include "savedata/mystatus.h"
#include "savedata/zukanwork.h"

#include "fld_bgm.h"
#include "poketool/monsno.h"
#include "fieldmap.h"
#include "fieldsys.h"
#include "fld_bmp.h"
#include "mapdefine.h"						//ZONE_ID_C01
#include "script.h"							//EventSet_Script
#include "guinness_win.h"					//
#include "ev_mapchange.h"					//

#include "sysflag.h"
#include "syswork.h"

#include "btl_searcher.h"

#include "msgdata/msg.naix"
#include "msgdata/msg_debug_nohara.h"

#include "..\fielddata\script\t01r0202_def.h"		//SCRID_TRAINER_MOVE_SCRIPT
#include "..\fielddata\script\common_scr_def.h"		//SCRID_TRAINER_MOVE_SCRIPT
#include "..\fielddata\script\connect_def.h"		//SCRID_CONNECT_COLOSSEUM
#include "..\fielddata\script\trainer_def.h"		//SCRID_TANPAN_01
#include "..\fielddata\script\r201_def.h"			//SCRID_R201_FLAG_CHANGE
#include "..\fielddata\script\hiden_def.h"			//SCRID_R201_FLAG_CHANGE
#include "..\fielddata\script\con_reception_def.h"	//
#include "..\fielddata\script\pc_ug_def.h"	//
#include "..\fielddata\script\perap_def.h"	//
#include "..\fielddata\script\saisen_def.h"	//
#include "..\fielddata\script\debug_scr_def.h"	//

#include "itemtool/myitem.h"
#include "itemtool/itemsym.h"


//==============================================================================================
//
//	��`
//
//==============================================================================================
#define D_NOHARA_BMPWIN_MAX	(1)				//BMP�E�B���h�E�f�[�^�ő吔

typedef void (*voidFunc)(void* func);		//�֐��|�C���^�^


//==============================================================================================
//
//	�ϐ�
//
//==============================================================================================
static NNSSndCaptureOutputEffectType stereo_mono = NNS_SND_CAPTURE_OUTPUT_EFFECT_NORMAL;

//static s16 d_buf[ 32*100 ] ATTRIBUTE_ALIGN(32);	//�g�`�i�[�o�b�t�@(�����̊��H)


//==============================================================================================
//
//	�f�o�b�N�\����
//
//==============================================================================================
typedef struct{
	u8	seq;										//�����i���o�[
	u8	wave_buf_flag:1;							//�g�`�i�[�o�b�t�@���m�ۂ����t���O
	u8	waveout_flag:1;								//�����Đ����t���O
	u8	play_flag:6;								//�Đ����t���O
	s16 work;										//�ėp���[�N

	u16 list_bak;									//���X�g�ʒu�o�b�N�A�b�v
	u16 cursor_bak;									//�J�[�\���ʒu�o�b�N�A�b�v

	u32 sel;
	u32 count;										//�J�E���^�[
	u32 count2;										//�J�E���^�[

	FIELDSYS_WORK* fsys;							//

	GF_BGL_BMPWIN bmpwin[D_NOHARA_BMPWIN_MAX];		//BMP�E�B���h�E�f�[�^
	BMPLIST_WORK* lw;								//BMP���X�g�f�[�^

	BMPLIST_DATA* menulist;							//

//	s16* wave_buf;									//�g�`�i�[�o�b�t�@�̃|�C���^

	//STRBUF* msg_buf[EV_WIN_MENU_MAX];				//���b�Z�[�W�f�[�^�̃|�C���^
	MSGDATA_MANAGER* msgman;						//���b�Z�[�W�}�l�[�W���[
	WORDSET* wordset;								//�P��Z�b�g

}D_NOHARA_WORK;


//==============================================================================================
//
//	�v���g�^�C�v�錾
//
//==============================================================================================
void DebugNoharaMenuInit( FIELDSYS_WORK* fsys );

static void DebugNoharaMenuMain( TCB_PTR tcb, void * work );
static void TcbBmpDel( TCB_PTR tcb, void * work );
static void BmpDel( TCB_PTR tcb );
static void NumMsgSet( D_NOHARA_WORK* wk, GF_BGL_BMPWIN* win, int num, u8 x, u8 y );

void DebugBgmMenuInit( FIELDSYS_WORK* fsys );
void DebugScriptMenuInit( FIELDSYS_WORK* fsys );

static void D_Nohara_01( TCB_PTR tcb, void * work );
static void D_Nohara_02( TCB_PTR tcb, void * work );
static void D_Nohara_03( TCB_PTR tcb, void * work );
static void D_Nohara_04( TCB_PTR tcb, void * work );
static void D_Nohara_05( TCB_PTR tcb, void * work );
static void D_Nohara_06( TCB_PTR tcb, void * work );
static void D_Nohara_07( TCB_PTR tcb, void * work );
static void D_Nohara_08( TCB_PTR tcb, void * work );
static void D_Nohara_09( TCB_PTR tcb, void * work );
static void D_Nohara_10( TCB_PTR tcb, void * work );
static void D_Nohara_11( TCB_PTR tcb, void * work );
static void D_Nohara_12( TCB_PTR tcb, void * work );
static void D_Nohara_13( TCB_PTR tcb, void * work );
static void D_Nohara_14( TCB_PTR tcb, void * work );
static void D_Nohara_15( TCB_PTR tcb, void * work );
static void D_Nohara_16( TCB_PTR tcb, void * work );
static void D_Nohara_17( TCB_PTR tcb, void * work );
static void D_Nohara_18( TCB_PTR tcb, void * work );
static void D_Nohara_19( TCB_PTR tcb, void * work );
static void D_Nohara_20( TCB_PTR tcb, void * work );
static void D_Nohara_21( TCB_PTR tcb, void * work );
static void D_Nohara_22( TCB_PTR tcb, void * work );
static void D_Nohara_23( TCB_PTR tcb, void * work );
static void D_Nohara_24( TCB_PTR tcb, void * work );
static void D_Nohara_25( TCB_PTR tcb, void * work );
static void D_Nohara_26( TCB_PTR tcb, void * work );


//==============================================================================================
//
//	���X�g�f�[�^
//
//==============================================================================================
static const struct{
	u32  str_id;
	u32  param;
}DebugMenuList[] = {
	{ msg_debug_nohara_24, (u32)D_Nohara_24 },		//�o�g���T�[�`���[
	{ msg_debug_nohara_01, (u32)D_Nohara_01 },
	{ msg_debug_nohara_02, (u32)D_Nohara_02 },
	//{ msg_debug_nohara_03, (u32)D_Nohara_03 },
	{ msg_debug_nohara_04, (u32)D_Nohara_04 },
	{ msg_debug_nohara_05, (u32)D_Nohara_05 },
	{ msg_debug_nohara_06, (u32)D_Nohara_06 },
	{ msg_debug_nohara_07, (u32)D_Nohara_07 },
	{ msg_debug_nohara_08, (u32)D_Nohara_08 },
	//{ msg_debug_nohara_09, (u32)D_Nohara_09 },
	//{ msg_debug_nohara_10, (u32)D_Nohara_10 },
	{ msg_debug_nohara_11, (u32)D_Nohara_11 },
	//{ msg_debug_nohara_12, (u32)D_Nohara_12 },
	//{ msg_debug_nohara_13, (u32)D_Nohara_13 },
	{ msg_debug_nohara_14, (u32)D_Nohara_14 },
	{ msg_debug_nohara_15, (u32)D_Nohara_15 },		//�g�`�e�X�g
	//{ msg_debug_nohara_16, (u32)D_Nohara_16 },	//���C���V�i���I�i�s
	{ msg_debug_nohara_17, (u32)D_Nohara_17 },		//�o�b�W�t���O�Z�b�g
	{ msg_debug_nohara_18, (u32)D_Nohara_18 },		//�B���A�C�e�����X�g
	{ msg_debug_nohara_19, (u32)D_Nohara_19 },		//�L���v�`���`�F�b�N
	{ msg_debug_nohara_20, (u32)D_Nohara_20 },		//�M�l�X�E�B���h�E
	{ msg_debug_nohara_21, (u32)D_Nohara_21 },		//�f�o�b�N�W�����v
	{ msg_debug_nohara_22, (u32)D_Nohara_22 },		//�|�P�b�`�g�`�e�X�g
	//{ msg_debug_nohara_23, (u32)D_Nohara_23 },		//�}�ӁA�o�b�O�V�X�e���t���O�Z�b�g
};

static const BMPLIST_HEADER DebugListH = {
	NULL,					//�\�������f�[�^�|�C���^

	NULL,					//�J�[�\���ړ����Ƃ̃R�[���o�b�N�֐�
	NULL,					//���\�����Ƃ̃R�[���o�b�N�֐�

	NULL,					//GF_BGL_BMPWIN�̃|�C���^

	NELEMS(DebugMenuList),	//���X�g���ڐ�
	9,						//�\���ő區�ڐ�

	0,						//���x���\���w���W
	8,						//���ڕ\���w���W
	0,						//�J�[�\���\���w���W
	0,						//�\���x���W
/*
	FBMP_COL_BLACK,			//�����F
	FBMP_COL_WHITE,			//�w�i�F
	FBMP_COL_BLK_SDW,		//�����e�F
*/
	FBMP_COL_WHITE,			//�����F
	FBMP_COL_BLACK,			//�w�i�F
	FBMP_COL_BLK_SDW,		//�����e�F
	0,						//�����Ԋu�w
	16,						//�����Ԋu�x
	BMPLIST_LRKEY_SKIP,		//�y�[�W�X�L�b�v�^�C�v
	FONT_SYSTEM,			//�����w��(�{���� u8 �����ǁA����Ȃɍ��Ȃ��Ǝv���̂�)
	0						//�a�f�J�[�\��(allow)�\���t���O(0:ON,1:OFF)
};


//==============================================================================================
//
//	BMP�E�B���h�E
//
//==============================================================================================
enum{
	D_NOHARA_BMPWIN_FRAME	= GF_BGL_FRAME3_M,
	D_NOHARA_BMPWIN_PX1		= 1,
	D_NOHARA_BMPWIN_PY1		= 1,
	D_NOHARA_BMPWIN_SX		= 16,
	D_NOHARA_BMPWIN_SY		= 20,
	D_NOHARA_BMPWIN_PL		= FLD_SYSFONT_PAL,
	D_NOHARA_BMPWIN_CH		= 1,
};

static const BMPWIN_DAT	DebugNoharaWinData = {
	D_NOHARA_BMPWIN_FRAME,					//�E�C���h�E�g�p�t���[��
	D_NOHARA_BMPWIN_PX1,D_NOHARA_BMPWIN_PY1,//�E�C���h�E�̈�̍����X,Y���W�i�L�����P�ʂŎw��j
	D_NOHARA_BMPWIN_SX,	D_NOHARA_BMPWIN_SY,	//�E�C���h�E�̈��X,Y�T�C�Y�i�L�����P�ʂŎw��j
	D_NOHARA_BMPWIN_PL,						//�E�C���h�E�̈�̃p���b�g�i���o�[	
	D_NOHARA_BMPWIN_CH						//�E�C���h�E�L�����̈�̊J�n�L�����N�^�i���o�[
};


//==============================================================================================
//
//	�v���O����
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�f�o�b�N���j���[�Ăяo��(fld_debug.c)
 *
 * @param	fsys	FIELDSYS_WORK�^�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
void DebugNoharaMenuInit( FIELDSYS_WORK* fsys )
{
	int i;
	BMPLIST_HEADER list_h;
	D_NOHARA_WORK* wk;

	wk = (D_NOHARA_WORK*)TCB_GetWork( PMDS_taskAdd(DebugNoharaMenuMain, sizeof(D_NOHARA_WORK), 0, HEAPID_BASE_DEBUG) );

	wk->seq				= 0;
	wk->sel				= 0;
	wk->work			= 0;
	wk->wave_buf_flag	= 0;								//�g�`�i�[�o�b�t�@���m�ۂ����t���OOFF
	wk->waveout_flag	= 0;								//�����Đ����t���OOFF
	wk->fsys			= fsys;

	GF_BGL_BmpWinAddEx( wk->fsys->bgl, &wk->bmpwin[0], &DebugNoharaWinData );	//�r�b�g�}�b�v�ǉ�

	wk->menulist = BMP_MENULIST_Create( NELEMS(DebugMenuList), HEAPID_BASE_DEBUG );


	wk->wordset = WORDSET_Create( HEAPID_BASE_DEBUG );

	wk->msgman = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, 
								NARC_msg_debug_nohara_dat, HEAPID_BASE_DEBUG);

	for( i=0; i < NELEMS(DebugMenuList); i++ ){
		BMP_MENULIST_AddArchiveString( wk->menulist, wk->msgman, 
										DebugMenuList[i].str_id, DebugMenuList[i].param );
	}

	list_h			= DebugListH;
	list_h.list		= wk->menulist;
	list_h.win		= &wk->bmpwin[0];
	wk->lw			= BmpListSet( &list_h, 0, 0, HEAPID_BASE_DEBUG );

	GF_BGL_BmpWinOn( &wk->bmpwin[0] );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	�f�o�b�N���j���[���C��
 *
 * @param	tcb		TCB_PTR�^
 * @param	work	���[�N
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void DebugNoharaMenuMain( TCB_PTR tcb, void * work )
{
	u32	ret;
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	switch( wk->seq ){
	case 0:
		ret = BmpListMain( wk->lw );

		switch( ret ){
		case BMPLIST_NULL:
			break;
		case BMPLIST_CANCEL:
			TcbBmpDel( tcb, work );				//TCBBMP�J��

			//�g�`�Đ��p�`�����l�����J������
			Snd_DebugNormalChannelFree();

			break;
		default:
			wk->sel = ret;
			wk->seq++;
			break;
		};

		//BMP���X�g�̃��X�g�ʒu�A�J�[�\���ʒu���擾
		BmpListPosGet( wk->lw, &wk->list_bak, &wk->cursor_bak );
		break;

	case 1:
		{
			voidFunc func = (voidFunc)wk->sel;
			TCB_ChangeFunc( tcb, (void*)func );	//TCB�̓���֐��؂�ւ�
		}
		break;

	};

	return;
}

//--------------------------------------------------------------
/**
 * @brief	TCB,BMP�J��
 *
 * @param	tcb		TCB_PTR�^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void TcbBmpDel( TCB_PTR tcb, void * work )
{
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	MSGMAN_Delete( wk->msgman );
	WORDSET_Delete( wk->wordset );

#if 0
	//�g�`�i�[�o�b�t�@���m�ۂ����t���OON��������
	if( wk->wave_buf_flag == 1 ){
		sys_FreeMemoryEz( wk->wave_buf );	//�o�b�t�@�J��
	}
#endif

	BmpDel( tcb );						//BMP�J��
	PMDS_taskDel( tcb );				//TCB�J��
	FieldSystemProc_SeqHoldEnd();
	return;
}

//--------------------------------------------------------------
/**
 * @brief	BMP�J��
 *
 * @param	tcb		TCB_PTR�^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void BmpDel( TCB_PTR tcb )
{
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)TCB_GetWork(tcb);

	//BMP
	BMP_MENULIST_Delete( wk->menulist );
	BmpListExit( wk->lw, &wk->list_bak, &wk->cursor_bak );
	GF_BGL_BmpWinOff( &wk->bmpwin[0] );
	GF_BGL_BmpWinDel( &wk->bmpwin[0] );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	�������b�Z�[�W�\��
 *
 * @param	win_index	�r�b�g�}�b�vINDEX
 * @param	num			���l
 * @param	x			�\���ʒuX
 * @param	y			�\���ʒuY
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void NumMsgSet( D_NOHARA_WORK* wk, GF_BGL_BMPWIN* win, int num, u8 x, u8 y )
{
	STRBUF* tmp_buf	= STRBUF_Create( 12, HEAPID_BASE_DEBUG );
	STRBUF* tmp_buf2= STRBUF_Create( 12, HEAPID_BASE_DEBUG );

	MSGMAN_GetString( wk->msgman, msg_debug_nohara_num, tmp_buf );
	WORDSET_RegisterNumber(wk->wordset, 1, num, 4, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT);

	//�o�^���ꂽ�P����g���ĕ�����W�J����
	WORDSET_ExpandStr( wk->wordset, tmp_buf2, tmp_buf );

	GF_STR_PrintSimple( win, FONT_SYSTEM, tmp_buf2, x, y, MSG_NO_PUT, NULL );

	STRBUF_Delete( tmp_buf );
	STRBUF_Delete( tmp_buf2 );
	return;
}


//==============================================================================================
//
//	01	�t�Đ��֘A
//
//==============================================================================================
static void D_Nohara_01_Main( TCB_PTR tcb, void * work );

//extern BOOL Snd_ArcStrmStart( u16 no );

//--------------------------------------------------------------
/**
 * @brief	������
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_01( TCB_PTR tcb, void * work )
{
	int i;
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;
	wk->seq		= 0;
	wk->count	= 0;
	wk->work	= MONSNO_HUSIGIDANE;

#if 0
	Snd_CtrlBgmFlagSet( 1 );
	TcbBmpDel( tcb, work );		//TCBBMP�J��
	return;
#endif

	//BGM���~�߂�
	Snd_Stop();

#if 0
	Snd_PerapVoiceWazaParamGet( 0 );
	TcbBmpDel( tcb, work );		//TCBBMP�J��
	return;
#endif

#if 0
	//�X�g���[���Đ�����
	//Snd_ArcStrmStart( STRM_PV001 );
	Snd_ArcStrmStart( STRM_PV009 );
	TcbBmpDel( tcb, work );		//TCBBMP�J��
	return;
#endif

#if 0
	//�t���O�`�F�b�N
	OS_Printf( "===============\n " );
	OS_Printf( "===============\n " );
	for( i=0; i < 10 ;i++ ){
		OS_Printf( "flag %d = %d\n ", i ,CheckEventFlag( wk->fsys, i) );
	}
	TcbBmpDel( tcb, work );		//TCBBMP�J��
#else
	TCB_ChangeFunc( tcb, D_Nohara_01_Main );	//TCB�̓���֐��؂�ւ�
#endif
	return;
}

//--------------------------------------------------------------
/**
 * @brief	���C��
 *
 * @param	tcb		TCB_PTR�^
 * @param	work	���[�N
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_01_Main( TCB_PTR tcb, void * work )
{
	int ret,flag;
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	flag = 0;	//���������t���O

	if( wk->waveout_flag == 0 ){					//�����Đ����t���OOFF��������

		//�����Đ�
		if( sys.trg == PAD_BUTTON_A ){
			wk->waveout_flag = 1;					//�����Đ����t���OON
			return;		//���ӁI
		}

		if( (sys.repeat == PAD_KEY_UP) || (sys.cont == PAD_KEY_RIGHT) ){
			flag = 1;
			wk->work++;
			if( wk->work >= MONSNO_MAX ){
				wk->work = 1;
			}
		}

		if( (sys.repeat == PAD_KEY_DOWN) || (sys.cont == PAD_KEY_LEFT) ){
			flag = 1;
			wk->work--;
			if( wk->work <= 0 ){
				wk->work = (MONSNO_MAX - 1);
			}
		}

		//���������t���O�������Ă�����
		if( flag == 1 ){
			//�w��͈͂�h��Ԃ�
			GF_BGL_BmpWinFill( &wk->bmpwin[0], FBMP_COL_BLACK, 8*11, 0, 8*6, 8*2 );
	
			//�|�P�����i���o�[�\��
			NumMsgSet( wk, &wk->bmpwin[0], wk->work, 8*11, 2 );
			GF_BGL_BmpWinOn( &wk->bmpwin[0] );
		}

		//�I��
		if( sys.cont == PAD_BUTTON_B ){
			TcbBmpDel( tcb, work );				//TCBBMP�J��
		}

		return;	//���ӁI
	}


	switch( wk->seq ){
	case 0:
		ret = Snd_PMVoicePlay( wk->work );		//�ʏ�Đ�
		//OS_Printf( "normal play = %d\n", ret );
		wk->seq++;
		break;
	case 1:
		if( Snd_PMVoicePlayCheck() == 0 ){
			wk->count = 0;
			wk->seq++;
		}
		break;
	case 2:
		wk->count++;
		if( wk->count >= 15 ){							//�Ԃ�����
			Snd_WaveOutAllocChannel( WAVEOUT_CH_NORMAL );//�g�`�Đ��p�`�����l�����m�ۂ���
			ret = Snd_WaveOutStartReverse( wk->work, 60, 64, WAVEOUT_CH_NORMAL, 
											HEAPID_BASE_DEBUG );//�t�Đ�
			//OS_Printf( "reverse play = %d\n", ret );
			wk->count = 0;
			wk->seq++;
		}
		break;
	case 3:
		//�g�`�Đ������`�F�b�N
		if( Snd_WaveOutIsPlaying( WAVEOUT_CH_NORMAL ) == FALSE ){
			Snd_WaveOutStopReverse( WAVEOUT_CH_NORMAL );//�t�Đ���~buf�J��
			Snd_WaveOutFreeChannel( WAVEOUT_CH_NORMAL );//�g�`�Đ��p�`�����l�����J������
			wk->seq = 0;
			wk->count = 0;
			wk->waveout_flag = 0;				//�����Đ����t���OOFF
		}
		break;
	};

	return;
}


//==============================================================================================
//
//	02	���o�[�u�֘A
//
//==============================================================================================
static void D_Nohara_02_Main( TCB_PTR tcb, void * work );

//--------------------------------------------------------------
/**
 * @brief	������
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_02( TCB_PTR tcb, void * work )
{
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;
	wk->seq		= 0;
	wk->count	= 0;
	wk->work	= 0;
	TCB_ChangeFunc( tcb, D_Nohara_02_Main );	//TCB�̓���֐��؂�ւ�
	return;
}

//--------------------------------------------------------------
/**
 * @brief	���C��
 *
 * @param	tcb		TCB_PTR�^
 * @param	work	���[�N
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_02_Main( TCB_PTR tcb, void * work )
{
	int flag;
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	flag = 0;	//���������t���O

	if( (sys.repeat == PAD_KEY_UP) || (sys.cont == PAD_KEY_RIGHT) ){
		flag = 1;
		wk->work++;
		if( wk->work >= 64 ){
			wk->work = 0;
		}
	}

	if( (sys.repeat == PAD_KEY_DOWN) || (sys.cont == PAD_KEY_LEFT) ){
		flag = 1;
		wk->work--;
		if( wk->work < 0 ){
			wk->work = 63;
		}
	}

	//���������t���O�������Ă�����
	if( flag == 1 ){
		if( Snd_CaptureStartReverb( wk->work ) == FALSE ){
			OS_Printf( "���o�[�u���s�I\n" );
		}
	
		//�w��͈͂�h��Ԃ�
		GF_BGL_BmpWinFill( &wk->bmpwin[0], FBMP_COL_BLACK, 8*7, 8*2, 
								8*8, 8*2 );
	
		//���o�[�u�l�\��
		NumMsgSet( wk, &wk->bmpwin[0], wk->work, 8*7, 8*2 );
		GF_BGL_BmpWinOn( &wk->bmpwin[0] );
	}

	//�I��
	if( sys.cont == PAD_BUTTON_B ){
		TcbBmpDel( tcb, work );		//TCBBMP�J��
	}

	return;
}


//==============================================================================================
//
//	03	�g���b�N�t�F�[�h�֘A
//
//==============================================================================================
static void D_Nohara_03_Main( TCB_PTR tcb, void * work );

//--------------------------------------------------------------
/**
 * @brief	������
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_03( TCB_PTR tcb, void * work )
{
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;
	wk->seq		= 0;
	wk->count	= 0;
	wk->work	= 0;
	TCB_ChangeFunc( tcb, D_Nohara_03_Main );	//TCB�̓���֐��؂�ւ�
	return;
}

//--------------------------------------------------------------
/**
 * @brief	���C��
 *
 * @param	tcb		TCB_PTR�^
 * @param	work	���[�N
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_03_Main( TCB_PTR tcb, void * work )
{
#if 0
	int ret;
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	switch( wk->seq ){
	case 0:
		ret = Snd_TrackFadeCall(wk->fsys, Snd_FieldBgmNoGet(wk->fsys,wk->fsys->location->zone_id));	
		//OS_Printf( "track fade moon = %d\n", ret );
		wk->count	= 0;
		wk->seq++;
		break;
	case 1:
		wk->count++;
		if( wk->count >= 300 ){
			wk->count = 0;
			wk->seq++;
		}
		break;
	case 2:
		ret = Snd_TrackFadeCall(wk->fsys, Snd_FieldBgmNoGet(wk->fsys,wk->fsys->location->zone_id));
		//OS_Printf( "track fade night = %d\n", ret );
		wk->count	= 0;
		wk->seq++;
		break;
	case 3:
		wk->count++;
		if( wk->count >= 200 ){
			TcbBmpDel( tcb, work );		//TCBBMP�J��
		}
		break;
	};
#else
	TcbBmpDel( tcb, work );		//TCBBMP�J��
#endif
	return;
}


//==============================================================================================
//
//	04	FIELD BGM ���ʊ֘A
//
//==============================================================================================
static void D_Nohara_04_Main( TCB_PTR tcb, void * work );

//--------------------------------------------------------------
/**
 * @brief	������
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_04( TCB_PTR tcb, void * work )
{
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;
	wk->seq		= 0;
	wk->count	= 0;
	wk->work	= 0;
	TCB_ChangeFunc( tcb, D_Nohara_04_Main );	//TCB�̓���֐��؂�ւ�
	return;
}

//--------------------------------------------------------------
/**
 * @brief	���C��
 *
 * @param	tcb		TCB_PTR�^
 * @param	work	���[�N
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_04_Main( TCB_PTR tcb, void * work )
{
	int flag;
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	flag = 0;	//���������t���O

	if( (sys.repeat == PAD_KEY_UP) || (sys.cont == PAD_KEY_RIGHT) ){
		flag = 1;
		wk->work++;
		if( wk->work >= 128 ){
			wk->work = 0;
		}
	}

	if( (sys.repeat == PAD_KEY_DOWN) || (sys.cont == PAD_KEY_LEFT) ){
		flag = 1;
		wk->work--;
		if( wk->work < 0 ){
			wk->work = 127;
		}
	}

	//���������t���O�������Ă�����
	if( flag == 1 ){
		Snd_PlayerSetInitialVolume( SND_HANDLE_FIELD, wk->work );
	
		//�w��͈͂�h��Ԃ�
		GF_BGL_BmpWinFill( &wk->bmpwin[0], FBMP_COL_BLACK, 8*11, 8*6, 8*8, 8*2 );
	
		//���ʕ\��
		NumMsgSet( wk, &wk->bmpwin[0], wk->work, 8*11, 8*6 );
		GF_BGL_BmpWinOn( &wk->bmpwin[0] );
	}

	//�I��
	if( sys.cont == PAD_BUTTON_B ){
		TcbBmpDel( tcb, work );		//TCBBMP�J��
	}

	return;
}


//==============================================================================================
//
//	05	�����p�^�[���֘A
//
//==============================================================================================
static void D_Nohara_05_Main( TCB_PTR tcb, void * work );

static const struct{
	u32  str_id;
	u32  param;
}DebugMenuList05[] = {
	{ msg_debug_nohara_05_01, (u32)D_Nohara_05_Main },
	{ msg_debug_nohara_05_02, (u32)D_Nohara_05_Main },
	{ msg_debug_nohara_05_03, (u32)D_Nohara_05_Main },
	{ msg_debug_nohara_05_04, (u32)D_Nohara_05_Main },
	{ msg_debug_nohara_05_05, (u32)D_Nohara_05_Main },
	{ msg_debug_nohara_05_06, (u32)D_Nohara_05_Main },
	{ msg_debug_nohara_05_07, (u32)D_Nohara_05_Main },
	{ msg_debug_nohara_05_08, (u32)D_Nohara_05_Main },
	{ msg_debug_nohara_05_09, (u32)D_Nohara_05_Main },
	{ msg_debug_nohara_05_10, (u32)D_Nohara_05_Main },
	{ msg_debug_nohara_05_11, (u32)D_Nohara_05_Main },
	{ msg_debug_nohara_05_12, (u32)D_Nohara_05_Main },
	{ msg_debug_nohara_05_13, (u32)D_Nohara_05_Main },
};

static const BMPLIST_HEADER ListH05 = {
	NULL,					//�\�������f�[�^�|�C���^
	NULL,					//�J�[�\���ړ����Ƃ̃R�[���o�b�N�֐�
	NULL,					//���\�����Ƃ̃R�[���o�b�N�֐�

	NULL,					//GF_BGL_BMPWIN�̃|�C���^

	NELEMS(DebugMenuList05),//���X�g���ڐ�
	9,						//�\���ő區�ڐ�

	0,						//���x���\���w���W
	8,						//���ڕ\���w���W
	0,						//�J�[�\���\���w���W
	0,						//�\���x���W
/*
	FBMP_COL_BLACK,			//�����F
	FBMP_COL_WHITE,			//�w�i�F
	FBMP_COL_BLK_SDW,		//�����e�F
*/
	FBMP_COL_WHITE,			//�����F
	FBMP_COL_BLACK,			//�w�i�F
	FBMP_COL_BLK_SDW,		//�����e�F
	0,						//�����Ԋu�w
	16,						//�����Ԋu�x
	BMPLIST_LRKEY_SKIP,		//�y�[�W�X�L�b�v�^�C�v
	FONT_SYSTEM,			//�����w��(�{���� u8 �����ǁA����Ȃɍ��Ȃ��Ǝv���̂�)
	0						//�a�f�J�[�\��(allow)�\���t���O(0:ON,1:OFF)
};

//--------------------------------------------------------------
/**
 * @brief	������
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_05( TCB_PTR tcb, void * work )
{
	int i;
	BMPLIST_HEADER list_h;
	GF_BGL_BMPWIN* win;
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	BmpDel( tcb );								//BMP�J��

	wk->seq		= 0;
	wk->sel		= 0;
	wk->count	= MONSNO_HUSIGIDANE;

	GF_BGL_BmpWinAddEx( wk->fsys->bgl, &wk->bmpwin[0], &DebugNoharaWinData );	//�r�b�g�}�b�v�ǉ�

	wk->menulist = BMP_MENULIST_Create( NELEMS(DebugMenuList05), HEAPID_BASE_DEBUG );

	for( i=0; i < NELEMS(DebugMenuList05); i++ ){
		BMP_MENULIST_AddArchiveString( wk->menulist, wk->msgman, 
										DebugMenuList05[i].str_id, DebugMenuList05[i].param );
	}

	list_h			= ListH05;
	list_h.list		= wk->menulist;
	list_h.win		= &wk->bmpwin[0];
	wk->lw			= BmpListSet( &list_h, 0, 0, HEAPID_BASE_DEBUG );

	GF_BGL_BmpWinOn( &wk->bmpwin[0] );

	//TCB_ChangeFunc( tcb, D_Nohara_05_Main );	//TCB�̓���֐��؂�ւ�
	TCB_ChangeFunc( tcb, DebugNoharaMenuMain );	//TCB�̓���֐��؂�ւ�
	return;
}

//--------------------------------------------------------------
/**
 * @brief	���C��
 *
 * @param	tcb		TCB_PTR�^
 * @param	work	���[�N
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_05_Main( TCB_PTR tcb, void * work )
{
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	if( sys.cont & PAD_BUTTON_L ){
		wk->count--;
	}else if( sys.cont & PAD_BUTTON_R ){
		wk->count++;
	}

	//�|�P���������p�^�[���Z�b�g
	//monsno,pan,vol,ptn
	Snd_PMVoicePlayEx( (wk->cursor_bak+wk->list_bak),
						wk->count, 0, 127, 
						//MONSNO_HUSIGIDANE, 0, 127, 
						//MONSNO_HIKOZARU, (gf_rand() % 127), 127, 
						HEAPID_BASE_DEBUG ); 

	wk->seq = 0;
	TCB_ChangeFunc( tcb, DebugNoharaMenuMain );		//TCB�̓���֐��؂�ւ�
	return;
}


//==============================================================================================
//
//	06	�o�̓G�t�F�N�g�֘A
//
//==============================================================================================
static void D_Nohara_06_Main( TCB_PTR tcb, void * work );

static const struct{
	u32  str_id;
	u32  param;
}DebugMenuList06[] = {
	{ msg_debug_nohara_06_01, (u32)D_Nohara_06_Main },
	{ msg_debug_nohara_06_02, (u32)D_Nohara_06_Main },
	{ msg_debug_nohara_06_03, (u32)D_Nohara_06_Main },
	{ msg_debug_nohara_06_04, (u32)D_Nohara_06_Main },
};

static const BMPLIST_HEADER ListH06 = {
	NULL,					//�\�������f�[�^�|�C���^
	NULL,					//�J�[�\���ړ����Ƃ̃R�[���o�b�N�֐�
	NULL,					//���\�����Ƃ̃R�[���o�b�N�֐�

	NULL,					//GF_BGL_BMPWIN�̃|�C���^

	NELEMS(DebugMenuList06),//���X�g���ڐ�
	5,						//�\���ő區�ڐ�

	0,						//���x���\���w���W
	8,						//���ڕ\���w���W
	0,						//�J�[�\���\���w���W
	0,						//�\���x���W
/*
	FBMP_COL_BLACK,			//�����F
	FBMP_COL_WHITE,			//�w�i�F
	FBMP_COL_BLK_SDW,		//�����e�F
*/
	FBMP_COL_WHITE,			//�����F
	FBMP_COL_BLACK,			//�w�i�F
	FBMP_COL_BLK_SDW,		//�����e�F
	0,						//�����Ԋu�w
	16,						//�����Ԋu�x
	BMPLIST_LRKEY_SKIP,		//�y�[�W�X�L�b�v�^�C�v
	FONT_SYSTEM,			//�����w��(�{���� u8 �����ǁA����Ȃɍ��Ȃ��Ǝv���̂�)
	0						//�a�f�J�[�\��(allow)�\���t���O(0:ON,1:OFF)
};

//--------------------------------------------------------------
/**
 * @brief	������
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_06( TCB_PTR tcb, void * work )
{
	int i;
	BMPLIST_HEADER list_h;
	GF_BGL_BMPWIN* win;
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	BmpDel( tcb );								//BMP�J��

	//Snd_CaptureCreateThread();

	wk->seq		= 0;
	wk->sel		= 0;
	wk->count	= 0;

	GF_BGL_BmpWinAddEx( wk->fsys->bgl, &wk->bmpwin[0], &DebugNoharaWinData );	//�r�b�g�}�b�v�ǉ�

	wk->menulist = BMP_MENULIST_Create( NELEMS(DebugMenuList06), HEAPID_BASE_DEBUG );

	for( i=0; i < NELEMS(DebugMenuList06); i++ ){
		BMP_MENULIST_AddArchiveString( wk->menulist, wk->msgman, 
										DebugMenuList06[i].str_id, DebugMenuList06[i].param );
	}

	list_h			= ListH06;
	list_h.list		= wk->menulist;
	list_h.win		= &wk->bmpwin[0];
	wk->lw			= BmpListSet( &list_h, 0, 0, HEAPID_BASE_DEBUG );

	GF_BGL_BmpWinOn( &wk->bmpwin[0] );

	//TCB_ChangeFunc( tcb, D_Nohara_06_Main );	//TCB�̓���֐��؂�ւ�
	TCB_ChangeFunc( tcb, DebugNoharaMenuMain );	//TCB�̓���֐��؂�ւ�
	return;
}

//--------------------------------------------------------------
/**
 * @brief	���C��
 *
 * @param	tcb		TCB_PTR�^
 * @param	work	���[�N
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_06_Main( TCB_PTR tcb, void * work )
{
	NNSSndCaptureOutputEffectType stereo_mono;
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	switch( wk->cursor_bak ){
	case 1:
		stereo_mono = NNS_SND_CAPTURE_OUTPUT_EFFECT_MONO;
		break;
	case 2:
		stereo_mono = NNS_SND_CAPTURE_OUTPUT_EFFECT_SURROUND;
		break;
	case 3:
		stereo_mono = NNS_SND_CAPTURE_OUTPUT_EFFECT_HEADPHONE;
		break;
	default:
		stereo_mono = NNS_SND_CAPTURE_OUTPUT_EFFECT_NORMAL;
		break;
	}

	Snd_CaptureStartOutputEffect( stereo_mono );
	//Snd_CaptureChangeOutputEffect( stereo_mono );

	TcbBmpDel( tcb, work );		//TCBBMP�J��
	return;
}


//==============================================================================================
//
//	07	�}�C�N�֘A
//
//==============================================================================================
static void D_Nohara_07_Main( TCB_PTR tcb, void * work );

static const struct{
	u32  str_id;
	u32  param;
}DebugMenuList07[] = {
	{ msg_debug_nohara_07_01, (u32)D_Nohara_07_Main },
	{ msg_debug_nohara_07_02, (u32)D_Nohara_07_Main },
	{ msg_debug_nohara_07_03, (u32)D_Nohara_07_Main },
	{ msg_debug_nohara_07_04, (u32)D_Nohara_07_Main },
	{ msg_debug_nohara_07_05, (u32)D_Nohara_07_Main },
	{ msg_debug_nohara_07_06, (u32)D_Nohara_07_Main },
};

static const BMPLIST_HEADER ListH07 = {
	NULL,					//�\�������f�[�^�|�C���^
	NULL,					//�J�[�\���ړ����Ƃ̃R�[���o�b�N�֐�
	NULL,					//���\�����Ƃ̃R�[���o�b�N�֐�

	NULL,					//GF_BGL_BMPWIN�̃|�C���^

	NELEMS(DebugMenuList07),//���X�g���ڐ�
	6,						//�\���ő區�ڐ�

	0,						//���x���\���w���W
	8,						//���ڕ\���w���W
	0,						//�J�[�\���\���w���W
	0,						//�\���x���W
/*
	FBMP_COL_BLACK,			//�����F
	FBMP_COL_WHITE,			//�w�i�F
	FBMP_COL_BLK_SDW,		//�����e�F
*/
	FBMP_COL_WHITE,			//�����F
	FBMP_COL_BLACK,			//�w�i�F
	FBMP_COL_BLK_SDW,		//�����e�F
	0,						//�����Ԋu�w
	16,						//�����Ԋu�x
	BMPLIST_LRKEY_SKIP,		//�y�[�W�X�L�b�v�^�C�v
	FONT_SYSTEM,			//�����w��(�{���� u8 �����ǁA����Ȃɍ��Ȃ��Ǝv���̂�)
	0						//�a�f�J�[�\��(allow)�\���t���O(0:ON,1:OFF)
};

//--------------------------------------------------------------
/**
 * @brief	������
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_07( TCB_PTR tcb, void * work )
{
	int i;
	BMPLIST_HEADER list_h;
	GF_BGL_BMPWIN* win;
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	BmpDel( tcb );								//BMP�J��

#if 0
	//�o�b�t�@�m��
	wk->wave_buf = sys_AllocMemory( HEAPID_BASE_DEBUG, WAVE_SAMPLE );
	if( wk->wave_buf == NULL ){
		GF_ASSERT( (0) && "�������m�ۂɎ��s���܂����I" );
	}
	memset( wk->wave_buf, 0, WAVE_SAMPLE );
#endif

	//�g�`�Đ��p�`�����l�����m�ۂ���
	Snd_WaveOutAllocChannel( WAVEOUT_CH_NORMAL );

	wk->seq				= 0;
	wk->sel				= 0;
	wk->count			= 0;
	wk->wave_buf_flag	= 1;					//�g�`�i�[�o�b�t�@���m�ۂ����t���OON

	GF_BGL_BmpWinAddEx( wk->fsys->bgl, &wk->bmpwin[0], &DebugNoharaWinData );	//�r�b�g�}�b�v�ǉ�

	wk->menulist = BMP_MENULIST_Create( NELEMS(DebugMenuList07), HEAPID_BASE_DEBUG );

	for( i=0; i < NELEMS(DebugMenuList07); i++ ){
		BMP_MENULIST_AddArchiveString( wk->menulist, wk->msgman, 
										DebugMenuList07[i].str_id, DebugMenuList07[i].param );
	}

	list_h			= ListH07;
	list_h.list		= wk->menulist;
	list_h.win		= &wk->bmpwin[0];
	wk->lw			= BmpListSet( &list_h, 0, 0, HEAPID_BASE_DEBUG );

	GF_BGL_BmpWinOn( &wk->bmpwin[0] );

	//TCB_ChangeFunc( tcb, D_Nohara_07_Main );	//TCB�̓���֐��؂�ւ�
	TCB_ChangeFunc( tcb, DebugNoharaMenuMain );	//TCB�̓���֐��؂�ւ�
	return;
}
 
//--------------------------------------------------------------
/**
 * @brief	���C��
 *
 * @param	tcb		TCB_PTR�^
 * @param	work	���[�N
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_07_Main( TCB_PTR tcb, void * work )
{
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	switch( wk->cursor_bak ){
	case 0:
		//�^���J�n
		Snd_PerapVoiceRecStart();
		break;

	case 1:
		//�^����~
		Snd_PerapVoiceRecStop();
		break;

	case 2:
		//�����̂؃��b�v�̘^�������f�[�^���Đ�
		Snd_PerapVoicePlay( SaveData_GetPerapVoice(wk->fsys->savedata), PM_MALE, 127, 64 );
		break;

	case 3:
		Snd_PMVoiceStop( 0 );
		break;

	case 4:
		//�^�������f�[�^�������̂؃��b�v�f�[�^�ɃR�s�[
		Snd_PerapVoiceDataSave( SaveData_GetPerapVoice(wk->fsys->savedata) );
		break;

	default:
		//�N��
		EventSet_Script( wk->fsys, SCRID_PERAP, NULL );
		TcbBmpDel( tcb, work );		//TCBBMP�J��
		return;
	};

	wk->seq = 0;
	TCB_ChangeFunc( tcb, DebugNoharaMenuMain );		//TCB�̓���֐��؂�ւ�
	return;
}


//==============================================================================================
//
//	08	FIELD TEMPO ���ʊ֘A
//
//==============================================================================================
static void D_Nohara_08_Main( TCB_PTR tcb, void * work );

//--------------------------------------------------------------
/**
 * @brief	������
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_08( TCB_PTR tcb, void * work )
{
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;
	wk->seq		= 0;
	wk->count	= 0;
	wk->work	= 256;
	TCB_ChangeFunc( tcb, D_Nohara_08_Main );	//TCB�̓���֐��؂�ւ�
	return;
}

//--------------------------------------------------------------
/**
 * @brief	���C��
 *
 * @param	tcb		TCB_PTR�^
 * @param	work	���[�N
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_08_Main( TCB_PTR tcb, void * work )
{
	int flag;
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	flag = 0;	//���������t���O

	if( (sys.repeat == PAD_KEY_UP) || (sys.cont == PAD_KEY_RIGHT) ){
		flag = 1;
		wk->work++;
		if( wk->work >= 512 ){
			wk->work = 64;
		}
	}

	if( (sys.repeat == PAD_KEY_DOWN) || (sys.cont == PAD_KEY_LEFT) ){
		flag = 1;
		wk->work--;
		if( wk->work < 64 ){
			wk->work = 512;
		}
	}

	//���������t���O�������Ă�����
	if( flag == 1 ){
		Snd_PlayerSetTempoRatio( SND_HANDLE_FIELD, wk->work );
	
		//�w��͈͂�h��Ԃ�
		GF_BGL_BmpWinFill( &wk->bmpwin[0], FBMP_COL_BLACK, 8*11, 8*14, 8*8, 8*2 );
	
		//�e���|�\��
		NumMsgSet( wk, &wk->bmpwin[0], wk->work, 8*11, 8*14 );
		GF_BGL_BmpWinOn( &wk->bmpwin[0] );
	}

	//�I��
	if( sys.cont == PAD_BUTTON_B ){
		TcbBmpDel( tcb, work );		//TCBBMP�J��
	}

	return;
}


//==============================================================================================
//
//	09	�X�N���v�g�֘A
//
//==============================================================================================
static void D_Nohara_09_Main( TCB_PTR tcb, void * work );

//--------------------------------------------------------------
/**
 * @brief	������
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_09( TCB_PTR tcb, void * work )
{
	TcbBmpDel( tcb, work );		//TCBBMP�J��
	return;
}


//==============================================================================================
//
//	10	�g���b�N�t�F�[�h�t���O����
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	������
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_10( TCB_PTR tcb, void * work )
{
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	//�؂�ւ�
	//debug_track_fade_flag = 1;

	TcbBmpDel( tcb, work );		//TCBBMP�J��
	return;
}


//==============================================================================================
//
//	11	�X�N���v�g���s�֘A
//
//==============================================================================================
static void D_Nohara_11_Main( TCB_PTR tcb, void * work );

static const struct{
	u32  str_id;
	u32  param;
}DebugMenuList11[] = {
	{ msg_debug_nohara_11_01, (u32)D_Nohara_11_Main },
	{ msg_debug_nohara_11_02, (u32)D_Nohara_11_Main },
	{ msg_debug_nohara_11_03, (u32)D_Nohara_11_Main },
};

static const BMPLIST_HEADER ListH11 = {
	NULL,					//�\�������f�[�^�|�C���^
	NULL,					//�J�[�\���ړ����Ƃ̃R�[���o�b�N�֐�
	NULL,					//���\�����Ƃ̃R�[���o�b�N�֐�

	NULL,					//GF_BGL_BMPWIN�̃|�C���^

	NELEMS(DebugMenuList11),//���X�g���ڐ�
	10,						//�\���ő區�ڐ�

	0,						//���x���\���w���W
	8,						//���ڕ\���w���W
	0,						//�J�[�\���\���w���W
	0,						//�\���x���W
/*
	FBMP_COL_BLACK,			//�����F
	FBMP_COL_WHITE,			//�w�i�F
	FBMP_COL_BLK_SDW,		//�����e�F
*/
	FBMP_COL_WHITE,			//�����F
	FBMP_COL_BLACK,			//�w�i�F
	FBMP_COL_BLK_SDW,		//�����e�F
	0,						//�����Ԋu�w
	16,						//�����Ԋu�x
	BMPLIST_LRKEY_SKIP,		//�y�[�W�X�L�b�v�^�C�v
	FONT_SYSTEM,			//�����w��(�{���� u8 �����ǁA����Ȃɍ��Ȃ��Ǝv���̂�)
	0						//�a�f�J�[�\��(allow)�\���t���O(0:ON,1:OFF)
};

//--------------------------------------------------------------
/**
 * @brief	������
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_11( TCB_PTR tcb, void * work )
{
	int i;
	BMPLIST_HEADER list_h;
	GF_BGL_BMPWIN* win;
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	BmpDel( tcb );								//BMP�J��

	wk->seq				= 0;
	wk->sel				= 0;
	wk->count			= 0;

	GF_BGL_BmpWinAddEx( wk->fsys->bgl, &wk->bmpwin[0], &DebugNoharaWinData );	//�r�b�g�}�b�v�ǉ�

	wk->menulist = BMP_MENULIST_Create( NELEMS(DebugMenuList11), HEAPID_BASE_DEBUG );

	for( i=0; i < NELEMS(DebugMenuList11); i++ ){
		BMP_MENULIST_AddArchiveString( wk->menulist, wk->msgman, 
										DebugMenuList11[i].str_id, DebugMenuList11[i].param );
	}

	list_h			= ListH11;
	list_h.list		= wk->menulist;
	list_h.win		= &wk->bmpwin[0];
	wk->lw			= BmpListSet( &list_h, 0, 0, HEAPID_BASE_DEBUG );

	GF_BGL_BmpWinOn( &wk->bmpwin[0] );

	//TCB_ChangeFunc( tcb, D_Nohara_11_Main );	//TCB�̓���֐��؂�ւ�
	TCB_ChangeFunc( tcb, DebugNoharaMenuMain );	//TCB�̓���֐��؂�ւ�
	return;
}
 
//--------------------------------------------------------------
/**
 * @brief	���C��
 *
 * @param	tcb		TCB_PTR�^
 * @param	work	���[�N
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_11_Main( TCB_PTR tcb, void * work )
{
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	switch( wk->cursor_bak ){
	case 0:
		//C07�̑q�ɂ̌��o��������
		SpScriptStart( wk->fsys, SCRID_DEBUG_C07_SOUKONOKAGI );
		break;

	case 1:
		//�R�̌΃C�x���g�J�n
		SpScriptStart( wk->fsys, SCRID_DEBUG_L01_L02_L03_LAKE );
		break;

	case 2:
		//�|�P�Z���n���X�g�b�p�[�폜�A�Ƃ������蒠�C�x���g����
		SpScriptStart( wk->fsys, SCRID_DEBUG_PC_UG );
		break;

	default:
		//EventSet_Script( wk->fsys, SCRID_TANPAN_01, NULL );
		TcbBmpDel( tcb, work );		//TCBBMP�J��
		return;
	};

	wk->seq = 0;
	TCB_ChangeFunc( tcb, DebugNoharaMenuMain );		//TCB�̓���֐��؂�ւ�
	return;
}


//==============================================================================================
//
//	12	��������
//
//==============================================================================================
static void D_Nohara_12_Main( TCB_PTR tcb, void * work );

#define D_NOHARA_12_PITCH_MAX	(128)					//64�Ŕ����A�S����128
#define D_NOHARA_12_PTN_MAX		(5)						//�p�^�[����
#define D_NOHARA_12_SEQ_NO		(SEQ_SE_DP_BADGE_C)		//�V�[�P���X�i���o�[
#define D_NOHARA_12_WAIT		(30)					//�E�F�C�g

//--------------------------------------------------------------
/**
 * @brief	������
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_12( TCB_PTR tcb, void * work )
{
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;
	wk->seq		= 0;
	wk->count	= 0;
	wk->count2	= 0;
	wk->work	= 0;

	Snd_BgmFadeOut( BGM_VOL_ZUKAN, BGM_FADE_ZUKAN_TIME );

	TCB_ChangeFunc( tcb, D_Nohara_12_Main );	//TCB�̓���֐��؂�ւ�
	return;
}

//--------------------------------------------------------------
/**
 * @brief	���C��
 *
 * @param	tcb		TCB_PTR�^
 * @param	work	���[�N
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_12_Main( TCB_PTR tcb, void * work )
{
#if 0
	int ret,flag,pitch,i;
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	//�t�F�[�h�I���҂�
	if( Snd_FadeCheck() != 0 ){
		return; //�������Ȃ�
	}

	flag = 0;	//���������t���O

	if( wk->play_flag == 0 ){						//�Đ����t���OOFF��������

		//�Đ�
		if( sys.trg == PAD_BUTTON_A ){
			wk->play_flag = 1;					//�Đ����t���OON
			return;		//���ӁI
		}

		if( (sys.repeat == PAD_KEY_UP) || (sys.cont == PAD_KEY_RIGHT) ){
			flag = 1;
			wk->work++;
			if( wk->work >= D_NOHARA_12_PITCH_MAX ){
				wk->work = 0;
			}
		}

		if( (sys.repeat == PAD_KEY_DOWN) || (sys.cont == PAD_KEY_LEFT) ){
			flag = 1;
			if( wk->work <= 0 ){
				wk->work = D_NOHARA_12_PITCH_MAX;
			}
			wk->work--;
		}

		//���������t���O�������Ă�����
		if( flag == 1 ){
			//�w��͈͂�h��Ԃ�
			GF_BGL_BmpWinFill( &wk->bmpwin[0], FBMP_COL_BLACK, 8*11, 0, 8*6, 8*2 );
	
			//�|�P�����i���o�[�\��
			NumMsgSet( wk, &wk->bmpwin[0], wk->work, 8*11, 2 );
			GF_BGL_BmpWinOn( &wk->bmpwin[0] );
		}

		//�I��
		if( sys.cont == PAD_BUTTON_B ){
			Snd_BgmFadeIn( BGM_VOL_MAX, 0, BGM_FADEIN_START_VOL_NOW );
			TcbBmpDel( tcb, work );				//TCBBMP�J��
		}

		return;	//���ӁI
	}

	switch( wk->seq ){
	case 0:
		Snd_SePlay( D_NOHARA_12_SEQ_NO );

		//�Ō�̉��́A�����𗐂��Ȃ�
		if( wk->count < 4 ){
			//wk->work							= �����ω��ő�l
			//wk->work / D_NOHARA_12_PTN_MAX	= �����ω�1���̒l
			//D_NOHARA_12_PTN_MAX - wk->count	= ���p�^�[���ڂ�(DEBUG_PTN_MAX�ɋ߂��قǗ���Ă���)
			pitch = ( (wk->work/D_NOHARA_12_PTN_MAX) * (D_NOHARA_12_PTN_MAX-wk->count) );

			//�v���C���[�����܂��Ă��Ȃ��̂ŁA�SSE�v���C���[�ɑ΂��đ��삷��
			for( i=0; i < SE_HANDLE_MAX ;i++ ){
				Snd_PlayerSetTrackPitch( SND_HANDLE_SE_1+i, 0xffff, pitch );
			}
		}

		wk->count2 = 0;							//�E�F�C�g�J�E���^�[�N���A
		wk->seq++;
		break;
	case 1:
		if( Snd_SePlayCheck( D_NOHARA_12_SEQ_NO ) == 0 ){

			//�E�F�C�g�`�F�b�N
			wk->count2++;
			if( wk->count2 < D_NOHARA_12_WAIT ){
				return;
			}

			wk->count++;						//�p�^�[���C���N�������g
			wk->seq = 0;						//�V�[�P���X��߂�

			if( wk->count >= D_NOHARA_12_PTN_MAX ){
				wk->seq = 0;
				wk->count = 0;
				wk->play_flag = 0;				//�Đ����t���OOFF
			}
		}
		break;
	};
#endif

	return;
}


//==============================================================================================
//
//	13	��������2
//
//==============================================================================================
static void D_Nohara_13_Main( TCB_PTR tcb, void * work );

#define D_NOHARA_13_SEQ_NO		(SEQ_SE_DP_BADGE_C)		//�V�[�P���X�i���o�[
#define D_NOHARA_13_WAIT		(1)//(5)//(10)//(30)					//�E�F�C�g

//����̒i�K
enum{
	P_0 = 0,			//�����̂���Ȃ�
	P_1 = 16,			//
	P_2 = 32,			//
	P_3 = 64,			//��������
	P_4 = 96,			//
};

//��{����
enum{
	P_C = 0,			//C
	P_D = (64*2),		//D
	P_E = (64*4),		//E
	P_F = (64*5),		//F
	P_G = (64*7),		//G
	P_A = (64*9),		//A
	P_B = (64*11),		//B
	PCC = (64*12),		//C
};

//�����e�[�u��
static const u16 pitch_tbl[][8] = {
	{ P_C, P_D,	P_E, P_F, P_G, P_A, P_B, PCC },							//��������Ȃ�
	{ P_C+P_3, P_D, P_E+P_2, P_F, P_G+P_3, P_A+P_2, P_B+P_4, PCC },		//�傫������
	{ P_C+P_1, P_D, P_E+P_1, P_F, P_G+P_1, P_A+P_1, P_B+P_1, PCC+P_1 },	//��������
};
#define D_NOHARA_13_PITCH_TBL_MAX	( NELEMS(pitch_tbl) )

//--------------------------------------------------------------
/**
 * @brief	������
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_13( TCB_PTR tcb, void * work )
{
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;
	wk->seq		= 0;
	wk->count	= 0;
	wk->count2	= 0;
	wk->work	= 0;

	Snd_BgmFadeOut( BGM_VOL_ZUKAN, BGM_FADE_ZUKAN_TIME );

	TCB_ChangeFunc( tcb, D_Nohara_13_Main );	//TCB�̓���֐��؂�ւ�
	return;
}

//--------------------------------------------------------------
/**
 * @brief	���C��
 *
 * @param	tcb		TCB_PTR�^
 * @param	work	���[�N
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_13_Main( TCB_PTR tcb, void * work )
{
#if 0
	int ret,flag,pitch,i;
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	//�t�F�[�h�I���҂�
	if( Snd_FadeCheck() != 0 ){
		return; //�������Ȃ�
	}

	flag = 0;	//���������t���O

	if( wk->play_flag == 0 ){						//�Đ����t���OOFF��������

		//�Đ�
		if( sys.trg == PAD_BUTTON_A ){
			wk->play_flag = 1;					//�Đ����t���OON
			return;		//���ӁI
		}

		if( (sys.repeat == PAD_KEY_UP) || (sys.cont == PAD_KEY_RIGHT) ){
			flag = 1;
			wk->work++;
			if( wk->work >= D_NOHARA_13_PITCH_TBL_MAX ){
				wk->work = 0;
			}
		}

		if( (sys.repeat == PAD_KEY_DOWN) || (sys.cont == PAD_KEY_LEFT) ){
			flag = 1;
			if( wk->work <= 0 ){
				wk->work = D_NOHARA_13_PITCH_TBL_MAX;
			}
			wk->work--;
		}

		//���������t���O�������Ă�����
		if( flag == 1 ){
			//�w��͈͂�h��Ԃ�
			GF_BGL_BmpWinFill( &wk->bmpwin[0], FBMP_COL_BLACK, 8*11, 0, 8*6, 8*2 );
	
			//�|�P�����i���o�[�\��
			NumMsgSet( wk, &wk->bmpwin[0], wk->work, 8*11, 2 );
			GF_BGL_BmpWinOn( &wk->bmpwin[0] );
		}

		//�I��
		if( sys.cont == PAD_BUTTON_B ){
			Snd_BgmFadeIn( BGM_VOL_MAX, 0, BGM_FADEIN_START_VOL_NOW );
			TcbBmpDel( tcb, work );				//TCBBMP�J��
		}

		return;	//���ӁI
	}

	switch( wk->seq ){
	case 0:
		//if( Snd_SePlayCheck( D_NOHARA_13_SEQ_NO ) == 0 ){

			//����ȍĐ��I
			//�Đ�����n���h���A�v���C���[�𑀍삵�Ă���I
			//Snd_SePlay( D_NOHARA_13_SEQ_NO );
			Snd_ArcPlayerStartSeqEx( SND_HANDLE_SE_1+(wk->count&0x3), 
										PLAYER_SE_1+(wk->count&0x3), D_NOHARA_13_SEQ_NO );

			//�v���C���[�����܂��Ă��Ȃ��̂ŁA�SSE�v���C���[�ɑ΂��đ��삷��
			for( i=0; i < SE_HANDLE_MAX ;i++ ){
				Snd_PlayerSetTrackPitch( SND_HANDLE_SE_1+i, 0xffff,pitch_tbl[wk->work][wk->count] );
			}

			wk->count2 = 0;								//�E�F�C�g�J�E���^�[�N���A
			wk->count++;
			wk->seq++;

			if( wk->count >= 8 ){
				wk->seq = 0;
				wk->count = 0;
				wk->play_flag = 0;						//�Đ����t���OOFF
				return;
			}
		//}
		break;
	case 1:
		//�E�F�C�g�`�F�b�N
		wk->count2++;
		if( wk->count2 < D_NOHARA_13_WAIT ){
			return;
		}

		wk->count2 = 0;									//�E�F�C�g�J�E���^�[�N���A
		wk->seq = 0;									//�V�[�P���X��߂�
		break;
	};

#endif
	return;
}


//==============================================================================================
//
//	14	�T�E���h�G�t�F�N�g
//
//==============================================================================================
static void D_Nohara_14_Main( TCB_PTR tcb, void * work );

//--------------------------------------------------------------
/**
 * @brief	������
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_14( TCB_PTR tcb, void * work )
{
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;
	wk->seq		= 0;
	wk->count	= 0;
	wk->count2	= 0;
	wk->work	= 0;
	Snd_CaptureStartEffect();
	TCB_ChangeFunc( tcb, D_Nohara_14_Main );	//TCB�̓���֐��؂�ւ�
	return;
}

//--------------------------------------------------------------
/**
 * @brief	���C��
 *
 * @param	tcb		TCB_PTR�^
 * @param	work	���[�N
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_14_Main( TCB_PTR tcb, void * work )
{
	D_NOHARA_WORK* wk;
	int flag = 0;

	wk = (D_NOHARA_WORK*)work;

	//�Đ�
	//if( sys.trg == PAD_BUTTON_A ){
	//	Snd_CaptureStartEffect();
	//	return;
	//}
	
	if( (sys.repeat == PAD_KEY_UP) || (sys.cont == PAD_KEY_RIGHT) ){
		flag = 1;
		wk->work++;
		if( wk->work > 8 ){
			wk->work = 8;
		}
	}

	if( (sys.repeat == PAD_KEY_DOWN) || (sys.cont == PAD_KEY_LEFT) ){
		flag = 1;
		wk->work--;
		if( wk->work < 0 ){
			wk->work = 0;
		}
	}

	//���������t���O�������Ă�����
	if( flag == 1 ){
		//�w��͈͂�h��Ԃ�
		GF_BGL_BmpWinFill( &wk->bmpwin[0], FBMP_COL_BLACK, 8*11, 0, 8*6, 8*2 );

		//�|�P�����i���o�[�\��
		NumMsgSet( wk, &wk->bmpwin[0], wk->work, 8*11, 2 );
		GF_BGL_BmpWinOn( &wk->bmpwin[0] );

		//�G�t�F�N�g���x���Z�b�g
		Snd_CaptureEffectLevel( wk->work );
	}

	//��~�A�I��
	if( sys.cont == PAD_BUTTON_B ){
		Snd_CaptureStopEffect();
		TcbBmpDel( tcb, work );				//TCBBMP�J��
		return;
	}

	return;
}


//==============================================================================================
//
//	15	�����g�`�֘A
//
//==============================================================================================
static void D_Nohara_15_Main( TCB_PTR tcb, void * work );

u32 now_tick;									//���݂̃e�B�b�N��

//--------------------------------------------------------------
/**
 * @brief	������
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_15( TCB_PTR tcb, void * work )
{
	int i;
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;
	wk->seq		= 0;
	wk->count	= 0;
	wk->work	= MONSNO_HUSIGIDANE;
	TCB_ChangeFunc( tcb, D_Nohara_15_Main );	//TCB�̓���֐��؂�ւ�
	return;
}

u8 test_buf[9];	//
const SNDWaveData* pw_data;
//--------------------------------------------------------------
/**
 * @brief	���C��
 *
 * @param	tcb		TCB_PTR�^
 * @param	work	���[�N
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_15_Main( TCB_PTR tcb, void * work )
{
	int ret,flag,i;
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	flag = 0;	//���������t���O

	if( wk->waveout_flag == 0 ){					//�����Đ����t���OOFF��������

		//�����Đ�
		if( sys.trg == PAD_BUTTON_A ){
			wk->waveout_flag = 1;					//�����Đ����t���OON
			return;		//���ӁI
		}

		if( (sys.repeat == PAD_KEY_UP) || (sys.cont == PAD_KEY_RIGHT) ){
			flag = 1;
			wk->work++;
			if( wk->work >= MONSNO_MAX ){
				wk->work = 1;
			}
		}

		if( (sys.repeat == PAD_KEY_DOWN) || (sys.cont == PAD_KEY_LEFT) ){
			flag = 1;
			wk->work--;
			if( wk->work <= 0 ){
				wk->work = (MONSNO_MAX - 1);
			}
		}

		//���������t���O�������Ă�����
		if( flag == 1 ){
			//�w��͈͂�h��Ԃ�
			GF_BGL_BmpWinFill( &wk->bmpwin[0], FBMP_COL_BLACK, 8*11, 0, 8*6, 8*2 );
	
			//�|�P�����i���o�[�\��
			NumMsgSet( wk, &wk->bmpwin[0], wk->work, 8*11, 2 );
			GF_BGL_BmpWinOn( &wk->bmpwin[0] );
		}

		//�I��
		if( sys.cont == PAD_BUTTON_B ){
			TcbBmpDel( tcb, work );				//TCBBMP�J��
		}

		return;	//���ӁI
	}

	switch( wk->seq ){
	case 0:
#if 1
		now_tick = 0;
		//Snd_ZukanWaveDataSet( wk->work );							//�g�`�f�[�^�̃A�h���X�擾
		pw_data = Snd_ZukanWaveDataSet( wk->work );					//�g�`�f�[�^�̃A�h���X�擾
		OS_Printf( "pw_data size = %d\n", Snd_WaveDataSampleSizeGet( pw_data ) );
		//Snd_DebugWaveDataPut( 0, 1000 );							//�g�`�f�[�^�\��
		
		for( i=0; i < 9 ;i++ ){
			test_buf[i] = 0;
		}

		ret = Snd_PMVoicePlay( wk->work );							//�ʏ�Đ�

		//��������
		if( sys.cont & PAD_BUTTON_L ){
			//Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, -64 * 12 );
			Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, 64 * 12 );
		}
#endif

		//pw_data = Snd_ZukanWaveDataSet( wk->work );					//�g�`�f�[�^�̃A�h���X�擾
		//Snd_PMVoicePlayPtn_ZukanChorus( 1, 0 );
		//Snd_PMVoicePlayPtn_ZukanChorus( 1, 80 );

		wk->seq++;
		break;
	case 1:
		if( Snd_PMVoicePlayCheck() == 0 ){
			wk->count = 0;
			wk->seq++;
		}else{
			{
				u32 tmp,old_tick;

#if 0
				old_tick = now_tick;								//�ޔ�
				//now_tick = Snd_ZukanPlayerGetTick();				//�e�B�b�N���擾
				now_tick = Snd_PlayerGetSampleTick( SND_HANDLE_PMVOICE, pw_data );	//�e�B�b�N���擾

				//240(��) - 180(�O) = 60(��)
				//60 / 2 = 30
				//240 - 30 = 210(����)
				tmp = (now_tick - ((now_tick-old_tick) / 2));
				Snd_DebugWaveDataPut( pw_data, tmp, tmp+1 );					//�O��Ƃ̒��Ԉʒu

				Snd_DebugWaveDataPut( pw_data, now_tick, now_tick+1 );		//���݂̈ʒu
				Snd_DebugWaveLevelGet( now_tick );					//���x��
#endif

				//���x���擾
				Snd_ZukanWaveLevelSet_New( pw_data, test_buf, 9, 0 );
			}
		}
		break;
	case 2:
		wk->seq = 0;
		wk->count = 0;
		wk->waveout_flag = 0;				//�����Đ����t���OOFF
		break;
	};

	return;
}


//==============================================================================================
//
//	16	���C���V�i���I�֘A
//
//	���݂̃]�[���̃X�N���v�g�ƃ��b�Z�[�W��ǂݍ��ނ悤�ɂ��Ă���̂ŁA
//	�f�o�b�N�ŃX�N���v�g��ID���w�肷�邾���ł͏o���Ȃ��I
//
//	�܂��X�N���v�g�����쐬���Ă��Ȃ����̂́Acommon_scr.ev�ɒǉ����Ď����B�B�B
//	�Ƃ��v�������A���b�Z�[�W���Ȃ��̂ŁA���������B�B�B
//
//==============================================================================================
static void D_Nohara_16_Main( TCB_PTR tcb, void * work );

//--------------------------------------------------------------
/**
 * @brief	������
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_16( TCB_PTR tcb, void * work )
{
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;
	wk->seq		= 0;
	wk->count	= 0;
	wk->work	= 0;
	TCB_ChangeFunc( tcb, D_Nohara_16_Main );	//TCB�̓���֐��؂�ւ�
	return;
}

//--------------------------------------------------------------
/**
 * @brief	���C��
 *
 * @param	tcb		TCB_PTR�^
 * @param	work	���[�N
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_16_Main( TCB_PTR tcb, void * work )
{
	//�I��
	if( sys.cont == PAD_BUTTON_B ){
		TcbBmpDel( tcb, work );		//TCBBMP�J��
	}

	return;
}


//==============================================================================================
//
//	17	�o�b�W�t���O�Z�b�g
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	������
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_17( TCB_PTR tcb, void * work )
{
	int i;
	D_NOHARA_WORK* wk = (D_NOHARA_WORK*)work;
	MYSTATUS* my = SaveData_GetMyStatus( wk->fsys->savedata );

	for( i=0; i < 8; i++ ){
		MyStatus_SetBadgeFlag( my, i );
	}

	TcbBmpDel( tcb, work );		//TCBBMP�J��
	return;
}


//==============================================================================================
//
//	18	�B���A�C�e������
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	������
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_18( TCB_PTR tcb, void * work )
{
	int i,count;
	D_NOHARA_WORK* wk = (D_NOHARA_WORK*)work;
	MYSTATUS* my = SaveData_GetMyStatus( wk->fsys->savedata );
	HIDE_ITEM_LIST* p = HideItem_CreateList( wk->fsys, HEAPID_BASE_DEBUG );

	count = 0;

	while( 1 ){
		if( p[count].response == HIDE_LIST_RESPONSE_NONE ){
			if( count == 0 ){
				OS_Printf( "�B���A�C�e���͌�����܂���ł����I\n" );
			}
			break;
		}

		OS_Printf( "\nresponse = %d\n", p[count].response );
		OS_Printf( "gx = %d\n", p[count].gx );
		OS_Printf( "gz = %d\n", p[count].gz );
		count++;
	};

	sys_FreeMemoryEz( p );

	TcbBmpDel( tcb, work );		//TCBBMP�J��
	return;
}


//==============================================================================================
//
//	19	�B���A�C�e������
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	������
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_19( TCB_PTR tcb, void * work )
{
	D_NOHARA_WORK* wk = (D_NOHARA_WORK*)work;

	Snd_CaptureIsActive();

	TcbBmpDel( tcb, work );		//TCBBMP�J��
	return;
}


//==============================================================================================
//
//	20	�M�l�X�E�B���h�E
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	������
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_20( TCB_PTR tcb, void * work )
{
	int type,ret;
	D_NOHARA_WORK* wk = (D_NOHARA_WORK*)work;

	EventSet_Script( wk->fsys, SCRID_GUINNESS_WIN, NULL );
	TcbBmpDel( tcb, work );		//TCBBMP�J��
	return;
}

//==============================================================================================
//
//	21	�f�o�b�N�W�����v
//
//==============================================================================================
static void D_Nohara_21_Main( TCB_PTR tcb, void * work );

typedef struct{
	u32 zone_id;
	u32 num;
	u32 x;
	u32 z;
}DEBUG_JUMP_WORK;

static const DEBUG_JUMP_WORK debug_jump_work[] = {
	{ ZONE_ID_T02,		2,		160,	846 },			//�}�T�S�^�E��
	{ ZONE_ID_T03,		3,		176,	624 },			//�\�m�I�^�E��
	{ ZONE_ID_R201,		201,	110,	856 },			//
	{ ZONE_ID_R205A,	2051,	208,	592 },			//
	{ ZONE_ID_R205B,	2052,	272,	528 },			//
	{ ZONE_ID_C05R1101,	511,	5,		5 },			//�R���e�X�g��t
	{ ZONE_ID_D27R0101, 2701,	46,		53 },			//
};
#define DEBUG_JUMP_WORK_MAX	( NELEMS(debug_jump_work) )

//--------------------------------------------------------------
/**
 * @brief	������
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_21( TCB_PTR tcb, void * work )
{
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;
	wk->seq		= 0;
	wk->count	= 0;
	wk->work	= 0;
	TCB_ChangeFunc( tcb, D_Nohara_21_Main );	//TCB�̓���֐��؂�ւ�
	return;
}

//--------------------------------------------------------------
/**
 * @brief	���C��
 *
 * @param	tcb		TCB_PTR�^
 * @param	work	���[�N
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_21_Main( TCB_PTR tcb, void * work )
{
	int flag;
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	flag = 0;	//���������t���O

	if( (sys.repeat == PAD_KEY_UP) || (sys.cont == PAD_KEY_RIGHT) ){
		flag = 1;
		wk->work++;
		if( wk->work >= DEBUG_JUMP_WORK_MAX ){
			wk->work = 0;
		}
	}

	if( (sys.repeat == PAD_KEY_DOWN) || (sys.cont == PAD_KEY_LEFT) ){
		flag = 1;
		wk->work--;
		if( wk->work < 0 ){
			wk->work = (DEBUG_JUMP_WORK_MAX - 1);
		}
	}

	//���������t���O�������Ă�����
	if( flag == 1 ){
		//�w��͈͂�h��Ԃ�
		GF_BGL_BmpWinFill( &wk->bmpwin[0], FBMP_COL_BLACK, 8*7, 8*2, 
								8*8, 8*2 );
	
		//�l�\��
		NumMsgSet( wk, &wk->bmpwin[0], debug_jump_work[wk->work].num, 8*7, 8*2 );
		GF_BGL_BmpWinOn( &wk->bmpwin[0] );
	}

	//�W�����v
	if( sys.trg == PAD_BUTTON_A ){

		EventSet_EasyMapChange( wk->fsys, debug_jump_work[wk->work].zone_id, DOOR_ID_JUMP_CODE, 
							debug_jump_work[wk->work].x , debug_jump_work[wk->work].z, DIR_DOWN );

		TcbBmpDel( tcb, work );		//TCBBMP�J��
		return;
	}

	//�I��
	if( sys.cont == PAD_BUTTON_B ){
		TcbBmpDel( tcb, work );		//TCBBMP�J��
		return;
	}

	return;
}


//==============================================================================================
//
//	22	�|�P�b�`�g�`�e�X�g
//
//==============================================================================================
static void D_Nohara_22_Main( TCB_PTR tcb, void * work );
static void Snd_DebugWaveBufWrite( u32 no );

static s8 d_sWaveBuffer[ 64 ] ATTRIBUTE_ALIGN(32);	//�g�`�i�[�o�b�t�@

//--------------------------------------------------------------
/**
 * @brief	������
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_22( TCB_PTR tcb, void * work )
{
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;
	wk->seq		= 0;
	wk->count	= 0;
	wk->work	= 0;

	//�g�`�Đ��p�`�����l�����m�ۂ���
	Snd_WaveOutAllocChannel( WAVEOUT_CH_NORMAL );

	TCB_ChangeFunc( tcb, D_Nohara_22_Main );	//TCB�̓���֐��؂�ւ�
	return;
}

//--------------------------------------------------------------
/**
 * @brief	���C��
 *
 * @param	tcb		TCB_PTR�^
 * @param	work	���[�N
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_22_Main( TCB_PTR tcb, void * work )
{
	int flag;
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	flag = 0;	//���������t���O


	switch( wk->seq ){
	case 0:
		//�Ăяo���p�^�[����؂�ւ���
		if( sys.trg & PAD_KEY_UP ){
			Snd_DebugWaveBufWrite( 0 );
			wk->seq++;
		}else if( sys.trg & PAD_KEY_DOWN ){
			Snd_DebugWaveBufWrite( 1 );
			wk->seq++;
		}else if( sys.trg & PAD_KEY_RIGHT ){
			Snd_DebugWaveBufWrite( 2 );
			wk->seq++;
		}else if( sys.trg & PAD_KEY_LEFT ){
			Snd_DebugWaveBufWrite( 3 );
			wk->seq++;
		}

		//�I��
		if( sys.cont == PAD_BUTTON_B ){
			//�g�`�Đ��p�`�����l�����J������
			Snd_DebugNormalChannelFree();

			TcbBmpDel( tcb, work );		//TCBBMP�J��
			return;
		}

		break;

	case 1:
		//�g�`�Đ�
		{
			WAVEOUT_WORK waveout_wk;

			waveout_wk.handle			= Snd_WaveOutHandleGet(WAVEOUT_CH_NORMAL);//�g�`�Đ��n���h��
			waveout_wk.format			= NNS_SND_WAVE_FORMAT_PCM8;//�g�`�f�[�^�t�H�[�}�b�g
			waveout_wk.dataaddr			= &d_sWaveBuffer[0];//�g�`�f�[�^�̐擪�A�h���X
			waveout_wk.loopFlag			= TRUE;					//���[�v�t���O
			waveout_wk.loopStartSample	= 0;						//���[�v�J�n�T���v���ʒu
			waveout_wk.samples			= 64;				//�g�`�f�[�^�̃T���v����
			//waveout_wk.samples		= WAVE_SAMPLE;				//�g�`�f�[�^�̃T���v����
			waveout_wk.sampleRate		= 16000;					//�g�`�f�[�^�̃T���v�����O���[�g
			waveout_wk.volume			= 127;						//����
			waveout_wk.speed			= 32768;					//�Đ��X�s�[�h
			//waveout_wk.speed			= 32768*3;					//�Đ��X�s�[�h
			//waveout_wk.speed			= 32768/3;					//�Đ��X�s�[�h
			waveout_wk.pan				= 64;						//�p��(0-127)

			Snd_WaveOutStart( &waveout_wk, WAVEOUT_CH_NORMAL );		//�g�`�Đ�
		}
		wk->count = 0;
		wk->seq++;
		break;

	case 2:
		wk->count++;

		if( wk->count == 16 ){					//�t���[�����Ȃ̂Œ��ӁI
			Snd_WaveOutSetSpeed( WAVEOUT_CH_NORMAL, (32768 * 2) );
		}

		if( wk->count == 24 ){					//�t���[�����Ȃ̂Œ��ӁI
			Snd_WaveOutSetSpeed( WAVEOUT_CH_NORMAL, (32768 / 2) );
		}

		if( wk->count >= 32 ){					//�t���[�����Ȃ̂Œ��ӁI
			Snd_WaveOutStop( WAVEOUT_CH_NORMAL );	//�g�`��~
			wk->seq = 0;
		}
		break;
	};

	return;
}

//--------------------------------------------------------------
/**
 * @brief	�K���Ȕg�`����������
 *
 * @param	no		�p�^�[��
 *
 * @retval	none
 */
//--------------------------------------------------------------
#define TEST_START	(0)
#define TEST_ADD	(64)
//#define TEST_LOOP	(40)
#define TEST_LOOP	(1)

static void Snd_DebugWaveBufWrite( u32 no )
{
	u8 add;
	int i,j;

	switch( no ){

	case 0:

		//�u���v
		
		for( j=0; j < TEST_LOOP ;j++ ){

			add = TEST_ADD * j;

			for( i=0+add; i < 32+add ;i++ ){
				d_sWaveBuffer[i] = 120;
			}
			for( i=32+add; i < 64+add ;i++ ){
				d_sWaveBuffer[i] = -120;
			}
		}
		break;

	case 1:

		//�u���v
		
		for( j=0; j < TEST_LOOP ;j++ ){

			add = TEST_ADD * j;

			for( i=0+add; i < 10+add ;i++ ){
				d_sWaveBuffer[i] = 0;
			}
			for( i=10+add; i < 20+add ;i++ ){
				d_sWaveBuffer[i] = 120;
			}
			for( i=20+add; i < 30+add ;i++ ){
				d_sWaveBuffer[i] = 0;
			}
			for( i=30+add; i < 40+add ;i++ ){
				d_sWaveBuffer[i] = -120;
				}
			for( i=40+add; i < 50+add ;i++ ){
				d_sWaveBuffer[i] = 0;
			}
			for( i=50+add; i < 64+add ;i++ ){
				d_sWaveBuffer[i] = 120;
			}
		}

	case 2:

		//�u���v
		//�}�C�i�X�Ȃ�
		
		for( j=0; j < TEST_LOOP ;j++ ){

			add = TEST_ADD * j;

			d_sWaveBuffer[0+add] = 0;
			d_sWaveBuffer[1+add] = 4;
			d_sWaveBuffer[2+add] = 8;
			d_sWaveBuffer[3+add] = 12;
			d_sWaveBuffer[4+add] = 16;
			d_sWaveBuffer[5+add] = 20;
			d_sWaveBuffer[6+add] = 24;
			d_sWaveBuffer[7+add] = 28;
			d_sWaveBuffer[8+add] = 32;
			d_sWaveBuffer[9+add] = 36;
			d_sWaveBuffer[10+add] = 40;
			d_sWaveBuffer[11+add] = 44;
			d_sWaveBuffer[12+add] = 48;
			d_sWaveBuffer[13+add] = 52;
			d_sWaveBuffer[14+add] = 56;
			d_sWaveBuffer[15+add] = 60;
			d_sWaveBuffer[16+add] = 64;
			d_sWaveBuffer[17+add] = 68;
			d_sWaveBuffer[18+add] = 72;
			d_sWaveBuffer[19+add] = 76;
			d_sWaveBuffer[20+add] = 80;
			d_sWaveBuffer[21+add] = 84;
			d_sWaveBuffer[22+add] = 88;
			d_sWaveBuffer[23+add] = 92;
			d_sWaveBuffer[24+add] = 96;
			d_sWaveBuffer[25+add] = 100;
			d_sWaveBuffer[26+add] = 104;
			d_sWaveBuffer[27+add] = 108;
			d_sWaveBuffer[28+add] = 112;
			d_sWaveBuffer[29+add] = 116;
			d_sWaveBuffer[30+add] = 120;
			d_sWaveBuffer[31+add] = 124;
			d_sWaveBuffer[32+add] = 128;
			d_sWaveBuffer[33+add] = 124;
			d_sWaveBuffer[34+add] = 120;
			d_sWaveBuffer[35+add] = 116;
			d_sWaveBuffer[36+add] = 112;
			d_sWaveBuffer[37+add] = 108;
			d_sWaveBuffer[38+add] = 104;
			d_sWaveBuffer[39+add] = 100;
			d_sWaveBuffer[40+add] = 96;
			d_sWaveBuffer[41+add] = 92;
			d_sWaveBuffer[42+add] = 88;
			d_sWaveBuffer[43+add] = 84;
			d_sWaveBuffer[44+add] = 80;
			d_sWaveBuffer[45+add] = 76;
			d_sWaveBuffer[46+add] = 72;
			d_sWaveBuffer[47+add] = 68;
			d_sWaveBuffer[48+add] = 64;
			d_sWaveBuffer[49+add] = 60;
			d_sWaveBuffer[50+add] = 56;
			d_sWaveBuffer[51+add] = 52;
			d_sWaveBuffer[52+add] = 48;
			d_sWaveBuffer[53+add] = 44;
			d_sWaveBuffer[54+add] = 40;
			d_sWaveBuffer[55+add] = 36;
			d_sWaveBuffer[56+add] = 32;
			d_sWaveBuffer[57+add] = 28;
			d_sWaveBuffer[58+add] = 24;
			d_sWaveBuffer[59+add] = 20;
			d_sWaveBuffer[60+add] = 16;
			d_sWaveBuffer[61+add] = 12;
			d_sWaveBuffer[62+add] = 8;
			d_sWaveBuffer[63+add] = 4;
		};

		break;

	case 3:

		//�u���v
		//�}�C�i�X����
		
		for( j=0; j < TEST_LOOP ;j++ ){

			add = TEST_ADD * j;

			d_sWaveBuffer[0+add] = -127;
			d_sWaveBuffer[1+add] = -119;
			d_sWaveBuffer[2+add] = -111;
			d_sWaveBuffer[3+add] = -103;
			d_sWaveBuffer[4+add] = -95;
			d_sWaveBuffer[5+add] = -87;
			d_sWaveBuffer[6+add] = -79;
			d_sWaveBuffer[7+add] = -71;
			d_sWaveBuffer[8+add] = -63;
			d_sWaveBuffer[9+add] = -55;
			d_sWaveBuffer[10+add] = -47;
			d_sWaveBuffer[11+add] = -39;
			d_sWaveBuffer[12+add] = -31;
			d_sWaveBuffer[13+add] = -23;
			d_sWaveBuffer[14+add] = -15;
			d_sWaveBuffer[15+add] = -7;
			d_sWaveBuffer[16+add] = 1;
			d_sWaveBuffer[17+add] = 9;
			d_sWaveBuffer[18+add] = 17;
			d_sWaveBuffer[19+add] = 25;
			d_sWaveBuffer[20+add] = 33;
			d_sWaveBuffer[21+add] = 41;
			d_sWaveBuffer[22+add] = 49;
			d_sWaveBuffer[23+add] = 57;
			d_sWaveBuffer[24+add] = 65;
			d_sWaveBuffer[25+add] = 73;
			d_sWaveBuffer[26+add] = 81;
			d_sWaveBuffer[27+add] = 89;
			d_sWaveBuffer[28+add] = 97;
			d_sWaveBuffer[29+add] = 105;
			d_sWaveBuffer[30+add] = 113;
			d_sWaveBuffer[31+add] = 121;
			d_sWaveBuffer[32+add] = 127;
			d_sWaveBuffer[33+add] = 121;
			d_sWaveBuffer[34+add] = 113;
			d_sWaveBuffer[35+add] = 105;
			d_sWaveBuffer[36+add] = 97;
			d_sWaveBuffer[37+add] = 89;
			d_sWaveBuffer[38+add] = 81;
			d_sWaveBuffer[39+add] = 73;
			d_sWaveBuffer[40+add] = 65;
			d_sWaveBuffer[41+add] = 57;
			d_sWaveBuffer[42+add] = 49;
			d_sWaveBuffer[43+add] = 41;
			d_sWaveBuffer[44+add] = 33;
			d_sWaveBuffer[45+add] = 25;
			d_sWaveBuffer[46+add] = 17;
			d_sWaveBuffer[47+add] = 9;
			d_sWaveBuffer[48+add] = 1;
			d_sWaveBuffer[49+add] = -7;
			d_sWaveBuffer[50+add] = -15;
			d_sWaveBuffer[51+add] = -23;
			d_sWaveBuffer[52+add] = -31;
			d_sWaveBuffer[53+add] = -39;
			d_sWaveBuffer[54+add] = -47;
			d_sWaveBuffer[55+add] = -55;
			d_sWaveBuffer[56+add] = -63;
			d_sWaveBuffer[57+add] = -71;
			d_sWaveBuffer[58+add] = -79;
			d_sWaveBuffer[59+add] = -87;
			d_sWaveBuffer[60+add] = -95;
			d_sWaveBuffer[61+add] = -103;
			d_sWaveBuffer[62+add] = -111;
			d_sWaveBuffer[63+add] = -119;
		};

		break;

	default:
		break;
	};

	//�e�X�g�\��
	for( j=0; j < 64*10 ;j++ ){
		OS_Printf( "d_sWaveBuffer[%d] = %d\n", j, d_sWaveBuffer[j] );
	}

	return;
}


//==============================================================================================
//
//	23	�}�ӁA�o�b�O�V�X�e���t���O�Z�b�g
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	������
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_23( TCB_PTR tcb, void * work )
{
	int type,ret;
	D_NOHARA_WORK* wk = (D_NOHARA_WORK*)work;

	{
		//���j���[�u�}�Ӂv
		ZUKAN_WORK* zw = SaveData_GetZukanWork( wk->fsys->savedata );
		ZukanWork_SetZukanGetFlag( zw );

		//���j���[�u�o�b�O�v
		SysFlag_BagSet( SaveData_GetEventWork(wk->fsys->savedata) );

		//���j���[�u�|�P�����v
		SysWork_FirstPokeNoSet( SaveData_GetEventWork(wk->fsys->savedata), MONSNO_HUSIGIDANE );
	}

	TcbBmpDel( tcb, work );		//TCBBMP�J��
	return;
}


//==============================================================================================
//
//	24	�o�g���T�[�`���[�֘A
//
//==============================================================================================
static void D_Nohara_24_Main( TCB_PTR tcb, void * work );

static const struct{
	u32  str_id;
	u32  param;
}DebugMenuList24[] = {
	{ msg_debug_nohara_24_01, (u32)D_Nohara_24_Main },
	{ msg_debug_nohara_24_02, (u32)D_Nohara_24_Main },
	{ msg_debug_nohara_24_03, (u32)D_Nohara_24_Main },
	{ msg_debug_nohara_24_04, (u32)D_Nohara_24_Main },
	{ msg_debug_nohara_24_05, (u32)D_Nohara_24_Main },
	{ msg_debug_nohara_24_06, (u32)D_Nohara_24_Main },
	{ msg_debug_nohara_24_07, (u32)D_Nohara_24_Main },
	{ msg_debug_nohara_24_08, (u32)D_Nohara_24_Main },
	{ msg_debug_nohara_24_09, (u32)D_Nohara_24_Main },
	{ msg_debug_nohara_24_10, (u32)D_Nohara_24_Main },
};

static const BMPLIST_HEADER ListH24 = {
	NULL,					//�\�������f�[�^�|�C���^
	NULL,					//�J�[�\���ړ����Ƃ̃R�[���o�b�N�֐�
	NULL,					//���\�����Ƃ̃R�[���o�b�N�֐�

	NULL,					//GF_BGL_BMPWIN�̃|�C���^

	NELEMS(DebugMenuList24),//���X�g���ڐ�
	10,						//�\���ő區�ڐ�

	0,						//���x���\���w���W
	8,						//���ڕ\���w���W
	0,						//�J�[�\���\���w���W
	0,						//�\���x���W
/*
	FBMP_COL_BLACK,			//�����F
	FBMP_COL_WHITE,			//�w�i�F
	FBMP_COL_BLK_SDW,		//�����e�F
*/
	FBMP_COL_WHITE,			//�����F
	FBMP_COL_BLACK,			//�w�i�F
	FBMP_COL_BLK_SDW,		//�����e�F
	0,						//�����Ԋu�w
	16,						//�����Ԋu�x
	BMPLIST_LRKEY_SKIP,		//�y�[�W�X�L�b�v�^�C�v
	FONT_SYSTEM,			//�����w��(�{���� u8 �����ǁA����Ȃɍ��Ȃ��Ǝv���̂�)
	0						//�a�f�J�[�\��(allow)�\���t���O(0:ON,1:OFF)
};

//--------------------------------------------------------------
/**
 * @brief	������
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_24( TCB_PTR tcb, void * work )
{
	int i;
	BMPLIST_HEADER list_h;
	GF_BGL_BMPWIN* win;
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	BmpDel( tcb );								//BMP�J��

	wk->seq				= 0;
	wk->sel				= 0;
	wk->count			= 0;

	GF_BGL_BmpWinAddEx( wk->fsys->bgl, &wk->bmpwin[0], &DebugNoharaWinData );	//�r�b�g�}�b�v�ǉ�

	wk->menulist = BMP_MENULIST_Create( NELEMS(DebugMenuList24), HEAPID_BASE_DEBUG );

	for( i=0; i < NELEMS(DebugMenuList24); i++ ){
		BMP_MENULIST_AddArchiveString( wk->menulist, wk->msgman, 
										DebugMenuList24[i].str_id, DebugMenuList24[i].param );
	}

	list_h			= ListH24;
	list_h.list		= wk->menulist;
	list_h.win		= &wk->bmpwin[0];
	wk->lw			= BmpListSet( &list_h, 0, 0, HEAPID_BASE_DEBUG );

	GF_BGL_BmpWinOn( &wk->bmpwin[0] );

	//TCB_ChangeFunc( tcb, D_Nohara_24_Main );	//TCB�̓���֐��؂�ւ�
	TCB_ChangeFunc( tcb, DebugNoharaMenuMain );	//TCB�̓���֐��؂�ւ�
	return;
}
 
//--------------------------------------------------------------
/**
 * @brief	���C��
 *
 * @param	tcb		TCB_PTR�^
 * @param	work	���[�N
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_24_Main( TCB_PTR tcb, void * work )
{
	EVENTWORK* ev;
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	ev = SaveData_GetEventWork( wk->fsys->savedata );

	switch( wk->cursor_bak ){
	case 0:
		//�o�b�e���[MAX
		SysWork_BtlSearcherBatterySet( ev, BS_BATTERY_MAX );
		break;

	case 1:
		//�o�b�e���[CLR
		SysWork_BtlSearcherBatterySet( ev, 0 );
		break;

	case 2:
		//�N���A�[MAX
		SysWork_BtlSearcherClearSet( ev, BS_CLEAR_MAX );
		break;

	case 3:
		//�N���A�[CLR
		SysWork_BtlSearcherClearSet( ev, 0 );
		break;

	case 4:
		//�N��
		EventSet_Script( wk->fsys, SCRID_BTL_SEARCHER, NULL );
		TcbBmpDel( tcb, work );		//TCBBMP�J��
		return;						//���ӁI

	case 5:
		//���x���P�Z�b�g
		SysFlag_BsLvSet( ev, 1 );

		MyItem_AddItem( SaveData_GetMyItem(wk->fsys->savedata),
						ITEM_BATORUSAATYAA, 1, HEAPID_BASE_DEBUG);
		break;

	case 6:
		//���x���Q�Z�b�g
		SysFlag_BsLvSet( ev, 2 );
		break;

	case 7:
		//���x���R�Z�b�g
		SysFlag_BsLvSet( ev, 3 );
		break;

	case 8:
		//���x���S�Z�b�g
		SysFlag_BsLvSet( ev, 4 );
		break;

	case 9:
		//���x���T�Z�b�g
		SysFlag_BsLvSet( ev, 5 );
		break;

	default:
		return;
	};

	wk->seq = 0;
	TCB_ChangeFunc( tcb, DebugNoharaMenuMain );		//TCB�̓���֐��؂�ւ�
	return;
}


//==============================================================================================
//
//	25	BGM�I�t
//
//==============================================================================================
extern void Snd_DebugBgmFlagSet( u8 sw );

//--------------------------------------------------------------
/**
 * @brief	BGM�I�t
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_25( TCB_PTR tcb, void * work )
{
#ifdef PM_DEBUG
	Snd_DebugBgmFlagSet( 1 );
	Snd_Stop();
#endif

	TcbBmpDel( tcb, work );		//TCBBMP�J��
	return;
}


//==============================================================================================
//
//	26	BGM�I��
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	BGM�I��
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_26( TCB_PTR tcb, void * work )
{
#ifdef PM_DEBUG
	u16 bgm_no;
	D_NOHARA_WORK* wk = (D_NOHARA_WORK*)work;

	Snd_DebugBgmFlagSet( 0 );

	//�T�E���h�f�[�^�Z�b�g(�V�[�����ύX����Ȃ����͉������Ȃ�)
	Snd_SceneSet( SND_SCENE_DUMMY );
	bgm_no = Snd_FieldBgmNoGet( wk->fsys, wk->fsys->location->zone_id );
	Snd_ZoneBgmSet(Snd_FieldBgmNoGetNonBasicBank(wk->fsys,wk->fsys->location->zone_id));//zone set

	Snd_DataSetByScene( SND_SCENE_FIELD, bgm_no, 1 );
#endif

	TcbBmpDel( tcb, work );		//TCBBMP�J��
	return;
}






//--------------------------------------------------------------
/**
 * @brief	�o�C�i�����b�Z�[�W�t�@�C���ǂݍ��݁A�\���e�X�g
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_89(void)
{
#if 1
	return;
#else
	static u16 * pMsg = NULL;

	//debug_msg.dat��cvs�ɓo�^���Ă��Ȃ��̂Œ��ӁI
	pMsg = (u16 *)sys_LoadFile( HEAPID_BASE_DEBUG, "/data/script/debug_msg.dat" );
	FieldTalkWinPut();
	msg_no_print( pMsg );
	FieldTalkMsgStart( pMsg, 1 );					//��2����=skip
	sys_FreeMemoryEz( pMsg );

	return;
#endif
}

//--------------------------------------------------------------
/**
 * @brief	�g���b�N�~���[�g�e�X�g
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_72(void)
{
	Snd_PlayerSetTrackMute( SND_HANDLE_FIELD, ( (1 << 0) | (2 << 0) ), TRUE );
	return;
}


















//==============================================================================================
//
//
//
//==============================================================================================

static const struct{
	u32  str_id;
	u32  param;
}DebugMenuList2[] = {
	{ msg_debug_nohara_25, (u32)D_Nohara_25 },
	{ msg_debug_nohara_26, (u32)D_Nohara_26 },
};

static const BMPLIST_HEADER DebugListH2 = {
	NULL,					//�\�������f�[�^�|�C���^

	NULL,					//�J�[�\���ړ����Ƃ̃R�[���o�b�N�֐�
	NULL,					//���\�����Ƃ̃R�[���o�b�N�֐�

	NULL,					//GF_BGL_BMPWIN�̃|�C���^

	NELEMS(DebugMenuList2),	//���X�g���ڐ�
	9,						//�\���ő區�ڐ�

	0,						//���x���\���w���W
	8,						//���ڕ\���w���W
	0,						//�J�[�\���\���w���W
	0,						//�\���x���W
/*
	FBMP_COL_BLACK,			//�����F
	FBMP_COL_WHITE,			//�w�i�F
	FBMP_COL_BLK_SDW,		//�����e�F
*/
	FBMP_COL_WHITE,			//�����F
	FBMP_COL_BLACK,			//�w�i�F
	FBMP_COL_BLK_SDW,		//�����e�F
	0,						//�����Ԋu�w
	16,						//�����Ԋu�x
	BMPLIST_LRKEY_SKIP,		//�y�[�W�X�L�b�v�^�C�v
	FONT_SYSTEM,			//�����w��(�{���� u8 �����ǁA����Ȃɍ��Ȃ��Ǝv���̂�)
	0						//�a�f�J�[�\��(allow)�\���t���O(0:ON,1:OFF)
};

//--------------------------------------------------------------
/**
 * @brief	BGM�f�o�b�N���j���[�Ăяo��(fld_debug.c)
 *
 * @param	fsys	FIELDSYS_WORK�^�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
void DebugBgmMenuInit( FIELDSYS_WORK* fsys )
{
	int i;
	BMPLIST_HEADER list_h;
	D_NOHARA_WORK* wk;

	wk = (D_NOHARA_WORK*)TCB_GetWork( PMDS_taskAdd(DebugNoharaMenuMain, sizeof(D_NOHARA_WORK), 0, HEAPID_BASE_DEBUG) );

	wk->seq				= 0;
	wk->sel				= 0;
	wk->work			= 0;
	wk->wave_buf_flag	= 0;								//�g�`�i�[�o�b�t�@���m�ۂ����t���OOFF
	wk->waveout_flag	= 0;								//�����Đ����t���OOFF
	wk->fsys			= fsys;

	GF_BGL_BmpWinAddEx( wk->fsys->bgl, &wk->bmpwin[0], &DebugNoharaWinData );	//�r�b�g�}�b�v�ǉ�

	wk->menulist = BMP_MENULIST_Create( NELEMS(DebugMenuList2), HEAPID_BASE_DEBUG );

	wk->wordset = WORDSET_Create( HEAPID_BASE_DEBUG );

	wk->msgman = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, 
								NARC_msg_debug_nohara_dat, HEAPID_BASE_DEBUG);

	for( i=0; i < NELEMS(DebugMenuList2); i++ ){
		BMP_MENULIST_AddArchiveString( wk->menulist, wk->msgman, 
										DebugMenuList2[i].str_id, DebugMenuList2[i].param );
	}

	list_h			= DebugListH2;
	list_h.list		= wk->menulist;
	list_h.win		= &wk->bmpwin[0];
	wk->lw			= BmpListSet( &list_h, 0, 0, HEAPID_BASE_DEBUG );

	GF_BGL_BmpWinOn( &wk->bmpwin[0] );
	return;
}


//==============================================================================================
//
//	�f�o�b�N�u�̂͂�v�ł͂Ȃ�������́u�f�o�b�N�X�N���v�g�v�Ăяo��
//
//==============================================================================================

static const struct{
	u32  str_id;
	u32  param;
}DebugMenuList3[] = {
	{ msg_debug_nohara_11, (u32)D_Nohara_11 },
};

static const BMPLIST_HEADER DebugListH3 = {
	NULL,					//�\�������f�[�^�|�C���^

	NULL,					//�J�[�\���ړ����Ƃ̃R�[���o�b�N�֐�
	NULL,					//���\�����Ƃ̃R�[���o�b�N�֐�

	NULL,					//GF_BGL_BMPWIN�̃|�C���^

	NELEMS(DebugMenuList3),	//���X�g���ڐ�
	9,						//�\���ő區�ڐ�

	0,						//���x���\���w���W
	8,						//���ڕ\���w���W
	0,						//�J�[�\���\���w���W
	0,						//�\���x���W
/*
	FBMP_COL_BLACK,			//�����F
	FBMP_COL_WHITE,			//�w�i�F
	FBMP_COL_BLK_SDW,		//�����e�F
*/
	FBMP_COL_WHITE,			//�����F
	FBMP_COL_BLACK,			//�w�i�F
	FBMP_COL_BLK_SDW,		//�����e�F
	0,						//�����Ԋu�w
	16,						//�����Ԋu�x
	BMPLIST_LRKEY_SKIP,		//�y�[�W�X�L�b�v�^�C�v
	FONT_SYSTEM,			//�����w��(�{���� u8 �����ǁA����Ȃɍ��Ȃ��Ǝv���̂�)
	0						//�a�f�J�[�\��(allow)�\���t���O(0:ON,1:OFF)
};

//--------------------------------------------------------------
/**
 * @brief	BGM�f�o�b�N���j���[�Ăяo��(fld_debug.c)
 *
 * @param	fsys	FIELDSYS_WORK�^�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
void DebugScriptMenuInit( FIELDSYS_WORK* fsys )
{
	int i;
	BMPLIST_HEADER list_h;
	D_NOHARA_WORK* wk;

	wk = (D_NOHARA_WORK*)TCB_GetWork( PMDS_taskAdd(DebugNoharaMenuMain, sizeof(D_NOHARA_WORK), 0, HEAPID_BASE_DEBUG) );

	wk->seq				= 0;
	wk->sel				= 0;
	wk->work			= 0;
	wk->wave_buf_flag	= 0;								//�g�`�i�[�o�b�t�@���m�ۂ����t���OOFF
	wk->waveout_flag	= 0;								//�����Đ����t���OOFF
	wk->fsys			= fsys;

	GF_BGL_BmpWinAddEx( wk->fsys->bgl, &wk->bmpwin[0], &DebugNoharaWinData );	//�r�b�g�}�b�v�ǉ�

	wk->menulist = BMP_MENULIST_Create( NELEMS(DebugMenuList3), HEAPID_BASE_DEBUG );

	wk->wordset = WORDSET_Create( HEAPID_BASE_DEBUG );

	wk->msgman = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, 
								NARC_msg_debug_nohara_dat, HEAPID_BASE_DEBUG);

	for( i=0; i < NELEMS(DebugMenuList3); i++ ){
		BMP_MENULIST_AddArchiveString( wk->menulist, wk->msgman, 
										DebugMenuList3[i].str_id, DebugMenuList3[i].param );
	}

	list_h			= DebugListH3;
	list_h.list		= wk->menulist;
	list_h.win		= &wk->bmpwin[0];
	wk->lw			= BmpListSet( &list_h, 0, 0, HEAPID_BASE_DEBUG );

	GF_BGL_BmpWinOn( &wk->bmpwin[0] );
	return;
}


