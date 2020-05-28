//==============================================================================================
/**
 * @file	snd_test.c
 * @brief	�T�E���h�e�X�g(�T�E���h�`�F�b�N)
 * @author	nohara
 * @date	2005.07.04
 *
 * ���T�E���h�e�X�g�̗�O�����ɂ��ā�
 *
 * �P�j
 * �T�E���h�q�[�v���g�p���āA�f�[�^�̃��[�h���s���悤�ɂ���ƁA
 * �Ȃ̍Đ��A��~���ƂɁA�m�ہA�J�����s��Ȃ��Ƃ����Ȃ��Ȃ�܂��B
 *
 * ���ꂾ�ƁABGM��SE�𓯎��ɍĐ����邱�Ƃ�����̂ŁA
 *
 * �q�[�v��S�ăN���A���āA
 * PLAYER_BGM��BGM�̃V�[�P���X�A�o���N�A�g�`�A�[�J�C�u���̃v���C���[�q�[�v���m�ہA
 *
 * BGM��PLAYER_BGM�̃v���C���[�q�[�v�ōĐ�����悤�ɂ��܂��B
 * ME��PLAYER_BGM�̃v���C���[�q�[�v�ōĐ�����悤�ɂ��܂��B
 *
 * �Q�j
 * SE�́A�Đ����邽�тɁA�V�[�P���X�A�o���N�A�g�`�A�[�J�C�u��
 * �T�E���h�q�[�v�Ń��[�h���Ȃ����悤�ɂ��܂��B
 *
 * �R�j
 * ��L�̗�O���������Ă���̂ŁA
 * �T�E���h�ݒ肪�A�Q�[�����Ƃ́A�S���قȂ�܂��B
 * ���̂��߁A�ʏ�̃T�E���h��������ʂ��������A
 * ���S�Ȃ̂ŁA�I�������ŁA�\�t�g���Z�b�g�������Ă��܂��B
 */
//==============================================================================================
#include "common.h"
#include "system/main.h"
#include "system/fontproc.h"
#include "system/bmp_list.h"
#include "system/lib_pack.h"
#include "system/palanm.h"
#include "system/pm_str.h"
#include "system/snd_tool.h"
#include "system/bmp_menu.h"
#include "system/msgdata.h"						//MSGDATA_MANAGER
#include "system/bmp_menu.h"
#include "system/arc_util.h"
#include "snd_test.h"

#include "../system/snd_system.h"

#include "msgdata/msg.naix"						//NARC_msg_??_dat
#include "msgdata/msg_snd_test_str.h"
#include "msgdata/msg_snd_test_name.h"


//==============================================================================================
//
//	��`
//
//==============================================================================================
enum{
	BUF_BGM = 0,
	BUF_SE,
	BUF_PV,

	BUF_MAX,								//�o�b�t�@�̍ő吔
};

#define SND_TEST_BUF_SIZE		(48)		//�o�b�t�@�̃T�C�Y


//==============================================================================================
//
//	�\����
//
//==============================================================================================
//�T�E���h�e�X�g�\����
typedef	struct {
	BOOL end_flag;
	u8	seq;							//�����i���o�[
	s8  select;							//�I��Ώ�
	u16 dmy2;

	int	old_bgm;						//�Â�BGM�i���o�[
	int	bgm;							//BGM�i���o�[
	int	se;								//SE�i���o�[
	int	pv;								//�|�P���������i���o�[

	int bgm_lv;							//�K�w
	int se_lv[SE_HANDLE_MAX];			//�K�w
	int pv_lv;							//�K�w

	u8  bgm_play_flag;					//��x�ł��Đ��������t���O
	u8  se_play_flag[SE_HANDLE_MAX];	//��x�ł��Đ��������t���O
	u8  pv_play_flag;					//��x�ł��Đ��������t���O
	u8  dmy3;
	
	int pitch;							//����
	int tempo;							//�e���|
	int var;							//�V�[�P���X���[�J�����[�N�ɃZ�b�g����l

	u16* pMsg;

	GF_BGL_INI * bgl;

	GF_BGL_BMPWIN bmpwin;				//BMP�E�B���h�E�f�[�^

	STRBUF* msg_buf[BUF_MAX];

	MSGDATA_MANAGER* msgman;			//���b�Z�[�W�}�l�[�W���[

}SND_TEST_WORK;


//==============================================================================================
//
//	�v���g�^�C�v�錾
//
//==============================================================================================
static void SndTestCall(SND_TEST_WORK * wk);

static void SndTestWorkInit( SND_TEST_WORK* wk );
static void SndTestSeqNext( SND_TEST_WORK* wk );

static void SndTestSeqInit( SND_TEST_WORK* wk );
static void SndTestSeqBgmFadeWait( SND_TEST_WORK* wk );
static void SndTestSeqKeyCheck( SND_TEST_WORK* wk );
static void SndTestSeqExit( SND_TEST_WORK* wk );

static void SndTestStop( SND_TEST_WORK* wk );
static void SndTestPlay( SND_TEST_WORK* wk );

//static void (* const SndTestTable[])() = {
static void (* const SndTestTable[])(SND_TEST_WORK*) = {
	SndTestSeqInit,						//������
	SndTestSeqBgmFadeWait,				//BGM�t�F�[�h�A�E�g�҂�
	SndTestSeqKeyCheck,					//�L�[�`�F�b�N
	SndTestSeqExit,						//�I��
};

static void SndTestNumMsgSet( GF_BGL_BMPWIN* win, int num, u8 x, u8 y );
static void SndTestNameMsgSet( GF_BGL_BMPWIN* win, const STRBUF* msg, u8 x, u8 y );
static void MsgRewrite( SND_TEST_WORK* wk, s8 select );
static void SndTestInit( SND_TEST_WORK* wk );
static void SndTestCursor( SND_TEST_WORK* wk );
static void SndTestSysMsgSet( SND_TEST_WORK* wk );
static void SndTestStrPrint( GF_BGL_BMPWIN* win, u32 fontID, u32 strID, u32 x, u32 y, u32 wait, pStrPrintCallBack callback );
static void SndTestTrackMute( SND_TEST_WORK* wk );

//BG�ݒ�
static void SetBank();
static void BgSet( SND_TEST_WORK* wk );


//==================================================================================================
//
//	�f�[�^
//
//==================================================================================================
static const BMPWIN_DAT	SndTestWinData = {
	SND_TEST_BMPWIN_FRAME,					//�E�C���h�E�g�p�t���[��
	SND_TEST_BMPWIN_PX1,SND_TEST_BMPWIN_PY1,//�E�C���h�E�̈�̍����X,Y���W�i�L�����P�ʂŎw��j
	SND_TEST_BMPWIN_SX,	SND_TEST_BMPWIN_SY,	//�E�C���h�E�̈��X,Y�T�C�Y�i�L�����P�ʂŎw��j
	SND_TEST_BMPWIN_PL,						//�E�C���h�E�̈�̃p���b�g�i���o�[	
	SND_TEST_BMPWIN_CH						//�E�C���h�E�L�����̈�̊J�n�L�����N�^�i���o�[
};


//==================================================================================================
//
//	�֐�
//
//==================================================================================================

//--------------------------------------------------------------
/**
 * @brief	�T�E���h�e�X�g�Ăяo��
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void SndTestCall(SND_TEST_WORK * wk)
{

	if( wk == NULL ){
		OS_Printf("snd_test.c Alloc ERROR!");
		return;
	}

	wk->bgl = GF_BGL_BglIniAlloc( HEAPID_BASE_DEBUG );

	//BG�ݒ�
	GF_Disp_GX_VisibleControlInit();	//���C����ʂ̊e�ʂ̕\���R���g���[��������
	SetBank();							//VRAM�o���N�ݒ�
	BgSet(wk);							//BG�ݒ�
	GF_Disp_DispOn();					//�\���L���ݒ�
	MSG_PrintInit();					//�����\���������֐�

	OS_Printf( "\n\n//==========================================\n" );
	OS_Printf( "//\t�T�E���h�e�X�g�@�X�^�[�g\n" );
	OS_Printf( "//==========================================\n" );

	wk->end_flag = FALSE;
	wk->seq			= 0;									//�����i���o�[
	SndTestWorkInit(wk);									//���[�N������

	//���b�Z�[�W�f�[�^�}�l�[�W���[�쐬
	wk->msgman = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, 
									NARC_msg_snd_test_name_dat, HEAPID_BASE_DEBUG );

	//app������(fld_debug.c)
	//FieldBitMapWinCgxSet();
	
	//SystemFontPaletteLoad( PALTYPE_MAIN_BG, 0, HEAPID_BASE_DEBUG );

	GF_BGL_BmpWinAddEx( wk->bgl, &wk->bmpwin, &SndTestWinData );		//�r�b�g�}�b�v�ǉ�
	GF_BGL_BmpWinDataFill( &wk->bmpwin, FBMP_COL_WHITE );				//�h��Ԃ�

	SndTestSysMsgSet( wk );									//�K�v�ȏ�񃁃b�Z�[�W
	SndTestCursor( wk );									//�J�[�\���X�V

	//�Ȗ����b�Z�[�W�\��
	MsgRewrite( wk, SND_TEST_TYPE_BGM );					//BGM�i���o�[
	MsgRewrite( wk, SND_TEST_TYPE_SE );						//SE�i���o�[
	MsgRewrite( wk, SND_TEST_TYPE_PV );						//PV�i���o�[

	SndTestNumMsgSet( &wk->bmpwin, wk->pitch, ST_TYPE_X+88, ST_BGM_MSG_Y );//����
	SndTestNumMsgSet( &wk->bmpwin, wk->tempo, ST_TYPE_X+168, ST_BGM_MSG_Y );//�e���|

	GF_BGL_BmpWinOn( &wk->bmpwin );


	return;
}

//--------------------------------------------------------------
/**
 * @brief	���[�N������
 *
 * @param	wk		SND_TEST_WORK�ւ̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void SndTestWorkInit( SND_TEST_WORK* wk )
{
	int i;

	wk->select		= SND_TEST_TYPE_BGM;		//�I��Ώ�

	wk->bgm			= SND_TEST_BGM_START_NO;	//BGM�X�^�[�g�i���o�[
	wk->se			= SND_TEST_SE_START_NO;		//SE�X�^�[�g�i���o�[
	wk->pv			= SND_TEST_PV_START_NO;		//�|�P���������X�^�[�g�i���o�[

	//�����K�w
	wk->bgm_lv		= 1;			
	wk->pv_lv		= 1;		

	for( i=0; i < SE_HANDLE_MAX ;i++ ){
		wk->se_lv[i] = 1;		
	}

	//��x�ł��Đ��������t���O
	wk->bgm_play_flag	= 0;					
	wk->pv_play_flag	= 0;

	for( i=0; i < SE_HANDLE_MAX ;i++ ){
		wk->se_play_flag[i]	= 0;
	}

	wk->pMsg = NULL;

	wk->pitch		= 0;	//����
	wk->tempo		= 256;	//�e���|

	// �o�b�t�@�쐬
	for(i=0; i<BUF_MAX; i++)
	{
		wk->msg_buf[i] = STRBUF_Create(SND_TEST_BUF_SIZE*2, HEAPID_BASE_DEBUG);
	}

	return;
}

//--------------------------------------------------------------
/**
 * @brief	���̏�����
 *
 * @param	wk		SND_TEST_WORK�ւ̃|�C���^
 *
 * @retval	none
 *
 * �K�v�ȏ�����ǉ����Ă���(�T�u�V�[�P���X�̃N���A�Ȃ�)
 */
//--------------------------------------------------------------
static void SndTestSeqNext( SND_TEST_WORK* wk)
{
	wk->seq++;
	return;
}

//--------------------------------------------------------------
/**
 * @brief	������
 *
 * @param	wk		SND_TEST_WORK�ւ̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void SndTestSeqInit( SND_TEST_WORK* wk )
{
	//Snd_BgmFadeOut( 60 );				//BGM�t�F�[�h�A�E�g
	Snd_Stop();							//�S��~
	Snd_BgmChannelSetAndReverbSet( 0 );	//�g�p�\�`�����l������A���o�[�u�ݒ�(�N���A)
	SndTestSeqNext(wk);
	return;
}

//--------------------------------------------------------------
/**
 * @brief	BGM�t�F�[�h�A�E�g�҂�
 *
 * @param	wk		SND_TEST_WORK�ւ̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void SndTestSeqBgmFadeWait( SND_TEST_WORK* wk )
{
	int ret;

	if( Snd_FadeCheck() ){						//BGM�t�F�[�h�A�E�g�҂�
		return;
	}

	Snd_HeapStateClear();						//�������[�h���Ă��Ȃ���Ԃɂ���(�풓�����������)
	
	//�x�[�V�b�N�o���N�A�g�`���[�h
	Snd_DebugLoadBank( BANK_BASIC );
	
	//�v���C���[�q�[�v�쐬
	ret = Snd_PlayerHeapCreate( PLAYER_BGM, 70000 );
	//Snd_UseHeapSizeOsPrint();					//�ǉ������T�E���h�q�[�v�̗e�ʂ��o�͂���
	//OS_Printf( "player_bgm heap create = %d\n", ret );

	Snd_HeapSaveState( Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_SE) );	//�K�w�ۑ�

	SndTestSeqNext(wk);
	return;
}

//--------------------------------------------------------------
/**
 * @brief	�L�[�`�F�b�N
 *
 * @param	wk		SND_TEST_WORK�ւ̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void SndTestSeqKeyCheck( SND_TEST_WORK* wk )
{
	int ret, i, spd;

	//�����ύX
	if( sys.cont & PAD_BUTTON_SELECT ){
		if( sys.repeat & PAD_KEY_UP ){
			wk->pitch++;
		}else if( sys.repeat & PAD_KEY_DOWN ){
			wk->pitch--;
		}
		SndTestNumMsgSet( &wk->bmpwin, wk->pitch, ST_TYPE_X+88, ST_BGM_MSG_Y );
		Snd_PlayerSetTrackPitch( SND_HANDLE_BGM, 0xffff, (wk->pitch*64) );
		GF_BGL_BmpWinOn( &wk->bmpwin );
		return;
	}

	//�V�[�P���X���[�J�����[�N��ύX
	if( (sys.cont & PAD_BUTTON_R) && (sys.repeat & PAD_KEY_UP) ){

		wk->var++;
		if( wk->var >= 128 ){
			wk->var = 0;
		}
		return;
	}

	if( (sys.cont & PAD_BUTTON_R) && (sys.repeat & PAD_KEY_DOWN) ){

		wk->var--;
		if( wk->var < 0 ){
			wk->var = 127;
		}
		return;
	}

	//�e���|�ύX
	if( sys.cont & PAD_BUTTON_START ){
		if( sys.repeat & PAD_KEY_UP ){
			wk->tempo+=32;
		}else if( sys.repeat & PAD_KEY_DOWN ){
			wk->tempo-=32;
		}
		SndTestNumMsgSet( &wk->bmpwin, wk->tempo, ST_TYPE_X+168, ST_BGM_MSG_Y );
		Snd_PlayerSetTempoRatio( SND_HANDLE_BGM, wk->tempo );
		GF_BGL_BmpWinOn( &wk->bmpwin );
		return;
	}

	//�Ώۂ�ύX(��BGM��PV��SE��)
	if( sys.trg & PAD_KEY_DOWN ){
		wk->select++;
		if( wk->select >= SND_TEST_TYPE_MAX ){
			wk->select = SND_TEST_TYPE_BGM;
		}

		SndTestCursor( wk );					//�J�[�\���X�V
		GF_BGL_BmpWinOn( &wk->bmpwin );
	}

	//�Ώۂ�ύX(��BGM��SE��PV��)
	if( sys.trg & PAD_KEY_UP ){
		wk->select--;
		if( wk->select < SND_TEST_TYPE_BGM ){
			wk->select = (SND_TEST_TYPE_MAX-1);
		}

		SndTestCursor( wk );					//�J�[�\���X�V
		GF_BGL_BmpWinOn( &wk->bmpwin );
	}

	//�V�[�P���X�i���o�[��i�߂�
	if( sys.repeat & PAD_KEY_RIGHT ){

		if( (sys.cont & PAD_BUTTON_R) || (sys.cont & PAD_BUTTON_L) ){
			spd = 10;												//10����
		}else{
			spd = 1;												//1����
		}

		switch( wk->select ){
		case SND_TEST_TYPE_BGM:
			wk->old_bgm = wk->bgm;
			wk->bgm+=spd;
			if( wk->bgm >= SND_TEST_BGM_END_NO ){
				wk->bgm = SND_TEST_BGM_START_NO;
			}

			MsgRewrite( wk, SND_TEST_TYPE_BGM );					//BGM�i���o�[
			GF_BGL_BmpWinOn( &wk->bmpwin );
			break;
		case SND_TEST_TYPE_SE:
			wk->se+=spd;
			if( wk->se >= SND_TEST_SE_END_NO ){
				wk->se = SND_TEST_SE_START_NO;
			}

			MsgRewrite( wk, SND_TEST_TYPE_SE );						//SE�i���o�[
			GF_BGL_BmpWinOn( &wk->bmpwin );
			break;
		case SND_TEST_TYPE_PV:
			wk->pv+=spd;
			if( wk->pv >= SND_TEST_PV_END_NO ){
				wk->pv = SND_TEST_PV_START_NO;
			}

			MsgRewrite( wk, SND_TEST_TYPE_PV );						//PV�i���o�[
			GF_BGL_BmpWinOn( &wk->bmpwin );
			break;
		};
	}

	//�V�[�P���X�i���o�[��߂�
	if( sys.repeat & PAD_KEY_LEFT ){

		if( (sys.cont & PAD_BUTTON_R) || (sys.cont & PAD_BUTTON_L) ){
			spd = 10;												//10����
		}else{
			spd = 1;												//1����
		}

		switch( wk->select ){
		case SND_TEST_TYPE_BGM:
			wk->old_bgm = wk->bgm;
			wk->bgm-=spd;
			if( wk->bgm < SND_TEST_BGM_START_NO ){
				wk->bgm = (SND_TEST_BGM_END_NO);
			}

			MsgRewrite( wk, SND_TEST_TYPE_BGM );					//BGM�i���o�[
			GF_BGL_BmpWinOn( &wk->bmpwin );
			break;
		case SND_TEST_TYPE_SE:
			wk->se-=spd;
			if( wk->se < SND_TEST_SE_START_NO ){
				wk->se = (SND_TEST_SE_END_NO);
			}

			MsgRewrite( wk, SND_TEST_TYPE_SE );						//SE�i���o�[
			GF_BGL_BmpWinOn( &wk->bmpwin );
			break;
		case SND_TEST_TYPE_PV:
			wk->pv-=spd;
			if( wk->pv < SND_TEST_PV_START_NO ){
				wk->pv = (SND_TEST_PV_END_NO);
			}

			MsgRewrite( wk, SND_TEST_TYPE_PV );						//PV�i���o�[
			GF_BGL_BmpWinOn( &wk->bmpwin );
			break;
		};
	}

	//��~
	if( sys.trg & PAD_BUTTON_B ){
		SndTestStop(wk);
	}

	//�Đ�(��~�����Ă���Đ�)
	if( sys.trg & PAD_BUTTON_A ){
		SndTestStop(wk);
		SndTestPlay(wk);

#if 1
		//�V�[�P���X���[�J�����[�N����
		//�T�E���h�n���h�����֘A�t����ꂽ��ɑ��삷��I
		Snd_PlayerWriteVariable( wk->var );
		SndTestNumMsgSet( &wk->bmpwin, wk->var, ST_TYPE_X+168, ST_BGM_MSG_Y+16 );
		GF_BGL_BmpWinOn( &wk->bmpwin );
#endif

	}

	//������
	//if( sys.cont & PAD_BUTTON_SELECT ){
	if( sys.cont & PAD_BUTTON_Y ){
		Snd_Stop();						//�S�Ē�~
		SndTestInit( wk );				//���[�N�A�f�[�^�ȂǃN���A
		GF_BGL_BmpWinOn( &wk->bmpwin );
	}

	//�I��
	//if( sys.cont & PAD_BUTTON_START ){
	if( sys.cont & PAD_BUTTON_X ){
		Snd_Stop();						//�S�Ē�~
		SndTestSeqNext(wk);
		return;
	}

	return;
}

//--------------------------------------------------------------
/**
 * @brief	�I��
 *
 * @param	wk		SND_TEST_WORK�ւ̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void SndTestSeqExit( SND_TEST_WORK* wk )
{
	int i;

	//BMP�E�B���h�EOFF
	GF_BGL_BmpWinOff( &wk->bmpwin );
	
	//BMP���X�g�j��
	//BmpListExit( wp->bmplistContID,&DebugList,&DebugCursor );
	//BmpListExit( wk->blwin, NULL, NULL );

	//BMPWindow����
	GF_BGL_BmpWinDel( &wk->bmpwin );

	MSGMAN_Delete( wk->msgman );

	//BGL�J��
	GF_BGL_BGControlExit( wk->bgl, SND_TEST_BMPWIN_FRAME );

	//bgl�폜
	sys_FreeMemoryEz( wk->bgl );

	//�����o�b�t�@�폜
	for(i=0; i<BUF_MAX; i++)
	{
		if(wk->msg_buf[i]){
			STRBUF_Delete(wk->msg_buf[i]);
		}
	}

	wk->end_flag = TRUE;

	return;
}

//--------------------------------------------------------------
/**
 * @brief	�T�E���h��~����
 *
 * @param	wk		SND_TEST_WORK�ւ̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void SndTestStop( SND_TEST_WORK* wk )
{
	int i,type;

	switch( wk->select ){
	case SND_TEST_TYPE_BGM:
		//Snd_BgmStop(Snd_NowBgmNoGet(), 0);
		//Snd_BgmStop( wk->old_bgm, 0 );
		NNS_SndPlayerStopSeqBySeqNo( wk->old_bgm, 0 );
		break;
	case SND_TEST_TYPE_SE:
		//Snd_SeStopBySeqNo( wk->se, 0 );
		Snd_SeStop( SND_HANDLE_SE_1, 0 );
		break;
	case SND_TEST_TYPE_PV:
		Snd_PMVoiceStop(0);
		break;
	};

	return;
}

//--------------------------------------------------------------
/**
 * @brief	�T�E���h�Đ�����
 *
 * @param	wk		SND_TEST_WORK�ւ̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void SndTestPlay( SND_TEST_WORK* wk )
{
	int type,ret;

	switch( wk->select ){
	case SND_TEST_TYPE_BGM:
		Snd_ArcPlayerStartSeqEx( SND_HANDLE_BGM, PLAYER_BGM, wk->bgm );
		break;

	case SND_TEST_TYPE_SE:
		//�V�[�P���X�A�o���N�A�g�`�A�[�J�C�u���[�h(�q�[�v���x���͓K���ł�)
		Snd_HeapLoadState( Snd_GetHeapSaveLv(SND_HEAP_SAVE_SE) );		//�J��
		Snd_ArcLoadSeq( wk->se );										//���[�h
		//Snd_HeapSaveState( Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_SE) );	//�K�w�ۑ�
		ret = Snd_ArcPlayerStartSeqEx( SND_HANDLE_SE_1, PLAYER_SE_1, wk->se );
		//OS_Printf( "se_play = %d\n", ret );
		break;

	case SND_TEST_TYPE_PV:
		Snd_PMVoicePlay( wk->pv );
		break;
	};

	return;
}


//==============================================================================================
//
//	�ݒ�֐�
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	VRAM�o���N�ݒ�
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void SetBank(void)
{
	//display.c
	
	GF_BGL_DISPVRAM vramSetTable = {	//VRAM�ݒ�\����
		//GX_VRAM_BG_256_AB,			//���C��2D�G���W����BG
		GX_VRAM_BG_128_C,				//���C��2D�G���W����BG
		GX_VRAM_BGEXTPLTT_NONE,			//���C��2D�G���W����BG�g���p���b�g

		GX_VRAM_SUB_BG_32_H,			//�T�u2D�G���W����BG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		//�T�u2D�G���W����BG�g���p���b�g

		//GX_VRAM_OBJ_64_E,				//���C��2D�G���W����OBJ
		GX_VRAM_OBJ_16_F,				//���C��2D�G���W����OBJ
		GX_VRAM_OBJEXTPLTT_NONE,		//���C��2D�G���W����OBJ�g���p���b�g

		//GX_VRAM_SUB_OBJ_NONE,			//�T�u2D�G���W����OBJ
		GX_VRAM_SUB_OBJ_16_I,			//�T�u2D�G���W����OBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	//�T�u2D�G���W����OBJ�g���p���b�g

		GX_VRAM_TEX_01_AB,			//�e�N�X�`���C���[�W�X���b�g
		//GX_VRAM_TEX_0_A,				//�e�N�X�`���C���[�W�X���b�g
		GX_VRAM_TEXPLTT_0123_E			//�e�N�X�`���p���b�g�X���b�g
		//GX_VRAM_TEX_NONE,				//�e�N�X�`���C���[�W�X���b�g
		//GX_VRAM_TEXPLTT_NONE			//�e�N�X�`���p���b�g�X���b�g
		//GX_VRAM_TEXPLTT_0123_E		//�e�N�X�`���p���b�g�X���b�g
	};

	GF_Disp_SetBank( &vramSetTable );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	BG�ݒ�
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void BgSet( SND_TEST_WORK* wk )
{
	//bg_system.c
	
#if 1
	{
		GF_BGL_SYS_HEADER BGsys_data = {	//BG�V�X�e���\����
			GX_DISPMODE_GRAPHICS,			//�\�����[�h�w�� 
			GX_BGMODE_0,					//�a�f���[�h�w��(���C���X�N���[��)
			GX_BGMODE_0,					//�a�f���[�h�w��(�T�u�X�N���[��)
			GX_BG0_AS_2D,					//�a�f�O�̂Q�c�A�R�c���[�h�I��
			//GX_BG0_AS_3D,					//�a�f�O�̂Q�c�A�R�c���[�h�I��
		};

		//���C���A�T�u�̃O���t�B�b�N�X�G���W���̕\�����[�h�ݒ�
		//���C���A�T�u�̉�ʂ̊e�ʂ̕\���R���g���[��������(display.c)
		//�r�b�g�}�b�v�E�B���h�E�ݒ�\���̏�����
		GF_BGL_InitBG( &BGsys_data );
	}
#endif

	{	//BMP�E�B���h�E
		GF_BGL_BGCNT_HEADER BmpWinBgCntData = {	//BG�R���g���[���ݒ�\����
			0, 0,								//�����\���w�x
			0x800,								//�X�N���[���o�b�t�@�T�C�Y( 0 = �g�p���Ȃ� )
			0,									//�X�N���[���o�b�t�@�I�t�Z�b�g

			//BG�ݒ�
			GF_BGL_SCRSIZ_256x256,				//�X�N���[���T�C�Y
			GX_BG_COLORMODE_16,					//�J���[���[�h
			GX_BG_SCRBASE_0xd000,				//�X�N���[���x�[�X�u���b�N
			GX_BG_CHARBASE_0x00000,				//�L�����N�^�x�[�X�u���b�N
			GX_BG_EXTPLTT_01,					//�a�f�g���p���b�g�X���b�g�I��

			0,									//�\���v���C�I���e�B�[
			0, 0,								//�G���A�I�[�o�[�t���O�A�_�~�[
			FALSE								//���U�C�N�ݒ�
		};

		GF_BGL_BGControlSet(wk->bgl, SND_TEST_BMPWIN_FRAME, 
							&BmpWinBgCntData, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( wk->bgl, SND_TEST_BMPWIN_FRAME );
	}

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
static void SndTestNumMsgSet( GF_BGL_BMPWIN* win, int num, u8 x, u8 y )
{
	STRBUF* buf = STRBUF_Create( 6, HEAPID_BASE_DEBUG );

	STRBUF_SetNumber( buf, num, 4, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT );
	GF_STR_PrintSimple( win, FONT_SYSTEM, buf, x, y, MSG_NO_PUT, NULL );
	STRBUF_Delete(buf);

	return;
}

//--------------------------------------------------------------
/**
 * @brief	�T�E���h�l�[�����b�Z�[�W�\��
 *
 * @param	win_index	�r�b�g�}�b�vINDEX
 * @param	num			���l
 * @param	x			�\���ʒuX
 * @param	y			�\���ʒuY
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void SndTestNameMsgSet( GF_BGL_BMPWIN* win, const STRBUF* msg, u8 x, u8 y )
{
	GF_STR_PrintSimple( win, FONT_SYSTEM, msg, x, y, MSG_NO_PUT, NULL );
	return;
}

//------------------------------------------------------------------
/**
 * �Œ蕶����o��
 *
 * @param   win			BitmapWindow
 * @param   fontID		�t�H���g
 * @param   strID		������h�c
 * @param   x			�`��w���W
 * @param   y			�`��x���W
 * @param   wait		�E�F�C�g
 * @param   callback	�R�[���o�b�N
 *
 */
//------------------------------------------------------------------
static void SndTestStrPrint( GF_BGL_BMPWIN* win, u32 fontID, u32 strID, u32 x, u32 y, u32 wait, pStrPrintCallBack callback )
{
	MSGDATA_MANAGER* man = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, 
									NARC_msg_snd_test_str_dat, HEAPID_BASE_DEBUG );

	STRBUF* str = MSGMAN_AllocString( man, strID );

	GF_STR_PrintSimple( win, fontID, str, x, y, wait, callback );

	STRBUF_Delete(str);
	MSGMAN_Delete(man);
}

//--------------------------------------------------------------
/**
 * @brief	BGM���b�Z�[�W�ĕ\��
 *
 * @param	wk		SND_TEST_WORK�ւ̃|�C���^
 * @param	select	�I��Ώ�
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void MsgRewrite( SND_TEST_WORK* wk, s8 select )
{
	int type;
	u32 msg_h_id;

	switch( select ){
	case SND_TEST_TYPE_BGM:
		//wk->bgm,se,pv�ɂ́A�V�[�P���X�i���o�[�������Ă���̂ŁA
		//�X�^�[�g�i���o�[�������A�I�����Ă���l�ɂ��āA
		//���b�Z�[�WID�̃X�^�[�g�i���o�[�𑫂����b�Z�[�W��\������
		msg_h_id = wk->bgm - SND_TEST_BGM_START_NO + msg_seq_pv_end + 1;

		//�w��͈͂�h��Ԃ�
		GF_BGL_BmpWinFill( &wk->bmpwin, 
							FBMP_COL_WHITE, ST_TYPE_X, ST_BGM_MSG_Y+16, 8*24, 16*1 );

		SndTestStrPrint( &wk->bmpwin, FONT_SYSTEM, msg_BGM, 
						ST_TYPE_X, ST_BGM_MSG_Y, MSG_NO_PUT, NULL );
		SndTestNumMsgSet( &wk->bmpwin, wk->bgm, ST_TYPE_X, ST_BGM_MSG_Y+16 );

		MSGMAN_GetString( wk->msgman, msg_h_id, wk->msg_buf[BUF_BGM] );
		SndTestNameMsgSet( &wk->bmpwin, wk->msg_buf[BUF_BGM], ST_NAME_X, ST_BGM_MSG_Y+16 );

		SndTestStrPrint( &wk->bmpwin, FONT_SYSTEM, msg_ME, 
						ST_TYPE_X+32, ST_BGM_MSG_Y, MSG_NO_PUT, NULL );

		SndTestStrPrint( &wk->bmpwin, FONT_SYSTEM, msg_KEY, 
						ST_TYPE_X+56, ST_BGM_MSG_Y, MSG_NO_PUT, NULL );

		SndTestStrPrint( &wk->bmpwin, FONT_SYSTEM, msg_TMP, 
						ST_TYPE_X+136, ST_BGM_MSG_Y, MSG_NO_PUT, NULL );

		break;

	case SND_TEST_TYPE_SE:
		msg_h_id = wk->se - SND_TEST_SE_START_NO + msg_seq_bgm_end + 1;

		//�w��͈͂�h��Ԃ�
		GF_BGL_BmpWinFill( &wk->bmpwin, 
							FBMP_COL_WHITE, ST_TYPE_X, ST_SE_MSG_Y+16, 8*24, 16*1 );

		//�V�[�P���X�i���o�[����ASE�̃v���C���[�i���o�[���擾
		type = Snd_GetPlayerNo(wk->se);
		type -= PLAYER_SE_1;

		//SE�̂݃v���C���[�i���o�[�\��
		SndTestStrPrint( &wk->bmpwin, FONT_SYSTEM, msg_PLAYER, 
						ST_TYPE_X+32, ST_SE_MSG_Y, MSG_NO_PUT, NULL );
		SndTestNumMsgSet( &wk->bmpwin, type, ST_TYPE_X+32+56, ST_SE_MSG_Y );

		SndTestStrPrint( &wk->bmpwin, FONT_SYSTEM, msg_SE, 
						ST_TYPE_X, ST_SE_MSG_Y, MSG_NO_PUT, NULL );

		SndTestNumMsgSet( &wk->bmpwin, wk->se, ST_TYPE_X, ST_SE_MSG_Y+16 );

		MSGMAN_GetString( wk->msgman, msg_h_id, wk->msg_buf[BUF_SE] );
		SndTestNameMsgSet( &wk->bmpwin, wk->msg_buf[BUF_SE], ST_NAME_X, ST_SE_MSG_Y+16 );
		break;

	case SND_TEST_TYPE_PV:
		msg_h_id = wk->pv - SND_TEST_PV_START_NO + msg_seq_pv001;

		//�w��͈͂�h��Ԃ�
		GF_BGL_BmpWinFill( &wk->bmpwin, 
							FBMP_COL_WHITE, ST_TYPE_X, ST_PV_MSG_Y+16, 8*24, 16*1 );

		SndTestStrPrint( &wk->bmpwin, FONT_SYSTEM, msg_PV, 
						ST_TYPE_X, ST_PV_MSG_Y, MSG_NO_PUT, NULL );
		SndTestNumMsgSet( &wk->bmpwin, wk->pv, ST_TYPE_X, ST_PV_MSG_Y+16 );

		MSGMAN_GetString( wk->msgman, msg_h_id, wk->msg_buf[BUF_PV] );
		SndTestNameMsgSet( &wk->bmpwin, wk->msg_buf[BUF_PV], ST_NAME_X, ST_PV_MSG_Y+16 );
		break;
	};

	return;
}

//--------------------------------------------------------------
/**
 * @brief	������Ԃɂ���(X_BUTTON�����������̏������I)
 *
 * @param	wk		SND_TEST_WORK�ւ̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void SndTestInit( SND_TEST_WORK* wk )
{
	//���[�N������
	SndTestWorkInit( wk );

	//��������
	MsgRewrite( wk, SND_TEST_TYPE_BGM );		//BGM�i���o�[
	MsgRewrite( wk, SND_TEST_TYPE_SE );			//SE�i���o�[
	MsgRewrite( wk, SND_TEST_TYPE_PV );			//PV�i���o�[

	SndTestCursor( wk );						//�J�[�\���X�V

	return;
}

//--------------------------------------------------------------
/**
 * @brief	�J�[�\��
 *
 * @param	wk		SND_TEST_WORK�ւ̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void SndTestCursor( SND_TEST_WORK* wk )
{
	u16 y;

	switch( wk->select ){
	case SND_TEST_TYPE_BGM:
		y = ST_BGM_MSG_Y;
		break;
	case SND_TEST_TYPE_SE:
		y = ST_SE_MSG_Y;
		break;
	case SND_TEST_TYPE_PV:
		y = ST_PV_MSG_Y;
		break;
	};

	//�w��͈͂�h��Ԃ�
	GF_BGL_BmpWinFill( &wk->bmpwin, 
						FBMP_COL_WHITE, ST_CURSOR_X, ST_BGM_MSG_Y, 8*1, 16*8 );
	GF_BGL_BmpWinFill( &wk->bmpwin, 
						FBMP_COL_RED, ST_CURSOR_X, y, 8*1, 16*1 );

	return;
}

//--------------------------------------------------------------
/**
 * @brief	�V�X�e�����b�Z�[�W
 *
 * @param	wk		SND_TEST_WORK�ւ̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void SndTestSysMsgSet( SND_TEST_WORK* wk )
{
	SndTestStrPrint( &wk->bmpwin, FONT_SYSTEM, msg_SOUND_TEST, 
				ST_TITLE_X, ST_TITLE_Y, MSG_NO_PUT, NULL );			//SOUND TEST
	SndTestStrPrint( &wk->bmpwin, FONT_SYSTEM, msg_A_PLAY, 
				ST_KEY_X, ST_KEY_Y, MSG_NO_PUT, NULL );				//A PLAY
	SndTestStrPrint( &wk->bmpwin, FONT_SYSTEM, msg_B_STOP, 
				ST_KEY_X+64, ST_KEY_Y, MSG_NO_PUT, NULL );			//B STOP
	SndTestStrPrint( &wk->bmpwin, FONT_SYSTEM, msg_X_END, 
				ST_KEY_X, ST_KEY_Y+16, MSG_NO_PUT, NULL );			//X END
	SndTestStrPrint( &wk->bmpwin, FONT_SYSTEM, msg_Y_INIT, 
				ST_KEY_X+64, ST_KEY_Y+16, MSG_NO_PUT, NULL );		//Y INIT

	return;
}


//==============================================================================================
//
//	PROC�֘A
//
//==============================================================================================

//--------------------------------------------------------------
//--------------------------------------------------------------
static PROC_RESULT SoundTestProc_Init(PROC * proc, int * seq)
{
	SND_TEST_WORK* wk = NULL;

	wk = PROC_AllocWork(proc, sizeof(SND_TEST_WORK), HEAPID_BASE_DEBUG);
	memset( wk, 0, sizeof(SND_TEST_WORK) );

	SndTestCall(wk);
	return PROC_RES_FINISH;
		
}

//--------------------------------------------------------------
//--------------------------------------------------------------
static PROC_RESULT SoundTestProc_Main(PROC * proc, int * seq)
{
	SND_TEST_WORK *swk;
	swk = PROC_GetWork(proc);

	SndTestTable[swk->seq](swk);

	if (swk->end_flag) {
		return PROC_RES_FINISH;
	} else {
		return PROC_RES_CONTINUE;
	}
}

//--------------------------------------------------------------
//--------------------------------------------------------------
static PROC_RESULT SoundTestProc_End(PROC * proc, int * seq)
{
	PROC_FreeWork(proc);
	//Main_SetNextProc(NO_OVERLAY_ID, &TitleProcData);

	//�\�t�g���Z�b�g
	//�ڍׂ̓\�[�X�擪�́u�T�E���h�e�X�g�̗�O�����ɂ��āv���Q�Ƃ��ĉ�����
	//OS_InitReset();
	OS_ResetSystem(0);									//�\�t�g���Z�b�g
	return PROC_RES_FINISH;
}

//--------------------------------------------------------------
//--------------------------------------------------------------
const PROC_DATA SoundTestProcData = {
	SoundTestProc_Init,
	SoundTestProc_Main,
	SoundTestProc_End,
	NO_OVERLAY_ID
};


