//============================================================================================
/**
 * @file	trainer_card.c
 * @bfief	�g���[�i�[�J�[�h
 * @author	Nozomu Saito
 * @date	05.11.15
 */
//============================================================================================
#include "trcard_sys.h"
#include "gflib/touchpanel.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/clact_tool.h"
#include "system/wipe.h"
#include "system/fontproc.h"

#include "system/snd_tool.h"
#include "trcard_snd_def.h"
#include "trcard_bmp.h"
#include "trcard_obj.h"
#include "trcard_cgx_def.h"
#include "application/app_tool.h"
#include "trainer_case.naix"

#include "msgdata/msg_trainerscard.h"
#include "msgdata/msg.naix"
#include "communication/wm_icon.h"

#define MIN_SCRUCH	(3)
#define MAX_SCRUCH	(40)
#define REV_SPEED	(FX32_SHIFT - wk->RevSpeed)

#define CGX_WIDE		(32)
#define BUTTON_CGX_POS	(4*CGX_WIDE)
#define	MAIN_BUTTON_CGX_SIZE	(4)
#define MAIN_BUTTON_POS_Y	(19)
#define MAIN_BUTTON_POS_X	(14)

#define NOBODY_CGX_POS	(5*CGX_WIDE+26)
#define	GYM_READER_CGX_SIZE	(5)
#define COVER_CGX_WIDTH	(16)

#define BADGE_BAD_PLTT_NO	(3)
#define UNI_TRAINER_PLTT_NO	(4)

#define TRC_BG_TRAINER		(GF_BGL_FRAME3_S)//(GF_BGL_FRAME0_S)
#define TRC_BG_FONT			(GF_BGL_FRAME3_S)
#define TRC_BG_SIGHN		(GF_BGL_FRAME3_S)
#define TRC_BG_CASE			(GF_BGL_FRAME1_S)
#define TRC_BG_CARD			(GF_BGL_FRAME2_S)
#define TRC_BG_UNDER_CASE	(GF_BGL_FRAME2_M)
#define TRC_BG_COVER		(GF_BGL_FRAME3_M)

#define CARD_SCALE_MIN	(0x24)

#define UNION_TR_MAX	(16)

enum {
	SEQ_IN,
	SEQ_MAIN,
	SEQ_OUT,
	SEQ_REV,
	SEQ_COVER,
};

typedef enum {
	TRC_KEY_REQ_NONE = 0,
	TRC_KEY_REQ_TP_BEAT,
	TRC_KEY_REQ_TP_BRUSH,
	TRC_KEY_REQ_REV_BUTTON,
	TRC_KEY_REQ_END_BUTTON,
}TRC_KEY_REQ;

typedef enum {
	COVER_CLOSE = 0,
	COVER_OPEN = 1,
}COVER_STATE;

enum {
	CASE_BUTTON,
	BADGE0,
	BADGE1,
	BADGE2,
	BADGE3,
	BADGE4,
	BADGE5,
	BADGE6,
	BADGE7,
};

enum {
	ANIME_NOTHING,
	ANIME_BUTTON_PUSH,
	ANIME_BUTTON_PULL
};

typedef struct {
	const RECT_HIT_TBL *const CoverTpRect[2];	//0:�J�o�[���Ă�Ƃ� 1:�J�o�[�J���Ă�Ƃ�
}RECT_HIT_TBL_LIST;

//�����Ŏw�肵���񐔈ȏケ����ƁA�o�b�W��1�񖁂������ƂɂȂ�(���x����)
static const u8 TempScruchMax[5] = {
	1,3,4,15,15
};

// 8�o�b�W�ƃP�[�X�{�^���̃^�b�`�p�l������e�[�u��
static const RECT_HIT_TBL TpRect1[] =
{
	//��	��		��		�E
	{ 19*8, 23*8-1,	15*8,	19*8-1, },
	{ 5*8,  10*8-1,	3*8,	8*8-1,  },
	{ 5*8,  10*8-1,	10*8,	15*8-1, },
	{ 5*8,  10*8-1,	17*8,	21*8-1, },
	{ 5*8,  10*8-1,	24*8,	29*8-1, },
	{ 12*8, 17*8-1,	3*8,	8*8-1,  },
	{ 12*8, 17*8-1,	10*8,	15*8-1, },
	{ 12*8, 17*8-1,	17*8,	21*8-1, },
	{ 12*8, 17*8-1,	24*8,	29*8-1, },
	{ RECT_HIT_END, 0, 0, 0 }
};

//�J�o�[�����Ă���Ƃ��̃^�b�`�p�l������e�[�u��(�{�^���̂�)
static const RECT_HIT_TBL TpRect2[] =
{
	//��	��		��		�E
	{ 19*8, 23*8-1,	15*8,	19*8-1, },
	{ RECT_HIT_END, 0, 0, 0 }
};

static const RECT_HIT_TBL_LIST TpHit[] =	{
	{TpRect2,TpRect2},		// �ʐM��(TR_CARD_DATA::BrushValid == 0) �J�o�[���J���Ă��A�o�b�W�����ł��Ȃ�
	{TpRect2,TpRect1},		//�ʏ펞(TR_CARD_DATA::BrushValid == 1)	�J�o�[�J������o�b�W������
};

static const u8 ButtonAnimePush[] = {
	1,1,	//1�t���[���A1�Ԗ�
	0,2,	//�I���A2�Ԗ�
};
static const u8 ButtonAnimePull[] = {
	1,1,	//1�t���[���A1�Ԗ�
	0,0,	//�I���A     0�Ԗ�
};

static const u8 * const ButtonAnime[] = {
	ButtonAnimePush,
	ButtonAnimePull
};

//���j�I�����[���g���[�i�[�\���e�[�u��
static const int UniTrTable[UNION_TR_MAX] = 
{
	//�j
	NARC_trainer_case_trdp_schoolb256_NCGR,
	NARC_trainer_case_trdp_mushi256_NCGR,
	NARC_trainer_case_trdp_elitem256_NCGR,
	NARC_trainer_case_trdp_heads256_NCGR,
	NARC_trainer_case_trdp_iseki256_NCGR,
	NARC_trainer_case_trdp_karate256_NCGR,
	NARC_trainer_case_trdp_prince256_NCGR,
	NARC_trainer_case_trdp_espm256_NCGR,
	//��
	NARC_trainer_case_trdp_mini256_NCGR,
	NARC_trainer_case_trdp_battleg256_NCGR,
	NARC_trainer_case_trdp_sister256_NCGR,
	NARC_trainer_case_trdp_elitew256_NCGR,
	NARC_trainer_case_trdp_idol256_NCGR,
	NARC_trainer_case_trdp_madam256_NCGR,
	NARC_trainer_case_trdp_cowgirl256_NCGR,
	NARC_trainer_case_trdp_princess256_NCGR,
};


//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================
static void AllocStrBuf( TR_CARD_WORK * wk );
static void FreeStrBuf( TR_CARD_WORK * wk );

static void SetTrCardVramBank(void);
static void SetTrCardBg( GF_BGL_INI * ini );
static void SetTrCardBgGraphic( TR_CARD_WORK * wk );

static void TrCardBgExit( GF_BGL_INI * ini );

static BOOL CardRev(TR_CARD_WORK * wk );
static BOOL CoverOpenClose(TR_CARD_WORK *wk);
static BOOL PushButton(TR_CARD_WORK *wk, const u8 *inAnime);
static int CheckKey(TR_CARD_WORK *wk);
static void BrushBadge(TR_CARD_WORK *wk);
static void SetCardPalette(const u8 inCardRank, const u8 inPokeBookHold);
static void SetCasePalette(const u8 inVersion);
static void SetUniTrainerPalette(const u8 inTrainerNo);

static void ChangeBgButton(TR_CARD_WORK *wk, const u8 inAnmNum);
static void ChangeBgGymReader(TR_CARD_WORK *wk, const u8 inNo);
static void VBlankFunc( void * work );
static void DispTrainer(TR_CARD_WORK *wk);
static void ClearTrainer(TR_CARD_WORK *wk);

static void BadgeLvUp(TR_CARD_WORK *wk, const u8 inBadgeNo);
static void ResetAffinePlane(void);
static void ButtonAnimeControl(TR_CARD_WORK *wk);
static const u8 GetBadgeLevel(const int inCount);

static void ClearScruchSndNow(TR_SCRUCH_SND *outScruchSnd);
static void ClearScruchSnd(TR_SCRUCH_SND *outScruchSnd);
static void PlayScruchSnd(TR_SCRUCH_SND *ioScruchSnd);
static void MakeSignData(const u8 *inRawData, u8 *outData);
static void TransSignData(GF_BGL_INI * bgl,const int inFrame, const u8 *inSignData);
static void PlayButtonAndCoverSnd(const COVER_STATE inIsOpen);
static void UpdatePlayTime(TR_CARD_WORK *wk, const u8 inUpdateFlg);
static int CheckTpBadgeTrg(GF_BGL_INI * bgl, const RECT_HIT_TBL *hitTbl);
static int CheckTpBadgeCont(GF_BGL_INI * bgl, const RECT_HIT_TBL *hitTbl);

//============================================================================================
//	�O���[�o���ϐ�
//============================================================================================


//--------------------------------------------------------------------------------------------
/**
 * �v���Z�X�֐��F������
 *
 * @param	proc	�v���Z�X�f�[�^
 * @param	seq		�V�[�P���X
 *
 * @return	������
 */
//--------------------------------------------------------------------------------------------
PROC_RESULT TrCardProc_Init( PROC * proc, int * seq )
{
	TR_CARD_WORK * wk;

	sys_VBlankFuncChange( NULL, NULL );	// VBlank�Z�b�g
	sys_HBlankIntrSet( NULL,NULL );		// HBlank�Z�b�g

	GF_Disp_GX_VisibleControlInit();
	GF_Disp_GXS_VisibleControlInit();
	GX_SetVisiblePlane( 0 );
	GXS_SetVisiblePlane( 0 );

	sys_KeyRepeatSpeedSet( 4, 8 );
	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_TR_CARD, 0x28000 );

	wk = PROC_AllocWork( proc, sizeof(TR_CARD_WORK), HEAPID_TR_CARD );
	memset( wk, 0, sizeof(TR_CARD_WORK) );

///	APP_WipeStart( APP_WIPE_IN, HEAPID_TR_CARD );	// �P�x�ύX�Z�b�g
	
	wk->TrCardData = PROC_GetParentWork( proc );
	wk->bgl = GF_BGL_BglIniAlloc( HEAPID_TR_CARD );
	
	AllocStrBuf(wk);
	
	SetTrCardVramBank();
	SetTrCardBg( wk->bgl );
	SetTrCardBgGraphic( wk );

	InitTPSystem();						// �^�b�`�p�l���V�X�e��������
	InitTPNoBuff(4);

	//���֘A������
	Snd_DataSetByScene( SND_SCENE_SUB_TRCARD, 0, 0 ); //�T�E���h�f�[�^���[�h(BGM���p��)
	Snd_BadgeWorkInit( &wk->SndBadgeWork );
	Snd_SePlay( SND_TRCARD_CALL );		//�Ăяo����
	
	InitTRCardCellActor( &wk->ObjWork );
	
	{
		int i;
		u8 badge_disp[TR_BADGE_NUM_MAX];
		for(i=0;i<TR_BADGE_NUM_MAX;i++){
			if (wk->TrCardData->BadgeData[i].BadgeHold){
				badge_disp[i] = 1;
			}else{
				badge_disp[i] = 0;
			}
		}
		
		SetTrCardActor( &wk->ObjWork, badge_disp );
	}
	
	TRCBmp_AddTrCardBmp( wk->bgl, wk->win );

	{
		u8 no;
		for(no=0;no<TR_BADGE_NUM_MAX;no++){
			//�}�X�N����
			if ( (wk->TrCardData->GymReaderMask>>no)&0x01 ){
				ChangeBgGymReader(wk,no);
			}
		}
		GF_BGL_LoadScreenReq( wk->bgl, TRC_BG_COVER );
	}
	
	TRCBmp_WriteTrWinInfo( wk->win, wk->TrCardData );
	//�R�����`��
	TRCBmp_WriteSec(&(wk->win[TRC_BMPWIN_PLAY_TIME]), TRUE, wk->SecBuf);
	
	wk->is_back = FALSE;		//�\�ʂ���X�^�[�g
	wk->IsOpen = COVER_CLOSE;			//�P�[�X�͕�����Ԃ���X�^�[�g

	wk->touch = RECT_HIT_NONE;			//�^�b�`�p�l���͉�����Ă��Ȃ�

	wk->ButtonPushFlg = FALSE;			//�{�^��������ĂȂ�
	wk->AnimeType = ANIME_NOTHING;		//�{�^���A�j������
	//�o�b�W���x���ɍ��킹�ăp���b�g�Z�b�g
	{
		u8 lv;
		u8 i;
		for(i=0;i<TR_BADGE_NUM_MAX;i++){
			wk->ScruchCounter[i] = 0;
			if (wk->TrCardData->BadgeData[i].BadgeHold){
				lv = GetBadgeLevel(wk->TrCardData->BadgeData[i].BadgeScruchCount);
				if (lv <= TR_CARD_BADGE_LV_MAX){
					if (lv == TR_CARD_BADGE_LV_MAX){	//�o�b�W���x�����ō��̂Ƃ��́A1�i�K���̃��x���̃p���b�g���g�p
						SetBadgePalette(&wk->ObjWork, i, 0);
					}else{
						SetBadgePalette(&wk->ObjWork, i, BADGE_BAD_PLTT_NO-lv);
					}
				}
				//���A�N�^�[�\��
				if (lv == TR_CARD_BADGE_LV_MAX-1){
					CLACT_SetDrawFlag(wk->ObjWork.ClActWork[TR_CARD_STAR_ACT_START+i], 1);	//�\��
				}
				else if (lv == TR_CARD_BADGE_LV_MAX){
					CLACT_SetDrawFlag(wk->ObjWork.ClActWork[TR_CARD_GRATE_STAR_ACT_START+i], 1);	//�\��
				}
			}
		}
	}

	//�g�k�ʂ����Z�b�g
	ResetAffinePlane();
	

	sys_VBlankFuncChange(VBlankFunc, NULL );	// VBlank�Z�b�g

	//�ʐM�A�C�R���Z�b�g
	// ��M���x�A�C�R����ʐM�ڑ����Ȃ�\�����邵�A
	// ���j�I���̂悤�ɒʐM��H�͓��삵�Ă��邪�ڑ��͂��Ă��Ȃ���ԂȂ�o���Ȃ�
	// Change by Mori 2006/07/19
	WirelessIconEasyUnion();

	//BGM�����ڂ�
	//Snd_BgmFadeOut( BGM_VOL_TR_CASE, BGM_FADE_TR_CASE_TIME );
	Snd_PlayerSetPlayerVolume( PLAYER_FIELD, BGM_VOL_TR_CASE );

	WIPE_SYS_Start(	WIPE_PATTERN_FSAM, WIPE_TYPE_SHUTTERIN_DOWN,
					WIPE_TYPE_SHUTTERIN_DOWN, WIPE_FADE_BLACK,
					WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_TR_CARD );

	return PROC_RES_FINISH;
}

//--------------------------------------------------------------------------------------------
/**
 * �v���Z�X�֐��F���C��
 *
 * @param	proc	�v���Z�X�f�[�^
 * @param	seq		�V�[�P���X
 *
 * @return	������
 */
//--------------------------------------------------------------------------------------------
PROC_RESULT TrCardProc_Main( PROC * proc, int * seq )
{
	TR_CARD_WORK * wk  = PROC_GetWork( proc );

	switch( *seq ){
	case SEQ_IN:
		if( WIPE_SYS_EndCheck() ){
			*seq = SEQ_MAIN;
		}
		break;

	case SEQ_MAIN:
		{
			int req;
			req = CheckKey(wk);

			if (req == TRC_KEY_REQ_TP_BEAT){
				//�^�b�`�p�l���e���v���[�g�ƃ^�b�`���W���r
				if (wk->touch == CASE_BUTTON){
					wk->ButtonPushFlg = TRUE;		//�{�^��������
					wk->AnimeType = ANIME_BUTTON_PUSH;	//�{�^�������A�j��
					//�{�^���G�t�F�N�g�A�N�^�[�\��
					CLACT_SetDrawFlag(wk->ObjWork.ClActWork[TR_CARD_BTNEFF_ACT_START], 1);	//�\��
					CLACT_SetAnmFlag(wk->ObjWork.ClActWork[TR_CARD_BTNEFF_ACT_START],1);
					CLACT_AnmChg( wk->ObjWork.ClActWork[TR_CARD_BTNEFF_ACT_START], 10 );
					
					wk->sub_seq = 0;	//�T�u�V�[�P���X������
					//�{�^���A�j��������
					wk->AnmNum = 0;
					wk->ButtonAnmCount = 0;
					//�V�[�P���X�҂��t���O������
					wk->rc_cover = FALSE;
					*seq = SEQ_COVER;	//�J�o�[�̊J��
				}else{
					u8 no = wk->touch-1;
					//�o�b�W���L����
					if (wk->TrCardData->BadgeData[no].BadgeHold){
						u8 lv;
						lv = GetBadgeLevel(wk->TrCardData->BadgeData[no].BadgeScruchCount);
						//�o�b�W��������
						Snd_BadgeWorkPlay( &wk->SndBadgeWork, no, lv );
					}
				}
			}else if (req == TRC_KEY_REQ_TP_BRUSH){
				if ( (wk->ButtonPushFlg)&&(wk->touch != CASE_BUTTON) ){
					wk->ButtonPushFlg = FALSE;
					wk->AnimeType = ANIME_BUTTON_PULL;	//�{�^���߂��A�j��
				}
				//�J�o�[���󂢂Ă���΁A�o�b�`����
				BrushBadge(wk);//�o�b�`����
			}else{
				if ( (wk->ButtonPushFlg)&&(wk->AnimeType == ANIME_NOTHING) ){
					wk->ButtonPushFlg = FALSE;
					wk->AnimeType = ANIME_BUTTON_PULL;	//�{�^���߂��A�j��
				}
				if (wk->TrCardData->BrushValid){
					ClearScruchSnd(&wk->ScruchSnd);
				}

				if (req == TRC_KEY_REQ_REV_BUTTON){
					//�J�[�h�Ђ�����Ԃ�
					wk->sub_seq = 0;	//�T�u�V�[�P���X������
					*seq = SEQ_REV;	//�J�[�h��]
				}else if (req == TRC_KEY_REQ_END_BUTTON){
					//�I��
					Snd_SePlay( SND_TRCARD_END );		//�I����
///					APP_WipeStart( APP_WIPE_OUT, HEAPID_TR_CARD );	// �P�x�ύX�Z�b�g
					WIPE_SYS_Start(	WIPE_PATTERN_FMAS, WIPE_TYPE_SHUTTEROUT_UP,
									WIPE_TYPE_SHUTTEROUT_UP, WIPE_FADE_BLACK,
									WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_TR_CARD );
					*seq = SEQ_OUT;
				}
			}
			UpdatePlayTime(wk, wk->TrCardData->TimeUpdate);
		}
		break;

	case SEQ_OUT:
		if( WIPE_SYS_EndCheck() ){
			return PROC_RES_FINISH;
		}
		break;
	
	case SEQ_REV:	//���o�[�X����
		if ( CardRev(wk) ){
			*seq = SEQ_MAIN;
		}
		break;
	case SEQ_COVER:
		if (wk->AnimeType == ANIME_NOTHING){
			int req;
			req = CheckKey(wk);

			if (req == TRC_KEY_REQ_TP_BEAT){
				if (wk->touch == CASE_BUTTON){
					wk->ButtonPushFlg = TRUE;		//�{�^��������
					wk->AnimeType = ANIME_BUTTON_PUSH;	//�{�^�������A�j��
					//�{�^���A�j��������
					wk->AnmNum = 0;
					wk->ButtonAnmCount = 0;
				}
			}else if (req == TRC_KEY_REQ_TP_BRUSH){
				if ( (wk->ButtonPushFlg)&&(wk->touch != CASE_BUTTON) ){
					wk->ButtonPushFlg = FALSE;
					wk->AnimeType = ANIME_BUTTON_PULL;	//�{�^���߂��A�j��
				}
			}else{
				if ( wk->ButtonPushFlg ){
					wk->ButtonPushFlg = FALSE;
					wk->AnimeType = ANIME_BUTTON_PULL;	//�{�^���߂��A�j��
				}
			}
		}
		//�J��
		if (wk->rc_cover == FALSE){
			wk->rc_cover = CoverOpenClose(wk);
		}

		if (wk->rc_cover){
			wk->rc_cover = FALSE;
			*seq = SEQ_MAIN;
		}
		break;
	}

	//�{�^���A�j��
	ButtonAnimeControl(wk);
	

	CLACT_Draw( wk->ObjWork.ClactSet );									// �Z���A�N�^�[�풓�֐�

	return PROC_RES_CONTINUE;
}

//--------------------------------------------------------------------------------------------
/**
 * �v���Z�X�֐��F�I��
 *
 * @param	proc	�v���Z�X�f�[�^
 * @param	seq		�V�[�P���X
 *
 * @return	������
 */
//--------------------------------------------------------------------------------------------
PROC_RESULT TrCardProc_End( PROC * proc, int * seq )
{
	TR_CARD_WORK * wk  = PROC_GetWork( proc );

	//�g�p�����g�k�ʂ����ɖ߂�
	ResetAffinePlane();
	
	FreeStrBuf( wk );					//��������
	
	RereaseCellObject(&wk->ObjWork);		//2D�I�u�W�F�N�g�֘A�̈���

	sys_FreeMemoryEz( wk->TrArcData );	//�g���[�i�[�L�����A�[�J�C�u�f�[�^���

	sys_FreeMemoryEz( wk->TrScrnArcData );//�g���[�i�[�X�N���[�����

	TRCBmp_ExitTrCardBmpWin( wk->win );			// BMP�E�B���h�E�J��
	TrCardBgExit( wk->bgl );			// BGL�폜
	StopTP();							// �^�b�`�p�l���I��

	PROC_FreeWork( proc );				// ���[�N�J��

	sys_VBlankFuncChange( NULL, NULL );		// VBlank�Z�b�g
	sys_DeleteHeap( HEAPID_TR_CARD );

	//BGM�����̉��ʂɖ߂�
	//Snd_BgmFadeIn( BGM_VOL_MAX, BGM_FADE_TR_CASE_TIME, BGM_FADEIN_START_VOL_NOW );
	Snd_PlayerSetPlayerVolume( PLAYER_FIELD, BGM_VOL_MAX );

	return PROC_RES_FINISH;
}

//--------------------------------------------------------------------------------------------
/**
 * ������o�b�t�@�̊m��
 *
 * @param	wk		��ʂ̃��[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void AllocStrBuf( TR_CARD_WORK * wk )
{
	wk->PlayTimeBuf = STRBUF_Create(TIME_H_DIGIT+1, HEAPID_TR_CARD);
	wk->SecBuf =	STRBUF_Create(5, HEAPID_TR_CARD);
	{
		MSGDATA_MANAGER* man;
		man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_trainerscard_dat, HEAPID_TR_CARD);
		MSGMAN_GetString(man, MSG_TCARD_12, wk->SecBuf);
		MSGMAN_Delete( man );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * ������o�b�t�@�̉��
 *
 * @param	wk		��ʂ̃��[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FreeStrBuf( TR_CARD_WORK * wk )
{
	STRBUF_Delete( wk->PlayTimeBuf );
	STRBUF_Delete( wk->SecBuf );
}

//--------------------------------------------------------------------------------------------
/**
 * VRAM�ݒ�
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void SetTrCardVramBank(void)
{
	GF_BGL_DISPVRAM tbl = {
		GX_VRAM_BG_64_E,				// ���C��2D�G���W����BG
		GX_VRAM_BGEXTPLTT_NONE,			// ���C��2D�G���W����BG�g���p���b�g

		GX_VRAM_SUB_BG_128_C,			// �T�u2D�G���W����BG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		// �T�u2D�G���W����BG�g���p���b�g

		GX_VRAM_OBJ_128_B,				// ���C��2D�G���W����OBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// ���C��2D�G���W����OBJ�g���p���b�g

		GX_VRAM_SUB_OBJ_16_I,			// �T�u2D�G���W����OBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// �T�u2D�G���W����OBJ�g���p���b�g

		GX_VRAM_TEX_NONE,				// �e�N�X�`���C���[�W�X���b�g
		GX_VRAM_TEXPLTT_NONE			// �e�N�X�`���p���b�g�X���b�g
	};
	GF_Disp_SetBank( &tbl );
}

//--------------------------------------------------------------------------------------------
/**
 * �J�[�h�p���b�g�ݒ�
 *
 * @param	inCardRank		�J�[�h�����N
 * @param	inPokeBookHold	�}�ӏ����t���O
 * 
 * @return	�Ȃ�
 */
//--------------------------------------------------------------------------------------------
static void SetCardPalette(const u8 inCardRank, const u8 inPokeBookHold)
{
	{
		void *buf;
		NNSG2dPaletteData *dat;

		if (inPokeBookHold){
			switch(inCardRank){
			case 0:
				buf = ArcUtil_PalDataGet(
					ARC_TR_CASE_GRA, NARC_trainer_case_card_0_NCLR, &dat, HEAPID_TR_CARD );
				break;
			case 1:
				buf = ArcUtil_PalDataGet(
					ARC_TR_CASE_GRA, NARC_trainer_case_card_1_NCLR, &dat, HEAPID_TR_CARD );
				break;
			case 2:
				buf = ArcUtil_PalDataGet(
					ARC_TR_CASE_GRA, NARC_trainer_case_card_2_NCLR, &dat, HEAPID_TR_CARD );
				break;
			case 3:
				buf = ArcUtil_PalDataGet(
					ARC_TR_CASE_GRA, NARC_trainer_case_card_3_NCLR, &dat, HEAPID_TR_CARD );
				break;
			case 4:
				buf = ArcUtil_PalDataGet(
					ARC_TR_CASE_GRA, NARC_trainer_case_card_4_NCLR, &dat, HEAPID_TR_CARD );
				break;
			case 5:
				buf = ArcUtil_PalDataGet(
					ARC_TR_CASE_GRA, NARC_trainer_case_card_5_NCLR, &dat, HEAPID_TR_CARD );
				break;
			}
		}else{
			buf = ArcUtil_PalDataGet(
					ARC_TR_CASE_GRA, NARC_trainer_case_card_6_NCLR, &dat, HEAPID_TR_CARD );
		}

		{
			u16 * adr;
			DC_FlushRange( dat->pRawData, 2*16*16 );	//16�{�����t���b�V��
			adr = dat->pRawData;
			//16�p���b�g�P�Ԗڂ���3�{�����[�h
			GXS_LoadBGPltt( &adr[16], 2*16, 2*16*3 );
			//f�Ԗڂ̃p���b�g�P�{�����[�h
			GXS_LoadBGPltt( &adr[16*15], 2*16*15, 2*16 );
			sys_FreeMemoryEz(buf);
		}
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �P�[�X�p���b�g�Z�b�g
 *
 * @param	inVersion	�o�[�W����
 *
 * @return	�Ȃ�
 */
//--------------------------------------------------------------------------------------------
static void SetCasePalette(const u8 inVersion)
{
	void *buf;
	NNSG2dPaletteData *dat;
	switch(inVersion){
	case VERSION_DIAMOND:		//�_�C��
		buf = ArcUtil_PalDataGet(
				ARC_TR_CASE_GRA, NARC_trainer_case_card_case_d_NCLR, &dat, HEAPID_TR_CARD );
		break;
	case VERSION_PEARL:		//�p�[��
		buf = ArcUtil_PalDataGet(
				ARC_TR_CASE_GRA, NARC_trainer_case_card_case_p_NCLR, &dat, HEAPID_TR_CARD );
		break;
	default:	//�ʃo�[�W����
		buf = ArcUtil_PalDataGet(
				ARC_TR_CASE_GRA, NARC_trainer_case_card_case_x_NCLR, &dat, HEAPID_TR_CARD );
		break;
	}
		
	DC_FlushRange( dat->pRawData, 2*16 );
	GX_LoadBGPltt( dat->pRawData, 0, 2*16 );
	GXS_LoadBGPltt( dat->pRawData, 0, 2*16 );
	sys_FreeMemoryEz(buf);
}

//--------------------------------------------------------------------------------------------
/**
 * ���j�I���g���[�i�[�p���b�g�Z�b�g
 *
 * @param	inTrainerNo
 *
 * @return	�Ȃ�
 */
//--------------------------------------------------------------------------------------------
static void SetUniTrainerPalette(const u8 inTrainerNo)
{
	void *buf;
	u8 *addr;
	NNSG2dPaletteData *dat;
	buf = ArcUtil_PalDataGet(
			ARC_TR_CASE_GRA, NARC_trainer_case_trdp_union_card_NCLR, &dat, HEAPID_TR_CARD );

	addr = (u8*)(dat->pRawData);
		
	DC_FlushRange(&addr[2*16*inTrainerNo] , 2*16 );
	GXS_LoadBGPltt( &addr[2*16*inTrainerNo], 2*16*UNI_TRAINER_PLTT_NO, 2*16 );
	sys_FreeMemoryEz(buf);
}

//--------------------------------------------------------------------------------------------
/**
 * BG�ݒ�
 *
 * @param	ini		BGL�f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void SetTrCardBg( GF_BGL_INI * ini )
{

	GX_SetDispSelect(GX_DISP_SELECT_SUB_MAIN);
	
	{	// BG SYSTEM
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS, GX_BGMODE_1, GX_BGMODE_4, GX_BG0_AS_2D,
		};
		GF_BGL_InitBG( &BGsys_data );
	}

	{	// FONT (BMP)
		GF_BGL_BGCNT_HEADER ExAffineBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_256,
			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x04000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, TRC_BG_FONT, &ExAffineBgCntDat, GF_BGL_MODE_256X16 );
		GF_BGL_ScrClear( ini, TRC_BG_FONT );
	}

	{	// BG (CASE CHAR)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe000, GX_BG_CHARBASE_0x0c000, GX_BG_EXTPLTT_01,
			3, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, TRC_BG_CASE, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, TRC_BG_CASE );
	}

	{	// BG (CARD CHAR)
		GF_BGL_BGCNT_HEADER AffineBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_256,
			GX_BG_SCRBASE_0xe800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			2, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, TRC_BG_CARD, &AffineBgCntDat, GF_BGL_MODE_AFFINE );
		GF_BGL_ScrClear( ini, TRC_BG_CARD );
	}

	{	// BG (UNDER_CASE CHAR)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe000, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			3, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, TRC_BG_UNDER_CASE, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, TRC_BG_UNDER_CASE );
	}

	{	// BG (UNDER_CASE_COVER CHAR)
		GF_BGL_BGCNT_HEADER AffineBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_256,
			GX_BG_SCRBASE_0xe800, GX_BG_CHARBASE_0x04000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, TRC_BG_COVER, &AffineBgCntDat, GF_BGL_MODE_AFFINE );
		GF_BGL_ScrClear( ini, TRC_BG_COVER );
	}

	
/*
	{	// BUTTON (CHAR)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME0_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME0_S );
	}

	{	// BG (CHAR)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
	}

	GF_BGL_ClearCharSet( GF_BGL_FRAME0_M, 32, 0, HEAPID_POKELIST );
	GF_BGL_ClearCharSet( GF_BGL_FRAME0_S, 32, 0, HEAPID_POKELIST );
*/	
}

//--------------------------------------------------------------------------------------------
/**
 * �O���t�B�b�N�f�[�^�Z�b�g
 *
 * @param	wk		��ʂ̃��[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void SetTrCardBgGraphic( TR_CARD_WORK * wk )
{
	// TRAINER_PALETTE(UP_DISPLAY)
	{
		void *buf;
		NNSG2dPaletteData *dat;
		buf = ArcUtil_PalDataGet(
				ARC_TR_CASE_GRA, NARC_trainer_case_card_0_NCLR, &dat, HEAPID_TR_CARD );
		DC_FlushRange( dat->pRawData, 2*16*16 );
		GXS_LoadBGPltt( dat->pRawData, 0, 2*16*16 );
		sys_FreeMemoryEz(buf);
	}
	
	// CARD PALETTE
	SetCardPalette(wk->TrCardData->CardRank, wk->TrCardData->PokeBookFlg);
	
	// UNSER_CASE_COVER PALETTE(UNDER_DISPLAY)
	{
		void *buf;
		NNSG2dPaletteData *dat;
		buf = ArcUtil_PalDataGet(
				ARC_TR_CASE_GRA, NARC_trainer_case_card_futa_NCLR, &dat, HEAPID_TR_CARD );
		DC_FlushRange( dat->pRawData, 16*2*16 );
		GX_LoadBGPltt( dat->pRawData, 0, 16*2*16 );
		sys_FreeMemoryEz(buf);
	}
	// CASE PALETTE
	SetCasePalette(wk->TrCardData->Version);

	//TRAINER
	if (wk->TrCardData->UnionTrNo == UNION_TR_NONE){
		{
			BOOL rc;
			//�A�[�J�C�u�f�[�^�擾
			wk->TrArcData = ArcUtil_Load(	ARC_TR_CASE_GRA, NARC_trainer_case_card_trainer_NCGR,
											FALSE, HEAPID_TR_CARD, ALLOC_TOP );
			GF_ASSERT(wk->TrArcData!=NULL);
			rc = NNS_G2dGetUnpackedBGCharacterData( wk->TrArcData, &wk->TrCharData);
			GF_ASSERT(rc);
		}
	
		if (wk->TrCardData->TrSex == PM_MALE){
			//�j
			wk->TrScrnArcData = ArcUtil_ScrnDataGet(ARC_TR_CASE_GRA, NARC_trainer_case_card_trainer01_NSCR,
													0, &wk->ScrnData, HEAPID_TR_CARD);
		}else{
			//��
			wk->TrScrnArcData = ArcUtil_ScrnDataGet(ARC_TR_CASE_GRA, NARC_trainer_case_card_trainer02_NSCR,
													0, &wk->ScrnData, HEAPID_TR_CARD);
		}
	}else{
		//���j�I�����[���ő��̐l�̃f�[�^�����鎞
		{
			BOOL rc;
			//�A�[�J�C�u�f�[�^�擾
			wk->TrArcData = ArcUtil_Load(	ARC_TR_CASE_GRA, UniTrTable[wk->TrCardData->UnionTrNo],
											FALSE, HEAPID_TR_CARD, ALLOC_TOP );
			GF_ASSERT(wk->TrArcData!=NULL);
			rc = NNS_G2dGetUnpackedBGCharacterData( wk->TrArcData, &wk->TrCharData);
			GF_ASSERT(rc);

			wk->TrScrnArcData = ArcUtil_ScrnDataGet(ARC_TR_CASE_GRA, NARC_trainer_case_card_test256_NSCR,
													0, &wk->ScrnData, HEAPID_TR_CARD);
			//�g���[�i�[�p���b�g�ύX
			SetUniTrainerPalette(wk->TrCardData->UnionTrNo);
		}
	}
	DispTrainer(wk);

	//CARD
	ArcUtil_BgCharSet(
			ARC_TR_CASE_GRA, NARC_trainer_case_card_NCGR, wk->bgl, TRC_BG_CARD, 0, 0, 0, HEAPID_TR_CARD );
	ArcUtil_ScrnSet(
			ARC_TR_CASE_GRA, NARC_trainer_case_card_faca_NSCR, wk->bgl, TRC_BG_CARD, 0, 0, 0, HEAPID_TR_CARD );
	//CASE
	ArcUtil_BgCharSet(
			ARC_TR_CASE_GRA, NARC_trainer_case_card_case_NCGR, wk->bgl, TRC_BG_CASE, 0, 0, 0, HEAPID_TR_CARD );
	ArcUtil_ScrnSet(
			ARC_TR_CASE_GRA, NARC_trainer_case_card_case_NSCR, wk->bgl, TRC_BG_CASE, 0, 0, 0, HEAPID_TR_CARD );

	//UNDER_CASE
	ArcUtil_BgCharSet(
			ARC_TR_CASE_GRA, NARC_trainer_case_card_case2_NCGR, wk->bgl, TRC_BG_UNDER_CASE, 0, 0, 0, HEAPID_TR_CARD );
	ArcUtil_ScrnSet(
			ARC_TR_CASE_GRA, NARC_trainer_case_card_case2_NSCR, wk->bgl, TRC_BG_UNDER_CASE, 0, 0, 0, HEAPID_TR_CARD );
	//UNDER_CASE_COVER
	ArcUtil_BgCharSet(
			ARC_TR_CASE_GRA, NARC_trainer_case_card_futa_NCGR, wk->bgl, TRC_BG_COVER, 0, 0, 0, HEAPID_TR_CARD );
	ArcUtil_ScrnSet(
			ARC_TR_CASE_GRA, NARC_trainer_case_card_futa_NSCR, wk->bgl, TRC_BG_COVER, 0, 0, 0, HEAPID_TR_CARD );

	//�T�C���W�J
	MakeSignData(wk->TrCardData->SignRawData, wk->TrSignData);

}

//--------------------------------------------------------------------------------------------
/**
 * BG���
 *
 * @param	ini		BGL�f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void TrCardBgExit( GF_BGL_INI * ini )
{
	GF_Disp_GX_VisibleControl(
		GX_PLANEMASK_BG0 | GX_PLANEMASK_BG1 | GX_PLANEMASK_BG2 |
		GX_PLANEMASK_BG3 | GX_PLANEMASK_OBJ, VISIBLE_OFF );
	GF_Disp_GXS_VisibleControl(
		GX_PLANEMASK_BG0 | GX_PLANEMASK_BG1 | GX_PLANEMASK_OBJ, VISIBLE_OFF );

	GF_BGL_BGControlExit( ini, TRC_BG_FONT );
	GF_BGL_BGControlExit( ini, TRC_BG_CARD );
	GF_BGL_BGControlExit( ini, TRC_BG_CASE );
	GF_BGL_BGControlExit( ini, TRC_BG_UNDER_CASE );
	GF_BGL_BGControlExit( ini, TRC_BG_COVER );

	sys_FreeMemoryEz( ini );
}

#define FIRST_SPEED	(8)
//--------------------------------------------------------------------------------------------
/**
 * �J�[�h���Ђ�����Ԃ�
 *
 * @param	wk		��ʂ̃��[�N
 *
 * @return	BOOL	TRUE:�I��	FALSE�F������
 */
//--------------------------------------------------------------------------------------------
static BOOL CardRev( TR_CARD_WORK *wk )
{
	BOOL rc;
	MtxFx22 mtx;
    fx32 rScale_x,rScale_y;
	rc = FALSE;
	switch(wk->sub_seq){
	case 0:
		wk->RevSpeed = FIRST_SPEED;	
		//��������
		//������Ɗg�債��
		wk->CardScaleX = 1 << FX32_SHIFT;
		wk->CardScaleY = 1 << FX32_SHIFT;
		wk->CardScaleX += 2 << (FX32_SHIFT - 6);
		wk->CardScaleY += 2 << (FX32_SHIFT - 6);

		Snd_SePlay( SND_TRCARD_REV );		//�Ђ�����Ԃ���

		wk->sub_seq++;
		break;
	case 1:
		//�����k�߂�
		wk->CardScaleX -= 2 << (REV_SPEED);
		if (wk->CardScaleX <= 0){//�J�[�h�X�N���[���ύX
			wk->CardScaleX = CARD_SCALE_MIN;	//�o�O�\���h�~(�l�̓J�[�h�̌��݂��ێ��ł���ʂ̖ڕ���)
			wk->sub_seq++;
		}

		wk->RevSpeed--;
		if (wk->RevSpeed <=1 ){
			wk->RevSpeed = 1;
		}
		break;
	case 2:
		if (wk->is_back == FALSE){
			wk->is_back = TRUE;
			ArcUtil_ScrnSet(
					ARC_TR_CASE_GRA, NARC_trainer_case_card_back_NSCR, wk->bgl, TRC_BG_CARD, 0, 0, 0, HEAPID_TR_CARD );
			//�\�ʂ�����
			TRCBmp_NonDispWinInfo(wk->win, TRC_BMPWIN_TR_ID, TRC_BMPWIN_START_TIME);
			//�g���[�i�[����
			ClearTrainer(wk);
			//�X�N���[���N���A
			GF_BGL_ScrClear( wk->bgl, TRC_BG_SIGHN );
			//���ʕ\��
			TRCBmp_WriteTrWinInfoRev( wk->win, wk->TrCardData );
			TransSignData(wk->bgl,TRC_BG_SIGHN, wk->TrSignData);
		}else{
			wk->is_back = FALSE;
			ArcUtil_ScrnSet(
					ARC_TR_CASE_GRA, NARC_trainer_case_card_faca_NSCR, wk->bgl, TRC_BG_CARD, 0, 0, 0, HEAPID_TR_CARD );
			//���ʂ�����
			TRCBmp_NonDispWinInfo(wk->win, TRC_BMPWIN_CLEAR_TIME, TRC_BMPWIN_TRADE_INFO);
			//�X�N���[���N���A
			GF_BGL_ScrClear( wk->bgl, TRC_BG_TRAINER );
			//�g���[�i�[�\��
			DispTrainer(wk);
			//�\�ʕ\��
			TRCBmp_WriteTrWinInfo( wk->win, wk->TrCardData );
		}
		wk->sub_seq++;
		break;
	case 3:
		//�����L����
		wk->RevSpeed++;
		if(wk->RevSpeed > FIRST_SPEED){
			wk->RevSpeed = FIRST_SPEED;
		}

		wk->CardScaleX += 2 << (REV_SPEED);
		if (wk->CardScaleX >= (1 << FX32_SHIFT)){
			wk->CardScaleX = 1 << FX32_SHIFT;
			//���̃T�C�Y��
			wk->CardScaleX = 1 << FX32_SHIFT;
			wk->CardScaleY = 1 << FX32_SHIFT;

			//Snd_SePlay( SND_TRCARD_REV_AFTER );		//�Ђ�����Ԃ�����\����
			rc = TRUE;
		}
		break;
	}

	rScale_x = FX_Inv(wk->CardScaleX);
	rScale_y = FX_Inv(wk->CardScaleY);
    mtx._00 = rScale_x;
    mtx._01 = 0;
    mtx._10 = 0;
    mtx._11 = rScale_y;
    SVC_WaitVBlankIntr();          // Waiting the end of VBlank interrup
	G2S_SetBG2Affine(&mtx,          // a matrix for rotation and scaling
                        128, 96,      // the center of rotation
                        0, 0           // the reference point before rotation and scaling applied
            );
	G2S_SetBG3Affine(&mtx,          // a matrix for rotation and scaling
                        128, 96,      // the center of rotation
                        0, 0           // the reference point before rotation and scaling applied
            );

	return rc;
}

/**
static const fx32 CoverSpeed[] =
{
	2 << (FX32_SHIFT - 11),
	2 << (FX32_SHIFT - 11),
	2 << (FX32_SHIFT - 7),
	2 << (FX32_SHIFT - 7),
	2 << (FX32_SHIFT - 6),
	2 << (FX32_SHIFT - 6),
	2 << (FX32_SHIFT - 5),
	2 << (FX32_SHIFT - 5),
	2 << (FX32_SHIFT - 4),
	2 << (FX32_SHIFT - 4),
	2 << (FX32_SHIFT - 4),
	2 << (FX32_SHIFT - 4),
	2 << (FX32_SHIFT - 4),
	1 << (FX32_SHIFT - 4),
	1 << (FX32_SHIFT - 4),
	1 << (FX32_SHIFT - 4),
};

#define COVER_MOVE	(16)
*/

static const fx32 CoverSpeed[] =
{
	2 << (FX32_SHIFT - 6),
	2 << (FX32_SHIFT - 6),
	2 << (FX32_SHIFT - 6),
	2 << (FX32_SHIFT - 6),
	2 << (FX32_SHIFT - 6),
	2 << (FX32_SHIFT - 5),
	2 << (FX32_SHIFT - 5),
	2 << (FX32_SHIFT - 5),
	2 << (FX32_SHIFT - 5),
	2 << (FX32_SHIFT - 5),
	2 << (FX32_SHIFT - 4),
	2 << (FX32_SHIFT - 4),
	2 << (FX32_SHIFT - 4),
	2 << (FX32_SHIFT - 4),
};

#define COVER_MOVE	(14)



//--------------------------------------------------------------------------------------------
/**
 * �P�[�X�J�o�[�̊J��
 *
 * @param	wk		��ʂ̃��[�N
 *
 * @return	BOOL	TRUE:�I��	FALSE�F������
 */
//--------------------------------------------------------------------------------------------

static BOOL CoverOpenClose(TR_CARD_WORK *wk)
{
	MtxFx22 mtx;
    fx32 rScale_x,rScale_y;

	switch(wk->sub_seq){
	case 0:
		wk->Counter = 0;		
		if (wk->IsOpen == COVER_CLOSE){
			wk->CoverScaleY = 1 << FX32_SHIFT;
			wk->sub_seq = 1;
		}else{
			wk->sub_seq = 2;
		}
		PlayButtonAndCoverSnd(wk->IsOpen);
		break;
	case 1:		
		//�J����
		wk->CoverScaleY -= CoverSpeed[wk->Counter++];///2 << (FX32_SHIFT - 4);
		if (wk->Counter==COVER_MOVE){//�J�[�h�X�N���[���ύX
			wk->IsOpen = COVER_OPEN;		//�J�������
			wk->sub_seq = 3;
		}
		break;
	case 2:
		//�߂�
		wk->CoverScaleY += CoverSpeed[(COVER_MOVE-1)-(wk->Counter++)];///2 << (FX32_SHIFT - 4);
		
		if (wk->Counter == COVER_MOVE){//�J�[�h�X�N���[���ύX
			wk->IsOpen = COVER_CLOSE;		//�������
			wk->CoverScaleY = (1 << FX32_SHIFT);
			wk->sub_seq = 3;
		}
		break;
	case 3:	
		return TRUE;
	}

	rScale_x = FX_Inv(1 << FX32_SHIFT);
	rScale_y = FX_Inv(wk->CoverScaleY);
    mtx._00 = rScale_x;
    mtx._01 = 0;
    mtx._10 = 0;
    mtx._11 = rScale_y;
    SVC_WaitVBlankIntr();          // Waiting the end of VBlank interrup
	G2_SetBG3Affine(&mtx,          // a matrix for rotation and scaling
                        128, 0,      // the center of rotation
                        0, 0           // the reference point before rotation and scaling applied
            );

	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * �L�[����
 *
 * @param	wk		��ʂ̃��[�N
 *
 * @return	int		���N�G�X�g
 */
//--------------------------------------------------------------------------------------------
static int CheckKey(TR_CARD_WORK *wk)
{
	int key_req;
	BOOL tp_key_flg;
	tp_key_flg = FALSE;
	key_req = TRC_KEY_REQ_NONE;

	wk->touch = RECT_HIT_NONE;

#ifdef PM_DEBUG
/**	
	if (sys.trg & PAD_BUTTON_R){
		if ( (wk->TrCardData->PokeBookFlg == 0)&&(wk->TrCardData->CardRank == 0) ){
			wk->TrCardData->PokeBookFlg = 1;
		}else{
			wk->TrCardData->CardRank = (wk->TrCardData->CardRank+1)%6;
			if (wk->TrCardData->CardRank == 0){
				wk->TrCardData->PokeBookFlg = 0;
			}
		}
		SetCardPalette(wk->TrCardData->CardRank, wk->TrCardData->PokeBookFlg);
		return key_req;
	}
	
	if (sys.trg & PAD_BUTTON_L){
		if (wk->TrCardData->Version == VERSION_DIAMOND){
			wk->TrCardData->Version = VERSION_PEARL;
		}else if(wk->TrCardData->Version == VERSION_PEARL){
			wk->TrCardData->Version = VERSION_DP_NEXT;
		}else{
			wk->TrCardData->Version = VERSION_DIAMOND;
		}
		SetCasePalette(wk->TrCardData->Version);
		return key_req;
	}
*/	
#endif
	if (sys.tp_trg){
///		OS_Printf("xy=%d,%d\n",sys.tp_x,sys.tp_y);
		wk->brushOK = TRUE;	//�o�b�W�����\
	}
	
///	wk->touch = GF_TP_RectHitTrg( TpHit[wk->TrCardData->BrushValid].CoverTpRect[wk->IsOpen] );
	wk->touch = CheckTpBadgeTrg( wk->bgl, TpHit[wk->TrCardData->BrushValid].CoverTpRect[wk->IsOpen] );
	//�q�b�g����
	if (wk->touch != RECT_HIT_NONE){	//�^�b�`�p�l���g���K�[����
///		OS_Printf("hit=%d\n",wk->touch);
		tp_key_flg = TRUE;	//�^�b�`�p�l�����N�G�X�g
		key_req = TRC_KEY_REQ_TP_BEAT;
	}else if (sys.tp_cont){	//�^�b�`�p�l���x�^��������
///		wk->touch = GF_TP_RectHitCont( TpHit[wk->TrCardData->BrushValid].CoverTpRect[wk->IsOpen] );
		wk->touch = CheckTpBadgeCont( wk->bgl, TpHit[wk->TrCardData->BrushValid].CoverTpRect[wk->IsOpen] );
		if (wk->brushOK){
			tp_key_flg = TRUE;	//�^�b�`�p�l�����N�G�X�g
			key_req = TRC_KEY_REQ_TP_BRUSH;
		}
	}else{	//�^�b�`�p�l���G���Ă��Ȃ�
		wk->brushOK = FALSE;	//�o�b�W�����s�\
	}

	//�^�b�`�p�l���L�[���N�����Ă��Ȃ���΃{�^������
	if (tp_key_flg == FALSE){
		if ( sys.trg & PAD_BUTTON_DECIDE ){
			key_req = TRC_KEY_REQ_REV_BUTTON;
		}else if ( sys.trg & PAD_BUTTON_CANCEL ){
			key_req = TRC_KEY_REQ_END_BUTTON;
		}
	}

	return key_req;
}

//--------------------------------------------------------------------------------------------
/**
 * �o�b�W����
 *
 * @param	wk		��ʂ̃��[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BrushBadge(TR_CARD_WORK *wk)
{
	BOOL scruch;
	int sub;
	scruch = FALSE;
	//�ێ����W�ƃ^�b�`���W�̍��������
	if( (sys.tp_x!=0xffff)&&(sys.tp_y!=0xffff)&&
			(wk->BeforeX!=0xffff)&&(wk->BeforeY!=0xffff) ){	//�l�L�����H
		//�ێ����W�ƃ^�b�`���W�������o�b�W���ɂ��邩�𒲂ׂ�
		if ( (wk->touch!=RECT_HIT_NONE)&&(wk->touch!=CASE_BUTTON) ){
			//�o�b�W���L����
			if (wk->TrCardData->BadgeData[wk->touch-1].BadgeHold){
				//�������K��l�ȏ�̏ꍇ�͖��������Ƃɂ���
				if ( wk->BeforeX > sys.tp_x ){		//�O��̂ق����l���傫�����H
					sub = wk->BeforeX - sys.tp_x;
					wk->ScruchSnd.DirX = -1;
				}else{
					sub = sys.tp_x - wk->BeforeX;
					wk->ScruchSnd.DirX = 1;
				}
				if ( (sub>=MIN_SCRUCH)&&(sub<=MAX_SCRUCH) ){
					if ( wk->BeforeY > sys.tp_y ){	//�O��̂ق����l���傫�����H
						sub = wk->BeforeY - sys.tp_y;
						wk->ScruchSnd.DirY = -1;
					}else{
						sub = sys.tp_y - wk->BeforeY;
						wk->ScruchSnd.DirY = 1;
					}
					if (sub<=MAX_SCRUCH){
						scruch = TRUE;			//��������
						PlayScruchSnd(&wk->ScruchSnd);
					}else{
						ClearScruchSndNow(&wk->ScruchSnd);
					}
				}else if (sub<=MAX_SCRUCH){
					if ( wk->BeforeY > sys.tp_y ){		//�O��̂ق����l���傫�����H
						sub = wk->BeforeY - sys.tp_y;
						wk->ScruchSnd.DirY = -1;
					}else{
						sub = sys.tp_y - wk->BeforeY;
						wk->ScruchSnd.DirY = 1;
					}
					if ((sub>=MIN_SCRUCH)&&(sub<=MAX_SCRUCH)){
						scruch = TRUE;		//��������
						PlayScruchSnd(&wk->ScruchSnd);
					}else{
						ClearScruchSndNow(&wk->ScruchSnd);
					}
				}

				if (scruch){
///					OS_Printf("scruch_%d\n",wk->touch);
///					OS_Printf("sc=%d,%d-%d,%d\n",wk->BeforeX,wk->BeforeY,sys.tp_x,sys.tp_y);
					//���������ԍX�V
					//���x���X�V
					BadgeLvUp(wk, wk->touch-1);
					OS_Printf("temp_scruch:%d\n",wk->ScruchCounter[wk->touch-1]);
					OS_Printf("brush=%d,%d\n",wk->touch,wk->TrCardData->BadgeData[wk->touch-1].BadgeScruchCount);
				}
			}
		}
	}
		//�ێ����W�X�V
	wk->BeforeX = sys.tp_x;
	wk->BeforeY = sys.tp_y;
}

//--------------------------------------------------------------------------------------------
/**
 * �{�^���ύX
 *
 * @param	wk			��ʂ̃��[�N
 * @param	inAnmNum	�A�j���i���o�[
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ChangeBgButton(TR_CARD_WORK *wk, const u8 inAnmNum)
{
    u16 * buf;
    u16 start;
    u8  x, y;
    
    buf   = (u16 *)GF_BGL_ScreenAdrsGet( wk->bgl, TRC_BG_UNDER_CASE );
	start = BUTTON_CGX_POS+(MAIN_BUTTON_CGX_SIZE*inAnmNum);

    for( y=0; y<MAIN_BUTTON_CGX_SIZE; y++ ){
        for( x=0; x<MAIN_BUTTON_CGX_SIZE; x++ ){
            buf[ (y+MAIN_BUTTON_POS_Y)*TRC_SCREEN_WIDTH + x+MAIN_BUTTON_POS_X ] = start+y*CGX_WIDE+x + (0<<12);
        }
    }
	GF_BGL_LoadScreenReq( wk->bgl, TRC_BG_UNDER_CASE );
}

#define GYM_READER_ST_SCR_POS_X	(3)		//�X�N���[���J�n���WX(�L�����P��)
#define GYM_READER_ST_SCR_POS_Y	(4)		//�X�N���[���J�n���WY(�L�����P��)
#define GYM_READER_SCR_OFFSET	(7)		//�W�����[�_�[�\���Ԋu(�L�����P��)
#define GYM_READER_SIDE_NUM		(4)		//�W�����[�_�[���\���l��

//--------------------------------------------------------------------------------------------
/**
 * �W�����[�_�[�獷���ւ�
 *
 * @param	wk		��ʂ̃��[�N
 * @param	inNo	���[�_�[�i���o�[
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ChangeBgGymReader(TR_CARD_WORK *wk, const u8 inNo)
{
    u8 * buf;
    u16 start;
    u8  x, y;
    
	u8 dst_start_x,pos_x;
	u8 dst_start_y,pos_y;

	dst_start_x = GYM_READER_ST_SCR_POS_X;
	dst_start_y = GYM_READER_ST_SCR_POS_Y;

	pos_x = inNo%GYM_READER_SIDE_NUM;
	pos_y = inNo/GYM_READER_SIDE_NUM;

	dst_start_x += (pos_x*GYM_READER_SCR_OFFSET);
	dst_start_y += (pos_y*GYM_READER_SCR_OFFSET);

    buf   = (u8 *)GF_BGL_ScreenAdrsGet( wk->bgl, TRC_BG_COVER );
	start = NOBODY_CGX_POS;

    for( y=0; y<GYM_READER_CGX_SIZE; y++ ){
        for( x=0; x<GYM_READER_CGX_SIZE	; x++ ){
            buf[ (y+dst_start_y)*TRC_SCREEN_WIDTH + x+dst_start_x ] = start+y*COVER_CGX_WIDTH+x;
        }
    }
}


//--------------------------------------------------------------------------------------------
/**
 * VBlank�֐�
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VBlankFunc( void * work )
{
	// �Z���A�N�^�[
	// Vram�]���}�l�[�W���[���s
	DoVramTransferManager();

	// �����_�����LOAM�}�l�[�W��Vram�]��
	REND_OAMTrans();	
	
	OS_SetIrqCheckFlag( OS_IE_V_BLANK );
}

//--------------------------------------------------------------------------------------------
/**
 * �o�b�W���x���A�b�v
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BadgeLvUp(TR_CARD_WORK *wk, const u8 inBadgeNo)
{
	int count;
	u8 lv, old_lv;
	
	count = (wk->TrCardData->BadgeData[inBadgeNo].BadgeScruchCount)+1;

	if (count<COUNT_LV4){
		old_lv = GetBadgeLevel(wk->TrCardData->BadgeData[inBadgeNo].BadgeScruchCount);

		wk->ScruchCounter[inBadgeNo]++;
		if (wk->ScruchCounter[inBadgeNo] >= TempScruchMax[old_lv]){
			wk->ScruchCounter[inBadgeNo] = 0;
			(wk->TrCardData->BadgeData[inBadgeNo].BadgeScruchCount)++;
		
			lv = GetBadgeLevel(count);
			GF_ASSERT(old_lv<=lv&&"error");
			if (old_lv < lv){		//�����āA���x�����オ�����ꍇ
				if (lv <= TR_CARD_BADGE_LV_MAX){
					if (lv == TR_CARD_BADGE_LV_MAX){	//�o�b�W���x�����ō��̂Ƃ��́A1�i�K���̃��x���̃p���b�g���g�p
						SetBadgePalette(&wk->ObjWork, inBadgeNo, 0);
					}else{
						SetBadgePalette(&wk->ObjWork, inBadgeNo, BADGE_BAD_PLTT_NO-lv);
					}
				}
				//���A�N�^�[�\��
				if (lv == TR_CARD_BADGE_LV_MAX-1){
					CLACT_SetDrawFlag(wk->ObjWork.ClActWork[TR_CARD_STAR_ACT_START+inBadgeNo], 1);	//�\��
				}else if(lv == TR_CARD_BADGE_LV_MAX){
					CLACT_SetDrawFlag(wk->ObjWork.ClActWork[TR_CARD_STAR_ACT_START+inBadgeNo], 0);	//��\��
					CLACT_SetDrawFlag(wk->ObjWork.ClActWork[TR_CARD_GRATE_STAR_ACT_START+inBadgeNo], 1);	//�\��
				}
			}
		}
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �g�k�ʃ��Z�b�g
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ResetAffinePlane(void)
{
	MtxFx22 mtx;
    fx32 rScale_x,rScale_y;
	
	rScale_x = FX_Inv((1 << FX32_SHIFT));
	rScale_y = FX_Inv((1 << FX32_SHIFT));
    mtx._00 = rScale_x;
    mtx._01 = 0;
    mtx._10 = 0;
    mtx._11 = rScale_y;
    SVC_WaitVBlankIntr();          // Waiting the end of VBlank interrup
	G2S_SetBG2Affine(&mtx,          // a matrix for rotation and scaling
                        128, 96,      // the center of rotation
                        0, 0           // the reference point before rotation and scaling applied
            );
	G2S_SetBG3Affine(&mtx,          // a matrix for rotation and scaling
                        128, 96,      // the center of rotation
                        0, 0           // the reference point before rotation and scaling applied
            );
	SVC_WaitVBlankIntr();          // Waiting the end of VBlank interrup
	G2_SetBG3Affine(&mtx,          // a matrix for rotation and scaling
                        128, 0,      // the center of rotation
                        0, 0           // the reference point before rotation and scaling applied
            );
}


//--------------------------------------------------------------------------------------------
/**
 * �{�^���A�j���R���g���[��
 *
 * @param	wk			��ʂ̃��[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ButtonAnimeControl(TR_CARD_WORK *wk)
{
	if (wk->AnimeType == ANIME_BUTTON_PUSH){
		//�{�^����������
		if( PushButton(wk, ButtonAnime[0]) ){
			wk->AnimeType = ANIME_NOTHING;
		}
	}else if (wk->AnimeType == ANIME_BUTTON_PULL){
		//�{�^���߂�
		if( PushButton(wk, ButtonAnime[1]) ){
			wk->AnimeType = ANIME_NOTHING;
		}
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �{�^���A�j��
 *
 * @param	wk			��ʂ̃��[�N
 * @param	inAnime		�A�j���e�[�u��
 *
 * @return	BOOL	TRUE:�I��	FALSE�F������
 */
//--------------------------------------------------------------------------------------------
static BOOL PushButton(TR_CARD_WORK *wk, const u8 *inAnime)
{
	u8 frame,num;
	frame = inAnime[wk->AnmNum*2];
	if (frame == 0){
		//�I��
		wk->ButtonAnmCount = 0;
		wk->AnmNum = 0;
		return TRUE;
	}else if (wk->ButtonAnmCount>=frame){
		wk->ButtonAnmCount = 0;
		wk->AnmNum++;
	}
	
	num = inAnime[wk->AnmNum*2+1];
	if (wk->ButtonAnmCount == 0){
		ChangeBgButton(wk, num);
	}
	wk->ButtonAnmCount++;

	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * �g���[�i�[�X�N���[���]��
 *
 * @param	wk			��ʂ̃��[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void DispTrainer(TR_CARD_WORK *wk)
{
	u32 transSize;
	
	transSize = wk->ScrnData->szByte;
	
	//TRAINER
	GF_BGL_LoadCharacter(wk->bgl, TRC_BG_TRAINER, wk->TrCharData->pRawData, wk->TrCharData->szByte, 0);
	
	if( GF_BGL_ScreenAdrsGet( wk->bgl, TRC_BG_TRAINER ) != NULL ){
		GF_BGL_ScreenBufSet( wk->bgl, TRC_BG_TRAINER, wk->ScrnData->rawData, transSize );
	}
	
	GF_BGL_LoadScreen( wk->bgl, TRC_BG_TRAINER, wk->ScrnData->rawData, transSize, 0 );
}

//--------------------------------------------------------------------------------------------
/**
 * �g���[�i�[�X�N���[���N���A
 *
 * @param	wk			��ʂ̃��[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ClearTrainer(TR_CARD_WORK *wk)
{
	GF_BGL_ScrFill(wk->bgl, TRC_BG_TRAINER, 0, 20, 6, 6, 9, GF_BGL_SCRWRT_PALNL);
}

//--------------------------------------------------------------------------------------------
/**
 * �o�b�W���x���擾
 *
 * @param	inCount			������
 *
 * @return	u8				���x��
 */
//--------------------------------------------------------------------------------------------
static const u8 GetBadgeLevel(const int inCount)
{
	u8 lv;
	if ((0<=inCount)&&(inCount<COUNT_LV0)){
		lv = 0;
	}else if(inCount<COUNT_LV1){
		lv =1;
	}else if (inCount<COUNT_LV2){
		lv = 2;
	}else if (inCount<COUNT_LV3){
		lv = 3;
	}else if (inCount<COUNT_LV4){
		lv = 4;
	}else{
		GF_ASSERT(0&&"BadgeLevelOver");
		lv = 0;
	}
	return lv;
}

//--------------------------------------------------------------------------------------------
/**
 * �o�b�W�����艹���䂷�邽�߂̌��ݕ������N���A
 *
 * @param	*outScruchSnd	�o�b�W�����艹�\���̂ւ̃|�C���^
 *
 * @return	none	
 */
//--------------------------------------------------------------------------------------------
static void ClearScruchSndNow(TR_SCRUCH_SND *outScruchSnd)
{
	outScruchSnd->DirX = 0;
	outScruchSnd->DirY = 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �o�b�W�����艹���䂷�邽�߂̃f�[�^���N���A
 *
 * @param	*outScruchSnd	�o�b�W�����艹�\���̂ւ̃|�C���^
 *
 * @return	none	
 */
//--------------------------------------------------------------------------------------------
static void ClearScruchSnd(TR_SCRUCH_SND *outScruchSnd)
{
	outScruchSnd->OldDirX = 0;
	outScruchSnd->OldDirY = 0;
	outScruchSnd->DirX = 0;
	outScruchSnd->DirY = 0;
	outScruchSnd->Snd = 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �o�b�W�����艹�Đ�
 *
 * @param	*ioScruchSnd	�o�b�W�����艹�\���̂ւ̃|�C���^
 *
 * @return	none	
 */
//--------------------------------------------------------------------------------------------
static void PlayScruchSnd(TR_SCRUCH_SND *ioScruchSnd)
{
	int snd_list[2] = {
		SND_TRCARD_SCRUCH01,
		SND_TRCARD_SCRUCH02
	};
	//���񔻒�
	if ((ioScruchSnd->OldDirX == 0)&&(ioScruchSnd->OldDirY == 0)){
///		OS_Printf("����\n");//����
		Snd_SePlay( SND_TRCARD_SCRUCH01 );
	}
	//�O��̕����ƍ���̕������r
	if ((ioScruchSnd->OldDirX*ioScruchSnd->DirX<0) ||
			(ioScruchSnd->OldDirY*ioScruchSnd->DirY<0)){
///		OS_Printf("�؂�ւ�\n");//�������ς�����̂ŉ���؂�ւ���
		ioScruchSnd->Snd = (ioScruchSnd->Snd+1)%2;
		Snd_SePlay( snd_list[ioScruchSnd->Snd] );
	}

	ioScruchSnd->OldDirX = ioScruchSnd->DirX;
	ioScruchSnd->OldDirY = ioScruchSnd->DirY;
	ioScruchSnd->DirX = 0;
	ioScruchSnd->DirY = 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �T�C���f�[�^�쐬
 *
 * @param	*inRawData	�r�b�g�P�ʂŎ����Ă���T�C���f�[�^
 * @param	*outData	�T�C���f�[�^�i�[�ꏊ
 *
 * @return	none	
 */
//--------------------------------------------------------------------------------------------
static void MakeSignData(const u8 *inRawData, u8 *outData)
{
	
	int dot,raw_dot;
	u8 raw_line;	//0�`7
	u8 shift;		//0�`7
	for(dot=0;dot<SIGN_SIZE_X*SIGN_SIZE_Y*64;dot++){
		raw_dot = dot/64;
		raw_line = (dot/8)%8;
		shift = (dot%8);
		outData[dot] = ( 0x01 & (inRawData[(raw_dot*8)+raw_line]>>shift) );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �T�C���f�[�^�]��
 *
 * @param	bgl				bgl
 * @param	inFrame			�Ώۃt���[��
 * @param	inSignData		�T�C���f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void TransSignData(GF_BGL_INI * bgl,const int inFrame, const u8 *inSignData)
{
	u16 *buf;
	u8 x,y;
	u16 count;
	
	GF_BGL_LoadCharacter( bgl, inFrame, inSignData, SIGN_BYTE_SIZE, SIGN_CGX );
	
	buf   = (u16 *)GF_BGL_ScreenAdrsGet( bgl, inFrame );
	
	count = 0;
	for( y=0; y<SIGN_SY; y++ ){
        for( x=0; x<SIGN_SX; x++ ){
            buf[ (SIGN_PY+y)*TRC_SCREEN_WIDTH + x+SIGN_PX ] = (SIGN_CGX+count);
			count++;
        }
    }
	GF_BGL_LoadScreenReq( bgl, inFrame );
}

//--------------------------------------------------------------------------------------------
/**
 * �{�^�������ƃJ�o�[�J��
 *
 * @param	inIsOpen		�J�o�[�̏��
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void PlayButtonAndCoverSnd(const COVER_STATE inIsOpen)
{
	//Snd_SePlay(SND_TRCARD_BUTTON);	//�{�^����
	if (inIsOpen == COVER_OPEN){	//�J�o�[�J���Ă���	
		Snd_SePlay(SND_TRCARD_CASE_CL);//�J�o�[�߂鉹
	}else{			//�J�o�[���Ă�
		Snd_SePlay(SND_TRCARD_CASE_OP);	//�J�o�[�J���鉹
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �v���C���ԍX�V
 *
 * @param	wk				��ʂ̃��[�N
 * @param	inUpdateFlg		���ԍX�V�t���O
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void UpdatePlayTime(TR_CARD_WORK *wk, const u8 inUpdateFlg)
{
	//�X�V�t���O�������Ă��邩���`�F�b�N
	if (!inUpdateFlg){
		return;
	}
	
	if (!wk->is_back){	//�\�ʂ̏ꍇ�̂ݕ`��
		if (wk->SecCount == 0){
			TRCBmp_WritePlayTime(wk->win, wk->TrCardData, wk->PlayTimeBuf);
			//�R�����`��
			TRCBmp_WriteSec(&(wk->win[TRC_BMPWIN_PLAY_TIME]), TRUE, wk->SecBuf);
		}else if(wk->SecCount == 15){
			//�R��������
			TRCBmp_WriteSec(&(wk->win[TRC_BMPWIN_PLAY_TIME]), FALSE, wk->SecBuf);
		}
	}
	//�J�E���g�A�b�v
	wk->SecCount = (wk->SecCount+1)%30;		//	1/30�Ȃ̂�
}

//--------------------------------------------------------------------------------------------
/**
 * �o�b�W�q�b�g����(�g���K�[)
 *
 * @param	bgl
 * @param	hitTbl		�q�b�g��`
 *
 * @return	int			����
 */
//--------------------------------------------------------------------------------------------
static int CheckTpBadgeTrg(GF_BGL_INI * bgl, const RECT_HIT_TBL *hitTbl)
{
	int	ret = GF_TP_RectHitTrg( hitTbl );

	if( ret != RECT_HIT_NONE ){
		if (ret != CASE_BUTTON){
			u16	pat = 0x40;
			if( GF_BGL_DotCheck( bgl, TRC_BG_UNDER_CASE, sys.tp_x, sys.tp_y, &pat ) == FALSE ){
				return RECT_HIT_NONE;
			}
		}else{
			return ret;
		}
	}
	return ret;
}

//--------------------------------------------------------------------------------------------
/**
 * �o�b�W�q�b�g����(�x�^)
 *
 * @param	bgl
 * @param	hitTbl		�q�b�g��`
 *
 * @return	int			����
 */
//--------------------------------------------------------------------------------------------
static int CheckTpBadgeCont(GF_BGL_INI * bgl, const RECT_HIT_TBL *hitTbl)
{
	int	ret = GF_TP_RectHitCont( hitTbl );

	if( ret != RECT_HIT_NONE ){
		if (ret != CASE_BUTTON){
			u16	pat = 0x40;
			if( GF_BGL_DotCheck( bgl, TRC_BG_UNDER_CASE, sys.tp_x, sys.tp_y, &pat ) == FALSE ){
				return RECT_HIT_NONE;
			}
		}else{
			return ret;
		}
	}
	return ret;
}

