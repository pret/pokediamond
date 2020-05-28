//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_sound_sub.c
 *	@brief		�������T�u���
 *	@author		tomoya takahashi 
 *	@data		2006.01.21
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>
#include "include/application/zukanlist/zkn_event_func.h"

#include "include/system/snd_tool.h"

#include "include/gflib/calctool.h"
#include "include/gflib/vram_transfer_manager.h"

#include "include/system/brightness.h"
#include "include/system/arc_tool.dat"
#include "include/system/arc_util.h"
#include "include/system/clact_util.h"
#include "include/application/zukanlist/zukan.naix"
#include "include/gflib/button_man.h"
#include "include/system/msgdata_util.h"
#include "include/msgdata/msg.naix"
#include "include/msgdata/msg_zkn.h"

#include "include/application/zukanlist/zkn_snd_def.h"
#include "include/application/zukanlist/zkn_zukan_common.h"
#include "include/application/zukanlist/zkn_cursor.h"
#include "include/application/zukanlist/zkn_sound.h"


#define	__ZKN_SOUND_SUB_SUB_H_GLOBAL
#include "include/application/zukanlist/zkn_sound_sub.h"

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
//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
#define ZKN_SOUND_SUB_EVENT_NUM ( 0 )	// �C�x���g��

#define ZKN_SOUND_SUB_OAM_BG_PTR	( 2 )

enum{
	ZKN_SOUNDSUB_SEQINIT_ALLOC,
	ZKN_SOUNDSUB_SEQINIT_LOAD,
	ZKN_SOUNDSUB_SEQINIT_FADEIN,
	ZKN_SOUNDSUB_SEQINIT_END,
};
enum{
	ZKN_SOUNDSUB_SEQDELETE_FADEOUT_INIT,
	ZKN_SOUNDSUB_SEQDELETE_FADEOUT,
	ZKN_SOUNDSUB_SEQDELETE_RELEASE,
	ZKN_SOUNDSUB_SEQDELETE_FREE,
	ZKN_SOUNDSUB_SEQDELETE_END,
};


//-------------------------------------
//	�{�^�����
//=====================================
enum{
	ZKN_SOUNDSUB_BUTTON_SWITCH,
	ZKN_SOUNDSUB_BUTTON_DIAL,
	ZKN_SOUNDSUB_BUTTON_DISK,
	ZKN_SOUNDSUB_BUTTON_NUM,
};
#define ZKN_SOUNDSUB_BUTTON_SWITCH_X	( 64 )
#define ZKN_SOUNDSUB_BUTTON_SWITCH_Y	( 67 )
#define ZKN_SOUNDSUB_BUTTON_SWITCH_SIZXH	( 42 )	// �T�C�Y�̔���
#define ZKN_SOUNDSUB_BUTTON_SWITCH_SIZYH	( 14 )	// �T�C�Y�̔���
#define ZKN_SOUNDSUB_BUTTON_DIAL_X	( 51 )
#define ZKN_SOUNDSUB_BUTTON_DIAL_Y	( 157 )
#define ZKN_SOUNDSUB_BUTTON_DIAL_R	( 32 )

#define ZKN_SOUNDSUB_DISK_BG_CENTER_X	( ZKN_SOUNDSUB_DISK_BG_BGCX - (ZKN_SOUNDSUB_DISK_BG_X) )
#define ZKN_SOUNDSUB_DISK_BG_CENTER_Y	( ZKN_SOUNDSUB_DISK_BG_BGCY - (ZKN_SOUNDSUB_DISK_BG_Y) )

#define ZKN_SOUNDSUB_DISK_BG_CENTER_T_OFS_Y	( 8 )	// �^�b�`����p�I�t�Z�b�g
#define ZKN_SOUNDSUB_DISK_BG_CENTER_OFS_Y	( 16 )	// �X���[�Đ��A�s�b�`�p���̔��苫�E�I�t�Z�b�g
#define ZKN_SOUNDSUB_DISK_BG_R			( 72 )

//-------------------------------------
//	�T�u�{�^�����
//	�̈�̂��Ԃ���̗p
//=====================================
enum{
	ZKN_SOUNDSUB_BUTTON_SUB_STARTSTOP,
	ZKN_SOUNDSUB_BUTTON_SUB_LOOP,
	ZKN_SOUNDSUB_BUTTON_SUB_NUM,
};
#define ZKN_SOUNDSUB_BUTTON_STARTSTOP_X	( 180 )
#define ZKN_SOUNDSUB_BUTTON_STARTSTOP_Y	( 131 )
#define ZKN_SOUNDSUB_BUTTON_STARTSTOP_SIZXH	( 24 )	// �T�C�Y�̔���
#define ZKN_SOUNDSUB_BUTTON_STARTSTOP_SIZYH	( 24 )	// �T�C�Y�̔���
#define ZKN_SOUNDSUB_BUTTON_STARTSTOP_X_DRAW	( ZKN_SOUNDSUB_BUTTON_STARTSTOP_X )	// �`��ʒu�̕␳�p
#define ZKN_SOUNDSUB_BUTTON_STARTSTOP_Y_DRAW	( ZKN_SOUNDSUB_BUTTON_STARTSTOP_Y )	// �`��ʒu�̕␳�p

#define ZKN_SOUNDSUB_BUTTON_LOOP_X	( 230 )
#define ZKN_SOUNDSUB_BUTTON_LOOP_Y	( 166 )
#define ZKN_SOUNDSUB_BUTTON_LOOP_SIZXH	( 16 )	// �T�C�Y�̔���
#define ZKN_SOUNDSUB_BUTTON_LOOP_SIZYH	( 16 )	// �T�C�Y�̔���
#define ZKN_SOUNDSUB_BUTTON_LOOP_X_DRAW	( ZKN_SOUNDSUB_BUTTON_LOOP_X )	// �`��ʒu�̕␳�p
#define ZKN_SOUNDSUB_BUTTON_LOOP_Y_DRAW	( ZKN_SOUNDSUB_BUTTON_LOOP_Y )	// �`��ʒu�̕␳�p

// �Đ��{�^���ʒu�J�[�\��
#define ZKN_SOUNDSUB_CURSOR_START_SIZX ( 24 )
#define ZKN_SOUNDSUB_CURSOR_START_SIZY ( 24 )

// �A�j���[�V�����V�[�P���X
enum{
	ZKN_SOUNDSUB_SEQ_SWITCH_PICH_PAN,
	ZKN_SOUNDSUB_SEQ_DIAL,
	ZKN_SOUNDSUB_SEQ_SOUND_STOP_ANM,
	ZKN_SOUNDSUB_SEQ_SOUND_START_ANM,
	ZKN_SOUNDSUB_SEQ_SWITCH_PAN_PICH,
	ZKN_SOUNDSUB_SEQ_SOUND_LOOPON_ANM,
	ZKN_SOUNDSUB_SEQ_SOUND_LOOPOFF_ANM,
};
#define ZKN_SOUNDSUB_ANIME_FRAME	( FX32_ONE * 2 )


// �s�b�`�X�C�b�`
enum{
	ZKN_SOUNDSUB_SWITCH_00,
	ZKN_SOUNDSUB_SWITCH_01,
	ZKN_SOUNDSUB_SWITCH_02,
	ZKN_SOUNDSUB_SWITCH_03,
	ZKN_SOUNDSUB_SWITCH_04,
	ZKN_SOUNDSUB_SWITCH_05,
	ZKN_SOUNDSUB_SWITCH_06,
	ZKN_SOUNDSUB_SWITCH_07,
	ZKN_SOUNDSUB_SWITCH_08,
};
enum{
	ZKN_SOUNDSUB_SEQ_SWITCH_PICH,
	ZKN_SOUNDSUB_SEQ_SWITCH_PAN,
	ZKN_SOUNDSUB_SEQ_SWITCH_NUM
};
#define ZKN_SOUNDSUB_SWITCH_MOVE_OK_DIS		( 12 )

// �Đ��{�^��
enum{
	ZKN_SOUNDSUB_START_00,
	ZKN_SOUNDSUB_START_01,
	ZKN_SOUNDSUB_START_02,
	ZKN_SOUNDSUB_START_03,
	ZKN_SOUNDSUB_START_04,
	ZKN_SOUNDSUB_START_05,
};
#define ZKN_SOUNDDUB_BUTTON_START_NOTOUCH	( 100 )

// ���[�v�{�^��
enum{
	ZKN_SOUNDSUB_LOOP_00,
	ZKN_SOUNDSUB_LOOP_01,
	ZKN_SOUNDSUB_LOOP_02,
	ZKN_SOUNDSUB_LOOP_03,
	ZKN_SOUNDSUB_LOOP_04,
	ZKN_SOUNDSUB_LOOP_05,
};

#define ZKN_SOUNDSUB_DIAL_LOOP_WAIT	( 10 )


// �_�C�A��
enum{
	ZKN_SOUNDSUB_DIAL_NONE,
	ZKN_SOUNDSUB_DIAL_REVERB,
	ZKN_SOUNDSUB_DIAL_FILTER,
};

#define ZKN_SOUNDSUB_DIAL_DIVISION	( 8 )

#define ZKN_SOUNDSUB_DIAL_REVERB_NUM	( 8 )
#define ZKN_SOUNDSUB_DIAL_FILTER_NUM	( 1 )
#define ZKN_SOUNDSUB_DIAL_DRAW_R		( 14 )
#define ZKN_SOUNDSUB_DIAL_MOVE_NUM_MAX	( 88 )
#define ZKN_SOUNDSUB_DIAL_MOVE_NUM_HALF	( ZKN_SOUNDSUB_DIAL_MOVE_NUM_MAX/2 )
#define ZKN_SOUNDSUB_DIAL_MOVE_LIMIT_ROTA	( 1 )
#define ZKN_SOUNDSUB_DIAL_LIMIT		( 32 )
#define ZKN_SOUNDSUB_DIAL_LIMIT_MIN	( ZKN_SOUNDSUB_DIAL_LIMIT )
#define ZKN_SOUNDSUB_DIAL_LIMIT_MAX	( (ZKN_SOUNDSUB_DIAL_MOVE_NUM_MAX - ZKN_SOUNDSUB_DIAL_LIMIT) )	

#define ZKN_SOUNDSUB_DIAL_CUT_ONE_NUM	( ZKN_SOUNDSUB_DIAL_LIMIT / ZKN_SOUNDSUB_DIAL_DIVISION )
#define ZKN_SOUNDSUB_DIAL_MIN_CUT_NUM	( ZKN_SOUNDSUB_DIAL_CUT_ONE_NUM )	// �������Ƃ��A���̊p�x�̔{���̒l�ɂ���
// ���o�[�u�̂Ƃ��̓_�C�A���̒l�����̊ԂɂȂ��Ă���
#define ZKN_SOUNDSUB_DIAL_REVERB_MIN	( ZKN_SOUNDSUB_DIAL_LIMIT_MAX / ZKN_SOUNDSUB_DIAL_MIN_CUT_NUM )
#define ZKN_SOUNDSUB_DIAL_REVERB_MAX	( ZKN_SOUNDSUB_DIAL_MOVE_NUM_MAX / ZKN_SOUNDSUB_DIAL_MIN_CUT_NUM )

// �f�B�X�N�����̍��W
#define ZKN_SOUNDSUB_DISK_BG_X		( -48 )
#define ZKN_SOUNDSUB_DISK_BG_Y		( -16 )
#define ZKN_SOUNDSUB_DISK_BG_BGCX	( 131 )		// BG�A�t�B���ϊ��p���S
#define ZKN_SOUNDSUB_DISK_BG_BGCY	( 99 )		// BG�A�t�B���ϊ��p���S
#define ZKN_SOUNDSUB_DISK_BG_ROTA_MUL	( -16 )

#define ZKN_SOUNDSUB_DISK_PITCK_MAX	( 1024 )
#define ZKN_SOUNDSUB_DISK_CHORUS_MAX	( 127 )
#define ZKN_SOUNDSUB_DISK_PAN_MAX	( 127 )
#define ZKN_SOUNDSUB_DISK_PITCH_PAN_PL	( 7 )

// �s�b�`�p��������
#define ZKN_SOUNDSUB_BUTTONFONT_BMP_SIZE_CX	( 8 )
#define ZKN_SOUNDSUB_BUTTONFONT_BMP_SIZE_CY	( 2 )
#define ZKN_SOUNDSUB_PITCH_FOTN_X		( 40 )
#define ZKN_SOUNDSUB_PAN_FOTN_X			( 50 )
#define ZKN_SOUNDSUB_PITCH_PAN_FOTN_Y	( 86 )
#define ZKN_SOUNDSUB_BUTTON_PAL_OFS	(0)

#define ZKN_SOUNDSUB_FADE_PLANEMSK	( GX_BLEND_PLANEMASK_BG2|GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_BD )

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�Ȃ������T�u��ʁ@�O���[�o���ϐ�
//=====================================
typedef struct {
	int* p_event_key;

	ZKN_GLB_DATA* p_glb;
	
	// �}�ӃR�����T�u�A�v���f�[�^
	const ZKN_APL_DATA* cp_zukan_common_apl;

	// �O���ĎQ�Ɨp
	int now_pitch;		// �ݒ蒆�̃s�b�`
} ZKN_SOUND_SUB_GLB;

//-------------------------------------
//	�傫������׃T�u��ʉ�ʁ@�`��O���[�o���ϐ�
//=====================================
typedef struct {
	ZKN_GLB_DRAWDATA* p_drawglb;
} ZKN_SOUND_SUB_DRAWGLB;

//-------------------------------------
//	�{�^���R�[���o�b�N�ւ̃��[�N
//=====================================
typedef struct {
	void* p_glb;
	void* p_work;
} ZKN_SOUND_BUTTON_CALLBACK;

//-------------------------------------
//	�Ȃ������T�u��ʁ@�������[�N
//=====================================
typedef struct {
	// �{�^���}�l�[�W��
	BUTTON_MAN* p_button_man;
	TP_HIT_TBL *hit_tbl;	// �{�^���f�[�^
	ZKN_SOUND_BUTTON_CALLBACK callcack;

	// �T�u�{�^���}�l�[�W��
	TP_HIT_TBL* p_sub_hit_tbl;	// �̈�̂��Ԃ���̂𔻒肷�邽��
	BUTTON_MAN* p_sub_button_man;
	int sub_button_event[ ZKN_SOUNDSUB_BUTTON_SUB_NUM ];

	// �Đ��{�^���p
	BOOL hit_start_stop_flag;

	
	// �Đ��{�^�������t���O
	BOOL start_touch_on;

	// �Đ��{�^���@�J�[�\���ŉ������t���O
	int sound_play_button_cursor;
		
	
	// �������Đ�����
	BOOL sound_play;

	// �s�b�`�X�C�b�`	�i�R�[���X�ƃp���ύX�X�C�b�`�ɕύX����܂����j
	int pitch_switch_touch;
	int pitch_switch_flag;
	int pitch_switch_touch_start_x;
	int pitch_num;		// �s�b�`�ݒ萔
	int pan_num;		// �p���ݒ萔
	int chorus_num;		// �R�[���X�{�����[��
	BOOL pitch_pan_push;// ������Ă���Ƃ�TRUE

	// ���o�[�u/�t�B���^�[�_�C����
	BOOL dial_touch;
	int	dial_flag;		// �Ȃ�0 ���o�[�u1 �t�B���^�[2
	int dial_start_x;
	int dial_start_y;
	int dial_rota;		// ���݂̉�]�p
	int dial_div;		// ���݂̕����ʒu


	// ���[�v
	BOOL loop;			// TRUE ���[�v
	int loop_wait;		// ���[�v�E�G�C�g

	const SNDWaveData* cp_snd_data;	// �T�E���h�f�[�^

} ZKN_SOUND_SUB_WORK;

//-------------------------------------
//	�A�j���{�^�����[�N
//=====================================
typedef struct {
	int anm_seq1;		// �V�[�P���X1
	int anm_seq2;		// �V�[�P���X2
	int now_anm_seq;	// ���̃V�[�P���X

	BOOL flag;			// �V�[�P���X�X�C�b�`�t���O

	int anm_num_max;	// �A�j���ڰѐ��ő�
	int push_anm_limit;	// �����A�j���̃��~�b�g�ڰѐ�
} ZKN_SOUND_SUB_ANM_BUTTON;


//-------------------------------------
//	�Ȃ������T�u��ʉ�ʁ@�������[�N
//=====================================
typedef struct {
	// �_�C����
	CLACT_WORK_PTR	dial;			// �_�C����	
	
	//�@�J�n��~
	CLACT_WORK_PTR	startstop;		// �J�n��~
	ZKN_SOUND_SUB_ANM_BUTTON start_stop_anim;

	// ���[�v�{�^��
	CLACT_WORK_PTR	loop;
	ZKN_SOUND_SUB_ANM_BUTTON loop_anim;
	
	// �X�C�b�`
	CLACT_WORK_PTR	pich_switch;	// �X�C�b�`	
	int now_switch;	// ���\������Ă���X�C�b�`���
	fx32 pich_switch_frame;

	//	�f�B�X�N 
	int disk_last_tick;
	u16	disk_rota;

	// �s�b�`�p��������
	ZKN_FONTOAM_DATA* p_fontoam[ ZKN_SOUNDSUB_SEQ_SWITCH_NUM ];

	// ���\�[�X
	CLACT_U_RES_OBJ_PTR res_obj[ ZKN_CLACT_RES_OBJ_NUM_DEF ];

	// �f�B�X�N�������点�悤�p���b�g
	void* p_pltt_buff;
	NNSG2dPaletteData* p_plt;
	BOOL pltt_anm;	// �p���b�gON���Ă���Ƃ�TRUE
} ZKN_SOUND_SUB_DRAW;


//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *		�A�v���P�[�V�����f�[�^�쐬�֌W
 */
//-----------------------------------------------------------------------------
static ZKN_SOUND_SUB_GLB* MakeSoundSubGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_SOUND_SUB_DRAWGLB* MakeSoundSubDrawGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_EVENT_DATA* MakeSoundSubEvent( int heap, ZKN_SYS_PTR zkn_sys );
static void DeleteSoundSubGlb( ZKN_SOUND_SUB_GLB* p_glb );
static void DeleteSoundSubDrawGlb( ZKN_SOUND_SUB_DRAWGLB* p_glb );
static void DeleteSoundSubEvent( ZKN_EVENT_DATA* p_event );


static int SoundSubEventDataNumGet( void );


//-----------------------------------------------------------------------------
/**
 *		�v���Z�X�֌W
 */
//-----------------------------------------------------------------------------
static int ZknSoundSubProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknSoundSubProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknSoundSubProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknSoundSubProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknSoundSubProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknSoundSubProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );

// �t�F�[�h����
static void ZknSoundSubOamFadeInit( ZKN_SOUND_SUB_DRAW* p_draw );
static void ZknSoundSubOamFadeDelete( ZKN_SOUND_SUB_DRAW* p_draw );
static void ZknSoundSubFadeInit( ZKN_SOUND_SUB_DRAW* p_draw, ZKN_SOUND_SUB_DRAWGLB* p_drawglb, const ZKN_SOUND_SUB_GLB* cp_glb, BOOL fadein_out );
static BOOL ZknSoundSubFadeMain( ZKN_SOUND_SUB_DRAW* p_draw, ZKN_SOUND_SUB_DRAWGLB* p_drawglb, const ZKN_SOUND_SUB_GLB* cp_glb, BOOL fadein_out );

// �{�^������
static void ZknSoundSubButtonMake( ZKN_SOUND_SUB_WORK* p_work, ZKN_SOUND_SUB_GLB* p_glb, int heap );
static void ZknSoundSubButtonMove( ZKN_SOUND_SUB_WORK* p_work, ZKN_SOUND_SUB_GLB* p_glb );
static void ZknSoundSubButtonDelete( ZKN_SOUND_SUB_WORK* p_work );
static void ZknSoundSubButtonCallBack( u32 button_no, u32 event, void* p_work );

// �J�[�\������
static void ZknSoundSubCursorMove( ZKN_SOUND_SUB_WORK* p_work, ZKN_SOUND_SUB_GLB* p_glb );
static void ZknSoundSubCursorDrawMove( ZKN_SOUND_SUB_DRAWGLB* p_drawglb, const ZKN_SOUND_SUB_GLB* cp_glb );

static void ZknSoundSubStartButtonCallBack( u32 button_no, u32 event, void* p_work );
static void ZknSoundSubButtonTouch( u32 button_no, ZKN_SOUND_SUB_GLB* p_glb, ZKN_SOUND_SUB_WORK* p_work );
static void ZknSoundSubButtonHold( u32 button_no, ZKN_SOUND_SUB_GLB* p_glb, ZKN_SOUND_SUB_WORK* p_work );
static void ZknSoundSubButtonRelease( u32 button_no, ZKN_SOUND_SUB_GLB* p_glb, ZKN_SOUND_SUB_WORK* p_work );
static void ZknSoundSubButtonSlideOut( u32 button_no, ZKN_SOUND_SUB_GLB* p_glb, ZKN_SOUND_SUB_WORK* p_work );

// ���Đ�
static void ZknSoundSubSoundStart( ZKN_SOUND_SUB_WORK* p_work, ZKN_SOUND_SUB_GLB* p_glb, int monsno );
static void ZknSoundSubSoundStop( ZKN_SOUND_SUB_WORK* p_work );
static void ZknSoundSubSoundLoop(  ZKN_SOUND_SUB_WORK* p_work, ZKN_SOUND_SUB_GLB* p_glb );
static void ZknSoundSubSoundLoopSet( ZKN_SOUND_SUB_WORK* p_work, BOOL flag );

// �{�^���A�j��
static void ZknSoundSubButtonAnimeMain( CLACT_WORK_PTR act, ZKN_SOUND_SUB_ANM_BUTTON* p_anmdata, BOOL now_flg, BOOL next_flg );
static void ZknSoundSubButtonAnimeMain_NO_Loop( CLACT_WORK_PTR act, ZKN_SOUND_SUB_ANM_BUTTON* p_anmdata, BOOL next_flg, int button_event );
static void ZknSoundSubButtonAnimeSeqSet( CLACT_WORK_PTR act, ZKN_SOUND_SUB_ANM_BUTTON* p_anmdata, BOOL flg );

// �X�C�b�`
static void ZknSoundSubSwitchDrawMove( ZKN_SOUND_SUB_DRAW* p_draw, const ZKN_SOUND_SUB_WORK* cp_work );
static void ZknSoundSubStartStopDrawMove( ZKN_SOUND_SUB_DRAW* p_draw, const ZKN_SOUND_SUB_WORK* cp_work );
static void ZknSoundSubLoopDrawMove( ZKN_SOUND_SUB_DRAW* p_draw, const ZKN_SOUND_SUB_WORK* cp_work );

static void ZknSoundSubPitchPanFontDraw( ZKN_SOUND_SUB_DRAW* p_draw );
static void ZknSoundSubPitchPanChorusOnOff( ZKN_SOUND_SUB_WORK* p_work, BOOL flag );
static void ZknSoundSubPitchPanChorusFlagOnOff( ZKN_SOUND_SUB_WORK* p_work, BOOL flag );
static void ZknSoundSubPitchPanChorusNumReset( ZKN_SOUND_SUB_WORK* p_work );
static void ZknSoundSubPitchPanChorusSet( ZKN_SOUND_SUB_WORK* p_work );
static void ZknSoundSubPitchPanAnm( ZKN_SOUND_SUB_DRAW* p_draw, const ZKN_SOUND_SUB_WORK* cp_work );

static void ZknSoundSubChorusSet( int volume );
static void ZknSoundSubPitchSet( int num );

// �_�C��������
static void ZknSoundSubDialCalc( ZKN_SOUND_SUB_WORK* p_work );
static void ZknSoundSubDialDivSet( ZKN_SOUND_SUB_WORK* p_work );
static void ZknSoundSubDialNumSet( ZKN_SOUND_SUB_WORK* p_work );
static void ZKnSoundSubDialDrawMove( ZKN_SOUND_SUB_DRAW* p_draw, const ZKN_SOUND_SUB_WORK* cp_work );
static void ZknSoundSubReverbEffectStop( ZKN_SOUND_SUB_WORK* p_work );

// �f�B�X�N
static void ZknSoundSubDiskDrawMove( ZKN_SOUND_SUB_DRAW* p_draw, ZKN_SOUND_SUB_DRAWGLB* p_drawglb, const ZKN_SOUND_SUB_WORK* cp_work );

static void ZknSoundSubDiskPitchSet( ZKN_SOUND_SUB_WORK* p_work, int x );
static void ZknSoundSubDiskChorusSet( ZKN_SOUND_SUB_WORK* p_work, int x );
static void ZknSoundSubDiskPanSet( ZKN_SOUND_SUB_WORK* p_work, int x );

// �ǂݍ���
static void ZknSoundSubLoadResource( ZKN_SOUND_SUB_DRAW* p_draw, ZKN_SOUND_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknSoundSubReleaseResource( ZKN_SOUND_SUB_DRAW* p_draw, ZKN_SOUND_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknSoundSubSetUpBg( ZKN_SOUND_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknSoundSubPutDownBg( ZKN_SOUND_SUB_DRAWGLB* p_drawglb );
static void ZknSoundSubLoadOamData( ZKN_SOUND_SUB_DRAW* p_draw, ZKN_SOUND_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknSoundSubReleaseOamData( ZKN_SOUND_SUB_DRAW* p_draw, ZKN_SOUND_SUB_DRAWGLB* p_drawglb );
static void ZknSoundSubAddClact( ZKN_SOUND_SUB_DRAW* p_draw, ZKN_SOUND_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknSoundSubDeleteClact( ZKN_SOUND_SUB_DRAW* p_draw );
static void ZknSoundSubAddFontOam( ZKN_SOUND_SUB_DRAW* p_draw, ZKN_SOUND_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknSoundSubDeleteFontOam( ZKN_SOUND_SUB_DRAW* p_draw, ZKN_SOUND_SUB_DRAWGLB* p_drawglb );

static void ZknSoundSubPlttLoad( ZKN_SOUND_SUB_DRAW* p_draw, ZKN_SOUND_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknSoundSubPlttRelease( ZKN_SOUND_SUB_DRAW* p_draw );
static void ZknSoundSubPlttOn( ZKN_SOUND_SUB_DRAW* p_draw );
static void ZknSoundSubPlttOff( ZKN_SOUND_SUB_DRAW* p_draw );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�Ȃ������T�u��ʁ@�A�v���쐬
 *
 *	@param	p_data		�A�v���P�[�V�����f�[�^
 *	@param	zkn_sys		�}�ӃV�X�e��
 *	@param	heap		�g�p�q�[�v
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_SoundSubAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap )
{
	ZKN_SOUND_SUB_GLB*	p_glb;
	ZKN_SOUND_SUB_DRAWGLB*	p_drawglb;
	ZKN_EVENT_DATA*	p_event;
	
	p_glb = MakeSoundSubGlb( heap, zkn_sys );
	p_drawglb = MakeSoundSubDrawGlb( heap, zkn_sys );
	p_event = MakeSoundSubEvent( heap, zkn_sys );

	p_data->p_glb_data		= p_glb;
	p_data->p_glb_draw		= p_drawglb;
	p_data->p_event_data	= p_event;
	p_data->event_num		= SoundSubEventDataNumGet();

	p_data->do_func[ ZKN_PROC_FUNC_INIT ] = ZknSoundSubProcDoFuncInit;
	p_data->do_func[ ZKN_PROC_FUNC_MAIN ] = ZknSoundSubProcDoFuncMain;
	p_data->do_func[ ZKN_PROC_FUNC_DELETE ] = ZknSoundSubProcDoFuncDelete;
	p_data->draw_func[ ZKN_PROC_FUNC_INIT ] = ZknSoundSubProcDrawFuncInit;
	p_data->draw_func[ ZKN_PROC_FUNC_MAIN ] = ZknSoundSubProcDrawFuncMain;
	p_data->draw_func[ ZKN_PROC_FUNC_DELETE ] = ZknSoundSubProcDrawFuncDelete;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�������X�g	�T�u��ʁ@���j���[�A�v���j��
 *
 *	@param	p_data	�A�v���P�[�V�����f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_SoundSubAplDelete( ZKN_APL_DATA* p_data )
{
	DeleteSoundSubGlb( p_data->p_glb_data ); 
	DeleteSoundSubDrawGlb( p_data->p_glb_draw ); 
	DeleteSoundSubEvent( p_data->p_event_data );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�s�b�`�����擾����
 *
 *	@param	cp_data	�A�v���P�[�V�����f�[�^
 *
 *	@return	�s�b�`��
 */
//-----------------------------------------------------------------------------
int ZKN_SoundSubAplGetPitchNum( const ZKN_APL_DATA* cp_data )
{
	const ZKN_SOUND_SUB_GLB* cp_glb = cp_data->p_glb_data;

	return cp_glb->now_pitch;
}


//-----------------------------------------------------------------------------
/**
 *		�v���C�x�[�g�֐�
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�Ȃ������T�u��ʁ@�O���[�o���f�[�^�쐬
 *
 *	@param	heap		�q�[�v
 *	@param	zkn_sys		�}�ӃV�X�e��
 *
 *	@return	�O���[�o���f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_SOUND_SUB_GLB* MakeSoundSubGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_SOUND_SUB_GLB* p_glb;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_SOUND_SUB_GLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_SOUND_SUB_GLB) );

	// �ϐ�������
	// �C�x���g�L�[
	p_glb->p_event_key = ZKN_SYS_GetEventKeyPtrSub( zkn_sys );		

	// �O���[�o���f�[�^
	p_glb->p_glb = ZKN_SYS_GetGlbData( zkn_sys );

	// �}�ӃR�����A�v���O���[�o���f�[�^
	p_glb->cp_zukan_common_apl = ZKN_GetAplDataSub( zkn_sys, ZKN_SYS_APLSUB_ZUKAN_COMMON );
	
	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�Ȃ������T�u��ʁ@�O���[�o���f�[�^�쐬
 *
 *	@param	heap		�q�[�v
 *	@param	zkn_sys		�}�ӃV�X�e��
 *
 *	@return	�O���[�o���f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_SOUND_SUB_DRAWGLB* MakeSoundSubDrawGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_SOUND_SUB_DRAWGLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_SOUND_SUB_DRAWGLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_SOUND_SUB_DRAWGLB) );


	// �`��f�[�^
	p_glb->p_drawglb = ZKN_SYS_GetGlbDrawData( zkn_sys );

	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�Ȃ������T�u��ʁ@�C�x���g�쐬
 *
 *	@param	heap		�g�p����q�[�v
 *	@param	zkn_sys		�}�ӃV�X�e��
 *
 *	@return	�C�x���g�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_EVENT_DATA* MakeSoundSubEvent( int heap, ZKN_SYS_PTR zkn_sys )
{
	return NULL;	// ���͂Ȃ�
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�Ȃ������T�u��ʁ@�O���[�o���f�[�^�j��
 *
 *	@param	p_glb		�O���[�o���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteSoundSubGlb( ZKN_SOUND_SUB_GLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�Ȃ������T�u��ʁ@�O���[�o���f�[�^�j��
 *
 *	@param	p_glb		�O���[�o���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteSoundSubDrawGlb( ZKN_SOUND_SUB_DRAWGLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�Ȃ������T�u��ʁ@�C�x���g�f�[�^�j��
 *
 *	@param	p_event	�C�x���g�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteSoundSubEvent( ZKN_EVENT_DATA* p_event )
{
	// ���͂Ȃ�
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�Ȃ������T�u��ʃA�v���@�C�x���g���擾
 *	
 *	@param	none	
 *
 *	@return	�Ȃ������T�u��ʃA�v���@�C�x���g��
 *
 *
 */
//-----------------------------------------------------------------------------
static int SoundSubEventDataNumGet( void )
{
	return ZKN_SOUND_SUB_EVENT_NUM;
}


//-----------------------------------------------------------------------------
/**
 *		�v���Z�X�֌W
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	[������]
 *	@brief	�A�v���P�[�V�����v���Z�X	�f�[�^�ύX
 *
 *	@param	p_dodata	ZKN_PROC_DO_DATA
 *	@param	p_glbdata	�Ǘ��҂���󂯎��f�[�^�@�i�ۑ����Ă��������f�[�^�j
 *
 *	@retval	ZKN_PROC_TRUE		���̏����֐i�݂܂��B
 *	@retval	ZKN_PROC_FALSE		�܂��i�݂܂���B
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZknSoundSubProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_SOUND_SUB_GLB* p_glb = p_glbdata;
	ZKN_SOUND_SUB_WORK* p_work = p_dodata->p_work;
	int i;
	int monsno = ZKN_GLBDATA_PokeMonsNoGet( p_glb->p_glb );

	// ���[�N�̍쐬
	p_work = sys_AllocMemory( p_dodata->heap, sizeof(ZKN_SOUND_SUB_WORK) );
	memset( p_work, 0, sizeof(ZKN_SOUND_SUB_WORK) );


	// �{�^�����쐬
	ZknSoundSubButtonMake( p_work, p_glb, p_dodata->heap );

	// �{�^���̏�Ԃ��P��ݒ�
	// �{�^������
	ZknSoundSubButtonMove( p_work, p_glb );

	// �T�E���h�f�[�^�擾
	p_work->cp_snd_data = Snd_ZukanWaveDataSet( monsno );	


	p_dodata->p_work = p_work;
	
	return ZKN_PROC_TRUE;
}

//----------------------------------------------------------------------------
/**
 *	[���C��]
 *	@brief	�A�v���P�[�V�����v���Z�X	�f�[�^�ύX
 *
 *	@param	p_dodata	ZKN_PROC_DO_DATA
 *	@param	p_glbdata	�Ǘ��҂���󂯎��f�[�^�@�i�ۑ����Ă��������f�[�^�j
 *
 *	@retval	ZKN_PROC_TRUE		���̏����֐i�݂܂��B
 *	@retval	ZKN_PROC_FALSE		�܂��i�݂܂���B
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZknSoundSubProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{

	ZKN_SOUND_SUB_GLB* p_glb = p_glbdata;
	ZKN_SOUND_SUB_WORK* p_work = p_dodata->p_work;
	
	// �I����
	if( p_dodata->end_req == TRUE ){
		ZknSoundSubSoundStop( p_work );
		// ���o�[�u�t�B���^�[���~�߂�
		ZknSoundSubReverbEffectStop( p_work );
		return ZKN_PROC_TRUE;
	}

	// lock
	if( p_dodata->lock == TRUE ){
		return ZKN_PROC_FALSE;
	}

	// ���ݍĐ����̃s�b�`���擾
	p_glb->now_pitch = p_work->pitch_num;

	// ����`�F�b�N
	if( ZKN_ZukanCommonSubMoveFlagGet( p_glb->cp_zukan_common_apl ) ){
		// �Đ������`�F�b�N
		if( Snd_PMVoicePlayCheck() == FALSE ){
			// ���[�v���[�h�ł͂Ȃ��Ȃ��~�ɂ���
			if( p_work->loop == FALSE ){
				ZknSoundSubSoundStop( p_work );
			}
		}

		// �{�^������
		ZknSoundSubButtonMove( p_work, p_glb );
		
		// �J�[�\������
		// �J�[�\������L���ŁA�T�u�A�v���ɃJ�[�\�����삪������Ă���Ƃ��̂�
		if( ZKN_ZukanCommonSubCursorFlagGet( p_glb->cp_zukan_common_apl ) &&
			ZKN_GLBDATA_TouchCursorFlagGet( p_glb->p_glb ) ){

			ZknSoundSubCursorMove( p_work, p_glb );
		}
		

		// ���[�v���[�h���̏���
		if( p_work->loop && p_work->sound_play ){
			ZknSoundSubSoundLoop( p_work, p_glb );
		}

	}

	return ZKN_PROC_FALSE;
}

//----------------------------------------------------------------------------
/**
 *	[�j��]
 *	@brief	�A�v���P�[�V�����v���Z�X	�f�[�^�ύX
 *
 *	@param	p_dodata	ZKN_PROC_DO_DATA
 *	@param	p_glbdata	�Ǘ��҂���󂯎��f�[�^�@�i�ۑ����Ă��������f�[�^�j
 *
 *	@retval	ZKN_PROC_TRUE		���̏����֐i�݂܂��B
 *	@retval	ZKN_PROC_FALSE		�܂��i�݂܂���B
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZknSoundSubProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_SOUND_SUB_GLB* p_glb = p_glbdata;
	ZKN_SOUND_SUB_WORK* p_work = p_dodata->p_work;

	// �{�^���j��
	ZknSoundSubButtonDelete( p_work );

	// ���[�N�j��
	sys_FreeMemoryEz( p_work );

	return ZKN_PROC_TRUE;
}

//----------------------------------------------------------------------------
/**
 * [������]
 *
 *	@brief	�A�v���P�[�V�����v���Z�X	�`��
 *
 *	@param	p_glbdraw	�`��O���[�o���f�[�^
 *	@param	p_drawdata	ZKN_PROC_DRAW_DATA
 *	@param	cp_glbdata	�Ǘ��҂���󂯎��f�[�^�@�i�ۑ����Ă��������f�[�^�j
 *	@param	cp_dodata	���̏����̓������[�N�f�[�^
 *
 *	@retval	ZKN_PROC_TRUE		���̏����֐i�݂܂��B
 *	@retval	ZKN_PROC_FALSE		�܂��i�݂܂���B
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZknSoundSubProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_SOUND_SUB_GLB* cp_dataglb = cp_glbdata;
	const ZKN_SOUND_SUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_SOUND_SUB_DRAWGLB*	p_drawglb = p_glbdraw;
	ZKN_SOUND_SUB_DRAW*		p_drawwork = p_drawdata->p_work;

	switch( p_drawdata->seq ){
	case ZKN_SOUNDSUB_SEQINIT_ALLOC:
		p_drawdata->p_work = sys_AllocMemory( p_drawdata->heap, sizeof(ZKN_SOUND_SUB_DRAW) );
		memset( p_drawdata->p_work, 0, sizeof(ZKN_SOUND_SUB_DRAW) );
		p_drawdata->seq++;
		break;
		
	case ZKN_SOUNDSUB_SEQINIT_LOAD:
		// Resource�ǂݍ���
		ZknSoundSubLoadResource( p_drawwork, p_drawglb, p_drawdata->heap );
		// �t�F�[�h����
		ZknSoundSubFadeInit( p_drawwork, p_drawglb, cp_dataglb, TRUE );
		
		p_drawdata->seq++;
		break;
		
	case ZKN_SOUNDSUB_SEQINIT_FADEIN:
		
		if( ZknSoundSubFadeMain( p_drawwork, p_drawglb, cp_dataglb, TRUE ) ){
			p_drawdata->seq++;
		}
		break;
		
	case ZKN_SOUNDSUB_SEQINIT_END:
		// �J�[�\���A�j���J�n
		ZKN_UTIL_CursorSetAnimeStopFlag( &p_drawglb->p_drawglb->cursor, FALSE );
		return ZKN_PROC_TRUE;
		
	default:
		break;
	}
	return ZKN_PROC_FALSE;
}

//----------------------------------------------------------------------------
/**
 * [���C��]
 *
 *	@brief	�A�v���P�[�V�����v���Z�X	�`��
 *
 *	@param	p_glbdraw	�`��O���[�o���f�[�^
 *	@param	p_drawdata	ZKN_PROC_DRAW_DATA
 *	@param	cp_glbdata	�Ǘ��҂���󂯎��f�[�^�@�i�ۑ����Ă��������f�[�^�j
 *	@param	cp_dodata	���̏����̓������[�N�f�[�^
 *
 *	@retval	ZKN_PROC_TRUE		���̏����֐i�݂܂��B
 *	@retval	ZKN_PROC_FALSE		�܂��i�݂܂���B
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZknSoundSubProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_SOUND_SUB_GLB* cp_dataglb = cp_glbdata;
	const ZKN_SOUND_SUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_SOUND_SUB_DRAWGLB*	p_drawglb = p_glbdraw;
	ZKN_SOUND_SUB_DRAW*		p_drawwork = p_drawdata->p_work;

	// ����`�F�b�N
	if( ZKN_ZukanCommonSubMoveFlagGet( cp_dataglb->cp_zukan_common_apl ) ){

		// �X�C�b�`����
		ZknSoundSubSwitchDrawMove( p_drawwork, cp_datawork );

		// �Đ��X�g�b�v�`��
		ZknSoundSubStartStopDrawMove( p_drawwork, cp_datawork );

		// ���[�v�`��
		ZknSoundSubLoopDrawMove( p_drawwork, cp_datawork );

		// �_�C�A���`��
		ZKnSoundSubDialDrawMove( p_drawwork, cp_datawork );

		// �f�B�X�N
		ZknSoundSubDiskDrawMove( p_drawwork, p_drawglb, cp_datawork );

		// �X�C�b�`����
		ZknSoundSubPitchPanFontDraw( p_drawwork );

		// �s�b�`�p�������p���b�g�A�j��
		ZknSoundSubPitchPanAnm( p_drawwork, cp_datawork );

		// �J�[�\��
		ZknSoundSubCursorDrawMove( p_drawglb, cp_dataglb );
	}


	return ZKN_PROC_FALSE;
}

//----------------------------------------------------------------------------
/**
 * [�j��]
 *
 *	@brief	�A�v���P�[�V�����v���Z�X	�`��
 *
 *	@param	p_glbdraw	�`��O���[�o���f�[�^
 *	@param	p_drawdata	ZKN_PROC_DRAW_DATA
 *	@param	cp_glbdata	�Ǘ��҂���󂯎��f�[�^�@�i�ۑ����Ă��������f�[�^�j
 *	@param	cp_dodata	���̏����̓������[�N�f�[�^
 *
 *	@retval	ZKN_PROC_TRUE		���̏����֐i�݂܂��B
 *	@retval	ZKN_PROC_FALSE		�܂��i�݂܂���B
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZknSoundSubProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_SOUND_SUB_GLB* cp_dataglb = cp_glbdata;
	const ZKN_SOUND_SUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_SOUND_SUB_DRAWGLB*	p_drawglb = p_glbdraw;
	ZKN_SOUND_SUB_DRAW*		p_drawwork = p_drawdata->p_work;

	switch( p_drawdata->seq ){
	case ZKN_SOUNDSUB_SEQDELETE_FADEOUT_INIT:
		// �J�[�\���A�j����~
		ZKN_UTIL_CursorSetAnimeStopFlag( &p_drawglb->p_drawglb->cursor, TRUE );

		// OFF�p���b�g��ݒ�
		ZknSoundSubPlttOff( p_drawwork );
		
		// �t�F�[�h����
		ZknSoundSubFadeInit( p_drawwork, p_drawglb, cp_dataglb, FALSE );
		p_drawdata->seq++;
		break;
		
	case ZKN_SOUNDSUB_SEQDELETE_FADEOUT:
		if( ZknSoundSubFadeMain( p_drawwork, p_drawglb, cp_dataglb, FALSE ) ){
			p_drawdata->seq++;
		}
		break;

	case ZKN_SOUNDSUB_SEQDELETE_RELEASE:
		// Resource�ǂݍ���
		ZknSoundSubReleaseResource( p_drawwork, p_drawglb, p_drawdata->heap );
		p_drawdata->seq++;
		break;
		
	case ZKN_SOUNDSUB_SEQDELETE_FREE:
		sys_FreeMemoryEz( p_drawdata->p_work );
		p_drawdata->seq++;
		break;
		
		
	case ZKN_SOUNDSUB_SEQDELETE_END:
		return ZKN_PROC_TRUE;
		
	default:
		break;
	}
	return ZKN_PROC_FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAM�t�F�[�h����	������
 *
 *	@param	p_draw	�`�惏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubOamFadeInit( ZKN_SOUND_SUB_DRAW* p_draw )
{
	CLACT_ObjModeSet( p_draw->dial, GX_OAM_MODE_XLU );
	CLACT_ObjModeSet( p_draw->pich_switch, GX_OAM_MODE_XLU );
	CLACT_ObjModeSet( p_draw->startstop, GX_OAM_MODE_XLU );
	CLACT_ObjModeSet( p_draw->loop, GX_OAM_MODE_XLU );

	FONTOAM_ObjModeSet( p_draw->p_fontoam[ ZKN_SOUNDSUB_SEQ_SWITCH_PICH ]->p_fontoam, GX_OAM_MODE_XLU );
	FONTOAM_ObjModeSet( p_draw->p_fontoam[ ZKN_SOUNDSUB_SEQ_SWITCH_PAN ]->p_fontoam, GX_OAM_MODE_XLU );
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAM�t�F�[�h�����@�㏈��
 *
 *	@param	p_draw 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubOamFadeDelete( ZKN_SOUND_SUB_DRAW* p_draw )
{
	CLACT_ObjModeSet( p_draw->dial, GX_OAM_MODE_NORMAL );
	CLACT_ObjModeSet( p_draw->pich_switch, GX_OAM_MODE_NORMAL );
	CLACT_ObjModeSet( p_draw->startstop, GX_OAM_MODE_NORMAL );
	CLACT_ObjModeSet( p_draw->loop, GX_OAM_MODE_NORMAL );

	FONTOAM_ObjModeSet( p_draw->p_fontoam[ ZKN_SOUNDSUB_SEQ_SWITCH_PICH ]->p_fontoam, GX_OAM_MODE_NORMAL );
	FONTOAM_ObjModeSet( p_draw->p_fontoam[ ZKN_SOUNDSUB_SEQ_SWITCH_PAN ]->p_fontoam, GX_OAM_MODE_NORMAL );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�T�u��ʃt�F�[�h����
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb		�`��O���[�o��
 *	@param	cp_glb		�O���[�o��
 *	@param	fadein_out	�t�F�[�h�C���@TRUE�@�A�E�g FALSE	
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubFadeInit( ZKN_SOUND_SUB_DRAW* p_draw, ZKN_SOUND_SUB_DRAWGLB* p_drawglb, const ZKN_SOUND_SUB_GLB* cp_glb, BOOL fadein_out )
{
	// ������OAM�ݒ�
	ZknSoundSubOamFadeInit( p_draw );

	// �u���C�g�l�X�������s���Ă悢��
	if( ZKN_ZukanCommonSubBrightnessOnFlagGet( cp_glb->cp_zukan_common_apl ) ){
		if( fadein_out ){
			// �t�F�[�h�C��
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade_sub, ZKN_SOUND_FADE_SYNC, 
					BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, 0, 16, ZKN_SOUNDSUB_FADE_PLANEMSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_SUB );
		}else{
			// �t�F�[�h�A�E�g
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade_sub, ZKN_SOUND_FADE_SYNC, 
					BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, 16, 0, ZKN_SOUNDSUB_FADE_PLANEMSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_SUB );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�F�[�h�����@���C��
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb		�`��O���[�o��
 *	@param	cp_glb		�O���[�o��
 *	@param	fadein_out	�t�F�[�h�C���@TRUE�@�A�E�g�@FALSE
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
static BOOL ZknSoundSubFadeMain( ZKN_SOUND_SUB_DRAW* p_draw, ZKN_SOUND_SUB_DRAWGLB* p_drawglb, const ZKN_SOUND_SUB_GLB* cp_glb, BOOL fadein_out )
{
	BOOL check;

	// �u���C�g�l�X���悤���łĂ邩�`�F�b�N
	if( ZKN_ZukanCommonSubBrightnessOnFlagGet( cp_glb->cp_zukan_common_apl ) ){
		check = ZKN_GLB_ChangeFadeMain( &p_drawglb->p_drawglb->fade_sub );
	}else{
//		check = ZKN_GLB_ChangeFadeEndCheck( &p_drawglb->p_drawglb->fade_sub );
		check = IsFinishedBrightnessChg( MASK_SUB_DISPLAY );
	}

	// �I�������I������
	if( check ){
		if( fadein_out ){
			// ������OAM�j��
			ZknSoundSubOamFadeDelete( p_draw );
		}

		return TRUE;
	}

	return FALSE;
}



//----------------------------------------------------------------------------
/**
 *	@brief	�{�^���쐬�֐�
 *
 *	@param	p_work	���[�N
 *	@param	p_glb	�O���[�o��
 *	@param	heap	�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubButtonMake( ZKN_SOUND_SUB_WORK* p_work, ZKN_SOUND_SUB_GLB* p_glb, int heap )
{
	// �e�[�u���쐬
	p_work->hit_tbl = sys_AllocMemory( heap, sizeof(TP_HIT_TBL) * ZKN_SOUNDSUB_BUTTON_NUM );
	p_work->p_sub_hit_tbl = sys_AllocMemory( heap, sizeof(TP_HIT_TBL) * ZKN_SOUNDSUB_BUTTON_SUB_NUM );

	// �e�[�u���f�[�^�ݒ�
	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_SOUNDSUB_BUTTON_SWITCH ],
			ZKN_SOUNDSUB_BUTTON_SWITCH_Y - (ZKN_SOUNDSUB_BUTTON_SWITCH_SIZYH),
			ZKN_SOUNDSUB_BUTTON_SWITCH_Y + (ZKN_SOUNDSUB_BUTTON_SWITCH_SIZYH),
			ZKN_SOUNDSUB_BUTTON_SWITCH_X - (ZKN_SOUNDSUB_BUTTON_SWITCH_SIZXH),
			ZKN_SOUNDSUB_BUTTON_SWITCH_X + (ZKN_SOUNDSUB_BUTTON_SWITCH_SIZXH) );

	p_work->hit_tbl[ ZKN_SOUNDSUB_BUTTON_DIAL ].circle.code = TP_USE_CIRCLE;
	p_work->hit_tbl[ ZKN_SOUNDSUB_BUTTON_DIAL ].circle.x = ZKN_SOUNDSUB_BUTTON_DIAL_X;
	p_work->hit_tbl[ ZKN_SOUNDSUB_BUTTON_DIAL ].circle.y = ZKN_SOUNDSUB_BUTTON_DIAL_Y;
	p_work->hit_tbl[ ZKN_SOUNDSUB_BUTTON_DIAL ].circle.r = ZKN_SOUNDSUB_BUTTON_DIAL_R;


	p_work->hit_tbl[ ZKN_SOUNDSUB_BUTTON_DISK ].circle.code = TP_USE_CIRCLE;
	p_work->hit_tbl[ ZKN_SOUNDSUB_BUTTON_DISK ].circle.x = ZKN_SOUNDSUB_DISK_BG_CENTER_X;
	p_work->hit_tbl[ ZKN_SOUNDSUB_BUTTON_DISK ].circle.y = ZKN_SOUNDSUB_DISK_BG_CENTER_Y + ZKN_SOUNDSUB_DISK_BG_CENTER_T_OFS_Y;
	p_work->hit_tbl[ ZKN_SOUNDSUB_BUTTON_DISK ].circle.r = ZKN_SOUNDSUB_DISK_BG_R;


	// �T�u�{�^���}�l�[�W���p
	ZKN_UTIL_HitTblDataSet( &p_work->p_sub_hit_tbl[ ZKN_SOUNDSUB_BUTTON_SUB_STARTSTOP ],
			ZKN_SOUNDSUB_BUTTON_STARTSTOP_Y - (ZKN_SOUNDSUB_BUTTON_STARTSTOP_SIZYH),
			ZKN_SOUNDSUB_BUTTON_STARTSTOP_Y + (ZKN_SOUNDSUB_BUTTON_STARTSTOP_SIZYH),
			ZKN_SOUNDSUB_BUTTON_STARTSTOP_X - (ZKN_SOUNDSUB_BUTTON_STARTSTOP_SIZXH),
			ZKN_SOUNDSUB_BUTTON_STARTSTOP_X + (ZKN_SOUNDSUB_BUTTON_STARTSTOP_SIZXH) );

	ZKN_UTIL_HitTblDataSet( &p_work->p_sub_hit_tbl[ ZKN_SOUNDSUB_BUTTON_SUB_LOOP ],
			ZKN_SOUNDSUB_BUTTON_LOOP_Y - (ZKN_SOUNDSUB_BUTTON_LOOP_SIZYH),
			ZKN_SOUNDSUB_BUTTON_LOOP_Y + (ZKN_SOUNDSUB_BUTTON_LOOP_SIZYH),
			ZKN_SOUNDSUB_BUTTON_LOOP_X - (ZKN_SOUNDSUB_BUTTON_LOOP_SIZXH),
			ZKN_SOUNDSUB_BUTTON_LOOP_X + (ZKN_SOUNDSUB_BUTTON_LOOP_SIZXH) );

	p_work->callcack.p_glb = p_glb;
	p_work->callcack.p_work = p_work;


	// �{�^���}�l�[�W���쐬
	p_work->p_button_man = BMN_Create( 
			p_work->hit_tbl,
			ZKN_SOUNDSUB_BUTTON_NUM,
			ZknSoundSubButtonCallBack,
			&p_work->callcack,
			heap );

	// �Đ��{�^���p�}�l�[�W��
	p_work->p_sub_button_man = BMN_Create( 
			p_work->p_sub_hit_tbl,
			ZKN_SOUNDSUB_BUTTON_SUB_NUM,
			ZknSoundSubStartButtonCallBack,
			&p_work->callcack,
			heap );
	
}

//----------------------------------------------------------------------------
/**
 *	@brief	�{�^�����쏈��
 *
 *	@param	p_work	���[�N
 *	@param	p_glb	�O���[�o���f�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubButtonMove( ZKN_SOUND_SUB_WORK* p_work, ZKN_SOUND_SUB_GLB* p_glb )
{
	int i;
	// �{�^���C�x���g���i�[
	for( i=0; i<ZKN_SOUNDSUB_BUTTON_SUB_NUM; i++ ){
		p_work->sub_button_event[ i ] = ZKN_SOUNDDUB_BUTTON_START_NOTOUCH;
	}
	
	BMN_Main( p_work->p_button_man );
	BMN_Main( p_work->p_sub_button_man );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�{�^���j��
 *
 *	@param	p_work	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubButtonDelete( ZKN_SOUND_SUB_WORK* p_work )
{
	BMN_Delete( p_work->p_button_man );
	BMN_Delete( p_work->p_sub_button_man );

	// �e�[�u�����[�N�j��
	sys_FreeMemoryEz( p_work->hit_tbl );
	p_work->hit_tbl = NULL;
	sys_FreeMemoryEz( p_work->p_sub_hit_tbl );
	p_work->p_sub_hit_tbl = NULL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�{�^���R�[���o�b�N�֐�
 *
 *	@param	button_no	�{�^���i���o�[
 *	@param	event		�{�^���C�x���g�^�C�v
 *	@param	p_work		���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubButtonCallBack( u32 button_no, u32 event, void* p_work )
{
	ZKN_SOUND_BUTTON_CALLBACK* p_work_data = p_work;
	ZKN_SOUND_SUB_GLB* p_glb = p_work_data->p_glb;
	ZKN_SOUND_SUB_WORK* p_subwork = p_work_data->p_work;

	switch( event ){
	case BMN_EVENT_TOUCH:
		ZknSoundSubButtonTouch( button_no, p_glb, p_subwork );
		break;

	case BMN_EVENT_HOLD:
		ZknSoundSubButtonHold( button_no, p_glb, p_subwork );
		break;

	case BMN_EVENT_RELEASE:	
		ZknSoundSubButtonRelease( button_no, p_glb, p_subwork );
		break;

	case BMN_EVENT_SLIDEOUT:
		ZknSoundSubButtonSlideOut( button_no, p_glb, p_subwork );
		break;
		
	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Đ��{�^���R�[���o�b�N�֐�
 *
 *	@param	button_no	�{�^���i���o�[
 *	@param	event		�{�^���C�x���g�^�C�v
 *	@param	p_work		���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubStartButtonCallBack( u32 button_no, u32 event, void* p_work )
{
	ZKN_SOUND_BUTTON_CALLBACK* p_work_data = p_work;
	ZKN_SOUND_SUB_GLB* p_glb = p_work_data->p_glb;
	ZKN_SOUND_SUB_WORK* p_subwork = p_work_data->p_work;
	int monsno = ZKN_GLBDATA_PokeMonsNoGet( p_glb->p_glb );

	// �{�^���C�x���g�ݒ�
	p_subwork->sub_button_event[ button_no ] = event;

	switch( event ){
	case BMN_EVENT_TOUCH:
		p_subwork->start_touch_on = FALSE;
		break;

	case BMN_EVENT_HOLD:
		if( p_subwork->start_touch_on == FALSE ){
			p_subwork->start_touch_on = TRUE;
			switch( button_no ){
			case ZKN_SOUNDSUB_BUTTON_SUB_STARTSTOP:
				// ���[�v���[�h�̎��̏���
				if( p_subwork->loop == TRUE ){
					// �Đ���~�ݒ�
					if( p_subwork->sound_play == FALSE ){
						ZknSoundSubSoundStart( p_subwork, p_glb, monsno );
					}else{
						// ��~
						ZknSoundSubSoundStop( p_subwork );
					}
				}else{
					// �Ȃ��Ă�����Ƃ߂�
					if( p_subwork->sound_play == TRUE ){
						Snd_PMVoiceStop(0);
					}	
					
					ZknSoundSubSoundStart( p_subwork, p_glb, monsno );
				}
				break;

			// ���[�v�{�^��
			case ZKN_SOUNDSUB_BUTTON_SUB_LOOP:

				// �L�[����ł̃{�^���A�j��OFF
				// �Đ��A�j��������������
				p_subwork->sound_play_button_cursor = 2;

				ZknSoundSubSoundLoopSet( p_subwork, p_subwork->loop ^ 1 );
				// �{�^���Ƀ^�b�`
				Snd_SePlay( ZKN_SND_BUTTON );
				break;

			default:
				break;
			}
		}
		break;

	case BMN_EVENT_RELEASE:	
		break;

	case BMN_EVENT_SLIDEOUT:
		break;
		
	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�{�^���^�b�`���֐�
 *
 *	@param	button_no		�{�^���i���o�[
 *	@param	p_glb			�O���[�o���f�[�^
 *	@param	p_work			���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubButtonTouch( u32 button_no, ZKN_SOUND_SUB_GLB* p_glb, ZKN_SOUND_SUB_WORK* p_work )
{

	switch( button_no ){
	case ZKN_SOUNDSUB_BUTTON_SWITCH:
		// �Đ����͕ύX�ł��Ȃ��̂Œ�~
		if( p_work->sound_play == TRUE ){
			ZknSoundSubSoundStop( p_work );
		}

		// �T���v�����O�J�n���W���擾
		p_work->pitch_switch_touch_start_x = sys.tp_x;
		p_work->pitch_switch_touch = TRUE;
		
		break;
		
	case ZKN_SOUNDSUB_BUTTON_DIAL:
		// �Đ����͕ύX�ł��Ȃ��̂Œ�~
		if( p_work->sound_play == TRUE ){
			ZknSoundSubSoundStop( p_work );
		}

		// �T���v�����O�J�n���W���擾
		p_work->dial_touch = TRUE;
		p_work->dial_start_x = sys.tp_x;
		p_work->dial_start_y = sys.tp_y;
		
		break;
		
	case ZKN_SOUNDSUB_BUTTON_DISK:

		// �Đ������`�F�b�N
		if( p_work->sound_play ){

			// �Đ��{�^�����[�v�Ƀq�b�g���Ă��邩�`�F�b�N
			p_work->hit_start_stop_flag = GF_TP_SingleHitCont( &p_work->p_sub_hit_tbl[ZKN_SOUNDSUB_BUTTON_SUB_STARTSTOP] );
			p_work->hit_start_stop_flag |= GF_TP_SingleHitCont( &p_work->p_sub_hit_tbl[ZKN_SOUNDSUB_BUTTON_SUB_LOOP] );

		}else{

			// �����TRUE�ɂ��邱�Ƃɂ��
			// �f�B�X�N�ʂ��^�b�`�������̏�����
			// �s��Ȃ�����
			p_work->hit_start_stop_flag = TRUE;
		}

		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�{�^��Hold
 *
 *	@param	button_no
 *	@param	p_glb
 *	@param	p_work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubButtonHold( u32 button_no, ZKN_SOUND_SUB_GLB* p_glb, ZKN_SOUND_SUB_WORK* p_work )
{
	int touch_move;

	switch( button_no ){
	case ZKN_SOUNDSUB_BUTTON_SWITCH:
		// �^�b�`�t���O�������Ă���Ƃ��̂�
		if( p_work->pitch_switch_touch == TRUE ){

			// �T���v�����O������W���v�Z
			touch_move = sys.tp_x - p_work->pitch_switch_touch_start_x;

			// ���̃X�C�b�`��Ԃ���؂�ւ��邩�`�F�b�N����
			if( p_work->pitch_switch_flag == ZKN_SOUNDSUB_SEQ_SWITCH_PICH ){
				// �؂�ւ��`�F�b�N
				if( ZKN_SOUNDSUB_SWITCH_MOVE_OK_DIS <= touch_move ){
					p_work->pitch_switch_flag = ZKN_SOUNDSUB_SEQ_SWITCH_PAN;
					p_work->pitch_switch_touch_start_x = sys.tp_x;	// �^�b�`�J�n���܂��ݒ�

					// �{�^���Ƀ^�b�`
					Snd_SePlay( ZKN_SND_SWITCH );
				}
			}else{

				// �؂�ւ��`�F�b�N
				if( -ZKN_SOUNDSUB_SWITCH_MOVE_OK_DIS >= touch_move ){
					p_work->pitch_switch_flag = ZKN_SOUNDSUB_SEQ_SWITCH_PICH;
					p_work->pitch_switch_touch_start_x = sys.tp_x;	// �^�b�`�J�n���܂��ݒ�

					// �{�^���Ƀ^�b�`
					Snd_SePlay( ZKN_SND_SWITCH );
				}
			}
		}
		break;
		
	case ZKN_SOUNDSUB_BUTTON_DIAL:
		// �Đ����͕ύX�ł��Ȃ�
		if( p_work->dial_touch == TRUE ){

			// �_�C�����p�x�v�Z
			ZknSoundSubDialCalc( p_work );

			// ���ݕ����ʒu��ݒ�
			ZknSoundSubDialDivSet( p_work );

			// ���o�[�u�t�B���^�[�ݒ�ɂ��l�ݒ�
			ZknSoundSubDialNumSet( p_work );

			// ���̒l�i�[
			p_work->dial_start_x = sys.tp_x;
			p_work->dial_start_y = sys.tp_y;
		}
		break;
		
	case ZKN_SOUNDSUB_BUTTON_DISK:


		// �Đ��{�^���ɐG���Ă��Ȃ��Ƃ�
		if( p_work->hit_start_stop_flag == FALSE  ){

			// �Đ����Ŗ����Ȃ���������������s��Ȃ��悤�ɂ���
			if( p_work->sound_play == FALSE ){
				p_work->hit_start_stop_flag = TRUE;

				// �ݒ蒆�t���O�𗎂Ƃ�
				ZknSoundSubPitchPanChorusOnOff( p_work, FALSE );
			}else{
			
				// �Z���^�[����ォ�����ŏ���������
				if( sys.tp_y < ZKN_SOUNDSUB_DISK_BG_CENTER_Y + ZKN_SOUNDSUB_DISK_BG_CENTER_OFS_Y ){
					// �s�b�`OR�p���̐ݒ�
					if( p_work->pitch_switch_flag == ZKN_SOUNDSUB_SEQ_SWITCH_PICH ){
//						ZknSoundSubDiskPitchSet( p_work, sys.tp_x );
						ZknSoundSubDiskChorusSet( p_work, sys.tp_x );
					}else{
						ZknSoundSubDiskPanSet( p_work, sys.tp_x );
					}
					p_work->pitch_num = 0;	// �s�b�`�̒l�͏�����
					// �ݒ蒆�t���O�𗧂Ă�
					ZknSoundSubPitchPanChorusOnOff( p_work, TRUE );
				}else{

					// �ݒ蒆�t���O�𗎂Ƃ�
					ZknSoundSubPitchPanChorusFlagOnOff( p_work, FALSE );

					// �s�b�`�̒l���Œ�ɂ���
					p_work->pitch_num = SND_ZUKAN_PITCH_MIN;
				}
			}

			// �s�b�`�p���̒l��ݒ�
			ZknSoundSubPitchPanChorusSet( p_work );
		}
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�{�^��Release
 *
 *	@param	button_no
 *	@param	p_glb
 *	@param	p_work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubButtonRelease( u32 button_no, ZKN_SOUND_SUB_GLB* p_glb, ZKN_SOUND_SUB_WORK* p_work )
{
		
	switch( button_no ){
	case ZKN_SOUNDSUB_BUTTON_SWITCH:
		p_work->pitch_switch_touch = FALSE;
		break;
		
	case ZKN_SOUNDSUB_BUTTON_DIAL:
		p_work->dial_rota = p_work->dial_div * ZKN_SOUNDSUB_DIAL_MIN_CUT_NUM;
		
		p_work->dial_touch = FALSE;
		break;
		
	case ZKN_SOUNDSUB_BUTTON_DISK:
		// �Đ��{�^���ɐG���Ă��Ȃ��Ƃ�
		if( p_work->hit_start_stop_flag == FALSE  ){

			// �ݒ蒆�t���O�𗎂Ƃ�
			ZknSoundSubPitchPanChorusOnOff( p_work, FALSE );
			
			// �s�b�`�p���̒l��ݒ�
			ZknSoundSubPitchPanChorusSet( p_work );
		}
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�{�^���X���C�h�A�E�g
 *
 *	@param	button_no
 *	@param	p_glb
 *	@param	p_work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubButtonSlideOut( u32 button_no, ZKN_SOUND_SUB_GLB* p_glb, ZKN_SOUND_SUB_WORK* p_work )
{
	switch( button_no ){
	case ZKN_SOUNDSUB_BUTTON_SWITCH:
		p_work->pitch_switch_touch = FALSE;
		break;
		
	case ZKN_SOUNDSUB_BUTTON_DIAL:
		p_work->dial_rota = p_work->dial_div * ZKN_SOUNDSUB_DIAL_MIN_CUT_NUM;
		p_work->dial_touch = FALSE;
		break;
		
	case ZKN_SOUNDSUB_BUTTON_DISK:
		// �Đ��{�^���ɐG���Ă��Ȃ��Ƃ�
		if( p_work->hit_start_stop_flag == FALSE  ){

			// �ݒ蒆�t���O�𗎂Ƃ�
			ZknSoundSubPitchPanChorusOnOff( p_work, FALSE );
			
			// �s�b�`�p���̒l��ݒ�
			ZknSoundSubPitchPanChorusSet( p_work );
		}
		break;

	default:
		break;
	}
}




//----------------------------------------------------------------------------
/**
 *	@brief	�O���t�B�b�N����������
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubLoadResource( ZKN_SOUND_SUB_DRAW* p_draw, ZKN_SOUND_SUB_DRAWGLB* p_drawglb, int heap )
{
	// �w�i
	ZknSoundSubSetUpBg( p_drawglb, heap );

	// OAM
	ZknSoundSubLoadOamData( p_draw, p_drawglb, heap );

	// �Z���A�N�^�[�o�^
	ZknSoundSubAddClact( p_draw, p_drawglb, heap );

	// FONTOAM�o�^
	ZknSoundSubAddFontOam( p_draw, p_drawglb, heap );

	// �A�j���p�p���b�g�ǂݍ���
	ZknSoundSubPlttLoad( p_draw, p_drawglb, heap );

}

//----------------------------------------------------------------------------
/**
 *	@brief	�O���t�B�b�N�j������
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubReleaseResource( ZKN_SOUND_SUB_DRAW* p_draw, ZKN_SOUND_SUB_DRAWGLB* p_drawglb, int heap )
{
	int i;
	
	// �Z���A�N�^�[�j��
	ZknSoundSubDeleteClact( p_draw );

	// FONTOAM�j��
	ZknSoundSubDeleteFontOam( p_draw, p_drawglb );

	// OAM
	ZknSoundSubReleaseOamData( p_draw, p_drawglb );

	// �w�i������
	ZknSoundSubPutDownBg( p_drawglb );

	// �A�j���p�p���b�g�j��
	ZknSoundSubPlttRelease( p_draw );
}

//----------------------------------------------------------------------------
/**
 *	@brief	BG�ʃZ�b�g�A�b�v
 *
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubSetUpBg( ZKN_SOUND_SUB_DRAWGLB* p_drawglb, int heap )
{
	void* buff;
	NNSG2dScreenData* p_scrn;

	// �L�����N�^�f�[�^�]��
	ZKN_GLBDATA_BgCharSet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_sub_lzh_NCGR, p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_S, 0, 0, TRUE, heap );

	// �X�N���[���f�[�^�ǂݍ���
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_voice_bg_sub1_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// �X�N���[���f�[�^��������
	GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_S,
			p_scrn->rawData, 0, 0,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );

	// �X�N���[���f�[�^�]��
	GF_BGL_LoadScreenV_Req(p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_S );


	// �f�B�X�N
	// �L�����N�^�f�[�^�]��
	ZKN_GLBDATA_BgCharSet( p_drawglb->p_drawglb, NARC_zukan_zkn_voice_disk_lzh_NCGR, p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_AFFINE_S, 0, 0, TRUE, heap );

	// �X�N���[���f�[�^�ǂݍ���
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_voice_disk_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// �X�N���[���f�[�^��������
	GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_AFFINE_S,
			p_scrn->rawData, 0, 0,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );

	// �X�N���[���f�[�^�]��
	GF_BGL_LoadScreenV_Req(p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_AFFINE_S );

	// �f�B�X�N���W��BG�D�揇�ʐݒ�
	GF_BGL_ScrollSet( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_AFFINE_S, GF_BGL_SCROLL_X_SET, ZKN_SOUNDSUB_DISK_BG_X );
	GF_BGL_ScrollSet( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_AFFINE_S, GF_BGL_SCROLL_Y_SET, ZKN_SOUNDSUB_DISK_BG_Y );
	GF_BGL_PrioritySet( ZKN_BG_FRM_AFFINE_S, 3 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	BG�ʍŏI����
 *
 *	@param	p_drawglb 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubPutDownBg( ZKN_SOUND_SUB_DRAWGLB* p_drawglb )
{
	// �X�N���[��������
	GF_BGL_ScrClear( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_S );
	GF_BGL_ScrClear( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_AFFINE_S );

	GF_BGL_PrioritySet( ZKN_BG_FRM_AFFINE_S, 1 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAM���\�[�X�ǂݍ���
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubLoadOamData( ZKN_SOUND_SUB_DRAW* p_draw, ZKN_SOUND_SUB_DRAWGLB* p_drawglb, int heap )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;
	ARCHANDLE* p_handle = ZKN_GLBDATA_ArcHandlGet( p_drawglb->p_drawglb );
	
	// �L�����N�^�f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ], p_handle,
			NARC_zukan_zkn_voice_oam_sub_lzh_NCGR, TRUE,
			NARC_zukan_zkn_voice_oam_sub_lzh_NCGR + ZKN_SOUND_SUB_RES_ID,
			NNS_G2D_VRAM_TYPE_2DSUB, heap );
	// �]��
	CLACT_U_CharManagerSetAreaCont( p_draw->res_obj[ CLACT_U_CHAR_RES ] );
	// �O���t�B�b�N�f�[�^�����j��
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_CHAR_RES ] );

	// �p���b�g�f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerResAddArcPltt_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ], p_handle,
			NARC_zukan_zkn_voice_oam_sub_NCLR, FALSE, 
			NARC_zukan_zkn_voice_oam_sub_NCLR + ZKN_SOUND_SUB_RES_ID, 
			NNS_G2D_VRAM_TYPE_2DSUB, 
			ZKN_SOUNDSUB_PLTT_LOAD, heap );
	// �]��
	CLACT_U_PlttManagerSetCleanArea( p_draw->res_obj[ CLACT_U_PLTT_RES ] );	
	// �O���t�B�b�N�f�[�^�����j��
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_PLTT_RES ] );


	// �Z���f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ], p_handle,
			NARC_zukan_zkn_voice_oam_sub_lzh_NCER, TRUE,
			NARC_zukan_zkn_voice_oam_sub_lzh_NCER + ZKN_SOUND_SUB_RES_ID,
			CLACT_U_CELL_RES, heap );

	// �Z���A�j���f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ], p_handle, 
			NARC_zukan_zkn_voice_oam_sub_lzh_NANR, TRUE,
			NARC_zukan_zkn_voice_oam_sub_lzh_NANR + ZKN_SOUND_SUB_RES_ID,
			CLACT_U_CELLANM_RES, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAM���\�[�X�j��
 *
 *	@param	p_draw			�`�惏�[�N
 *	@param	p_drawglb		�`��O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubReleaseOamData( ZKN_SOUND_SUB_DRAW* p_draw, ZKN_SOUND_SUB_DRAWGLB* p_drawglb )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;


	CLACT_U_CharManagerDelete( p_draw->res_obj[ CLACT_U_CHAR_RES ] );
	CLACT_U_PlttManagerDelete( p_draw->res_obj[ CLACT_U_PLTT_RES ] );

	// ���\�[�X�j��
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw->res_obj[ CLACT_U_CHAR_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw->res_obj[ CLACT_U_PLTT_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw->res_obj[ CLACT_U_CELL_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			p_draw->res_obj[ CLACT_U_CELLANM_RES ] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Z���A�N�^�[�o�^
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubAddClact( ZKN_SOUND_SUB_DRAW* p_draw, ZKN_SOUND_SUB_DRAWGLB* p_drawglb, int heap )
{
	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	ZKN_GLB_DRAWDATA*	p_draw_glb = p_drawglb->p_drawglb;
	int i;
	int x, y;
	
	// �A�N�^�[�w�b�_�[�쐬
	CLACT_U_MakeHeader( &clact_head,
			NARC_zukan_zkn_voice_oam_sub_lzh_NCGR + ZKN_SOUND_SUB_RES_ID,
			NARC_zukan_zkn_voice_oam_sub_NCLR + ZKN_SOUND_SUB_RES_ID, 
			NARC_zukan_zkn_voice_oam_sub_lzh_NCER + ZKN_SOUND_SUB_RES_ID,
			NARC_zukan_zkn_voice_oam_sub_lzh_NANR + ZKN_SOUND_SUB_RES_ID,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, ZKN_SOUND_SUB_OAM_BG_PTR,
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	// �o�^���ʕ�����ݒ�
	add.ClActSet	= p_draw_glb->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= 31;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DSUB;
	add.heap		= heap;
	
	// �s�b�`switch
	add.mat.x = ZKN_SOUNDSUB_BUTTON_SWITCH_X << FX32_SHIFT;
	add.mat.y = ZKN_SOUNDSUB_BUTTON_SWITCH_Y << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_draw->pich_switch = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->pich_switch, ZKN_SOUNDSUB_SEQ_SWITCH_PAN_PICH );	
	CLACT_SetAnmFlag( p_draw->pich_switch, TRUE );
	CLACT_SetAnmFrame( p_draw->pich_switch, ZKN_SOUNDSUB_ANIME_FRAME );
	CLACT_AnmFrameSet( p_draw->pich_switch,ZKN_SOUNDSUB_SWITCH_08 );

	// �_�C����
	add.mat.x = ZKN_SOUNDSUB_BUTTON_DIAL_X << FX32_SHIFT;
	add.mat.y = ZKN_SOUNDSUB_BUTTON_DIAL_Y << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_draw->dial = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->dial, ZKN_SOUNDSUB_SEQ_DIAL );	
	CLACT_SetAffineParam( p_draw->dial, CLACT_AFFINE_NORMAL );

	// �J�n��~
	add.mat.x = ZKN_SOUNDSUB_BUTTON_STARTSTOP_X_DRAW << FX32_SHIFT;
	add.mat.y = ZKN_SOUNDSUB_BUTTON_STARTSTOP_Y_DRAW << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_draw->startstop = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->startstop, ZKN_SOUNDSUB_SEQ_SOUND_START_ANM );	
	CLACT_SetAnmFlag( p_draw->startstop, TRUE );
	CLACT_SetAnmFrame( p_draw->startstop, ZKN_SOUNDSUB_ANIME_FRAME );
	CLACT_AnmFrameSet(p_draw->startstop, ZKN_SOUNDSUB_START_05 );
	// �A�j���f�[�^�ݒ�
	p_draw->start_stop_anim.anm_seq1 = ZKN_SOUNDSUB_SEQ_SOUND_START_ANM; 
	p_draw->start_stop_anim.anm_seq2 = ZKN_SOUNDSUB_SEQ_SOUND_STOP_ANM; 
	p_draw->start_stop_anim.now_anm_seq = ZKN_SOUNDSUB_SEQ_SOUND_START_ANM;
	p_draw->start_stop_anim.anm_num_max = ZKN_SOUNDSUB_START_05;
	p_draw->start_stop_anim.push_anm_limit = ZKN_SOUNDSUB_START_02;


	// ���[�v
	add.mat.x = ZKN_SOUNDSUB_BUTTON_LOOP_X_DRAW << FX32_SHIFT;
	add.mat.y = ZKN_SOUNDSUB_BUTTON_LOOP_Y_DRAW << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_draw->loop = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->loop, ZKN_SOUNDSUB_SEQ_SOUND_LOOPOFF_ANM );	
	CLACT_SetAnmFlag( p_draw->loop, TRUE );
	CLACT_SetAnmFrame( p_draw->loop, ZKN_SOUNDSUB_ANIME_FRAME );
	CLACT_AnmFrameSet(p_draw->loop, ZKN_SOUNDSUB_LOOP_05 );
	// �A�j���f�[�^�ݒ�
	p_draw->loop_anim.anm_seq1 = ZKN_SOUNDSUB_SEQ_SOUND_LOOPOFF_ANM; 
	p_draw->loop_anim.anm_seq2 = ZKN_SOUNDSUB_SEQ_SOUND_LOOPON_ANM; 
	p_draw->loop_anim.now_anm_seq = ZKN_SOUNDSUB_SEQ_SOUND_LOOPOFF_ANM;
	p_draw->loop_anim.anm_num_max = ZKN_SOUNDSUB_LOOP_05;
	p_draw->loop_anim.push_anm_limit = ZKN_SOUNDSUB_LOOP_02;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Z���A�N�^�[�j��
 *
 *	@param	p_draw	�`�惏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubDeleteClact( ZKN_SOUND_SUB_DRAW* p_draw )
{
	CLACT_Delete( p_draw->dial );
	CLACT_Delete( p_draw->pich_switch );
	CLACT_Delete( p_draw->startstop );
	CLACT_Delete( p_draw->loop );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�t�H���gOAM�쐬
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubAddFontOam( ZKN_SOUND_SUB_DRAW* p_draw, ZKN_SOUND_SUB_DRAWGLB* p_drawglb, int heap )
{
	GF_BGL_BMPWIN* win;	// �����񏑂����ݐ�
	ZKN_FONTOAM_INIT fontoam_init;
	CLACT_U_RES_OBJ_PTR res_obj;
	ZKN_GLB_DRAWDATA* p_glb_draw = p_drawglb->p_drawglb;
	int pltt_ofs;	// �p���b�g�A�h���X

	// �p���b�g�̃��\�[�X�f�[�^�擾
	// �p���b�g�v���N�V�擾�p
	res_obj = CLACT_U_ResManagerGetIDResObjPtr( p_glb_draw->res_manager[ CLACT_U_PLTT_RES ], NARC_zukan_zkn_voice_oam_sub_NCLR + ZKN_SOUND_SUB_RES_ID );

	// �������f�[�^�̋��ʕ������쐬
	// ���ʃf�[�^���
	fontoam_init.zkn_fontoam = p_glb_draw->fontoam_sys;
	fontoam_init.pltt		 = CLACT_U_PlttManagerGetProxy( res_obj, NULL );
	fontoam_init.parent		 = NULL;
	fontoam_init.y			 = ZKN_SOUNDSUB_PITCH_PAN_FOTN_Y + 192;
	fontoam_init.bg_pri		 = ZKN_SOUND_SUB_OAM_BG_PTR;
	fontoam_init.soft_pri	 = 0;
	fontoam_init.draw_area	 = NNS_G2D_VRAM_TYPE_2DSUB;
	fontoam_init.heap		 = heap;

	// �p���b�g�]����A�h���X�擾
	pltt_ofs = GetPlttProxyOffset( fontoam_init.pltt, NNS_G2D_VRAM_TYPE_2DSUB );

	// �r�b�g�}�b�v�E�B���h�E�쐬
	win = ZKN_FONTOAM_GetBmp( p_glb_draw->fontoam_sys, 
			ZKN_SOUNDSUB_BUTTONFONT_BMP_SIZE_CX,
			ZKN_SOUNDSUB_BUTTONFONT_BMP_SIZE_CY );


	// �s�b�`
	fontoam_init.x			 = ZKN_SOUNDSUB_PITCH_FOTN_X;
	ZKN_FONTOAM_PrintBmpStr( p_glb_draw->fontoam_sys, win,
			NARC_msg_zkn_dat, ZNK_SOUND_BUTTON_00, 0, 0 );
	fontoam_init.p_bmp		 = win;
	p_draw->p_fontoam[ ZKN_SOUNDSUB_SEQ_SWITCH_PICH ] = ZKN_FONTOAM_Make( &fontoam_init );
	FONTOAM_SetPaletteNo( p_draw->p_fontoam[ ZKN_SOUNDSUB_SEQ_SWITCH_PICH ]->p_fontoam, pltt_ofs + ZKN_SOUNDSUB_BUTTON_PAL_OFS );

	// �r�b�g�}�b�v�E�B���h�E�j��
	ZKN_FONTOAM_DeleteBmp( win );


	// �r�b�g�}�b�v�E�B���h�E�쐬
	win = ZKN_FONTOAM_GetBmp( p_glb_draw->fontoam_sys, 
			ZKN_SOUNDSUB_BUTTONFONT_BMP_SIZE_CX,
			ZKN_SOUNDSUB_BUTTONFONT_BMP_SIZE_CY );


	// �p��
	fontoam_init.x			 = ZKN_SOUNDSUB_PAN_FOTN_X;
	ZKN_FONTOAM_PrintBmpStr( p_glb_draw->fontoam_sys, win,
			NARC_msg_zkn_dat, ZNK_SOUND_BUTTON_01, 0, 0 );
	fontoam_init.p_bmp		 = win;
	p_draw->p_fontoam[ ZKN_SOUNDSUB_SEQ_SWITCH_PAN ] = ZKN_FONTOAM_Make( &fontoam_init );
	FONTOAM_SetPaletteNo( p_draw->p_fontoam[ ZKN_SOUNDSUB_SEQ_SWITCH_PAN ]->p_fontoam, pltt_ofs + ZKN_SOUNDSUB_BUTTON_PAL_OFS );

	// �r�b�g�}�b�v�E�B���h�E�j��
	ZKN_FONTOAM_DeleteBmp( win );

	// �p����W��
	FONTOAM_SetDrawFlag( p_draw->p_fontoam[ ZKN_SOUNDSUB_SEQ_SWITCH_PAN ]->p_fontoam, FALSE );

}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�H���gOAM�j��
 *	
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubDeleteFontOam( ZKN_SOUND_SUB_DRAW* p_draw, ZKN_SOUND_SUB_DRAWGLB* p_drawglb )
{
	int i;
	for( i=0; i<ZKN_SOUNDSUB_SEQ_SWITCH_NUM; i++ ){
		ZKN_FONTOAM_Delete( p_draw->p_fontoam[ i ] );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�s�b�`�p���؂�ւ��X�C�b�`����
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	cp_work		���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubSwitchDrawMove( ZKN_SOUND_SUB_DRAW* p_draw, const ZKN_SOUND_SUB_WORK* cp_work )
{
	int anm_frm;
	
	if( p_draw->now_switch != cp_work->pitch_switch_flag ){
		anm_frm = CLACT_AnmFrameGet( p_draw->pich_switch );
		
		// �A�j���V�[�P���X�ύX
		if( cp_work->pitch_switch_flag == ZKN_SOUNDSUB_SEQ_SWITCH_PICH ){
			CLACT_AnmChg( p_draw->pich_switch, ZKN_SOUNDSUB_SEQ_SWITCH_PAN_PICH );
			CLACT_AnmFrameSet( p_draw->pich_switch, ZKN_SOUNDSUB_SWITCH_08 - anm_frm );
		}else{
			CLACT_AnmChg( p_draw->pich_switch, ZKN_SOUNDSUB_SEQ_SWITCH_PICH_PAN );
			CLACT_AnmFrameSet( p_draw->pich_switch, ZKN_SOUNDSUB_SWITCH_08 - anm_frm );
		}

		p_draw->now_switch = cp_work->pitch_switch_flag;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Đ��X�g�b�v�`�擮��
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	cp_work		���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubStartStopDrawMove( ZKN_SOUND_SUB_DRAW* p_draw, const ZKN_SOUND_SUB_WORK* cp_work )
{
	int button_event = cp_work->sub_button_event[ZKN_SOUNDSUB_BUTTON_SUB_STARTSTOP];

	// ���[�v�Đ��Ŗ����Ƃ��͒�~�{�^���ɂȂ�Ȃ�
	if( cp_work->loop == FALSE ){

		ZknSoundSubButtonAnimeMain_NO_Loop( p_draw->startstop, &p_draw->start_stop_anim,
				FALSE, button_event );
	}else{

		ZknSoundSubButtonAnimeMain( p_draw->startstop, &p_draw->start_stop_anim,
				cp_work->sound_play, button_event );


	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	���[�v�{�^���A�j��
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	cp_work		���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubLoopDrawMove( ZKN_SOUND_SUB_DRAW* p_draw, const ZKN_SOUND_SUB_WORK* cp_work )
{
	int button_event = cp_work->sub_button_event[ZKN_SOUNDSUB_BUTTON_SUB_LOOP];

	ZknSoundSubButtonAnimeMain( p_draw->loop, &p_draw->loop_anim,
			cp_work->loop, button_event );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�_�C��������
 *
 *	@param	p_work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubDialCalc( ZKN_SOUND_SUB_WORK* p_work )
{
	int last_y, last_x;
	int now_y, now_x;
	int rota_num;
	int zettai;
	u16 last_rota, now_rota;

	// �z�C�[���̒��S���W����̒l�ɂ���
	last_x = p_work->dial_start_x - ZKN_SOUNDSUB_BUTTON_DIAL_X;
	last_y = p_work->dial_start_y - ZKN_SOUNDSUB_BUTTON_DIAL_Y;
	now_x = sys.tp_x - ZKN_SOUNDSUB_BUTTON_DIAL_X;
	now_y = sys.tp_y - ZKN_SOUNDSUB_BUTTON_DIAL_Y;

#if 1	// �_���������������擾����^�C�v�̂Ƃ�1
	// �����l�����߂�
	rota_num = CalcTool_CircleVectorDistance( last_x, last_y, now_x, now_y, 0 );
#else
	// �~����
	last_rota = FX_Atan2Idx( last_y, last_x );
	now_rota = FX_Atan2Idx( now_y, now_x );

	rota_num = now_rota - last_rota;

	// ��Βl�����߂�
	if( rota_num < 0 ){
		zettai = -rota_num;
	}else{
		zettai = rota_num;
	}

	// 180�ȏ�ɂȂ邱�Ƃ͍l���ɂ������̏ꍇ��,�O���R�U�O�Ƃ��čl����
	if( zettai >= FX_GET_ROTA_NUM(180) ){
		zettai = FX_GET_ROTA_NUM(360) - zettai;
		zettai = -zettai;		// 0->360�Ƃ����l���ɂȂ邩��x�N�g����ς���K�v������
	}

	// �ݒ�
	if( rota_num < 0 ){
		rota_num = -zettai;
	}else{
		rota_num = zettai;
	}
#endif

	// ���~�b�g�ȉ��̒l�Ȃ甲����
	if( MATH_IAbs( rota_num ) < ZKN_SOUNDSUB_DIAL_MOVE_LIMIT_ROTA ){
		return;
	}

	// ����
	p_work->dial_rota += rota_num;


	// �}�C�i�X�ɂȂ��������
	if( p_work->dial_rota < 0 ){
		p_work->dial_rota += ZKN_SOUNDSUB_DIAL_MOVE_NUM_MAX;
	}else{
		p_work->dial_rota %= ZKN_SOUNDSUB_DIAL_MOVE_NUM_MAX;
	}

//	OS_Printf( "before rota %d\n", p_work->dial_rota / 182 );

	// ���~�b�g�p�x�܂ł����s���Ȃ��悤�ɂ���
	if( (p_work->dial_rota >= ZKN_SOUNDSUB_DIAL_LIMIT_MIN) &&
		(p_work->dial_rota <= ZKN_SOUNDSUB_DIAL_LIMIT_MAX) ){

		if( rota_num > 0 ){
			p_work->dial_rota = ZKN_SOUNDSUB_DIAL_LIMIT_MIN;
		}else{
			p_work->dial_rota = ZKN_SOUNDSUB_DIAL_LIMIT_MAX;
		}
	}

/*	// �Œ�p�x�ɖ������Ȃ��Ƃ���0�ɂ���
	if( (p_work->dial_rota <= ZKN_SOUNDSUB_DIAL_MIN_CUT_NUM) ||
		(p_work->dial_rota >= (FX_GET_ROTA_NUM(360) - ZKN_SOUNDSUB_DIAL_MIN_CUT_NUM)) ){

		p_work->dial_rota = 0;
	}//*/

//	OS_Printf( "after rota %d\n", p_work->dial_rota / 182 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�_�C�����̊p�x�𕪊�����Ă��錈�߂�ꂽ�p�x�̒l�ɐݒ�
 *
 *	@param	p_work	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubDialDivSet( ZKN_SOUND_SUB_WORK* p_work )
{

	// �����p�x�̔{���ɂȂ����特��炷
	if( (p_work->dial_rota / ZKN_SOUNDSUB_DIAL_MIN_CUT_NUM) != p_work->dial_div ){
		// �������̂ŉ����o��
		Snd_SePlay( ZKN_SND_DIAL );

		p_work->dial_div= p_work->dial_rota / ZKN_SOUNDSUB_DIAL_MIN_CUT_NUM;
	}

}


//----------------------------------------------------------------------------
/**
 *	@brief	�_�C�A����]�p�x�ɂ��l��ݒ�
 *
 *	@param	p_work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubDialNumSet( ZKN_SOUND_SUB_WORK* p_work )
{
	int set_num;

	// 0�Ȃ�S��~
	if( p_work->dial_rota == 0 ){
		ZknSoundSubReverbEffectStop( p_work );

		return ;
	}
	
	if( (p_work->dial_rota > 0) &&
		(p_work->dial_rota <= ZKN_SOUNDSUB_DIAL_MOVE_NUM_HALF) ){

		// ���o�[�u���ݒ肳��Ă���Ƃ��͂Ƃ߂�
		if( p_work->dial_flag == ZKN_SOUNDSUB_DIAL_REVERB ){
			Snd_CaptureStopReverb(0);
		}

		// �G�t�F�N�g�J�n���Ă��Ȃ��Ƃ��͊J�n
		if( p_work->dial_flag != ZKN_SOUNDSUB_DIAL_FILTER ){
			Snd_CaptureStartEffect();
			p_work->dial_flag = ZKN_SOUNDSUB_DIAL_FILTER;
		}


		// �ݒ�l�v�Z
		set_num = p_work->dial_div * ZKN_SOUNDSUB_DIAL_FILTER_NUM;
		
		if( set_num == 0 ){
			set_num = 1;
		}

		// �t�B���^�[�ݒ�
		Snd_CaptureEffectLevel( set_num );

	}else{
		// �t�B���^�[�ݒ肳��Ă��鎞�͎~�߂�
		if( p_work->dial_flag == ZKN_SOUNDSUB_DIAL_FILTER ){
			Snd_CaptureStopEffect();
		}

		// ���o�[�u�J�n���Ă��Ȃ��Ƃ��͊J�n
		if( p_work->dial_flag != ZKN_SOUNDSUB_DIAL_REVERB ){
			Snd_CaptureStartReverb( 0 );
			p_work->dial_flag = ZKN_SOUNDSUB_DIAL_REVERB;
		}
		

		// 0�Ȃ�ZKN_SOUNDSUB_DIAL_MOVE_NUM_MAX�ɂ���
		if( p_work->dial_rota == 0 ){
			p_work->dial_rota = ZKN_SOUNDSUB_DIAL_MOVE_NUM_MAX;
		}

		// ���̂Ƃ�dial_div��ZKN_SOUNDSUB_DIAL_REVERB_MIN�`ZKN_SOUNDSUB_DIAL_REVERB_MAX�̒l�ɂȂ��Ă���̂ŕϊ�
		set_num = ZKN_SOUNDSUB_DIAL_REVERB_MAX - p_work->dial_div;
		
		// �ݒ�l�v�Z
		set_num = set_num * ZKN_SOUNDSUB_DIAL_REVERB_NUM;
		if( set_num > 0 ){	//0�`63������
			set_num --;
		}

		// ���o�[�u�ݒ�
		Snd_CaptureReverbVol( set_num, 0 );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�p�x�ɂ��OAM�̉�]
 *
 *	@param	p_draw
 *	@param	cp_work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZKnSoundSubDialDrawMove( ZKN_SOUND_SUB_DRAW* p_draw, const ZKN_SOUND_SUB_WORK* cp_work )
{
	OS_Printf( "%d\n", cp_work->dial_rota );
	CLACT_SetRotation( p_draw->dial, CalcTool_CircleVectroDistRotaGet(ZKN_SOUNDSUB_DIAL_DRAW_R , cp_work->dial_rota ) );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�`�b�N�ɂ���ăf�B�X�N������
 *
 *	@param	p_draw	
 *	@param	cp_work 
 *	@param	p_drawglb
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubDiskDrawMove( ZKN_SOUND_SUB_DRAW* p_draw, ZKN_SOUND_SUB_DRAWGLB* p_drawglb, const ZKN_SOUND_SUB_WORK* cp_work )
{
	int now_tick = Snd_ZukanPlayerGetSampleTick( SND_HANDLE_PMVOICE, cp_work->cp_snd_data, cp_work->pitch_num );

	// ����now_tick��0�������烋�[�v�����̂�last��0�ɂ���
	if( now_tick == 0 ){
		p_draw->disk_last_tick = 0;
	}

	// �`�b�N�̕ω��ʕ���]
	p_draw->disk_rota += (now_tick - p_draw->disk_last_tick) * ZKN_SOUNDSUB_DISK_BG_ROTA_MUL;
	p_draw->disk_rota &= 0xffff;

	// ��]�p�x�̐ݒ�
	GF_BGL_RadianSetReq( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_AFFINE_S, GF_BGL_RADION_SET, p_draw->disk_rota / 182 );
	GF_BGL_RotateCenterSetReq( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_AFFINE_S, GF_BGL_CENTER_X_SET, ZKN_SOUNDSUB_DISK_BG_BGCX );
	GF_BGL_RotateCenterSetReq( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_AFFINE_S, GF_BGL_CENTER_Y_SET, ZKN_SOUNDSUB_DISK_BG_BGCY );

	p_draw->disk_last_tick = now_tick;
}


//----------------------------------------------------------------------------
/**
 *	@brief	�s�b�`�ݒ�
 *
 *	@param	x	�����W
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubDiskPitchSet( ZKN_SOUND_SUB_WORK* p_work, int x )
{
	int dis_x;
	fx32 calc;
	int set_num;
	
	// X���W����s�b�`��ݒ�
	dis_x = x - ZKN_SOUNDSUB_DISK_BG_CENTER_X;

	calc = FX_Mul( ZKN_SOUNDSUB_DISK_PITCK_MAX << FX32_SHIFT, dis_x << FX32_SHIFT );
	calc = FX_Div( calc, ZKN_SOUNDSUB_DISK_BG_R << FX32_SHIFT );
	
	set_num = calc >> FX32_SHIFT;

	// �����ݒ�
	p_work->pitch_num = set_num;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�R�[���X�{�����[���ݒ�
 *
 *	@param	p_work	���[�N
 *	@param	x		X���W
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubDiskChorusSet( ZKN_SOUND_SUB_WORK* p_work, int x )
{
	int dis_x;
	fx32 calc;
	int set_num;
	
	// X���W����s�b�`��ݒ�
	dis_x = x - (ZKN_SOUNDSUB_DISK_BG_CENTER_X - ZKN_SOUNDSUB_DISK_BG_R);	// ������̋����ɂ���

	calc = FX_Mul( ZKN_SOUNDSUB_DISK_CHORUS_MAX << FX32_SHIFT, dis_x << FX32_SHIFT );
	calc = FX_Div( calc, (ZKN_SOUNDSUB_DISK_BG_R*2) << FX32_SHIFT );
	
	set_num = calc >> FX32_SHIFT;

	// �����ݒ�
	p_work->chorus_num = set_num;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�p���ݒ�
 *
 *	@param	x	�����W
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubDiskPanSet( ZKN_SOUND_SUB_WORK* p_work, int x )
{
	int dis_x;
	fx32 calc;
	int set_num;
	
	// X���W����p����ݒ�
	dis_x = x - ZKN_SOUNDSUB_DISK_BG_CENTER_X;

	calc = FX_Mul( ZKN_SOUNDSUB_DISK_PAN_MAX << FX32_SHIFT, dis_x << FX32_SHIFT );
	calc = FX_Div( calc, ZKN_SOUNDSUB_DISK_BG_R << FX32_SHIFT );
	
	set_num = calc >> FX32_SHIFT;

	// �����ݒ�
	p_work->pan_num = set_num;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�s�b�`�p���\���ݒ�
 *
 *	@param	p_draw 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubPitchPanFontDraw( ZKN_SOUND_SUB_DRAW* p_draw )
{
	if( p_draw->now_switch == ZKN_SOUNDSUB_SEQ_SWITCH_PICH ){
		FONTOAM_SetDrawFlag( p_draw->p_fontoam[ ZKN_SOUNDSUB_SEQ_SWITCH_PICH ]->p_fontoam, TRUE );
		FONTOAM_SetDrawFlag( p_draw->p_fontoam[ ZKN_SOUNDSUB_SEQ_SWITCH_PAN ]->p_fontoam, FALSE );
	}else{
		FONTOAM_SetDrawFlag( p_draw->p_fontoam[ ZKN_SOUNDSUB_SEQ_SWITCH_PICH ]->p_fontoam, FALSE );
		FONTOAM_SetDrawFlag( p_draw->p_fontoam[ ZKN_SOUNDSUB_SEQ_SWITCH_PAN ]->p_fontoam, TRUE );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	�{�^���A�j��
 *
 *	@param	act			�A�N�^�[
 *	@param	p_anmdata	�A�j���f�[�^
 *	@param	next_flg	���̃t���O
 *	@param	button_event�@�{�^���C�x���g
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubButtonAnimeMain( CLACT_WORK_PTR act, ZKN_SOUND_SUB_ANM_BUTTON* p_anmdata, BOOL next_flg, int button_event )
{
	int anm_frm;

	// �X���C�h�A�E�g���邱�Ƃ͂Ȃ�
	if( button_event == BMN_EVENT_SLIDEOUT ){
		button_event = BMN_EVENT_RELEASE;
	}

	anm_frm = CLACT_AnmFrameGet( act );
	
	// �X�C�b�`���ς������A�j�����I�[�g�ōs��
	if( p_anmdata->flag != next_flg ){
		
		// �A�j���V�[�P���X�ύX
		ZknSoundSubButtonAnimeSeqSet( act, p_anmdata,  next_flg );

		p_anmdata->flag = next_flg;
	}


	// �����{�^���C�x���g������Ƃ��̓{�^���ڰт��R���g���[������
	switch( button_event ){
	case BMN_EVENT_TOUCH:		///< �G�ꂽ�u��
		break;
		
	case BMN_EVENT_HOLD:		///< �G��Â��Ă���
		// push_anm_limit�܂ŃA�j����i�߂�
		if( anm_frm > p_anmdata->push_anm_limit ){
			CLACT_AnmFrameSet( act, p_anmdata->push_anm_limit );
			CLACT_SetAnmFrame( act, 0 );
		}
		break;

	case BMN_EVENT_RELEASE:
	case ZKN_SOUNDDUB_BUTTON_START_NOTOUCH:
		// �A�j���V�[�P���X�ύX
		ZknSoundSubButtonAnimeSeqSet( act, p_anmdata,  next_flg );
		CLACT_SetAnmFrame( act, ZKN_SOUNDSUB_ANIME_FRAME );
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�{�^���A�j��		���[�v����Ȃ��Ƃ��悤
 *
 *	@param	act			�A�N�^�[
 *	@param	p_anmdata	�A�j���f�[�^
 *	@param	next_flg	���̃t���O
 *	@param	button_event�@�{�^���C�x���g
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubButtonAnimeMain_NO_Loop( CLACT_WORK_PTR act, ZKN_SOUND_SUB_ANM_BUTTON* p_anmdata, BOOL next_flg, int button_event )
{
	int anm_frm;

	// �X���C�h�A�E�g�I�����邱�Ƃ͂Ȃ�
	if( button_event == BMN_EVENT_RELEASE ){
		button_event = BMN_EVENT_SLIDEOUT;
	}

	anm_frm = CLACT_AnmFrameGet( act );
	
	// �X�C�b�`���ς������A�j�����I�[�g�ōs��
	if( p_anmdata->flag != next_flg ){
		
		// �A�j���V�[�P���X�ύX
		ZknSoundSubButtonAnimeSeqSet( act, p_anmdata,  next_flg );

		p_anmdata->flag = next_flg;
	}


	// �����{�^���C�x���g������Ƃ��̓{�^���ڰт��R���g���[������
	switch( button_event ){
	case BMN_EVENT_TOUCH:		///< �G�ꂽ�u��
		// �A�j���V�[�P���X�ݒ�
		if( next_flg == TRUE ){
			ZknSoundSubButtonAnimeSeqSet( act, p_anmdata,  FALSE );
		}else{
			ZknSoundSubButtonAnimeSeqSet( act, p_anmdata,  TRUE );
		}
		CLACT_AnmFrameSet( act, p_anmdata->push_anm_limit - 1 );
		break;
		
	case BMN_EVENT_HOLD:		///< �G��Â��Ă���
		CLACT_AnmFrameSet( act, p_anmdata->push_anm_limit );
		CLACT_SetAnmFrame( act, 0 );
		break;

	case BMN_EVENT_SLIDEOUT:		///< ��ʃ^�b�`�����܂܃{�^���̈悩��O�ꂽ�u��
	case ZKN_SOUNDDUB_BUTTON_START_NOTOUCH:
		// �A�j���V�[�P���X�ݒ�
		ZknSoundSubButtonAnimeSeqSet( act, p_anmdata,  next_flg );
		CLACT_SetAnmFrame( act, ZKN_SOUNDSUB_ANIME_FRAME );
		break;//*/

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�j���V�[�P���X�ύX����
 *
 *	@param	act			�A�N�^�[
 *	@param	p_anmdata	�A�j���f�[�^
 *	@param	flg			�t���O
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubButtonAnimeSeqSet( CLACT_WORK_PTR act, ZKN_SOUND_SUB_ANM_BUTTON* p_anmdata, BOOL flg )
{
	int anm_frm;

	anm_frm = CLACT_AnmFrameGet( act );

	// �A�j���V�[�P���X�ύX
	if( flg == TRUE ){
		// ��~��
		if( p_anmdata->now_anm_seq == p_anmdata->anm_seq1 ){
			CLACT_AnmChg( act, p_anmdata->anm_seq2 );
			p_anmdata->now_anm_seq = p_anmdata->anm_seq2;
			CLACT_AnmFrameSet( act, p_anmdata->anm_num_max - anm_frm );
		}
	}else{

		// �Đ���
		if( p_anmdata->now_anm_seq == p_anmdata->anm_seq2 ){
			CLACT_AnmChg( act, p_anmdata->anm_seq1 );
			p_anmdata->now_anm_seq = p_anmdata->anm_seq1;
			CLACT_AnmFrameSet( act, p_anmdata->anm_num_max - anm_frm );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�����Đ�
 *
 *	@param	p_work
 *	@param	monno
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubSoundStart( ZKN_SOUND_SUB_WORK* p_work, ZKN_SOUND_SUB_GLB* p_glb, int monsno )
{
	p_work->sound_play = TRUE;

	Snd_PMVoicePlayEx( PV_ZUKAN_CHORUS, monsno, 0, 
					   PV_VOL_MAX, PV_PTN_PARAM_NONE );	//�؃��b�v

	// ���o�[�u�t�B���^�[�ݒ�ɂ��l�ݒ�
//	ZknSoundSubDialNumSet( p_work );

	// �s�b�`�p���̒l��ݒ�
	ZknSoundSubPitchPanChorusSet( p_work );
}

//----------------------------------------------------------------------------
/**
 *	@brief	��~���ɍs������
 *
 *	@param	p_work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubSoundStop( ZKN_SOUND_SUB_WORK* p_work )
{
	Snd_PMVoiceStop(0);

	p_work->sound_play = FALSE;

	// ���o�[�u�t�B���^�[���~�߂�
//	ZknSoundSubReverbEffectStop( p_work );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���o�[�u�t�B���^�[���~�߂�
 *
 *	@param	p_work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubReverbEffectStop( ZKN_SOUND_SUB_WORK* p_work )
{
	// �t�B���^�[���o�[�u�̐ݒ���~�߂�
	if( p_work->dial_flag == ZKN_SOUNDSUB_DIAL_REVERB ){
		Snd_CaptureStopReverb(0);
	}
	// �t�B���^�[�ݒ肳��Ă��鎞�͎~�߂�
	if( p_work->dial_flag == ZKN_SOUNDSUB_DIAL_FILTER ){
		Snd_CaptureStopEffect();
	}

	p_work->dial_flag = ZKN_SOUNDSUB_DIAL_NONE;
}


//----------------------------------------------------------------------------
/**
 *	@brief	���[�v�Đ�
 ;*
 *	@param	p_work
 *	@param	p_glb 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubSoundLoop(  ZKN_SOUND_SUB_WORK* p_work, ZKN_SOUND_SUB_GLB* p_glb )
{
	int monsno = ZKN_GLBDATA_PokeMonsNoGet( p_glb->p_glb );

	// �Ƃ܂�����Đ�
	if( Snd_PMVoicePlayCheck() == FALSE ){

		p_work->loop_wait--;
		if( p_work->loop_wait == 0 ){
			ZknSoundSubSoundStart( p_work, p_glb, monsno );
			p_work->loop_wait = ZKN_SOUNDSUB_DIAL_LOOP_WAIT;
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	���[�v�Đ��ݒ������
 *
 *	@param	p_work	���[�Nk
 *	@param	flag	TRUE�@���[�v�@FALSE�@���ʂɖ߂�
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubSoundLoopSet( ZKN_SOUND_SUB_WORK* p_work, BOOL flag )
{
	p_work->loop = flag;
	p_work->loop_wait = ZKN_SOUNDSUB_DIAL_LOOP_WAIT;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�p���b�g�ǂݍ���
 *
 *	@param	p_draw	�`�惏�[�N
 *	@param	heap	�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubPlttLoad( ZKN_SOUND_SUB_DRAW* p_draw, ZKN_SOUND_SUB_DRAWGLB* p_drawglb, int heap )
{
	p_draw->p_pltt_buff = ZKN_GLBDATA_PalDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_voice_NCLR, &p_draw->p_plt, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�p���b�g�j��
 *
 *	@param	p_draw	�`�惏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubPlttRelease( ZKN_SOUND_SUB_DRAW* p_draw )
{
	sys_FreeMemoryEz( p_draw->p_pltt_buff );
	p_draw->p_pltt_buff = NULL;
	p_draw->p_plt = NULL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ON�p���b�g��ݒ�
 *
 *	@param	p_draw	�`�惏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubPlttOn( ZKN_SOUND_SUB_DRAW* p_draw )
{
	AddVramTransferManager(
			NNS_GFD_DST_2D_BG_PLTT_SUB,
			ZKN_SOUNDSUB_DISK_PITCH_PAN_PL * 32,
			p_draw->p_plt->pRawData,
			32 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	OFF�p���b�g��ݒ�
 *
 *	@param	p_draw	�`�惏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubPlttOff( ZKN_SOUND_SUB_DRAW* p_draw )
{
	AddVramTransferManager(
			NNS_GFD_DST_2D_BG_PLTT_SUB,
			ZKN_SOUNDSUB_DISK_PITCH_PAN_PL * 32,
			&((u8*)(p_draw->p_plt->pRawData))[32],
			32 );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�s�b�`�p���̃I���I�t
 *
 *	@param	p_work	���[�N
 *	@param	flag	�t���O�@TRUE�@ON�@�@FALSE�@OFF
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubPitchPanChorusOnOff( ZKN_SOUND_SUB_WORK* p_work, BOOL flag )
{
	ZknSoundSubPitchPanChorusFlagOnOff( p_work, flag );

	if( flag == FALSE ){
		ZknSoundSubPitchPanChorusNumReset( p_work );
	}
}
//�@�t���O�̏グ����
static void ZknSoundSubPitchPanChorusFlagOnOff( ZKN_SOUND_SUB_WORK* p_work, BOOL flag )
{
	// ON�@OFF�ݒ�
	p_work->pitch_pan_push = flag;
}
// �l�̏�����
static void ZknSoundSubPitchPanChorusNumReset( ZKN_SOUND_SUB_WORK* p_work )
{
	p_work->pitch_num = 0;
	p_work->pan_num = 0;
	p_work->chorus_num = 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�s�b�`�p���R�[���X�ݒ�
 *
 *	@param	p_work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubPitchPanChorusSet( ZKN_SOUND_SUB_WORK* p_work )
{
	// �Đ����Ȃ�ݒ�
	if( p_work->sound_play ){
		ZknSoundSubPitchSet( p_work->pitch_num );
		Snd_PlayerSetTrackPan( SND_HANDLE_PMVOICE, 0xffff, p_work->pan_num );

		ZknSoundSubChorusSet( p_work->chorus_num );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�R�[���X�ݒ�
 *
 *	@param	p_work	���[�N
 *	@param	volume	�{�����[��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubChorusSet( int volume )
{
	Snd_PlayerMoveVolume( SND_HANDLE_CHORUS, volume, 0 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�s�b�`�p���A�j��
 *
 *	@param	p_draw
 *	@param	cp_work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubPitchPanAnm( ZKN_SOUND_SUB_DRAW* p_draw, const ZKN_SOUND_SUB_WORK* cp_work )
{
	// �p���b�g�A�j��������
	if( cp_work->pitch_pan_push != p_draw->pltt_anm ){
		
		if( cp_work->pitch_pan_push == TRUE ){
			ZknSoundSubPlttOn( p_draw );	
		}else{
			ZknSoundSubPlttOff( p_draw );	
		}
		p_draw->pltt_anm = cp_work->pitch_pan_push;
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	�J�[�\������
 *
 *	@param	p_work		���[�N
 *	@param	p_glb		�O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubCursorMove( ZKN_SOUND_SUB_WORK* p_work, ZKN_SOUND_SUB_GLB* p_glb )
{
	int monsno = ZKN_GLBDATA_PokeMonsNoGet( p_glb->p_glb );

	// ���삷��
	if( sys.trg & PAD_BUTTON_A ){

		p_work->sound_play_button_cursor = 1;

		// �{�^���C�x���g�ݒ�
		p_work->sub_button_event[ ZKN_SOUNDSUB_BUTTON_SUB_STARTSTOP ] = BMN_EVENT_TOUCH;

		// �����Đ�
		if( p_work->loop == FALSE ){
			// �Ȃ��Ă�����Ƃ߂�
			if( p_work->sound_play == TRUE ){
				Snd_PMVoiceStop(0);
			}	
			
			ZknSoundSubSoundStart( p_work, p_glb, monsno );
		}else{
			// �Đ���~�ݒ�
			if( p_work->sound_play == FALSE ){
				ZknSoundSubSoundStart( p_work, p_glb, monsno );
			}else{
				// ��~
				ZknSoundSubSoundStop( p_work );
			}
		}
	}else if( p_work->sound_play_button_cursor == 1 ){

		// Hold
		p_work->sound_play_button_cursor = 2;
		p_work->sub_button_event[ ZKN_SOUNDSUB_BUTTON_SUB_STARTSTOP ] = BMN_EVENT_HOLD;

	}else if( p_work->sound_play_button_cursor == 2 ){

		p_work->sound_play_button_cursor = 0;
		p_work->sub_button_event[ ZKN_SOUNDSUB_BUTTON_SUB_STARTSTOP ] = BMN_EVENT_RELEASE;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�J�[�\���`�揈��
 *
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_glb		�O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubCursorDrawMove( ZKN_SOUND_SUB_DRAWGLB* p_drawglb, const ZKN_SOUND_SUB_GLB* cp_glb )
{
	ZKN_GLB_DRAWDATA* p_draw = p_drawglb->p_drawglb;
	
	if( ZKN_ZukanCommonSubCursorFlagGet( cp_glb->cp_zukan_common_apl ) == TRUE ){
	
		ZKN_UTIL_CursorSetMatrix( p_draw, ZKN_SOUNDSUB_BUTTON_STARTSTOP_X, ZKN_SOUNDSUB_BUTTON_STARTSTOP_Y, ZKN_SOUNDSUB_CURSOR_START_SIZX, ZKN_SOUNDSUB_CURSOR_START_SIZY );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�s�b�`�ݒ�
 *
 *	@param	num 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubPitchSet( int num )
{
	Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, num);
	Snd_PlayerSetTrackPitch( SND_HANDLE_CHORUS, 0xffff, SND_ZUKAN_PITCH_CHORUS + num );
}
