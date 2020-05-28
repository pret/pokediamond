//******************************************************************************
/**
 *
 * @file	slot_main.c
 * @brief	�~�j�Q�[���@�X���b�g�@���C��
 * @author	kagaya
 * @data	05.07.13
 *
 */
//******************************************************************************
#include "common.h"
#include "slot_local.h"

//==============================================================================
//	define
//==============================================================================
//--------------------------------------------------------------
//	DEBUG
//--------------------------------------------------------------
//----
#ifdef DEBUG_ON_SLOT
//----
//#define DEBUG_DDISPTEST							//����ʃe�X�g
//#define DEBUG_BONUS_COUNT_TEST (4)				//�����{�[�i�X�ő��
//#define DEBUG_LOTTERY_S_FORCE (LOTTERY_HITBIT_BELL)	//������
//#define DEBUG_LOTTERY_S_RND
//----
#endif
//----

//--------------------------------------------------------------
///	�܂���
//--------------------------------------------------------------
#define FADE_CHANGE( before, after, evy )					\
			( before + ( ( after - before ) * evy >> 4 ) )

//--------------------------------------------------------------
//	�V���{��
//--------------------------------------------------------------
#define PAD_KEYALL (PAD_KEY_UP|PAD_KEY_DOWN|PAD_KEY_LEFT|PAD_KEY_RIGHT)	///<�L�[�S����
#define PAD_END 		(PAD_BUTTON_START)			///<�I���{�^��
#define PAD_BET 		(PAD_BUTTON_X)				///<�x�b�h�{�^��
#define PAD_GAMESTART	(PAD_KEY_DOWN|PAD_BUTTON_X)	///<�Q�[���J�n�{�^��

#define PAD_REELPUSH0	(PAD_BUTTON_Y)
#define PAD_REELPUSH1	(PAD_BUTTON_B)
#define PAD_REELPUSH2	(PAD_BUTTON_A)

#define PAD_PAYOUT_SKIP	(PAD_BUTTON_X)				///<�x�����X�L�b�v�{�^��

#define REEL_SPEED_DEF (NUM_FX32(16))				///<���[���X�s�[�h
//#define REEL_SPEED_DEF (NUM_FX32(1))				///<���[���X�s�[�h

#define SLIP_MAX (4)								///<�X�x���ő�

#ifdef DEBUG_BONUS_COUNT_TEST
#define BONUS_GAME_COUNT (DEBUG_BONUS_COUNT_TEST)
#else
#define BONUS_GAME_COUNT (15)
#endif

#define LINE_EVY_BET (10)
#define LINE_EVY_BET_1 (12)

//--------------------------------------------------------------
///	���o�n
//--------------------------------------------------------------
///�{�^�������J�n�܂ł̃E�F�C�g
#define GE_FXFRAME_BTN_PUSHWAIT (NUM_FX32(8))

#define PUSHWAIT (GE_FXFRAME_BTN_PUSHWAIT)

///�ʏ�Q�[���@���I�����~�X���̃E�F�C�g
#define GE_FXFRAME_NOHIT_MISS_WAIT (NUM_FX32(8))
///�ʏ�Q�[���@�q���q�b�g���̃{�[���߂�J�n�t���[��
#define GE_FXFRAME_HITS_BALL_BACK_START (NUM_FX32(30))
///�ʏ�Q�[���@���v���C�q�b�g���̃{�[���߂�J�n�t���[��
#define GE_FXFRAME_HITRP_BALL_BACK_START (NUM_FX32(15))
///�ʏ�Q�[���@�{�[�i�X���[�h�q�����̃s�b�s�o��J�n�t���[��
#define GE_FXFRAME_HITBMODE_PIP_START (NUM_FX32(30))
///�ʏ�Q�[���@�{�[�i�X���[�h���v���C���̃s�b�s�o��t���[��
#define GE_FXFRAME_HITBMODE_REPLAY_PIP_START (NUM_FX32(8))

//--------------------------------------------------------------
///	�Q�[���v���Z�X�߂�l
//--------------------------------------------------------------
typedef enum
{
	RET_NON = 0,///<���ɖ���
	RET_NEXT,	///<����
	RET_END,	///<�I��
}GAMERET;

//--------------------------------------------------------------
///	�L�[�߂�l
//--------------------------------------------------------------
typedef enum
{
	PAD_NON = 0,	///<�����薳��
	PAD_ON,			///<������L��
	PAD_SAME,		///<��v
}PADRET;

//--------------------------------------------------------------
///	���C���p���b�g�A�j���߂�l
//--------------------------------------------------------------
enum
{
	LINERET_START = 0,
	LINERET_UP,
};

//--------------------------------------------------------------
///	����������
//--------------------------------------------------------------
typedef enum
{
	MOON_LIGHT = 0,	//����
	MOON_RED,		//��
}MOONTYPE;

//--------------------------------------------------------------
///	�Ԃ����t���O
//--------------------------------------------------------------
typedef enum
{
	MOONRED_NON,		//�Ԃ����������Ė���
	MOONRED_HIT,		//�Ԃ�����������
	MOONRED_SUCCESS,	//�Ԃ�����������
	MOONRED_MISS,
}MOONRED;

//--------------------------------------------------------------
///	�Q�[���V�[�P���X
//--------------------------------------------------------------
enum
{
	//�ʏ�Q�[��
	SEQNO_GAME_INIT = 0,
	SEQNO_BET,
	SEQNO_GAME_START_BUTTON_PUSH_WAIT,
	SEQNO_GAME_START,
	SEQNO_REELPUSH_START_WAIT,
	SEQNO_REELPUSH,
	SEQNO_REELSTOP_WAIT,
	SEQNO_HIT_CHECK,
	SEQNO_NOHIT_MISS_START,
	SEQNO_NOHIT_MISS_WAIT_NEXT,
	SEQNO_HIT_MISS_START,
	SEQNO_HIT_MISS_WAIT_NEXT,
	SEQNO_HIT_PAYOUT_START,
	SEQNO_HIT_PAYOUT_WAIT_NEXT,
	SEQNO_HIT_REPLAY_START,
	SEQNO_HIT_REPLAY_WAIT_NEXT,
	SEQNO_HIT_MISS_BONUS_START,
	SEQNO_HIT_MISS_BONUS_BALL_STOP_WAIT,
	SEQNO_HIT_MISS_BONUS_WAIT_NEXT,
	SEQNO_HIT_PAYOUT_BONUS_START,
	SEQNO_HIT_PAYOUT_BONUS_WAIT_NEXT,
	SEQNO_HIT_REPLAY_BONUS_START,
	SEQNO_HIT_REPLAY_BONUS_WAIT_NEXT,
	//�{�[�i�X���[�h
	SEQNO_BMODE_NORMAL_GAME_CHANGE_INIT,
	SEQNO_BMODE_NORMAL_GAME_REPLAY_INIT,
	SEQNO_BMODE_INIT,
	SEQNO_BMODE_BET,
	SEQNO_BMODE_GAME_START_BUTTON_PUSH_WAIT,
	SEQNO_BMODE_GAME_START,
	SEQNO_BMODE_REELPUSH_START_WAIT,
	SEQNO_BMODE_REELPUSH,
	SEQNO_BMODE_REELSTOP_WAIT,
	SEQNO_BMODE_HIT_CHECK,
	SEQNO_BMODE_MISS_START,
	SEQNO_BMODE_MISS_WAIT_NEXT,
	SEQNO_BMODE_HIT_PAYOUT_START,
	SEQNO_BMODE_HIT_PAYOUT_WAIT_NEXT,
	SEQNO_BMODE_HIT_REPLAY_START,
	SEQNO_BMODE_HIT_REPLAY_WAIT_NEXT,
	SEQNO_BMODE_HIT_SEVEN_START,
	SEQNO_BMODE_HIT_SEVEN_WAIT_NEXT,
	//�{�[�i�X�Q�[��
	SEQNO_BGAME_INIT_FIRST,
	SEQNO_BGAME_INIT,
	SEQNO_BGAME_START,
	SEQNO_BGAME_BET,
	SEQNO_BGAME_GAME_START_BUTTON_PUSH_WAIT,
	SEQNO_BGAME_GAME_START,
	SEQNO_BGAME_REELPUSH_START_WAIT,
	SEQNO_BGAME_REELPUSH,
	SEQNO_BGAME_REELSTOP_WAIT,
	SEQNO_BGAME_HIT_CHECK,
	SEQNO_BGAME_MISS_START,
	SEQNO_BGAME_PAYOUT_START,
	SEQNO_BGAME_PAYOUT_WAIT_NEXT,
	SEQNO_BGAME_ONE_GAME_FINISH,
	SEQNO_BGAME_RATE_DOWN,
	SEQNO_BGAME_ANENCORE,
	SEQNO_BGAME_PIP_RECOVER,
	SEQNO_BGAME_PIP_OUT,
	//���b�Z�[�W�A�I��
	SEQNO_MSGSET_CREDIT_3,
	SEQNO_MSGSET_CREDIT_0,
	SEQNO_MSGSET_CREDIT_MAX,
	SEQNO_MSGSET_WAIT_NEXT,
	SEQNO_GAME_END,
	SEQNO_MAX,
};

//--------------------------------------------------------------
//	���[������
//--------------------------------------------------------------
enum
{
	RC_NON = 0,
	RC_SCROLL,
	RC_STOP_SET,
	RC_STOP,
	RC_STOP_SHAKE,
	RC_MAX,
};

//--------------------------------------------------------------
///	����ʐ���
//--------------------------------------------------------------
enum
{
	DDISP_NON = 0,
	DDISP_MBALL_SPIN_START,
	DDISP_MBALL_SPIN_OUT,
	DDISP_PIP_START,
	DDISP_PIP_OUT,
	DDISP_PIP_ANENCORE,	
	DDISP_PIP_YUBISASHI,
	DDISP_PIP_STOP,
	DDISP_BONUS_END,
	DDISP_PIP_PATAPATA,
	DDISP_PIP_BANZAI,
	DDISP_MBALL_STOP,
	DDISP_PIP_RECOVER,
	DDISP_MAX,
};

//--------------------------------------------------------------
///	�w����
//--------------------------------------------------------------
enum
{
	YUBI0 = 0,
	YUBI1,
	YUBI2,
	YUBI3,
	YUBI4,
	YUBI5,
	YUBI_MAX,
};

//==============================================================================
//	typedef
//==============================================================================
//--------------------------------------------------------------
///	PLTT�\����
//--------------------------------------------------------------
typedef struct
{
	u16 red:5;
	u16 green:5;
	u16 blue:5;
	u16 dummy:1;
}PLTT;

//--------------------------------------------------------------
///	PIPNAVI
//--------------------------------------------------------------
typedef struct
{
	u32 btn[3];
	PIPMT pipmt[3];
}PIPNAVI;

//==============================================================================
//	�v���g�^�C�v
//==============================================================================
static void slotMain_InitPosSet( SLOTMAIN *main );

static GAMERET (* const DATA_SlotGameTbl[SEQNO_MAX])( SLOTMAIN *main );

static void slot_ReelControlSet( SLOTMAIN *main );
static void slot_ReelControlDelete( SLOTMAIN *main );
static void ReelControlScrollSet( SLOTMAIN *main, REEL_NUM no );
static void ReelControlStopSet( SLOTMAIN *main, REEL_NUM no );
static int ReelControlScrollCheck( SLOTMAIN *main, REEL_NUM no );
static void ReelControlTcb( TCB_PTR tcb, void *wk );

static int (* const DATA_ReelControlTbl[RC_MAX])( REELCONTROL *reel, SLOTMAIN *main );

static int ReelSlip_Hit( REELCONTROL *reel, SLOTMAIN *main );
static int ReelSlipBonus_Hit( REELCONTROL *reel, SLOTMAIN *main );
static int Reel0Slip_HitSlip( REELCONTROL *reel, SLOTMAIN *main );
static int Reel1Slip_HitSlip( REELCONTROL *reel, SLOTMAIN *main );
static int Reel2Slip_HitSlip( REELCONTROL *reel, SLOTMAIN *main );
static int Reel0Slip_HitSlipFirst( REELCONTROL *reel, SLOTMAIN *main, REEL_PATTERN hit );
static int Reel0Slip_HitSlipAfter( REELCONTROL *reel, SLOTMAIN *main, REEL_PATTERN hit );
static int Reel12Slip_HitSlipFirst( REELCONTROL *reel, SLOTMAIN *main, REEL_PATTERN hit );
static int Reel12Slip_HitSlipAfter( REELCONTROL *reel, SLOTMAIN *main, REEL_PATTERN hit );
static int Reel012SlipBonus_HitSlip( REELCONTROL *reel, SLOTMAIN *main, REEL_PATTERN hit );
static void ReelSlip_Miss( REELCONTROL *reel, SLOTMAIN *main );
static void ReelSlipBonus_Miss( REELCONTROL *reel, SLOTMAIN *main );
static int Reel0Slip_Cherry1HitCheck( SLOTMAIN *main, int offs );
static int Reel0Slip_PatCherry1HitCheck( SLOTMAIN *main, int offs, REEL_PATTERN hit );
static int Reel0Slip_OffsetHitCheck( REELCONTROL *reel, SLOTMAIN *main, int offs );
static int Reel1Slip_OffsetHitCheck( REELCONTROL *reel, SLOTMAIN *main, int offs );
static int Reel2Slip_OffsetHitCheck( REELCONTROL *reel, SLOTMAIN *main, int offs );
static int Reel0SlipBonus_OffsetHitCheck( REELCONTROL *reel, SLOTMAIN *main, int offs );
static int Reel1SlipBonus_OffsetHitCheck( REELCONTROL *reel, SLOTMAIN *main, int offs );
static int Reel2SlipBonus_OffsetHitCheck( REELCONTROL *reel, SLOTMAIN *main, int offs );
static int Reel0Slip_OffsetHitCountGet( REELCONTROL *reel, SLOTMAIN *main, int offs );
static int Reel1Slip_OffsetHitCountGet( REELCONTROL *reel, SLOTMAIN *main, int offs );
static int Reel2Slip_OffsetHitCountGet( REELCONTROL *reel, SLOTMAIN *main, int offs );

static int ReelSlip_StopReelCountGet( SLOTMAIN *main );
static int ReelSlip_StartSlipCheck( REELCONTROL *reel, SLOTMAIN *main );
static int ReelSlip_HitStopPosGet(
		REELCONTROL *reel, SLOTMAIN *main, int *pos0, int *pos1, int *pos2 );

static void ReelScroll( SLOTMAIN *main, REEL_NUM no, fx32 y );
static fx32 ReelScrollGrid( SLOTMAIN *main, REEL_NUM no, fx32 y );

static u32 LotteryProbGet( SLOTMAIN *main );
static int LotteryProbCheck( u32 hit, u32 *mainprob );
static int LotteryCheck_Basic( SLOTMAIN *main );
static int LotterySet_SmallA( SLOTMAIN *main );
static int LotteryCheck_Navi( SLOTMAIN *main );
static void LotterySet_BonusContinueBase( SLOTMAIN *main );
static void LotterySet_PipType( SLOTMAIN *main );
static int LotteryCheck_BasicLotteryB( SLOTMAIN *main );
static void LotterySet_BasicLotteryB( SLOTMAIN *main );
static int LotteryCheck_MoonLightRed( SLOTMAIN *main );
static int LotteryCheck_MoonLight( SLOTMAIN *main );
static int LotteryCheck_BonusContinue( SLOTMAIN *main );
static void LotterySet_BonusContinueDown( SLOTMAIN *main );
static BCEFF LotteryGet_BonusContinueEffect( SLOTMAIN *main );
static void LotterySet_Yubisashi( SLOTMAIN *main );

static void slot_PayOutControlSet( SLOTMAIN *main );
static void slot_PayOutControlDelete( SLOTMAIN *main );
static void PayOutControlPayOutSet( SLOTMAIN *main );
static int PayOutControlEndCheck( SLOTMAIN *main );
static void PayOutControlTCB( TCB_PTR tcb, void *wk );
static void PayOutLineAnimeSet( PAYOUTCONTROL *work );

static void slot_DDispControlSet( SLOTMAIN *main );
static void slot_DDispControlDelete( SLOTMAIN *main );
static void DDC_TypeChange( SLOTMAIN *main, u32 type );
static int DDC_EndCheck( SLOTMAIN *main );
static void DDC_BonusFontSet( SLOTMAIN *main );
static void DDC_BonusFontDelete( SLOTMAIN *main );
static int (* const * const DATA_DDCM_Tbl[DDISP_MAX])( DDISPCONTROL *work );

static void slot_PlttControlSet( SLOTMAIN *main );
static void slot_PlttControlDelete( SLOTMAIN *main );
static void PlttCopy( NNSG2dPaletteData *pPltt, int offs, u16 *dest );
static void ColorTargetFade( u16 base, u16 target, u16 evy, u16 *dest );
static void ColorTargetFade16( const u16 *base, const u16 *target, u16 evy, u16 *dest );
static void PaletteBGSet( SLOTMAIN *main, u32 frame, int no, u16 *pltt );

static void PlttEff_LineLightON( SLOTMAIN *main, LINENO no );
static void PlttEff_LineLightOFF( SLOTMAIN *main, LINENO no );
static void PlttEff_LineLightBet( SLOTMAIN *main, LINENO no );
static void PlttEff_LineLightBetOne( SLOTMAIN *main, LINENO no );
static void PlttEff_LineLightONAll( SLOTMAIN *main );
static void PlttEff_LineLightOFFAll( SLOTMAIN *main );
static void PlttEff_LineLightBetAll( SLOTMAIN *main );
static EOA_PTR PlttEff_EoaLineHitAnm( SLOTMAIN *main, LINENO no, u32 payout );
static int PlttEff_EoaLineHitAnmRetGet( EOA_PTR eoa );

static void PlttEff_EoaLineBetAnmStart( SLOTMAIN *main );
static void PlttEff_EoaLineBetAnmDelete( SLOTMAIN *main );

static void PlttEff_MountKuraku( SLOTMAIN *main );
static void PlttEff_MountAkaruku( SLOTMAIN *main );
static void PlttEff_MountMoonLight( SLOTMAIN *main, MOONTYPE type );

static PADRET keyTrg( u32 pad );
static REEL_PATTERN lotteryHitBitPattern( u32 bit );
static REEL_PATTERN reelHitPatternGet_111( SLOTMAIN *main );
static REEL_PATTERN reelHitPatternGet_222( SLOTMAIN *main );
static REEL_PATTERN reelHitPatternGet_333( SLOTMAIN *main );
static REEL_PATTERN reelHitPatternGet_123( SLOTMAIN *main );
static REEL_PATTERN reelHitPatternGet_321( SLOTMAIN *main );
static REEL_PATTERN reelHitPatternGet( SLOTMAIN *main, u32 lottery_bit, u32 *hitline );
static REEL_PATTERN reelHitPatternGetBonus( SLOTMAIN *main, u32 lottery_bit, u32 *line );

static BALLTYPE Lottery_NaviBallGet( u32 bit );

static void StopButtonClear( SLOTMAIN *main );
static void StopButtonSet( SLOTMAIN *main, u32 btn );
static int StopButtonCheck012( SLOTMAIN *main );
static int StopButtonCheckYubisashi( SLOTMAIN *main );
#ifdef DEBUG_ON_SLOT
static u32 DEBUG_StopButtonGetYubisashi( SLOTMAIN *main );
#endif

static void ReelButtonAttr_ON( SLOTMAIN *main, REEL_NUM no );
static void ReelButtonAttr_OFF( SLOTMAIN *main, REEL_NUM no );

static u32 PayOutCoinGet_Small( SLOTMAIN *main );

static const u32 DATA_ContBonusTypeHitBit[CONT_BONUS_TYPE_MAX];
static const PIPNAVI DATA_BonusGamePipNaveTbl[YUBI_MAX];
static const int DATA_ButtonPos[3][2];

//--------------------------------------------------------------
//	�f�o�b�O
//--------------------------------------------------------------
#ifdef PM_DEBUG
static void DEBUG_reelHitPatternCheck( SLOTMAIN *main, u32 lottery_bit );

#ifdef DEBUG_DDISPTEST
static int DEBUG_SeqNoDDispTest;
static int DEBUG_DDispTestFrame;
static int DEBUG_DDispTest( SLOTMAIN *main );
#endif

#ifdef DEBUG_ON_SLOT
static int DEBUG_DebugKeyCheck( SLOTMAIN *main );
static int DEBUG_DebugProc( SLOTMAIN *main );
static int DEBUG_AutoPlayEndCheck( SLOTMAIN *main );
static void DEBUG_AutoPlayInit( SLOTMAIN *main );
static int DEBUG_AutoPlayCheck( SLOTMAIN *main );
static int DEBUG_AutoPlayPushCheck( SLOTMAIN *main );
static void DEBUG_SlotInit( SLOTMAIN *main );
static void DEBUG_SlotHitLineCount( SLOTMAIN *main );
#endif

#endif	//PM_DEBUG

//==============================================================================
//	�X���b�g�@�Q�[���V�X�e��
//==============================================================================
//--------------------------------------------------------------
/**
 * �X���b�g�@�Q�[���V�X�e��������
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
void SlotMain_GameInit( SLOTMAIN *main )
{
	slotMain_InitPosSet( main );
	slot_ReelControlSet( main );
	slot_PayOutControlSet( main );
	slot_DDispControlSet( main );
	slot_PlttControlSet( main );
	
#ifdef DEBUG_ON_SLOT
	DEBUG_SlotInit( main );
#endif
	
#ifdef DEBUG_DDISPTEST	
	DEBUG_SeqNoDDispTest = 0;
	DEBUG_DDispTestFrame = 0;
#endif
}

//--------------------------------------------------------------
/**
 * �X���b�g�@�Q�[���V�X�e���폜
 * �����O��EOA�A�Z���A�N�^�[�͍폜����Ă���
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
void SlotMain_GameDelete( SLOTMAIN *main )
{
	slot_ReelControlDelete( main );
	slot_PayOutControlDelete( main );
	slot_DDispControlDelete( main );
	slot_PlttControlDelete( main );
}

//--------------------------------------------------------------
/**
 * �X���b�g�@�����ʒu�Z�b�g
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slotMain_InitPosSet( SLOTMAIN *main )
{
	int i,gy;
	fx32 y;
	
	for( i = REEL_0; i < REEL_MAX; i++ ){
		gy = (int)gf_rand() % REEL_PT_MAX;
		main->reel_grid_y[i] = gy;
		main->reel_dot_y[i] = NUM_FX32( REEL_SCROLL_MAX ) - REEL_PT_V_GD32( gy );
		main->reel_dot_y[i] %= NUM_FX32( REEL_SCROLL_MAX );
	}
}

//==============================================================================
//	�X���b�g�@�Q�[�����C��
//==============================================================================
//--------------------------------------------------------------
/**
 * �X���b�g�Q�[������
 * @param	main	SLOTMAIN *
 * @retval	int		TRUE=�I��
 */
//--------------------------------------------------------------
int SlotMain_Game( SLOTMAIN *main )
{
	GAMERET ret;
	
	#ifdef DEBUG_DDISPTEST
	if( DEBUG_DDispTest(main) == TRUE ){
		return( TRUE );
	}
	#endif
	
	#ifdef DEBUG_ON_SLOT
	if( DEBUG_DebugProc(main) == TRUE ){
		return( FALSE );
	}
	#endif
	
	do{
		ret = DATA_SlotGameTbl[main->seq_no]( main );
	}while( ret == RET_NEXT );
	
	if( ret == RET_END ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �Q�[���@�Q�[��������
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_Init( SLOTMAIN *main )
{
	main->payout = 0;
	main->bet = 0;
	main->reel_speed = REEL_SPEED_DEF;
	main->lottery_bit = LOTTERY_HITBIT_NON;
	main->bonus_game_flag = FALSE;
	main->seq_no = SEQNO_BET;
	
	ReelButtonAttr_OFF( main, REEL_0 );
	ReelButtonAttr_OFF( main, REEL_1 );
	ReelButtonAttr_OFF( main, REEL_2 );
	PlttEff_LineLightOFFAll( main );
	PlttEff_EoaLineBetAnmStart( main );
	
	if( main->credit == 0 ){
		main->seq_no = SEQNO_MSGSET_CREDIT_0;
		main->next_seq_no = SEQNO_GAME_END;
	}else if( main->credit < BET_LOWEST ){
		main->seq_no = SEQNO_MSGSET_CREDIT_3;
		main->next_seq_no = SEQNO_GAME_END;
	}else if( main->credit >= SLOT_COIN_MAX ){
		main->seq_no = SEQNO_MSGSET_CREDIT_MAX;
		main->next_seq_no = SEQNO_BET;
	}
	
	return( RET_NEXT );
}

//--------------------------------------------------------------
/**
 * �Q�[���@�x�b�g
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_Bet( SLOTMAIN *main )
{
#ifdef DEBUG_ON_SLOT
	DEBUG_AutoPlayEndCheck( main ); 
	
	if( DEBUG_DebugKeyCheck(main) == TRUE ){
		return( RET_NON );
	}
	
	if( DEBUG_AutoPlayCheck(main) == TRUE ){
		main->credit -= BET_LOWEST;
		main->bet_total += BET_LOWEST;
		main->seq_no = SEQNO_GAME_START_BUTTON_PUSH_WAIT;
		
		Snd_SePlay( SE_SLOT_BET );
		PlttEff_EoaLineBetAnmDelete( main );
		PlttEff_LineLightBetAll( main );
		return( RET_NON );
	}
#endif
	
	if( keyTrg(PAD_END) != PAD_NON ){	//�I��
		PlttEff_EoaLineBetAnmDelete( main );
		main->seq_no = SEQNO_GAME_END;
		return( RET_NON );
	}
	
	if( keyTrg(PAD_BET) != PAD_NON ){
		main->credit -= BET_LOWEST;
		main->bet_total += BET_LOWEST;
		main->seq_no = SEQNO_GAME_START_BUTTON_PUSH_WAIT;
		
		Snd_SePlay( SE_SLOT_BET );
		PlttEff_EoaLineBetAnmDelete( main );
		PlttEff_LineLightBetAll( main );
		return( RET_NON );
	}
	
	return( RET_NON );
}

//--------------------------------------------------------------
/**
 * �Q�[���@�x�b�g��̃X�^�[�g�{�^���҂�
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_GameStartButtonPushWait( SLOTMAIN *main )
{
#ifdef DEBUG_ON_SLOT
	if( DEBUG_AutoPlayCheck(main) == TRUE ){
		main->seq_no = SEQNO_GAME_START;
		return( RET_NEXT );
	}
#endif
	
	if( keyTrg(PAD_END) != PAD_NON ){	//�I��
		main->credit += BET_LOWEST;
		main->seq_no = SEQNO_GAME_END;
		return( RET_NON );
	}
	
	if( keyTrg(PAD_GAMESTART) != PAD_NON ){
		main->seq_no = SEQNO_GAME_START;
		return( RET_NEXT );
	}
	
	return( RET_NON );
}

//--------------------------------------------------------------
/**
 * �Q�[���@�Q�[���X�^�[�g������
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_GameStart( SLOTMAIN *main )
{
	LotterySet_SmallA( main );
	
	main->game_count++;
	main->ngame_count++;
	
	main->auto_hit_flag = FALSE;
	
	if( (main->lottery_bit & LOTTERY_HITBIT_AUTO_AND) ){
		main->auto_hit_flag = TRUE;
	}
	
	main->reel_slip_hit_flag = FALSE;
	
	if( main->lottery_bit != LOTTERY_HITBIT_NON ){
		if( LotteryCheck_Navi(main) == FALSE ){
			main->ddispcont.balltype = BALL_PRE;
		}else{
			main->ddispcont.balltype = Lottery_NaviBallGet( main->lottery_bit );
			main->navi_hit_count++;
		}
		
		main->reel_slip_hit_flag = TRUE;
		DDC_TypeChange( main, DDISP_MBALL_SPIN_START );
	}
	
	ReelButtonAttr_OFF( main, REEL_0 );
	ReelButtonAttr_OFF( main, REEL_1 );
	ReelButtonAttr_OFF( main, REEL_2 );
	PlttEff_LineLightBetAll( main );
	
	ReelControlScrollSet( main, 0 );
	ReelControlScrollSet( main, 1 );
	ReelControlScrollSet( main, 2 );
	StopButtonClear( main );
	
	main->reel_status[REEL_0] = REEL_ST_SCROLL;
	main->reel_status[REEL_1] = REEL_ST_SCROLL;
	main->reel_status[REEL_2] = REEL_ST_SCROLL;
	main->frame = 0;
	main->seq_no = SEQNO_REELPUSH_START_WAIT;
	
	Snd_SePlay( SE_SLOT_REEL_START );
	
#ifdef DEBUG_ON_SLOT
	if( DEBUG_AutoPlayCheck(main) == TRUE ){
		DEBUG_AutoPlayInit( main );
	}
#endif
	
	return( RET_NEXT );
}

//--------------------------------------------------------------
/**
 * �Q�[���@�{�^�������J�n�܂ł̈ꐡ�҂�
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_ReelPushStartWait( SLOTMAIN *main )
{
	main->frame += FX32_ONE;
	
	if( main->frame >= GE_FXFRAME_BTN_PUSHWAIT ){
		main->frame = 0;
		main->seq_no = SEQNO_REELPUSH;
		return( RET_NEXT );
	}
	
	return( RET_NON );
}

//--------------------------------------------------------------
/**
 * �Q�[���@���[���{�^������
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_ReelPush( SLOTMAIN *main )
{
	u32 trg = sys.trg;
	
#ifdef DEBUG_ON_SLOT
	if( DEBUG_AutoPlayCheck(main) ){
		trg = 0;
		
		if( DEBUG_AutoPlayPushCheck(main) == TRUE ){
			if( main->reel_status[REEL_0] == REEL_ST_SCROLL ){
				trg |= PAD_REELPUSH0;
			}else if( main->reel_status[REEL_1] == REEL_ST_SCROLL ){
				trg |= PAD_REELPUSH1;
			}else if( main->reel_status[REEL_2] == REEL_ST_SCROLL ){
				trg |= PAD_REELPUSH2;
			}
			
			Snd_SePlay( SE_SLOT_REEL_STOP );
		}
	}
#endif
	
	if( main->reel_status[REEL_0] == REEL_ST_SCROLL && (trg&PAD_REELPUSH0) ){
		main->reel_status[REEL_0] = REEL_ST_WAIT;
		StopButtonSet( main, PAD_REELPUSH0 );
		if( StopButtonCheck012(main) == FALSE ){ main->auto_hit_flag = FALSE; }
		ReelButtonAttr_ON( main, REEL_0 );
		ReelControlStopSet( main, REEL_0 );
		Snd_SePlay( SE_SLOT_REEL_STOP );
	}else if( main->reel_status[REEL_1] == REEL_ST_SCROLL && (trg&PAD_REELPUSH1) ){
		main->reel_status[REEL_1] = REEL_ST_WAIT;
		StopButtonSet( main, PAD_REELPUSH1 );
		if( StopButtonCheck012(main) == FALSE ){ main->auto_hit_flag = FALSE; }
		ReelButtonAttr_ON( main, REEL_1 );
		ReelControlStopSet( main, REEL_1 );
		Snd_SePlay( SE_SLOT_REEL_STOP );
	}else if( main->reel_status[REEL_2] == REEL_ST_SCROLL && (trg&PAD_REELPUSH2) ){
		main->reel_status[REEL_2] = REEL_ST_WAIT;
		StopButtonSet( main, PAD_REELPUSH2 );
		if( StopButtonCheck012(main) == FALSE ){ main->auto_hit_flag = FALSE; }
		ReelButtonAttr_ON( main, REEL_2 );
		ReelControlStopSet( main, REEL_2 );
		Snd_SePlay( SE_SLOT_REEL_STOP );
	}
	
	if( main->reel_status[REEL_0] == REEL_ST_WAIT && 
		main->reel_status[REEL_1] == REEL_ST_WAIT && 
		main->reel_status[REEL_2] == REEL_ST_WAIT ){
		main->seq_no = SEQNO_REELSTOP_WAIT;
	}
	
	return( RET_NON );
}

//--------------------------------------------------------------
/**
 * �Q�[���@���[����~�҂�
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_ReelStopWait( SLOTMAIN *main )
{
	if( ReelControlScrollCheck(main,REEL_0) == TRUE ||
		ReelControlScrollCheck(main,REEL_1) == TRUE ||
		ReelControlScrollCheck(main,REEL_2) == TRUE ){
		return( RET_NON );
	}
	
	PlttEff_LineLightOFFAll( main );
	main->seq_no = SEQNO_HIT_CHECK;
	return( RET_NEXT );
}

//--------------------------------------------------------------
/**
 * �Q�[���@�q�b�g�`�F�b�N
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_HitCheck( SLOTMAIN *main )
{
	REEL_PATTERN pat = reelHitPatternGet( main, main->lottery_bit, &main->reel_hit_line_bit );
	
	main->reel_hit_pattern = pat;
	
	if( pat == REEL_PATTERN_MAX ){								//�O��
		if( (main->lottery_bit & LOTTERY_HITBIT_BONUS_AND) ){	//�O��Ă��{�[�i�X���[�h��
			main->seq_no = SEQNO_HIT_MISS_BONUS_START;
			return( RET_NEXT );
		}
		
		if( (main->lottery_bit != LOTTERY_HITBIT_NON) ){		//���I����O��
			main->seq_no = SEQNO_HIT_MISS_START;
			return( RET_NEXT );
		}
		
		main->seq_no = SEQNO_NOHIT_MISS_START;					//�f�O��
		return( RET_NEXT );
	}
	
	if( (main->lottery_bit & LOTTERY_HITBIT_BONUS_AND) ){		//�{�[�i�X���[�h������
		if( (main->lottery_bit & LOTTERY_HITBIT_REPLAY_B) ){	//���v���C
			main->seq_no = SEQNO_HIT_REPLAY_BONUS_START;
		}else{													//�q��
			main->seq_no = SEQNO_HIT_PAYOUT_BONUS_START;
		}
		
		return( RET_NEXT );
	}
	
	if( pat == REEL_REPLAY ){									//���v���C
		main->seq_no = SEQNO_HIT_REPLAY_START;
		return( RET_NEXT );
	}
	
	main->seq_no = SEQNO_HIT_PAYOUT_START;						//�q�𓖂���
	return( RET_NEXT );
}

//--------------------------------------------------------------
/**
 * �Q�[���@���I�����O��@�J�n
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_NoHitMissStart( SLOTMAIN *main )
{
	PlttEff_LineLightOFFAll( main );
	
	main->frame = 0;
	main->seq_no = SEQNO_NOHIT_MISS_WAIT_NEXT;
	return( RET_NEXT );
}

//--------------------------------------------------------------
/**
 * �Q�[���@���I�����O��@�ꐡ�҂��̂��߂�
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_NoHitMissWaitNext( SLOTMAIN *main )
{
	main->frame += FX32_ONE;
	
	if( main->frame >= GE_FXFRAME_NOHIT_MISS_WAIT ){ 
		main->frame = 0;
		main->seq_no = SEQNO_GAME_INIT;
	}
	
	return( RET_NON );
}

//--------------------------------------------------------------
/**
 * �Q�[���@���I����O��@�J�n
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_HitMissStart( SLOTMAIN *main )
{
	PlttEff_LineLightOFFAll( main );
	DDC_TypeChange( main, DDISP_MBALL_SPIN_OUT );
	main->seq_no = SEQNO_HIT_MISS_WAIT_NEXT;
	
	return( RET_NON );
}

//--------------------------------------------------------------
/**
 * �Q�[���@���I����O��@�{�[���҂��̂��߂�
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_HitMissWaitNext( SLOTMAIN *main )
{
	if( DDC_EndCheck(main) == TRUE ){
		DDC_TypeChange( main, DDISP_NON );
		main->seq_no = SEQNO_GAME_INIT;
		return( RET_NEXT );
	}
	
	return( RET_NON );
}

//--------------------------------------------------------------
/**
 * �Q�[���@���I����q�b�g�@�y�C�A�E�g�J�n
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_HitPayOutStart( SLOTMAIN *main )
{
	main->payout = PayOutCoinGet_Small( main );
	main->payout_total += main->payout;
	main->frame = 0;
	main->seq_no = SEQNO_HIT_PAYOUT_WAIT_NEXT;
	PayOutControlPayOutSet( main );
	DDC_TypeChange( main, DDISP_MBALL_STOP );
	return( RET_NON );
}

//--------------------------------------------------------------
/**
 * �Q�[���@���I����q�b�g�@�y�C�A�E�g��
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_HitPayOutWaitNext( SLOTMAIN *main )
{
	main->frame += FX32_ONE;
	
	if( main->frame == GE_FXFRAME_HITS_BALL_BACK_START ){
		DDC_TypeChange( main, DDISP_MBALL_SPIN_OUT );
	}else if( main->frame > GE_FXFRAME_HITS_BALL_BACK_START ){
		if( PayOutControlEndCheck(main) == TRUE && DDC_EndCheck(main) == TRUE ){
			DDC_TypeChange( main, DDISP_NON );
			main->frame = 0;
			main->seq_no = SEQNO_GAME_INIT;
			return( RET_NEXT );
		}
	}
	
	return( RET_NON );
}

//--------------------------------------------------------------
/**
 * �Q�[���@���v���C�q�b�g�@�J�n
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_HitReplayStart( SLOTMAIN *main )
{
	main->payout = 0;
	main->frame = 0;
	main->seq_no = SEQNO_HIT_REPLAY_WAIT_NEXT;
	PayOutControlPayOutSet( main );
	DDC_TypeChange( main, DDISP_MBALL_STOP );
	return( RET_NON );
}

//--------------------------------------------------------------
/**
 * �Q�[���@���v���C�q�b�g�@�҂�
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_HitReplayWaitNext( SLOTMAIN *main )
{
	main->frame += FX32_ONE;
	
	if( main->frame == GE_FXFRAME_HITRP_BALL_BACK_START ){
		DDC_TypeChange( main, DDISP_MBALL_SPIN_OUT );
	}else if( main->frame > GE_FXFRAME_HITRP_BALL_BACK_START ){
		if( PayOutControlEndCheck(main) == TRUE && DDC_EndCheck(main) == TRUE ){
			DDC_TypeChange( main, DDISP_NON );
			main->frame = 0;
			main->seq_no = SEQNO_GAME_START;
			return( RET_NEXT );
		}
	}
	
	return( RET_NON );
}

//--------------------------------------------------------------
/**
 * �Q�[���@�O��Ń{�[�i�X�q�b�g�@�J�n
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_HitMissBonusStart( SLOTMAIN *main )
{
	PlttEff_LineLightOFFAll( main );
	LotterySet_BonusContinueBase( main );
	LotterySet_PipType( main );
	DDC_TypeChange( main, DDISP_MBALL_STOP );
	
	main->frame = 0;
	main->seq_no = SEQNO_HIT_MISS_BONUS_BALL_STOP_WAIT;
	return( RET_NON );
}

//--------------------------------------------------------------
/**
 * �Q�[���@�O��Ń{�[�i�X�q�b�g�@�{�[����~�҂�
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_HitMissBonusBallStopWait( SLOTMAIN *main )
{
	main->frame += FX32_ONE;
	
	if( main->frame >= GE_FXFRAME_NOHIT_MISS_WAIT ){
		DDC_TypeChange( main, DDISP_PIP_START );
		SlotBGM_Play( main, BGM_HIT );
		main->seq_no = SEQNO_HIT_MISS_BONUS_WAIT_NEXT;
	}
	
	return( RET_NON );
}

//--------------------------------------------------------------
/**
 * �Q�[���@�O��Ń{�[�i�X�q�b�g�@�s�b�s�o��҂���A�{�[�i�X���[�h��
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_HitMissBonusWaitNext( SLOTMAIN *main )
{
	if( DDC_EndCheck(main) == TRUE ){
		main->seq_no = SEQNO_BMODE_NORMAL_GAME_CHANGE_INIT;
		return( RET_NEXT );
	}
	
	return( RET_NON );
}

//--------------------------------------------------------------
/**
 * �Q�[���@�{�[�i�X�q�b�g�@�y�C�A�E�g���s�b�s�o��@�J�n
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_HitPayOutBonusStart( SLOTMAIN *main )
{
	main->payout = PayOutCoinGet_Small( main );
	main->frame = 0;
	main->seq_no = SEQNO_HIT_PAYOUT_BONUS_WAIT_NEXT;
	
	PayOutControlPayOutSet( main );
	LotterySet_BonusContinueBase( main );
	LotterySet_PipType( main );
	DDC_TypeChange( main, DDISP_MBALL_STOP );
	
	return( RET_NON );
}

//--------------------------------------------------------------
/**
 * �Q�[���@�{�[�i�X�q�b�g�@�y�C�A�E�g���s�b�s�o��@�҂���{�[�i�X���[�h��
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_HitPayOutBonusWaitNext( SLOTMAIN *main )
{
	main->frame += FX32_ONE;
	
	if( main->frame == GE_FXFRAME_HITBMODE_PIP_START ){
		SlotBGM_Play( main, BGM_HIT );
		DDC_TypeChange( main, DDISP_PIP_START );
	}else if( main->frame >= GE_FXFRAME_HITBMODE_PIP_START ){
		if( PayOutControlEndCheck(main) == TRUE && DDC_EndCheck(main) == TRUE ){
			main->frame = 0;
			main->seq_no = SEQNO_BMODE_NORMAL_GAME_CHANGE_INIT;
			return( RET_NEXT );
		}
	}
	
	return( RET_NON );
}

//--------------------------------------------------------------
/**
 * �Q�[���@�{�[�i�X�q�b�g�@���v���C���s�b�s�o��@�J�n
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_HitReplayBonusStart( SLOTMAIN *main )
{
	main->frame = 0;
	main->seq_no = SEQNO_HIT_REPLAY_BONUS_WAIT_NEXT;
	
	PayOutControlPayOutSet( main );
	DDC_TypeChange( main, DDISP_MBALL_STOP );
	LotterySet_BonusContinueBase( main );
	LotterySet_PipType( main );
	
	return( RET_NON );
}

//--------------------------------------------------------------
/**
 * �Q�[���@�{�[�i�X�q�b�g�@���v���C���s�b�s�o��@�҂���{�[�i�X���[�h��
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_HitReplayBonusWaitNext( SLOTMAIN *main )
{
	main->frame += FX32_ONE;
	
	if( main->frame == GE_FXFRAME_HITBMODE_REPLAY_PIP_START ){
		DDC_TypeChange( main, DDISP_PIP_START );
		SlotBGM_Play( main, BGM_HIT );
	}else if( main->frame >= GE_FXFRAME_HITBMODE_REPLAY_PIP_START ){
		if( PayOutControlEndCheck(main) == TRUE && DDC_EndCheck(main) == TRUE ){
			main->frame = 0;
			main->seq_no = SEQNO_BMODE_NORMAL_GAME_REPLAY_INIT;
			return( RET_NEXT );
		}
	}
	
	return( RET_NON );
}

//==============================================================================
//	�Q�[���@�{�[�i�X���[�h
//==============================================================================
//--------------------------------------------------------------
/**
 * �{�[�i�X���[�h�@�ʏ�Q�[���A�q������̈ڍs������
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_BMode_NormalGameChangeInit( SLOTMAIN *main )
{
	GF_ASSERT( main->bonus_continue_type < CONT_BONUS_TYPE_MAX );
	main->seq_no = SEQNO_BMODE_INIT;
	return( RET_NEXT );
}

//--------------------------------------------------------------
/**
 * �{�[�i�X���[�h�@�ʏ�Q�[���A���v���C����̈ڍs������
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_BMode_NormalGameReplayChangeInit( SLOTMAIN *main )
{
	GF_ASSERT( main->bonus_continue_type < CONT_BONUS_TYPE_MAX );
	main->seq_no = SEQNO_BMODE_GAME_START;
	return( RET_NEXT );
}

//--------------------------------------------------------------
/**
 * �{�[�i�X���[�h�@������
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_BMode_Init( SLOTMAIN *main )
{
	main->payout = 0;
	main->bet = 0;
	main->seq_no = SEQNO_BMODE_BET;
	main->lottery_bit = LOTTERY_HITBIT_NON;
	
	ReelButtonAttr_OFF( main, REEL_0 );
	ReelButtonAttr_OFF( main, REEL_1 );
	ReelButtonAttr_OFF( main, REEL_2 );
	PlttEff_LineLightOFFAll( main );
	PlttEff_EoaLineBetAnmStart( main );
	DDC_TypeChange( main, DDISP_PIP_STOP );
	
	if( main->credit == 0 ){
		main->seq_no = SEQNO_MSGSET_CREDIT_0;
		main->next_seq_no = SEQNO_GAME_END;
	}else if( main->credit < BET_LOWEST ){
		main->seq_no = SEQNO_MSGSET_CREDIT_3;
		main->next_seq_no = SEQNO_GAME_END;
	}else if( main->credit >= SLOT_COIN_MAX ){
		main->seq_no = SEQNO_MSGSET_CREDIT_MAX;
		main->next_seq_no = SEQNO_BMODE_BET;
	}
	
	return( RET_NEXT );
}

//--------------------------------------------------------------
/**
 * �{�[�i�X���[�h�@�x�b�g
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_BMode_Bet( SLOTMAIN *main )
{
#ifdef DEBUG_ON_SLOT
	DEBUG_AutoPlayEndCheck( main ); 
	
	if( DEBUG_DebugKeyCheck(main) == TRUE ){
		return( RET_NON );
	}
	
	if( DEBUG_AutoPlayCheck(main) == TRUE ){
		main->credit -= BET_LOWEST;
		main->bet_total += BET_LOWEST;
		main->seq_no = SEQNO_BMODE_GAME_START_BUTTON_PUSH_WAIT;
		
		Snd_SePlay( SE_SLOT_BET );
		PlttEff_EoaLineBetAnmDelete( main );
		PlttEff_LineLightBetAll( main );
		return( RET_NON );
	}
#endif
	
	if( keyTrg(PAD_END) != PAD_NON ){	//�I��
		main->seq_no = SEQNO_GAME_END;
		PlttEff_EoaLineBetAnmDelete( main );
		return( RET_NON );
	}
	
	if( keyTrg(PAD_BET) != PAD_NON ){
		main->credit -= BET_LOWEST;
		main->bet_total += BET_LOWEST;
		main->seq_no = SEQNO_BMODE_GAME_START_BUTTON_PUSH_WAIT;
		
		Snd_SePlay( SE_SLOT_BET );
		PlttEff_EoaLineBetAnmDelete( main );
		PlttEff_LineLightBetAll( main );
		return( RET_NON );
	}
	
	return( RET_NON );
}

//--------------------------------------------------------------
/**
 * �{�[�i�X���[�h�@�x�b�g��̃X�^�[�g�{�^���҂�
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_BMode_GameStartButtonPushWait( SLOTMAIN *main )
{
#ifdef DEBUG_ON_SLOT
	if( DEBUG_AutoPlayCheck(main) == TRUE ){
		main->seq_no = SEQNO_BMODE_GAME_START;
		return( RET_NEXT );
	}
#endif
	
	if( keyTrg(PAD_END) != PAD_NON ){	//�I��
		main->credit += BET_LOWEST;
		main->seq_no = SEQNO_GAME_END;
		return( RET_NON );
	}
	
	if( keyTrg(PAD_GAMESTART) != PAD_NON ){
		main->seq_no = SEQNO_BMODE_GAME_START;
		return( RET_NEXT );
	}
	
	return( RET_NON );
}

//--------------------------------------------------------------
/**
 * �{�[�i�X���[�h�@�Q�[���X�^�[�g
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_BMode_GameStart( SLOTMAIN *main )
{
	LotterySet_BasicLotteryB( main );
	
	main->game_count++;
	main->bmode_count++;
	
	main->auto_hit_flag = FALSE;
	
	if( (main->lottery_bit & LOTTERY_HITBIT_AUTO_AND) ){
		main->auto_hit_flag = TRUE;
	}
	
#ifdef DEBUG_ON_SLOT
	if( main->d_work.debug_auto_set == TRUE ){
		main->auto_hit_flag = TRUE;
		main->d_work.debug_auto_set = FALSE;
	}
#endif
	
	main->reel_slip_hit_flag = FALSE;
	
	if( main->lottery_bit != LOTTERY_HITBIT_NON ){
		main->reel_slip_hit_flag = TRUE;
	}
	
	ReelButtonAttr_OFF( main, REEL_0 );
	ReelButtonAttr_OFF( main, REEL_1 );
	ReelButtonAttr_OFF( main, REEL_2 );
	PlttEff_LineLightBetAll( main );
	
	ReelControlScrollSet( main, 0 );
	ReelControlScrollSet( main, 1 );
	ReelControlScrollSet( main, 2 );
	StopButtonClear( main );
	
	DDC_TypeChange( main, DDISP_PIP_PATAPATA );
	
	main->reel_status[REEL_0] = REEL_ST_SCROLL;
	main->reel_status[REEL_1] = REEL_ST_SCROLL;
	main->reel_status[REEL_2] = REEL_ST_SCROLL;
	main->frame = 0;
	main->seq_no = SEQNO_BMODE_REELPUSH_START_WAIT;
	
	Snd_SePlay( SE_SLOT_REEL_START );
	
#ifdef DEBUG_ON_SLOT
	if( DEBUG_AutoPlayCheck(main) == TRUE ){
		DEBUG_AutoPlayInit( main );
	}
#endif
	
	return( RET_NEXT );
}

//--------------------------------------------------------------
/**
 * �{�[�i�X���[�h�@�{�^�������J�n�҂�
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_BMode_ReelPushStartWait( SLOTMAIN *main )
{
	main->frame += FX32_ONE;
	
	if( main->frame >= GE_FXFRAME_BTN_PUSHWAIT ){
		main->frame = 0;
		main->seq_no = SEQNO_BMODE_REELPUSH;
		return( RET_NEXT );
	}
	
	return( RET_NON );
}

//--------------------------------------------------------------
/**
 * �Q�[���@�{�[�i�X���[�h�@���[���{�^������
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_BMode_ReelPush( SLOTMAIN *main )
{
	u32 trg = sys.trg;
	
#ifdef DEBUG_ON_SLOT
	if( DEBUG_AutoPlayCheck(main) ){
		trg = 0;
		
		if( DEBUG_AutoPlayPushCheck(main) == TRUE ){
			if( main->reel_status[REEL_0] == REEL_ST_SCROLL ){
				trg |= PAD_REELPUSH0;
			}else if( main->reel_status[REEL_1] == REEL_ST_SCROLL ){
				trg |= PAD_REELPUSH1;
			}else if( main->reel_status[REEL_2] == REEL_ST_SCROLL ){
				trg |= PAD_REELPUSH2;
			}
			
			Snd_SePlay( SE_SLOT_REEL_STOP );
		}
		
	}
#endif
	
	if( main->reel_status[REEL_0] == REEL_ST_SCROLL && (trg&PAD_REELPUSH0) ){
		main->reel_status[REEL_0] = REEL_ST_WAIT;
		StopButtonSet( main, PAD_REELPUSH0 );
		if( StopButtonCheck012(main) == FALSE ){ main->auto_hit_flag = FALSE; }
		ReelButtonAttr_ON( main, REEL_0 );
		ReelControlStopSet( main, REEL_0 );
		Snd_SePlay( SE_SLOT_REEL_STOP );
	}else if( main->reel_status[REEL_1] == REEL_ST_SCROLL && (trg&PAD_REELPUSH1) ){
		main->reel_status[REEL_1] = REEL_ST_WAIT;
		StopButtonSet( main, PAD_REELPUSH1 );
		if( StopButtonCheck012(main) == FALSE ){ main->auto_hit_flag = FALSE; }
		ReelButtonAttr_ON( main, REEL_1 );
		ReelControlStopSet( main, REEL_1 );
		Snd_SePlay( SE_SLOT_REEL_STOP );
	}else if( main->reel_status[REEL_2] == REEL_ST_SCROLL && (trg&PAD_REELPUSH2) ){
		main->reel_status[REEL_2] = REEL_ST_WAIT;
		StopButtonSet( main, PAD_REELPUSH2 );
		if( StopButtonCheck012(main) == FALSE ){ main->auto_hit_flag = FALSE; }
		ReelButtonAttr_ON( main, REEL_2 );
		ReelControlStopSet( main, REEL_2 );
		Snd_SePlay( SE_SLOT_REEL_STOP );
	}
	
	if( main->reel_status[REEL_0] == REEL_ST_WAIT && 
		main->reel_status[REEL_1] == REEL_ST_WAIT && 
		main->reel_status[REEL_2] == REEL_ST_WAIT ){
		main->seq_no = SEQNO_BMODE_REELSTOP_WAIT;
	}
	
	return( RET_NON );
}

//--------------------------------------------------------------
/**
 * �Q�[���@�{�[�i�X���[�h�@���[����~�҂�
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_BMode_ReelStopWait( SLOTMAIN *main )
{
	if( ReelControlScrollCheck(main,REEL_0) == TRUE ||
		ReelControlScrollCheck(main,REEL_1) == TRUE ||
		ReelControlScrollCheck(main,REEL_2) == TRUE ){
		return( RET_NON );
	}
	
	PlttEff_LineLightOFFAll( main );
	main->seq_no = SEQNO_BMODE_HIT_CHECK;
	return( RET_NEXT );
}

//--------------------------------------------------------------
/**
 * �Q�[���@�{�[�i�X���[�h�@�q�b�g�`�F�b�N
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_BMode_HitCheck( SLOTMAIN *main )
{
	REEL_PATTERN pat = reelHitPatternGet( main, main->lottery_bit, &main->reel_hit_line_bit );
	
	main->reel_hit_pattern = pat;
	
	if( pat == REEL_PATTERN_MAX ){								//�O��
		main->seq_no = SEQNO_BMODE_MISS_START;
		return( RET_NEXT );
	}
	
	if( (main->lottery_bit & LOTTERY_HITBIT_SEVEN_AND) ){		//7�q�b�g
		main->seq_no = SEQNO_BMODE_HIT_SEVEN_START;
		return( RET_NEXT );
	}
	
	if( pat == REEL_REPLAY ){									//���v���C
		main->seq_no = SEQNO_BMODE_HIT_REPLAY_START;
		return( RET_NEXT );
	}
	
	main->seq_no = SEQNO_BMODE_HIT_PAYOUT_START;				//�q�𓖂���
	return( RET_NEXT );
}

//--------------------------------------------------------------
/**
 * �{�[�i�X���[�h�@���I�����O��@�J�n
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_BMode_MissStart( SLOTMAIN *main )
{
	PlttEff_LineLightOFFAll( main );
	DDC_TypeChange( main, DDISP_PIP_STOP );
	main->frame = 0;
	main->seq_no = SEQNO_BMODE_MISS_WAIT_NEXT;
	return( RET_NEXT );
}

//--------------------------------------------------------------
/**
 * �{�[�i�X���[�h�@���I�����O��@�ꐡ�҂��̂��߂�
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_BMode_MissWaitNext( SLOTMAIN *main )
{
	main->frame += FX32_ONE;
	
	if( main->frame >= GE_FXFRAME_NOHIT_MISS_WAIT ){ 
		main->frame = 0;
		main->seq_no = SEQNO_BMODE_INIT;
		return( RET_NEXT );
	}
	
	return( RET_NON );
}

//--------------------------------------------------------------
/**
 * �{�[�i�X���[�h�@���I����q�b�g�@�y�C�A�E�g�J�n
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_BMode_HitPayOutStart( SLOTMAIN *main )
{
	main->payout = PayOutCoinGet_Small( main );
	main->payout_total += main->payout;
	main->frame = 0;
	main->seq_no = SEQNO_BMODE_HIT_PAYOUT_WAIT_NEXT;
	PayOutControlPayOutSet( main );
	DDC_TypeChange( main, DDISP_PIP_BANZAI );
	return( RET_NON );
}

//--------------------------------------------------------------
/**
 * �{�[�i�X���[�h�@���I����q�b�g�@�y�C�A�E�g�̂��߂�
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_BMode_HitPayOutWaitNext( SLOTMAIN *main )
{
	if( PayOutControlEndCheck(main) == TRUE ){
		DDC_TypeChange( main, DDISP_PIP_STOP );
		main->seq_no = SEQNO_BMODE_INIT;
		return( RET_NEXT );
	}
	
	return( RET_NON );
}

//--------------------------------------------------------------
/**
 * �{�[�i�X���[�h�@���I����q�b�g�@���v���C�J�n
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_BMode_HitReplayStart( SLOTMAIN *main )
{
	main->payout = 0;
	main->frame = 0;
	main->seq_no = SEQNO_BMODE_HIT_REPLAY_WAIT_NEXT;
	PayOutControlPayOutSet( main );
	DDC_TypeChange( main, DDISP_PIP_BANZAI );
	return( RET_NON );
}

//--------------------------------------------------------------
/**
 * �{�[�i�X���[�h�@���v���C�q�b�g�@�҂�
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_BMode_HitReplayWaitNext( SLOTMAIN *main )
{
	main->frame += FX32_ONE;
	
	if( main->frame > GE_FXFRAME_HITRP_BALL_BACK_START ){
		if( PayOutControlEndCheck(main) == TRUE ){
			DDC_TypeChange( main, DDISP_PIP_STOP );
			PlttEff_LineLightOFFAll( main );
			main->frame = 0;
			main->seq_no = SEQNO_BMODE_GAME_START;
			return( RET_NEXT );
		}
	}
	
	return( RET_NON );
}

//--------------------------------------------------------------
/**
 * �{�[�i�X���[�h�@�r�b�O�q�b�g�@�J�n
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_BMode_HitSevenStart( SLOTMAIN *main )
{
	main->payout = PayOutCoinGet_Small( main );
	main->payout_total += main->payout;
	main->frame = 0;
	main->seq_no = SEQNO_BMODE_HIT_SEVEN_WAIT_NEXT;
	PayOutControlPayOutSet( main );
	DDC_TypeChange( main, DDISP_PIP_BANZAI );
	PlttEff_MountKuraku( main );
	SlotBGM_Play( main, BGM_BIGHIT );
	
	main->eoa_reel_bighit = SlotSubEoa_ReelBigHitInit( main );
	return( RET_NON );
}

//--------------------------------------------------------------
/**
 * �{�[�i�X���[�h�@�r�b�O�q�b�g�@�x�����҂��̂��{�[�i�X�Q�[����
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_BMode_HitSevenWaitNext( SLOTMAIN *main )
{
	if( PayOutControlEndCheck(main) == TRUE ){
		EOA_Delete( main->eoa_reel_bighit );
		DDC_TypeChange( main, DDISP_PIP_STOP );
		main->seq_no = SEQNO_BGAME_INIT_FIRST;
		return( RET_NEXT );
	}
	
	return( RET_NON );
}

//==============================================================================
//	�Q�[���@�{�[�i�X�Q�[��
//==============================================================================
//--------------------------------------------------------------
/**
 * �{�[�i�X�Q�[���@����݂̂̏�����
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_BGame_InitFirst( SLOTMAIN *main )
{
	DDC_BonusFontSet( main );
	
	main->bonus_continue_count = 0;
	main->bonus_get_coin = 0;
	main->bonus_game_flag = TRUE;
	main->seq_no = SEQNO_BGAME_INIT;
	return( RET_NEXT );
}

//--------------------------------------------------------------
/**
 * �{�[�i�X�Q�[���@������
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_BGame_Init( SLOTMAIN *main )
{
	main->bonus_hit_count++;							//���R�[�h�Ƀv���X�����J�E���g
	main->bonus_continue_count++;						//�{�[�i�X��
	
	if( main->bonus_continue_count > 999 ){
		main->bonus_continue_count = 999;
	}
	
	SlotSubEoa_MoonFontInit( main, main->bonus_continue_count );
	
	main->bonus_count = BONUS_GAME_COUNT + 1;			//+1=���ŃJ�E���g������
	main->bonus_game_flag = TRUE;						//�{�[�i�X�Q�[��
	main->bonus_moonlight_flag = FALSE;					//����
	main->bonus_moonlight_red_flag = MOONRED_NON;		//��
	main->bonus_game_end_flag = FALSE;

	if( LotteryCheck_BonusContinue(main) == FALSE ){
		main->bonus_game_end_flag = TRUE;
	}
	
	main->seq_no = SEQNO_BGAME_START;
	return( RET_NEXT );
}

//--------------------------------------------------------------
/**
 * �{�[�i�X�Q�[���@�J�n
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_BGame_Start( SLOTMAIN *main )
{
	main->bonus_count--;
	GF_ASSERT( (int)main->bonus_count >= 1 );
	
	ReelButtonAttr_OFF( main, REEL_0 );
	ReelButtonAttr_OFF( main, REEL_1 );
	ReelButtonAttr_OFF( main, REEL_2 );
	PlttEff_LineLightOFFAll( main );
	PlttEff_EoaLineBetAnmStart( main );
	DDC_TypeChange( main, DDISP_PIP_STOP );
	
	main->seq_no = SEQNO_BGAME_BET;
	
	if( main->credit == 0 ){
		main->seq_no = SEQNO_MSGSET_CREDIT_0;
		main->next_seq_no = SEQNO_GAME_END;
	}else if( main->credit < BET_LOWEST_BONUS ){
		main->seq_no = SEQNO_MSGSET_CREDIT_0;
		main->next_seq_no = SEQNO_GAME_END;
	}else if( main->credit >= SLOT_COIN_MAX ){
		main->seq_no = SEQNO_MSGSET_CREDIT_MAX;
		main->next_seq_no = SEQNO_BGAME_BET;
	}
	
	return( RET_NEXT );
}

//--------------------------------------------------------------
/**
 * �{�[�i�X�Q�[���@�x�b�g
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_BGame_Bet( SLOTMAIN *main )
{
#ifdef DEBUG_ON_SLOT
	DEBUG_AutoPlayEndCheck( main ); 
	
	if( DEBUG_DebugKeyCheck(main) == TRUE ){
		return( RET_NON );
	}
	
	if( DEBUG_AutoPlayCheck(main) == TRUE ){
		main->credit -= BET_LOWEST_BONUS;
		main->bonus_get_coin -= BET_LOWEST_BONUS;
		main->bet_total += BET_LOWEST_BONUS;
		
		if( (int)main->bonus_get_coin < 0 ){
			main->bonus_get_coin = 0;
		}
		
		main->seq_no = SEQNO_BGAME_GAME_START_BUTTON_PUSH_WAIT;
		
		Snd_SePlay( SE_SLOT_BET );
		PlttEff_EoaLineBetAnmDelete( main );
		PlttEff_LineLightBetOne( main, LINE_1 );
		return( RET_NON );
	}
#endif
	
	if( keyTrg(PAD_END) != PAD_NON ){	//�I��
		main->seq_no = SEQNO_GAME_END;
		return( RET_NON );
	}
	
	if( keyTrg(PAD_BET) != PAD_NON ){
		main->credit -= BET_LOWEST_BONUS;
		main->bonus_get_coin -= BET_LOWEST_BONUS;
		main->bet_total += BET_LOWEST_BONUS;
		
		if( (int)main->bonus_get_coin < 0 ){
			main->bonus_get_coin = 0;
		}
		
		main->seq_no = SEQNO_BGAME_GAME_START_BUTTON_PUSH_WAIT;
		
		Snd_SePlay( SE_SLOT_BET );
		PlttEff_EoaLineBetAnmDelete( main );
		PlttEff_LineLightBetOne( main, LINE_1 );
		return( RET_NON );
	}
	
	return( RET_NON );
}

//--------------------------------------------------------------
/**
 * �{�[�i�X�Q�[���@�x�b�g��̃X�^�[�g�{�^���҂�
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_BGame_GameStartButtonPushWait( SLOTMAIN *main )
{
#ifdef DEBUG_ON_SLOT
	if( DEBUG_AutoPlayCheck(main) == TRUE ){
		main->seq_no = SEQNO_BGAME_GAME_START;
		return( RET_NEXT );
	}
#endif
	
	if( keyTrg(PAD_END) != PAD_NON ){	//�I��
		main->credit += BET_LOWEST_BONUS;
		main->seq_no = SEQNO_GAME_END;
		return( RET_NON );
	}
	
	if( keyTrg(PAD_GAMESTART) != PAD_NON ){
		main->seq_no = SEQNO_BGAME_GAME_START;
		return( RET_NEXT );
	}
	
	return( RET_NON );
}

//--------------------------------------------------------------
/**
 * �{�[�i�X�Q�[���@�Q�[���X�^�[�g
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_BGame_GameStart( SLOTMAIN *main )
{
	main->game_count++;
	main->bgame_count++;
	
	main->lottery_bit = LOTTERY_HITBIT_REPLAY;
	main->reel_slip_hit_flag = TRUE;
	main->auto_hit_flag = TRUE;
	
	ReelButtonAttr_OFF( main, REEL_0 );
	ReelButtonAttr_OFF( main, REEL_1 );
	ReelButtonAttr_OFF( main, REEL_2 );
	PlttEff_LineLightBetOne( main, LINE_1 );
	
	ReelControlScrollSet( main, 0 );
	ReelControlScrollSet( main, 1 );
	ReelControlScrollSet( main, 2 );
	StopButtonClear( main );
	LotterySet_Yubisashi( main );
	
	main->reel_status[REEL_0] = REEL_ST_SCROLL;
	main->reel_status[REEL_1] = REEL_ST_SCROLL;
	main->reel_status[REEL_2] = REEL_ST_SCROLL;
	main->frame = 0;
	main->seq_no = SEQNO_BGAME_REELPUSH_START_WAIT;
	
	Snd_SePlay( SE_SLOT_REEL_START );
	
	if( main->bonus_moonlight_flag == FALSE &&
		main->bonus_moonlight_red_flag == MOONRED_NON ){
		
		if( LotteryCheck_MoonLightRed(main) == TRUE ){
			main->bonus_moonlight_red_flag = MOONRED_HIT;
			main->moonred_count++;
		}
		
#ifdef DEBUG_ON_SLOT
		if( main->d_work.debug_moon_red == TRUE ){
			main->d_work.debug_moon_red = FALSE;
			main->bonus_moonlight_red_flag = MOONRED_HIT;
		}
#endif
		
		if( main->bonus_moonlight_red_flag == MOONRED_HIT ){
			PlttEff_MountMoonLight( main, MOON_RED );
		}
	}
	
	if( main->bonus_moonlight_flag == FALSE &&
		main->bonus_moonlight_red_flag == MOONRED_NON ){
		
		if( LotteryCheck_MoonLight(main) == TRUE ){
			main->bonus_moonlight_flag = TRUE;
			main->moonlight_count++;
		}
		
#ifdef DEBUG_ON_SLOT
		if( main->d_work.debug_moon_light == TRUE ){
			main->d_work.debug_moon_light = FALSE;
			main->bonus_moonlight_flag = TRUE;
		}
#endif
		if( main->bonus_moonlight_flag == TRUE ){
			PlttEff_MountMoonLight( main, MOON_LIGHT );
		}
	}
	
#ifdef PM_DEBUG
	{
		if( main->bonus_moonlight_flag != FALSE &&
			main->bonus_moonlight_red_flag != MOONRED_NON ){
			GF_ASSERT( 0 && "SLOT ERROR MOON LIGHT AND RED  0" );
		}
	}
#endif
	
#ifdef DEBUG_ON_SLOT
	if( DEBUG_AutoPlayCheck(main) == TRUE ){
		DEBUG_AutoPlayInit( main );
	}
#endif
	
	return( RET_NEXT );
}

#if 0	//�Ԃ�����A�O���Έ������������`�����X�A��
static GAMERET Game_BGame_GameStart( SLOTMAIN *main )
{
	main->game_count++;
	main->bgame_count++;
	
	main->lottery_bit = LOTTERY_HITBIT_REPLAY;
	main->reel_slip_hit_flag = TRUE;
	main->auto_hit_flag = TRUE;
	
	ReelButtonAttr_OFF( main, REEL_0 );
	ReelButtonAttr_OFF( main, REEL_1 );
	ReelButtonAttr_OFF( main, REEL_2 );
	PlttEff_LineLightBetOne( main, LINE_1 );
	
	ReelControlScrollSet( main, 0 );
	ReelControlScrollSet( main, 1 );
	ReelControlScrollSet( main, 2 );
	StopButtonClear( main );
	LotterySet_Yubisashi( main );
	
	main->reel_status[REEL_0] = REEL_ST_SCROLL;
	main->reel_status[REEL_1] = REEL_ST_SCROLL;
	main->reel_status[REEL_2] = REEL_ST_SCROLL;
	main->frame = 0;
	main->seq_no = SEQNO_BGAME_REELPUSH_START_WAIT;
	
	Snd_SePlay( SE_SLOT_REEL_START );
	
	if( main->bonus_moonlight_flag == FALSE &&
		main->bonus_moonlight_red_flag == MOONRED_NON ){
		OS_Printf( "�Ԃ����`�F�b�N\n" );
		
		if( LotteryCheck_MoonLightRed(main) == TRUE ){
			main->bonus_moonlight_red_flag = MOONRED_HIT;
			main->moonred_count++;
		}
		
#ifdef DEBUG_ON_SLOT
		if( main->d_work.debug_moon_red == TRUE ){
			main->d_work.debug_moon_red = FALSE;
			main->bonus_moonlight_red_flag = MOONRED_HIT;
		}
#endif
		
		if( main->bonus_moonlight_red_flag == MOONRED_HIT ){
			OS_Printf( "�Ԃ����@����\n" );
			PlttEff_MountMoonLight( main, MOON_RED );
		}
	}
	
	if( main->bonus_moonlight_flag == FALSE &&
		(main->bonus_moonlight_red_flag == MOONRED_NON ||
		 main->bonus_moonlight_red_flag == MOONRED_MISS) ){
		
		OS_Printf( "�����`�F�b�N\n" );
		
		if( LotteryCheck_MoonLight(main) == TRUE ){
			main->bonus_moonlight_flag = TRUE;
			main->moonlight_count++;
		}
		
#ifdef DEBUG_ON_SLOT
		if( main->d_work.debug_moon_light == TRUE ){
			main->d_work.debug_moon_light = FALSE;
			main->bonus_moonlight_flag = TRUE;
		}
#endif
		if( main->bonus_moonlight_flag == TRUE ){
			OS_Printf( "�����@�����Ɛ���\n" );
			PlttEff_MountMoonLight( main, MOON_LIGHT );
		}
	}
	
#ifdef DEBUG_ON_SLOT
	if( DEBUG_AutoPlayCheck(main) == TRUE ){
		DEBUG_AutoPlayInit( main );
	}
#endif
	
	return( RET_NEXT );
}
#endif

//--------------------------------------------------------------
/**
 * �{�[�i�X�Q�[���@�{�^�������J�n�҂�
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_BGame_ReelPushStartWait( SLOTMAIN *main )
{
	main->frame += FX32_ONE;
	
	if( main->frame >= GE_FXFRAME_BTN_PUSHWAIT ){
		main->frame = 0;
		main->seq_no = SEQNO_BGAME_REELPUSH;
		DDC_TypeChange( main, DDISP_PIP_YUBISASHI );
		return( RET_NEXT );
	}
	
	return( RET_NON );
}

//--------------------------------------------------------------
/**
 * �{�[�i�X�Q�[���@���[���{�^������
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_BGame_ReelPush( SLOTMAIN *main )
{
	u32 trg = sys.trg;
	
#ifdef DEBUG_ON_SLOT
	if( DEBUG_AutoPlayCheck(main) ){
		trg = 0;
		
		if( DEBUG_AutoPlayPushCheck(main) == TRUE ){
			trg |= DEBUG_StopButtonGetYubisashi( main );
		}
	}
#endif
	
	if( main->reel_status[REEL_0] == REEL_ST_SCROLL && (trg&PAD_REELPUSH0) ){
		main->reel_status[REEL_0] = REEL_ST_WAIT;
		StopButtonSet( main, PAD_REELPUSH0 );
		if( StopButtonCheckYubisashi(main) == FALSE ){
			main->auto_hit_flag = FALSE;
			main->reel_slip_hit_flag = FALSE;
		}
		ReelButtonAttr_ON( main, REEL_0 );
		ReelControlStopSet( main, REEL_0 );
		Snd_SePlay( SE_SLOT_REEL_STOP2 );
	}else if( main->reel_status[REEL_1] == REEL_ST_SCROLL && (trg&PAD_REELPUSH1) ){
		main->reel_status[REEL_1] = REEL_ST_WAIT;
		StopButtonSet( main, PAD_REELPUSH1 );
		if( StopButtonCheckYubisashi(main) == FALSE ){
			main->auto_hit_flag = FALSE;
			main->reel_slip_hit_flag = FALSE;
		}
		ReelButtonAttr_ON( main, REEL_1 );
		ReelControlStopSet( main, REEL_1 );
		Snd_SePlay( SE_SLOT_REEL_STOP2 );
	}else if( main->reel_status[REEL_2] == REEL_ST_SCROLL && (trg&PAD_REELPUSH2) ){
		main->reel_status[REEL_2] = REEL_ST_WAIT;
		StopButtonSet( main, PAD_REELPUSH2 );
		if( StopButtonCheckYubisashi(main) == FALSE ){
			main->auto_hit_flag = FALSE;
			main->reel_slip_hit_flag = FALSE;
		}
		ReelButtonAttr_ON( main, REEL_2 );
		ReelControlStopSet( main, REEL_2 );
		Snd_SePlay( SE_SLOT_REEL_STOP2 );
	}
	
	if( main->reel_status[REEL_0] == REEL_ST_WAIT && 
		main->reel_status[REEL_1] == REEL_ST_WAIT && 
		main->reel_status[REEL_2] == REEL_ST_WAIT ){
		main->seq_no = SEQNO_BGAME_REELSTOP_WAIT;
	}
	
	return( RET_NON );
}

//--------------------------------------------------------------
/**
 * �{�[�i�X�Q�[���@���[����~�҂�
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_BGame_ReelStopWait( SLOTMAIN *main )
{
	if( ReelControlScrollCheck(main,REEL_0) == TRUE ||
		ReelControlScrollCheck(main,REEL_1) == TRUE ||
		ReelControlScrollCheck(main,REEL_2) == TRUE ){
		return( RET_NON );
	}
	
	PlttEff_LineLightOFFAll( main );
	main->seq_no = SEQNO_BGAME_HIT_CHECK;
	return( RET_NEXT );
}

//--------------------------------------------------------------
/**
 * �{�[�i�X�Q�[���@�q�b�g�`�F�b�N
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_BGame_HitCheck( SLOTMAIN *main )
{
	REEL_PATTERN pat =
		reelHitPatternGetBonus( main, main->lottery_bit, &main->reel_hit_line_bit );
	
	main->reel_hit_pattern = pat;
	
	if( pat == REEL_PATTERN_MAX ){								//�q�b�g����
		if( main->bonus_moonlight_red_flag == MOONRED_HIT ){	//���v���C�O��
			main->bonus_moonlight_red_flag = MOONRED_MISS;
		}
		
		main->seq_no = SEQNO_BGAME_MISS_START;
		return( RET_NEXT );									
	}
	
	if( main->bonus_moonlight_red_flag == MOONRED_HIT ){	//���v���C�O��
		main->bonus_moonlight_red_flag = MOONRED_SUCCESS;
	}
	
	main->seq_no = SEQNO_BGAME_PAYOUT_START;				//������
	return( RET_NEXT );
}

//--------------------------------------------------------------
/**
 * �{�[�i�X�Q�[���@�~�X
 * @param	main	SLOTMAIN
 * @retval	GAMERET GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_BGame_MissStart( SLOTMAIN *main )
{
	PlttEff_LineLightOFFAll( main );
	DDC_TypeChange( main, DDISP_PIP_STOP );
	
	if( (int)main->bonus_count <= 1 ){
		main->seq_no = SEQNO_BGAME_ONE_GAME_FINISH;			//�P�Q�[��������
	}else{
		main->seq_no = SEQNO_BGAME_START;
	}
	
	return( RET_NON );
}

//--------------------------------------------------------------
/**
 * �{�[�i�X�Q�[���@�x�����@�J�n
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_BGame_PayOutStart( SLOTMAIN *main )
{
	main->payout = DATA_SlotPayOutBonus[main->reel_hit_pattern];
	main->payout_total += main->payout;
	
	PayOutControlPayOutSet( main );
	DDC_TypeChange( main, DDISP_PIP_BANZAI );
	
	main->frame = 0;
	main->seq_no = SEQNO_BGAME_PAYOUT_WAIT_NEXT;
	return( RET_NON );
}

//--------------------------------------------------------------
/**
 * �{�[�i�X�Q�[���@�x�����҂��㎟��
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_BGame_PayOutWaitNext( SLOTMAIN *main )
{
	if( PayOutControlEndCheck(main) == FALSE ){
		return( RET_NON );
	}
	
	DDC_TypeChange( main, DDISP_PIP_STOP );
	
	if( (int)main->bonus_count <= 1 ){
		main->seq_no = SEQNO_BGAME_ONE_GAME_FINISH;				//���[�g�_�E��
	}else{
		main->seq_no = SEQNO_BGAME_START;					//���Q�[����
	}
	
	return( RET_NEXT );
}

//--------------------------------------------------------------
/**
 * �{�[�i�X�Q�[���@�P�Q�[������
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_BGame_OneGameFinish( SLOTMAIN *main )
{
#ifdef DEBUG_ON_SLOT
	if( main->d_work.debug_bonus_end == TRUE ){
		main->d_work.debug_bonus_end = FALSE;
		main->bonus_game_end_flag = TRUE;
		main->bonus_moonlight_flag = FALSE;
	}
#endif
	
#ifdef PM_DEBUG
	{
		if( main->bonus_moonlight_flag != FALSE &&
			main->bonus_moonlight_red_flag != MOONRED_NON ){
			GF_ASSERT( 0 && "SLOT ERROR MOON LIGHT AND RED  1" );
		}
	}
#endif
	
	main->bonus_count--;	//0��
	GF_ASSERT( main->bonus_count == 0 );
	
	if( main->bonus_game_end_flag == TRUE && main->bonus_moonlight_flag == FALSE ){
		DDC_TypeChange( main, DDISP_BONUS_END );
		main->seq_no = SEQNO_BGAME_PIP_OUT;
		return( RET_NON );
	}
	
	main->seq_no = SEQNO_BGAME_RATE_DOWN;
	return( RET_NEXT );
}

//--------------------------------------------------------------
/**
 * �{�[�i�X�Q�[���@�p�����_�E��
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_BGame_RateDown( SLOTMAIN *main )
{
	BCEFF bceff;
	
	LotterySet_BonusContinueDown( main );
	bceff = LotteryGet_BonusContinueEffect( main );
	
	if( main->bonus_moonlight_flag == TRUE ){				//����
		bceff = BCEFF_ANENCORE;								//�A���R�[����
	}
	
#ifdef DEBUG_ON_SLOT
	{
		if( main->d_work.debug_bonus_end_effect != BCEFF_MAX ){
			bceff = main->d_work.debug_bonus_end_effect;
			main->d_work.debug_bonus_end_effect = BCEFF_MAX;
		}
	}
#endif
	
	if( bceff == BCEFF_ANENCORE ){
		DDC_TypeChange( main, DDISP_PIP_ANENCORE );
		main->seq_no = SEQNO_BGAME_ANENCORE;
		return( RET_NON );
	}
	
	if( bceff == BCEFF_BACK ){								//�s�b�s�߂艉�o
		DDC_TypeChange( main, DDISP_PIP_RECOVER );
		main->seq_no = SEQNO_BGAME_PIP_RECOVER;
		return( RET_NON );
	}
	
	Snd_PMVoicePlay( MONSNO_PIPPI );
	main->seq_no = SEQNO_BGAME_INIT;						//���Q�[����
	return( RET_NON );
}

//--------------------------------------------------------------
/**
 * �Q�[���@�{�[�i�X�Q�[���@�A���R�[��
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_BGame_Anencore( SLOTMAIN *main )
{
	if( DDC_EndCheck(main) == FALSE ){
		return( RET_NON );
	}
	
	main->seq_no = SEQNO_BGAME_INIT;
	return( RET_NEXT );
}

//--------------------------------------------------------------
/**
 * �Q�[���@�{�[�i�X�Q�[���@�s�b�s����
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_BGame_PipRecover( SLOTMAIN *main )
{
	if( DDC_EndCheck(main) == FALSE ){
		return( RET_NON );
	}
	
	main->seq_no = SEQNO_BGAME_INIT;
	return( RET_NEXT );
}

//--------------------------------------------------------------
/**
 * �Q�[���@�{�[�i�X�Q�[���@�s�b�s�ޏ�
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_BGame_PipOut( SLOTMAIN *main )
{
	if( DDC_EndCheck(main) == FALSE ){
		return( RET_NON );
	}
	
	if( main->bonus_continue_count > main->bonus_continue_count_max ){
		main->bonus_continue_count_max = main->bonus_continue_count;
	}
	
	SlotBGM_Play( main, BGM_NORMAL );
	PlttEff_MountAkaruku( main );
	main->seq_no = SEQNO_GAME_INIT;
	return( RET_NEXT );
}

//==============================================================================
//	�Q�[���@�I���@���b�Z�[�W
//==============================================================================
//--------------------------------------------------------------
/**
 * �Q�[���@�R�C��3���ȉ����b�Z�[�W�J�n
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_MsgCredit3Start( SLOTMAIN *main )
{
	SlotTalkWin_Write( main, msg_00 );
	main->seq_no = SEQNO_MSGSET_WAIT_NEXT;
	return( RET_NON );
}

//--------------------------------------------------------------
/**
 * �Q�[���@�R�C��0���b�Z�[�W�J�n
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_MsgCredit0Start( SLOTMAIN *main )
{
	SlotTalkWin_Write( main, msg_02 );
	main->seq_no = SEQNO_MSGSET_WAIT_NEXT;
	return( RET_NON );
}

//--------------------------------------------------------------
/**
 * �Q�[���@�R�C��50000���b�Z�[�W�J�n
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_MsgCreditMaxStart( SLOTMAIN *main )
{
	SlotTalkWin_Write( main, msg_01 );
	main->seq_no = SEQNO_MSGSET_WAIT_NEXT;
	return( RET_NON );
}

//--------------------------------------------------------------
/**
 * �Q�[���@���b�Z�[�W�\��������
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_MsgWaitNext( SLOTMAIN *main )
{
	if( keyTrg(PAD_BUTTON_A|PAD_BUTTON_B) ){
		SlotTalkWin_Clear( main );
		main->seq_no = main->next_seq_no;
	}
	
	return( RET_NON );
}

//--------------------------------------------------------------
/**
 * �Q�[���@�I��
 * @param	main	SLOTMAIN
 * @retval	GAMERET	GAMERET
 */
//--------------------------------------------------------------
static GAMERET Game_End( SLOTMAIN *main )
{
	PlttEff_EoaLineBetAnmDelete( main );
	return( RET_END );
}

//--------------------------------------------------------------
///	�X���b�g�Q�[������e�[�u��
//--------------------------------------------------------------
static GAMERET (* const DATA_SlotGameTbl[SEQNO_MAX])( SLOTMAIN *main ) =
{
	//�ʏ�Q�[��
	Game_Init,
	Game_Bet,
	Game_GameStartButtonPushWait,
	Game_GameStart,
	Game_ReelPushStartWait,
	Game_ReelPush,
	Game_ReelStopWait,
	Game_HitCheck,
	Game_NoHitMissStart,
	Game_NoHitMissWaitNext,
	Game_HitMissStart,
	Game_HitMissWaitNext,
	Game_HitPayOutStart,
	Game_HitPayOutWaitNext,
	Game_HitReplayStart,
	Game_HitReplayWaitNext,
	Game_HitMissBonusStart,
	Game_HitMissBonusBallStopWait,
	Game_HitMissBonusWaitNext,
	Game_HitPayOutBonusStart,
	Game_HitPayOutBonusWaitNext,
	Game_HitReplayBonusStart,
	Game_HitReplayBonusWaitNext,
	//�{�[�i�X���[�h
	Game_BMode_NormalGameChangeInit,
	Game_BMode_NormalGameReplayChangeInit,
	Game_BMode_Init,
	Game_BMode_Bet,
	Game_BMode_GameStartButtonPushWait,
	Game_BMode_GameStart,
	Game_BMode_ReelPushStartWait,
	Game_BMode_ReelPush,
	Game_BMode_ReelStopWait,
	Game_BMode_HitCheck,
	Game_BMode_MissStart,
	Game_BMode_MissWaitNext,
	Game_BMode_HitPayOutStart,
	Game_BMode_HitPayOutWaitNext,
	Game_BMode_HitReplayStart,
	Game_BMode_HitReplayWaitNext,
	Game_BMode_HitSevenStart,
	Game_BMode_HitSevenWaitNext,
	//�{�[�i�X�Q�[��
	Game_BGame_InitFirst,
	Game_BGame_Init,
	Game_BGame_Start,
	Game_BGame_Bet,
	Game_BGame_GameStartButtonPushWait,
	Game_BGame_GameStart,
	Game_BGame_ReelPushStartWait,
	Game_BGame_ReelPush,
	Game_BGame_ReelStopWait,
	Game_BGame_HitCheck,
	Game_BGame_MissStart,
	Game_BGame_PayOutStart,
	Game_BGame_PayOutWaitNext,
	Game_BGame_OneGameFinish,
	Game_BGame_RateDown,
	Game_BGame_Anencore,
	Game_BGame_PipRecover,
	Game_BGame_PipOut,
	//���b�Z�[�W�A�I��
	Game_MsgCredit3Start,
	Game_MsgCredit0Start,
	Game_MsgCreditMaxStart,
	Game_MsgWaitNext,
	Game_End,
};

//==============================================================================
//�@���[������
//==============================================================================
//--------------------------------------------------------------
/**
 * ���[�����䏈���Z�b�g
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slot_ReelControlSet( SLOTMAIN *main )
{
	u32 i = 0;
	REELCONTROL *reelcont = main->reelcont;
	
	do{
		reelcont->seq_no = 0;
		reelcont->reel_no = i;
		reelcont->main = main;
		reelcont->tcb = TCB_Add( ReelControlTcb, &main->reelcont[i], TCBPRI_REELCONTROL0+i );
		reelcont++; i++;
	}while( i < REEL_MAX );
}

//--------------------------------------------------------------
/**
 * ���[�����䏈���폜
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slot_ReelControlDelete( SLOTMAIN *main )
{
	u32 i = 0;
	do{ TCB_Delete( main->reelcont[i].tcb ); i++; }while( i < REEL_MAX );
}

//--------------------------------------------------------------
/**
 * ���[������@��]����
 * @param	main	SLOTMAIN
 * @param	no		REEL_NUM
 * @retval	nothing
 */
//--------------------------------------------------------------
static void ReelControlScrollSet( SLOTMAIN *main, REEL_NUM no )
{
	main->reelcont[no].seq_no = RC_SCROLL;
	main->reelcont[no].scroll_flag = TRUE;
}

//--------------------------------------------------------------
/**
 * ���[������@��~����
 * @param	main	SLOTMAIN
 * @param	no		REEL_NUM
 * @retval	nothing
 */
//--------------------------------------------------------------
static void ReelControlStopSet( SLOTMAIN *main, REEL_NUM no )
{
	main->reelcont[no].seq_no = RC_STOP_SET;
}

//--------------------------------------------------------------
/**
 * ���[������@�X�N���[���`�F�b�N
 * @param	main	SLOTMAIN
 * @param	no		REEL_NUM
 * @retval	int		TRUE=��]��
 */
//--------------------------------------------------------------
static int ReelControlScrollCheck( SLOTMAIN *main, REEL_NUM no )
{
	return( main->reelcont[no].scroll_flag );
}

//--------------------------------------------------------------
/**
 * ���[�����䓮��
 * @param	tcb		TCB_PTR
 * @param	wk		tcb work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void ReelControlTcb( TCB_PTR tcb, void *wk )
{
	REELCONTROL *reel = wk;
	SLOTMAIN *main = reel->main;
	
	while( DATA_ReelControlTbl[reel->seq_no](reel,main) == TRUE ){};
}

//--------------------------------------------------------------
/**
 * ���[������@����
 * @param	reel	REELCONTROL
 * @param	main	SLOTMAIN *
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int ReelControl_Non( REELCONTROL *reel, SLOTMAIN *main )
{
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ���[������@�X�N���[��
 * @param	reel	REELCONTROL
 * @param	main	SLOTMAIN *
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int ReelControl_Scroll( REELCONTROL *reel, SLOTMAIN *main )
{
	ReelScroll( main, reel->reel_no, main->reel_speed );
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ���[������@��~�Z�b�g
 * @param	reel	REELCONTROL
 * @param	main	SLOTMAIN *
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int ReelControl_StopSet( REELCONTROL *reel, SLOTMAIN *main )
{
	reel->seq_no++;
	reel->reel_hit_grid_y = 0;
	reel->reel_slip_grid_y = 0;
	
	if( main->reel_slip_hit_flag == TRUE ){
		if( main->bonus_game_flag == FALSE ){
			if( ReelSlip_Hit(reel,main) == FALSE ){
				ReelSlip_Miss( reel, main );
				main->reel_slip_hit_flag = FALSE;
			}
		}else{
			if( ReelSlipBonus_Hit(reel,main) == FALSE ){
				ReelSlipBonus_Miss( reel, main );
				main->reel_slip_hit_flag = FALSE;
			}
		}
	}else{
		if( main->bonus_game_flag == FALSE ){
			ReelSlip_Miss( reel, main );
		}else{
			ReelSlipBonus_Miss( reel, main );
		}
	}
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * ���[������@��~
 * @param	reel	REELCONTROL
 * @param	main	SLOTMAIN *
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int ReelControl_Stop( REELCONTROL *reel, SLOTMAIN *main )
{
	fx32 d,speed;
	int no = reel->reel_no;
	int flag = FALSE;
	
	d = main->reel_dot_y[no] % NUM_FX32( REEL_PT_V_SIZE );
	
	if( d ){
		flag = TRUE;
		speed = main->reel_speed;
		if( d < speed ){ speed = d; }
		d = ReelScrollGrid( main, no, speed );
	}else if( reel->reel_slip_grid_y ){
		flag = TRUE;
		reel->reel_slip_grid_y--;
		ReelScroll( main, no, main->reel_speed );
		d = main->reel_dot_y[no] % NUM_FX32( REEL_PT_V_SIZE );
	}
	
	if( d == 0 && reel->reel_slip_grid_y == 0 ){
		fx32 tbl[5] = {NUM_FX32(4),NUM_FX32(8),NUM_FX32(8),NUM_FX32(8),NUM_FX32(16)};
		s32 slip_grid_y = reel->reel_slip_grid_y;
		if( slip_grid_y > 4 ){ slip_grid_y = 4; }
		reel->slip_dot_y = tbl[slip_grid_y];
		reel->frame = 0;
		reel->seq_no++;
		
		if( flag == FALSE ){	//���[���������Ă��Ȃ�
			return( TRUE );
		}
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ���[������@��~�U��
 * @param	reel	REELCONTROL
 * @param	main	SLOTMAIN *
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int ReelControl_StopShake( REELCONTROL *reel, SLOTMAIN *main )
{
	int no = reel->reel_no;
	
	main->reel_offs_y[no] = reel->slip_dot_y;
	reel->slip_dot_y = -reel->slip_dot_y;
	reel->frame++;
	
	if( (reel->frame&0x01) == 0 ){
		reel->slip_dot_y >>= 2;
	}
	
	if( reel->slip_dot_y == 0 ){
		reel->seq_no = RC_NON;
		reel->scroll_flag = FALSE;
		main->reel_offs_y[no] = 0;
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
///	���[������e�[�u��
//--------------------------------------------------------------
static int (* const DATA_ReelControlTbl[RC_MAX])( REELCONTROL *reel, SLOTMAIN *main ) =
{
	ReelControl_Non,
	ReelControl_Scroll,
	ReelControl_StopSet,
	ReelControl_Stop,
	ReelControl_StopShake,
};

//==============================================================================
//	���[���@�X�x��
//==============================================================================
//--------------------------------------------------------------
/**
 * ���[���q�b�g�X�x���Z�b�g
 * @param	reel	REELCONTROL
 * @param	main	SLOTMAIN
 * @retval	int		TRUE=�q�b�g FALSE=�����薳��
 */
//--------------------------------------------------------------
static int ReelSlip_Hit( REELCONTROL *reel, SLOTMAIN *main )
{
	if( main->lottery_bit == 0 ){
		return( FALSE );
	}
	
	switch( reel->reel_no ){
	case REEL_0: return( Reel0Slip_HitSlip(reel,main) );
	case REEL_1: return( Reel1Slip_HitSlip(reel,main) );
	case REEL_2: return( Reel2Slip_HitSlip(reel,main) );
	}
	
	GF_ASSERT( 0 );
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ���[���q�b�g�X�x���Z�b�g�@�{�[�i�X�P�R
 * @param	reel	REELCONTROL
 * @param	main	SLOTMAIN
 * @retval	int		TRUE=�q�b�g FALSE=�����薳��
 */
//--------------------------------------------------------------
static int ReelSlipBonus_Hit( REELCONTROL *reel, SLOTMAIN *main )
{
	if( main->lottery_bit == 0 ){
		return( FALSE );
	}
	
	{
		REEL_PATTERN hit = lotteryHitBitPattern( main->lottery_bit );
		return( Reel012SlipBonus_HitSlip(reel,main,hit) );
	}
}

//--------------------------------------------------------------
/**
 * ���[���O�@�q�b�g�X�x��
 * @param	reel	REELCONTROL
 * @param	main	SLOTMAIN
 * @retval	int		TRUE=�q�b�g FALSE=����
 */
//--------------------------------------------------------------
static int Reel0Slip_HitSlip( REELCONTROL *reel, SLOTMAIN *main )
{
	REEL_PATTERN hit = lotteryHitBitPattern( main->lottery_bit );
	
	if( hit == REEL_PATTERN_MAX ){
		return( FALSE );
	}
	
	if( ReelSlip_StartSlipCheck(reel,main) == TRUE ){
		return( Reel0Slip_HitSlipFirst(reel,main,hit) );
	}
	
	return( Reel0Slip_HitSlipAfter(reel,main,hit) );
}

//--------------------------------------------------------------
/**
 * ���[���P�@�q�b�g�X�x��
 * @param	reel	REELCONTROL
 * @param	main	SLOTMAIN
 * @param	hit		REEL_PATTERN
 * @retval	int		TRUE=�q�b�g FALSE=����
 */
//--------------------------------------------------------------
static int Reel1Slip_HitSlip( REELCONTROL *reel, SLOTMAIN *main )
{
	REEL_PATTERN hit = lotteryHitBitPattern( main->lottery_bit );
	
	if( hit == REEL_PATTERN_MAX ){
		return( FALSE );
	}
	
	if( ReelSlip_StartSlipCheck(reel,main) == TRUE ){
		return( Reel12Slip_HitSlipFirst(reel,main,hit) );
	}
	
	return( Reel12Slip_HitSlipAfter(reel,main,hit) );
}

//--------------------------------------------------------------
/**
 * ���[���Q�@�q�b�g�X�x��
 * @param	reel	REELCONTROL
 * @param	main	SLOTMAIN
 * @retval	int		TRUE=�q�b�g FALSE=����
 */
//--------------------------------------------------------------
static int Reel2Slip_HitSlip( REELCONTROL *reel, SLOTMAIN *main )
{
	REEL_PATTERN hit = lotteryHitBitPattern( main->lottery_bit );
	
	if( hit == REEL_PATTERN_MAX ){
		return( FALSE );
	}
	
	if( ReelSlip_StartSlipCheck(reel,main) == TRUE ){
		return( Reel12Slip_HitSlipFirst(reel,main,hit) );
	}
	
	return( Reel12Slip_HitSlipAfter(reel,main,hit) );
}

//--------------------------------------------------------------
/**
 * ���[���O�@�q�b�g�X�x���@����
 * @param	reel	REELCONTROL
 * @param	main	SLOTMAIN
 * @param	hit		REEL_PATTERN
 * @retval	int		TRUE=�q�b�g FALSE=����
 */
//--------------------------------------------------------------
static int Reel0Slip_HitSlipFirst( REELCONTROL *reel, SLOTMAIN *main, REEL_PATTERN hit )
{
	int i,j,max,prm,rnd;
	int no = reel->reel_no;
	
	for( i = 1; i <= 3; i++ ){							//���Ֆ�
		if(	Slot_ReelPatternGridGet(main,no,i) == hit ){
			for( j = 0; (i+j) <= 3; j++ ){ 
				if( Reel0Slip_PatCherry1HitCheck(main,j,hit) == TRUE ){
					reel->reel_hit_grid_y = i+j;
					reel->reel_slip_grid_y = j;
					return( TRUE );
				}
			}
		}
	}
	
	max = SLIP_MAX;
	
	if( main->auto_hit_flag == TRUE ){
		max = REEL_PT_MAX;
	}
	
	rnd = (int)main->reel_grid_y[REEL_0];
	
	for( i = 1; i <= max; i++ ){
		if( Slot_ReelPatternGridGet(main,no,1-i) == hit ){
			for( j = 0; j < 3; j++ ){
				if( Reel0Slip_PatCherry1HitCheck(main,i+j,hit) == TRUE ){
					//0,1�̏ꍇ�͈ʒu�����_���ŏ㉺����U��
					if( j == 0 ){
						prm = rnd % 4;
						if( prm == 0 && Reel0Slip_PatCherry1HitCheck(main,i+2,hit) == TRUE ){
							reel->reel_hit_grid_y = 3;
							reel->reel_slip_grid_y = i + 2;
							return( TRUE );
						}
					}else if( j == 1 ){
						prm = rnd % 6;
						if( prm < 2 && Reel0Slip_PatCherry1HitCheck(main,i+2,hit) == TRUE ){
							reel->reel_hit_grid_y = 3;
							reel->reel_slip_grid_y = i + 2;
							return( TRUE );
						}
					}	
					
					reel->reel_hit_grid_y = 1 + j;
					reel->reel_slip_grid_y = i + j;
					return( TRUE );
				}
			}
		}
	}
	
	#ifdef PM_DEBUG
	if( main->auto_hit_flag == TRUE ){
		GF_ASSERT( 0 && "Reel0Slip_HitSlipFirst() auot error" );
	}
	#endif
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ���[��0�@�q�b�g�X�x���@���Ɏ~�߂Ă��郊�[���A��
 * @param	reel	REELCONTROL
 * @param	main	SLOTMAIN
 * @param	hit		REEL_PATTERN
 * @retval	int		TRUE=�q�b�g FALSE=����
 */
//--------------------------------------------------------------
static int Reel0Slip_HitSlipAfter( REELCONTROL *reel, SLOTMAIN *main, REEL_PATTERN hit )
{
	int i,j,pos0,pos1,pos2,max;
	int no = reel->reel_no;
	
	if( ReelSlip_HitStopPosGet(reel,main,&pos0,&pos1,&pos2) == FALSE ){
		return( FALSE );
	}
	
	//���Ֆʃ`�F�b�N
	if( Reel0Slip_PatCherry1HitCheck(main,0,hit) == TRUE ){
		if( Slot_ReelPatternGridGet(main,no,pos0) == hit ){
			reel->reel_hit_grid_y = pos0;
			reel->reel_slip_grid_y = 0;
			return( TRUE );
		}
	
		if( pos1 != 0 && Slot_ReelPatternGridGet(main,no,pos1) == hit ){
			reel->reel_hit_grid_y = pos1;
			reel->reel_slip_grid_y = 0;
			return( TRUE );
		}
	
		if( pos2 != 0 && Slot_ReelPatternGridGet(main,no,pos2) == hit ){
			reel->reel_hit_grid_y = pos2;
			reel->reel_slip_grid_y = 0;
			return( TRUE );
		}
	}
	
	max = SLIP_MAX;
	
	if( main->auto_hit_flag == TRUE ){
		max = REEL_PT_MAX;
	}
	
	if( pos1 == 0 ){			//pos0�̂�
		for( i = 1; i <= max; i++ ){
			if( Slot_ReelPatternGridGet(main,no,pos0-i) == hit ){
				if( Reel0Slip_PatCherry1HitCheck(main,i,hit) == TRUE ){
					reel->reel_hit_grid_y = pos0;
					reel->reel_slip_grid_y = i;
					return( TRUE );
				}
			}
		}
		
		#ifdef PM_DEBUG
		if( main->auto_hit_flag == TRUE ){
			GF_ASSERT( 0 && "Reel0Slip_HitSlipAfter() auot error sono 1" );
		}
		#endif
		
		return( FALSE );
	}
	
	//pos0,1 hit
	if( pos2 == 0 ){
		for( i = 1; i <= max; i++ ){
			if( (i&0x01) ){				//�D�揇�� 0����
				if( Slot_ReelPatternGridGet(main,no,pos0-i) == hit ){
					if( Reel0Slip_PatCherry1HitCheck(main,i,hit) == TRUE ){
						reel->reel_hit_grid_y = pos0;
						reel->reel_slip_grid_y = i;
						return( TRUE );
					}
				}
				
				if( Slot_ReelPatternGridGet(main,no,pos1-i) == hit ){
					if( Reel0Slip_PatCherry1HitCheck(main,i,hit) == TRUE ){
						reel->reel_hit_grid_y = pos1;
						reel->reel_slip_grid_y = i;
						return( TRUE );
					}
				}
			}else{							//�P����
				if( Slot_ReelPatternGridGet(main,no,pos1-i) == hit ){
					if( Reel0Slip_PatCherry1HitCheck(main,i,hit) == TRUE ){
						reel->reel_hit_grid_y = pos1;
						reel->reel_slip_grid_y = i;
						return( TRUE );
					}
				}
				
				if( Slot_ReelPatternGridGet(main,no,pos0-i) == hit ){
					if( Reel0Slip_PatCherry1HitCheck(main,i,hit) == TRUE ){
						reel->reel_hit_grid_y = pos0;
						reel->reel_slip_grid_y = i;
						return( TRUE );
					}
				}
			}
		}
		
		#ifdef PM_DEBUG
		if( main->auto_hit_flag == TRUE ){
			GF_ASSERT( 0 && "Reel0Slip_HitSlipAfter() auot error sono2" );
		}
		#endif
		
		return( FALSE );
	}
	
	//pos0,1,2
	for( i = 1; i <= max; i++ ){
		int prm = i & 0x03;
		
		if( prm == 0 ){
			if( Slot_ReelPatternGridGet(main,no,pos0-i) == hit ){
				if( Reel0Slip_PatCherry1HitCheck(main,i,hit) == TRUE ){
					reel->reel_hit_grid_y = pos0;
					reel->reel_slip_grid_y = i;
					return( TRUE );
				}
			}
			
			if( Slot_ReelPatternGridGet(main,no,pos1-i) == hit ){
				if( Reel0Slip_PatCherry1HitCheck(main,i,hit) == TRUE ){
					reel->reel_hit_grid_y = pos1;
					reel->reel_slip_grid_y = i;
					return( TRUE );
				}
			}
			
			if( Slot_ReelPatternGridGet(main,no,pos2-i) == hit ){
				if( Reel0Slip_PatCherry1HitCheck(main,i,hit) == TRUE ){
					reel->reel_hit_grid_y = pos2;
					reel->reel_slip_grid_y = i;
					return( TRUE );
				}
			}
		}else if( prm == 1 ){
			if( Slot_ReelPatternGridGet(main,no,pos1-i) == hit ){
				if( Reel0Slip_PatCherry1HitCheck(main,i,hit) == TRUE ){
					reel->reel_hit_grid_y = pos1;
					reel->reel_slip_grid_y = i;
					return( TRUE );
				}
			}
			
			if( Slot_ReelPatternGridGet(main,no,pos0-i) == hit ){
				if( Reel0Slip_PatCherry1HitCheck(main,i,hit) == TRUE ){
					reel->reel_hit_grid_y = pos0;
					reel->reel_slip_grid_y = i;
					return( TRUE );
				}
			}
		}else{
			if( Slot_ReelPatternGridGet(main,no,pos2-i) == hit ){
				if( Reel0Slip_PatCherry1HitCheck(main,i,hit) == TRUE ){
					reel->reel_hit_grid_y = pos2;
					reel->reel_slip_grid_y = i;
					return( TRUE );
				}
			}
			
			if( Slot_ReelPatternGridGet(main,no,pos0-i) == hit ){
				if( Reel0Slip_PatCherry1HitCheck(main,i,hit) == TRUE ){
					reel->reel_hit_grid_y = pos0;
					reel->reel_slip_grid_y = i;
					return( TRUE );
				}
			}
			
			if( Slot_ReelPatternGridGet(main,no,pos1-i) == hit ){
				if( Reel0Slip_PatCherry1HitCheck(main,i,hit) == TRUE ){
					reel->reel_hit_grid_y = pos1;
					reel->reel_slip_grid_y = i;
					return( TRUE );
				}
			}
		}
	}
	
	#ifdef PM_DEBUG
	if( main->auto_hit_flag == TRUE ){
		GF_ASSERT( 0 && "Reel0Slip_HitSlipAfter() auot error sono3" );
	}
	#endif
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ���[��1,2�@�q�b�g�X�x���@����
 * @param	reel	REELCONTROL
 * @param	main	SLOTMAIN
 * @param	hit		REEL_PATTERN
 * @retval	int		TRUE=�q�b�g FALSE=����
 */
//--------------------------------------------------------------
static int Reel12Slip_HitSlipFirst( REELCONTROL *reel, SLOTMAIN *main, REEL_PATTERN hit )
{
	int i,j,max;
	int no = reel->reel_no;
	
	for( i = 1; i <= 3; i++ ){							//���Ֆ�
		if( Slot_ReelPatternGridGet(main,no,i) == hit ){
			reel->reel_hit_grid_y = i;
			reel->reel_slip_grid_y = 0;
			return( TRUE );
		}
	}
	
	max = SLIP_MAX;
	
	if( main->auto_hit_flag == TRUE ){
		max = REEL_PT_MAX;
	}
	
	for( i = 1; i <= max; i++ ){
		if( Slot_ReelPatternGridGet(main,no,1-i) == hit ){
			j = i % 4;
			
			if( j == 1 ){						//�X�x��1 ->�@��
				reel->reel_hit_grid_y = 3;
				reel->reel_slip_grid_y = i + 2;
				return( TRUE );
			}
			
			if( j == 2 || j == 3 ){				//�X�x��2,3 -> ��
				reel->reel_hit_grid_y = 2;
				reel->reel_slip_grid_y = i + 1;
				return( TRUE );
			}
			
			reel->reel_hit_grid_y = 1;			//�X�x��4 ->�@��
			reel->reel_slip_grid_y = i;
			return( TRUE );
		}
	}
	
	#ifdef PM_DEBUG
	if( main->auto_hit_flag == TRUE ){
		GF_ASSERT( 0 && "Reel12Slip_HitSlipFirst() auot error" );
	}
	#endif
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ���[��12���ʁ@�q�b�g�X�x���@���Ɏ~�߂Ă��郊�[���A��
 * @param	reel	REELCONTROL
 * @param	main	SLOTMAIN
 * @param	hit		REEL_PATTERN
 * @retval	int		TRUE=�q�b�g FALSE=����
 */
//--------------------------------------------------------------
static int Reel12Slip_HitSlipAfter( REELCONTROL *reel, SLOTMAIN *main, REEL_PATTERN hit )
{
	int i,j,prm,pos0,pos1,pos2,max=SLIP_MAX,no=reel->reel_no;
	
	if( ReelSlip_HitStopPosGet(reel,main,&pos0,&pos1,&pos2) == FALSE ){
		return( FALSE );
	}
	
	//���Ֆʃ`�F�b�N
	if( Slot_ReelPatternGridGet(main,no,pos0) == hit ){
		reel->reel_hit_grid_y = pos0;
		reel->reel_slip_grid_y = 0;
		return( TRUE );
	}
	
	if( pos1 != 0 && Slot_ReelPatternGridGet(main,no,pos1) == hit ){
		reel->reel_hit_grid_y = pos1;
		reel->reel_slip_grid_y = 0;
		return( TRUE );
	}
	
	if( pos2 != 0 && Slot_ReelPatternGridGet(main,no,pos2) == hit ){
		reel->reel_hit_grid_y = pos2;
		reel->reel_slip_grid_y = 0;
		return( TRUE );
	}
	
	max = SLIP_MAX;
	
	if( main->auto_hit_flag == TRUE ){
		max = REEL_PT_MAX;
	}
	
	if( pos1 == 0 ){			//pos0�̂�
		for( i = 1; i <= max; i++ ){
			if( Slot_ReelPatternGridGet(main,no,pos0-i) == hit ){
				reel->reel_hit_grid_y = pos0;
				reel->reel_slip_grid_y = i;
				return( TRUE );
			}
		}
		
		#ifdef PM_DEBUG
		if( main->auto_hit_flag == TRUE ){
			GF_ASSERT( 0 && "Reel12Slip_HitSlipAfter() auot error sono 1" );
		}
		#endif
		
		return( FALSE );
	}
	
	prm = (int)main->reel_grid_y[no];
	
	#ifdef DEBUG_ON_SLOT
	{
	/*	if( no == REEL_1 ){
			if( pos2 == 0 ){
				OS_Printf( "���[��1�X�x���@2�ӏ��@prm=%d,0x01=%d\n", prm, (prm&0x01) );
			}else{
				OS_Printf( "���[��1�X�x���@3�ӏ��@prm=%d,0x01=%d\n", prm, (prm&0x01) );
			}
		} */
	}
	#endif
	
	//pos0,1 hit
	if( pos2 == 0 ){
		if( (prm & 0x01) ){
			for( i = 1; i <= max; i++ ){						//�D�揇�� 0����
				if( Slot_ReelPatternGridGet(main,no,pos0-i) == hit ){
					reel->reel_hit_grid_y = pos0;
					reel->reel_slip_grid_y = i;
					return( TRUE );
				}
			}
			
			for( i = 1; i <= max; i++ ){
				if( Slot_ReelPatternGridGet(main,no,pos1-i) == hit ){
					reel->reel_hit_grid_y = pos1;
					reel->reel_slip_grid_y = i;
					return( TRUE );
				}
			}
		}else{													//1����
			for( i = 1; i <= max; i++ ){
				if( Slot_ReelPatternGridGet(main,no,pos1-i) == hit ){
					reel->reel_hit_grid_y = pos1;
					reel->reel_slip_grid_y = i;
					return( TRUE );
				}
			}
			
			for( i = 1; i <= max; i++ ){
				if( Slot_ReelPatternGridGet(main,no,pos0-i) == hit ){
					reel->reel_hit_grid_y = pos0;
					reel->reel_slip_grid_y = i;
					return( TRUE );
				}
			}
		}
		
		#ifdef PM_DEBUG
		if( main->auto_hit_flag == TRUE ){
			GF_ASSERT( 0 && "Reel12Slip_HitSlipAfter() auot error sono2" );
		}
		#endif
		
		return( FALSE );
	}
	
	prm %= 3;
	
	if( prm == 0 ){				//�D�揇�ʁ@0����
		for( i = 1; i <= max; i++ ){
			if( Slot_ReelPatternGridGet(main,no,pos0-i) == hit ){
				reel->reel_hit_grid_y = pos0;
				reel->reel_slip_grid_y = i;
				return( TRUE );
			}
		}	
		
		for( i = 1; i <= max; i++ ){
			if( Slot_ReelPatternGridGet(main,no,pos1-i) == hit ){
				reel->reel_hit_grid_y = pos1;
				reel->reel_slip_grid_y = i;
				return( TRUE );
			}
		}
		
		for( i = 1; i <= max; i++ ){
			if( Slot_ReelPatternGridGet(main,no,pos2-i) == hit ){
				reel->reel_hit_grid_y = pos2;
				reel->reel_slip_grid_y = i;
				return( TRUE );
			}
		}
	}else if( prm == 1 ){			//�D�揇�ʁ@1����
		for( i = 1; i <= max; i++ ){
			if( Slot_ReelPatternGridGet(main,no,pos1-i) == hit ){
				reel->reel_hit_grid_y = pos1;
				reel->reel_slip_grid_y = i;
				return( TRUE );
			}
		}
		
		for( i = 1; i <= max; i++ ){
			if( Slot_ReelPatternGridGet(main,no,pos2-i) == hit ){
				reel->reel_hit_grid_y = pos2;
				reel->reel_slip_grid_y = i;
				return( TRUE );
			}
		}
		
		for( i = 1; i <= max; i++ ){
			if( Slot_ReelPatternGridGet(main,no,pos0-i) == hit ){
				reel->reel_hit_grid_y = pos0;
				reel->reel_slip_grid_y = i;
				return( TRUE );
			}
		}	
	}else{						//�D�揇�ʁ@2����
		for( i = 1; i <= max; i++ ){
			if( Slot_ReelPatternGridGet(main,no,pos2-i) == hit ){
				reel->reel_hit_grid_y = pos2;
				reel->reel_slip_grid_y = i;
				return( TRUE );
			}
		}
		
		for( i = 1; i <= max; i++ ){
			if( Slot_ReelPatternGridGet(main,no,pos0-i) == hit ){
				reel->reel_hit_grid_y = pos0;
				reel->reel_slip_grid_y = i;
				return( TRUE );
			}
		}
		
		for( i = 1; i <= max; i++ ){
			if( Slot_ReelPatternGridGet(main,no,pos1-i) == hit ){
				reel->reel_hit_grid_y = pos1;
				reel->reel_slip_grid_y = i;
				return( TRUE );
			}
		}
	}
	
	#ifdef PM_DEBUG
	if( main->auto_hit_flag == TRUE ){
		GF_ASSERT( 0 && "Reel12Slip_HitSlipAfter() auto error sono3" );
	}
	#endif
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ���[���O�P�Q�@�q�b�g�X�x���@�{�[�i�X
 * @param	reel	REELCONTROL
 * @param	main	SLOTMAIN
 * @param	hit		REEL_PATTERN
 * @retval	int		TRUE=�q�b�g FALSE=����
 */
//--------------------------------------------------------------
static int Reel012SlipBonus_HitSlip( REELCONTROL *reel, SLOTMAIN *main, REEL_PATTERN hit )
{
	int i,j,max;
	int no = reel->reel_no;
	
	max = SLIP_MAX;
	
	if( main->auto_hit_flag == TRUE ){
		max = REEL_PT_MAX;
	}
	
	for( i = 0; i <= max; i++ ){
		if(	Slot_ReelPatternGridGet(main,no,2-i) == hit ){
			reel->reel_hit_grid_y = 2;
			reel->reel_slip_grid_y = i;
			return( TRUE );
		}
	}
	
	#ifdef PM_DEBUG
	if( main->auto_hit_flag == TRUE ){
		GF_ASSERT( 0 && "Reel012SlipBonus_HitSlip() auto error" );
	}
	#endif
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ���[���n�Y���X�x���Z�b�g
 * @param	reel	REELCONTROL
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void ReelSlip_Miss( REELCONTROL *reel, SLOTMAIN *main )
{
	int i,count;
	
	count = ReelSlip_StopReelCountGet( main );
	
	if( reel->reel_no != 0 && count < 2 ){		//0�ȊO�ōŌ�łȂ��ꍇ�̓X�x������
		return; 
	}
	
	if( reel->reel_no == 0 && count < 2 ){		//0�Œ�~2�܂łȂ�Ӓn�ł��P�`�F���[�O��
		for( i = 0; i <= REEL_PT_MAX; i++ ){
			if( Reel0Slip_Cherry1HitCheck(main,i) == FALSE ){
				reel->reel_slip_grid_y = i;
				return;
			}
		}
		
		GF_ASSERT( 0 && "ReelSlip_Miss() miss slip error 0 cherry1 " );
		return;
	}
	
	switch( reel->reel_no ){
	case REEL_0:
		for( i = 1; i <= REEL_PT_MAX; i++ ){
			if( Reel0Slip_OffsetHitCheck(reel,main,i) == FALSE ){
				reel->reel_slip_grid_y = i;
				return;
			}
		}
		
		GF_ASSERT( 0 && "ReelSlip_Miss() miss slip error 0" );
		return;
	case REEL_1:
		for( i = 1; i <= REEL_PT_MAX; i++ ){
			if( Reel1Slip_OffsetHitCheck(reel,main,i) == FALSE ){
				reel->reel_slip_grid_y = i;
				return;
			}
		}
		
		GF_ASSERT( 0 && "ReelSlip_Miss() miss slip error 1" );
		
		break;
	case REEL_2:
		for( i = 1; i <= REEL_PT_MAX; i++ ){
			if( Reel2Slip_OffsetHitCheck(reel,main,i) == FALSE ){
				reel->reel_slip_grid_y = i;
				return;
			}
		}
		
		GF_ASSERT( 0 && "ReelSlip_Miss() miss slip error 2" );
		break;
	}
	
	GF_ASSERT( 0 && "ReelSlip_Miss() miss slip error no" );
}

//--------------------------------------------------------------
/**
 * ���[���n�Y���X�x���Z�b�g�@�{�[�i�X
 * @param	reel	REELCONTROL
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void ReelSlipBonus_Miss( REELCONTROL *reel, SLOTMAIN *main )
{
	int i,count;
	
	count = ReelSlip_StopReelCountGet( main );
	
	if( reel->reel_no != 0 && count < 2 ){		//0�ȊO�ōŌ�łȂ��ꍇ�̓X�x������
		return; 
	}
	
	if( reel->reel_no == 0 && count < 2 ){		//0�Œ�~���Q�ȉ��Ȃ�Ӓn�ł��P�`�F���[�O��
		for( i = 0; i < REEL_PT_MAX; i++ ){
			if( Slot_ReelPatternGridGet(main,0,2-i) != REEL_CHERRY ){
				reel->reel_slip_grid_y = i;
				return;
			}
		}
		
		GF_ASSERT( 0 && "ReelSlipBonus_Miss() miss slip error 0 cherry1 " );
	}
	
	switch( reel->reel_no ){
	case REEL_0:
		for( i = 0; i < REEL_PT_MAX; i++ ){
			if( Reel0SlipBonus_OffsetHitCheck(reel,main,i) == FALSE ){
				reel->reel_slip_grid_y = i;
				return;
			}
		}
		
		GF_ASSERT( 0 && "ReelSlipBonus_Miss() miss slip error no 0" );
		return;
	case REEL_1:
		for( i = 0; i <= REEL_PT_MAX; i++ ){
			if( Reel1SlipBonus_OffsetHitCheck(reel,main,i) == FALSE ){
				reel->reel_slip_grid_y = i;
				return;
			}
		}
		
		GF_ASSERT( 0 && "ReelSlipBonus_Miss() miss slip error no 1" );
		return;
	case REEL_2:	
		for( i = 0; i <= REEL_PT_MAX; i++ ){
			if( Reel2SlipBonus_OffsetHitCheck(reel,main,i) == FALSE ){
				reel->reel_slip_grid_y = i;
				return;
			}
		}
	
		GF_ASSERT( 0 && "ReelSlipBonus_Miss() miss slip error no 2" );
	}
	
	GF_ASSERT( 0 && "ReelSlipBonus_Miss() miss slip error no" );
}

//--------------------------------------------------------------
/**
 * ���ɒ�~������s���Ă��郊�[�����J�E���g
 * @param	main	SLOTMAIN
 * @retval	int		0,1,2,3
 */
//--------------------------------------------------------------
static int ReelSlip_StopReelCountGet( SLOTMAIN *main )
{
	int i = REEL_0,count = 0;
	do{ if(main->reel_status[i] != REEL_ST_SCROLL){ count++; } i++; }while( i < REEL_MAX );
	return( count );
}

//--------------------------------------------------------------
/**
 * �����~���ǂ���
 * @param	reel	REELCONTROL
 * @param	main	SLOTMAIN
 * @retval	int		TRUE=����
 */
//--------------------------------------------------------------
static int ReelSlip_StartSlipCheck( REELCONTROL *reel, SLOTMAIN *main )
{
	switch( reel->reel_no ){
	case REEL_0:
		if( main->reel_status[REEL_1] != REEL_ST_SCROLL ||
			main->reel_status[REEL_2] != REEL_ST_SCROLL ){
			return( FALSE );
		}
		
		break;
	case REEL_1:
		if( main->reel_status[REEL_0] != REEL_ST_SCROLL ||
			main->reel_status[REEL_2] != REEL_ST_SCROLL ){
			return( FALSE );
		}
		
		break;
	case REEL_2:
		if( main->reel_status[REEL_0] != REEL_ST_SCROLL ||
			main->reel_status[REEL_1] != REEL_ST_SCROLL ){
			return( FALSE );
		}
		
		break;
	}
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * ������ʒu�擾
 * @param	reel	REELCONTROL
 * @param	main	SLOTMAIN
 * @param	pos0	�~�ߏ�����0 0=����
 * @param	pos1	�~�ߏ�����1 0=����
 * @param	pos1	�~�ߏ�����2 0=����
 * @retval	int		TRUE=�|�W����
 */
//--------------------------------------------------------------
static int ReelSlip_HitStopPosGet(
		REELCONTROL *reel, SLOTMAIN *main, int *pos0, int *pos1, int *pos2 )
{
	REEL_ST st0 = main->reel_status[REEL_0];
	REEL_ST st1 = main->reel_status[REEL_1];
	REEL_ST st2 = main->reel_status[REEL_2];
	REELCONTROL *reel0 = &main->reelcont[REEL_0];
	REELCONTROL *reel1 = &main->reelcont[REEL_1];
	REELCONTROL *reel2 = &main->reelcont[REEL_2];
	int hit0 = reel0->reel_hit_grid_y;
	int hit1 = reel1->reel_hit_grid_y;
	int hit2 = reel2->reel_hit_grid_y;
	
	*pos0 = 0;
	*pos1 = 0;
	*pos2 = 0;
	
	switch( reel->reel_no ){
	case REEL_0:
		if( st1 != REEL_ST_SCROLL && st2 != REEL_ST_SCROLL ){		//1,2�~��
			if( hit1 == hit2 ){										//���s
				*pos0 = hit1;
				return( TRUE );
			}
			
			if( hit2 == 1 ){										//�΂ߏ�
				*pos0 = 3;
				return( TRUE );
			}
			
			*pos0 = 1;
			return( TRUE );
		}
		
		if( st1 != REEL_ST_SCROLL ){								//�^�񒆂݂̂Ƃ܂�
			if( hit1 == 2 ){										//���Ȃ牡�Ɏ΂߂�
				*pos0 = 1;
				*pos1 = 2;
				*pos2 = 3;
				return( TRUE );
			}
			
			*pos0 = hit1;
			return( TRUE );
		}
		
		if( hit2 == 2 ){											//�E�̂�
			*pos0 = hit2;											//�΂߂̗]�n����
			return( TRUE );
		}
		
		*pos0 = 1;													//1,3 ����
		*pos1 = 3;
		return( TRUE );
	case REEL_1:
		if( st0 != REEL_ST_SCROLL && st2 != REEL_ST_SCROLL ){		//0,2�~��
			if( hit0 == hit2 ){										//���s
				*pos0 = hit0;
				return( TRUE );
			}
			
			*pos0 = 2;												//�΂߈ȊO�]�n����
			return( TRUE );
		}
		
		if( st0 != REEL_ST_SCROLL ){
			if( hit0 == 2 ){										//�^�񒆈ȊO�]�n����
				*pos0 = 2;
				return( TRUE );
			}
			
			if( hit0 == 1 ){
				*pos0 = 1;
				*pos1 = 2;
				return( TRUE );
			}
			
			*pos0 = 2;
			*pos1 = 3;
			return( TRUE );
		}
		
		if( hit2 == 2 ){											//�^�񒆈ȊO�̗]�n����
			*pos0 = 2;
			return( TRUE );
		}
		
		if( hit2 == 1 ){
			*pos0 = 1;
			*pos1 = 2;
			return( TRUE );
		}
		
		*pos0 = 2;
		*pos1 = 3;
		return( TRUE );
	case REEL_2:
		if( st0 != REEL_ST_SCROLL && st1 != REEL_ST_SCROLL ){		//0,1�~��
			if( hit0 == hit1 ){										//���s
				*pos0 = hit0;
				return( TRUE );
			}
			
			if( hit0 == 1 ){
				*pos0 = 3;
			}else{
				*pos0 = 1;
			}
			
			return( TRUE );
		}
		
		if( st0 != REEL_ST_SCROLL ){				//0�̂�
			if( hit0 == 2 ){						
				*pos0 = 2;
				return( TRUE );
			}
			
			*pos0 = 1;								//1,3����
			*pos1 = 3;
			return( TRUE );
		}
													//1�̂�
		if( hit1 == 2 ){							//���Ȃ�R��
			*pos0 = 1;
			*pos1 = 2;
			*pos2 = 3;
			return( TRUE );
		}
		
		*pos0 = hit1;
		return( TRUE );
	}
	
	GF_ASSERT( 0 && "ReelSlip_HitStopPosGet() HitPos Error" );
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ���[���O�@�w�肳�ꂽ�I�t�Z�b�g�ŒP�`�F���[�`�F�b�N
 * @param	reel	REELCONTROL
 * @param	main	SLOTMAIN
 * @param	offs	�I�t�Z�b�g
 * @retval	int		TRUE=�A��
 */
//--------------------------------------------------------------
static int Reel0Slip_Cherry1HitCheck( SLOTMAIN *main, int offs )
{
	u32 pat0;
	
	pat0 = Slot_ReelPatternGridGet( main, 0, 1-offs );
	if( pat0 == REEL_CHERRY ){ return( TRUE ); }
	pat0 = Slot_ReelPatternGridGet( main, 0, 2-offs );
	if( pat0 == REEL_CHERRY ){ return( TRUE ); }
	pat0 = Slot_ReelPatternGridGet( main, 0, 3-offs );
	if( pat0 == REEL_CHERRY ){ return( TRUE ); }
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ���[���O�@�P�`�F���[�q�b�g�`�F�b�N
 * @param	reel	REELCONTROL
 * @param	main	SLOTMAIN
 * @param	offs	�I�t�Z�b�g
 * @retval	int		TRUE=����
 */
//--------------------------------------------------------------
static int Reel0Slip_PatCherry1HitCheck( SLOTMAIN *main, int offs, REEL_PATTERN hit )
{
	if( hit == REEL_CHERRY ){				//�`�F���[�q�b�gOK
		return( TRUE );
	}
	
	if( Reel0Slip_Cherry1HitCheck(main,offs) == FALSE ){
		return( TRUE );						//�ՖʂɃ`�F���[����
	}
	
	return( FALSE );						//�`�F���[�����ŔՖʃ`�F���[
}

//--------------------------------------------------------------
/**
 * ���[���O�@�w�肳�ꂽ�I�t�Z�b�g�œ����肪���邩�B���O�ɂQ�~�܂��Ă��鎖������
 * @param	reel	REELCONTROL
 * @param	main	SLOTMAIN
 * @param	offs	�I�t�Z�b�g
 * @retval	int		TRUE=�A��
 */
//--------------------------------------------------------------
static int Reel0Slip_OffsetHitCheck( REELCONTROL *reel, SLOTMAIN *main, int offs )
{
	u32 pat0,pat1,pat2;
	int slip1 = main->reelcont[REEL_1].reel_slip_grid_y;
	int slip2 = main->reelcont[REEL_2].reel_slip_grid_y;
	
	//1-1-1�`�F�b�N
	pat0 = Slot_ReelPatternGridGet( main, 0, 1-offs );
	pat1 = Slot_ReelPatternGridGet( main, 1, 1-slip1 );
	pat2 = Slot_ReelPatternGridGet( main, 2, 1-slip2 );
	
	if( pat0 == REEL_CHERRY || (pat0 == pat1 && pat0 == pat2) ){
		return( TRUE );
	}
	
	//2-2-2�`�F�b�N
	pat0 = Slot_ReelPatternGridGet( main, 0, 2-offs );
	pat1 = Slot_ReelPatternGridGet( main, 1, 2-slip1 );
	pat2 = Slot_ReelPatternGridGet( main, 2, 2-slip2 );
	
	if( pat0 == REEL_CHERRY || (pat0 == pat1 && pat0 == pat2) ){
		return( TRUE );
	}
	
	//3-3-3�`�F�b�N
	pat0 = Slot_ReelPatternGridGet( main, 0, 3-offs );
	pat1 = Slot_ReelPatternGridGet( main, 1, 3-slip1 );
	pat2 = Slot_ReelPatternGridGet( main, 2, 3-slip2 );
	
	if( pat0 == REEL_CHERRY || (pat0 == pat1 && pat0 == pat2) ){
		return( TRUE );
	}
	
	//1-2-3�`�F�b�N
	pat0 = Slot_ReelPatternGridGet( main, 0, 1-offs );
	pat1 = Slot_ReelPatternGridGet( main, 1, 2-slip1 );
	pat2 = Slot_ReelPatternGridGet( main, 2, 3-slip2 );
	
	if( pat0 == REEL_CHERRY || (pat0 == pat1 && pat0 == pat2) ){
		return( TRUE );
	}
	
	
	//3-2-1�`�F�b�N
	pat0 = Slot_ReelPatternGridGet( main, 0, 3-offs );
	pat1 = Slot_ReelPatternGridGet( main, 1, 2-slip1 );
	pat2 = Slot_ReelPatternGridGet( main, 2, 1-slip2 );
	
	if( pat0 == REEL_CHERRY || (pat0 == pat1 && pat0 == pat2) ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ���[���P�@�w�肳�ꂽ�I�t�Z�b�g�œ����肪���邩�B���O�ɂQ�~�܂��Ă��鎖������
 * @param	reel	REELCONTROL
 * @param	main	SLOTMAIN
 * @param	offs	�I�t�Z�b�g
 * @retval	int		TRUE=�A��
 */
//--------------------------------------------------------------
static int Reel1Slip_OffsetHitCheck( REELCONTROL *reel, SLOTMAIN *main, int offs )
{
	u32 pat0,pat1,pat2;
	int slip0 = main->reelcont[REEL_0].reel_slip_grid_y;
	int slip2 = main->reelcont[REEL_2].reel_slip_grid_y;
	
	//1-1-1�`�F�b�N
	pat0 = Slot_ReelPatternGridGet( main, 0, 1-slip0 );
	pat1 = Slot_ReelPatternGridGet( main, 1, 1-offs );
	pat2 = Slot_ReelPatternGridGet( main, 2, 1-slip2 );
	
	if( pat0 == pat1 && pat0 == pat2 ){
		return( TRUE );
	}
	
	//2-2-2�`�F�b�N
	pat0 = Slot_ReelPatternGridGet( main, 0, 2-slip0 );
	pat1 = Slot_ReelPatternGridGet( main, 1, 2-offs );
	pat2 = Slot_ReelPatternGridGet( main, 2, 2-slip2 );
	
	if( pat0 == pat1 && pat0 == pat2 ){
		return( TRUE );
	}
	
	//3-3-3�`�F�b�N
	pat0 = Slot_ReelPatternGridGet( main, 0, 3-slip0 );
	pat1 = Slot_ReelPatternGridGet( main, 1, 3-offs );
	pat2 = Slot_ReelPatternGridGet( main, 2, 3-slip2 );
	
	if( pat0 == pat1 && pat0 == pat2 ){
		return( TRUE );
	}
	
	//1-2-3�`�F�b�N
	pat0 = Slot_ReelPatternGridGet( main, 0, 1-slip0 );
	pat1 = Slot_ReelPatternGridGet( main, 1, 2-offs );
	pat2 = Slot_ReelPatternGridGet( main, 2, 3-slip2 );
	
	if( pat0 == pat1 && pat0 == pat2 ){
		return( TRUE );
	}
	
	//3-2-1�`�F�b�N
	pat0 = Slot_ReelPatternGridGet( main, 0, 3-slip0 );
	pat1 = Slot_ReelPatternGridGet( main, 1, 2-offs );
	pat2 = Slot_ReelPatternGridGet( main, 2, 1-slip2 );
	
	if( pat0 == pat1 && pat0 == pat2 ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ���[���Q�@�w�肳�ꂽ�I�t�Z�b�g�œ����肪���邩�B���O�ɂQ�~�܂��Ă��鎖������
 * @param	reel	REELCONTROL
 * @param	main	SLOTMAIN
 * @param	offs	�I�t�Z�b�g
 * @retval	int		TRUE=�A��
 */
//--------------------------------------------------------------
static int Reel2Slip_OffsetHitCheck( REELCONTROL *reel, SLOTMAIN *main, int offs )
{
	u32 pat0,pat1,pat2;
	int slip0 = main->reelcont[REEL_0].reel_slip_grid_y;
	int slip1 = main->reelcont[REEL_1].reel_slip_grid_y;
	
	//1-1-1�`�F�b�N
	pat0 = Slot_ReelPatternGridGet( main, 0, 1-slip0 );
	pat1 = Slot_ReelPatternGridGet( main, 1, 1-slip1 );
	pat2 = Slot_ReelPatternGridGet( main, 2, 1-offs );
	
	if( pat0 == pat1 && pat0 == pat2 ){
		return( TRUE );
	}
	
	//2-2-2�`�F�b�N
	pat0 = Slot_ReelPatternGridGet( main, 0, 2-slip0 );
	pat1 = Slot_ReelPatternGridGet( main, 1, 2-slip1 );
	pat2 = Slot_ReelPatternGridGet( main, 2, 2-offs );
	
	if( pat0 == pat1 && pat0 == pat2 ){
		return( TRUE );
	}
	
	//3-3-3�`�F�b�N
	pat0 = Slot_ReelPatternGridGet( main, 0, 3-slip0 );
	pat1 = Slot_ReelPatternGridGet( main, 1, 3-slip1 );
	pat2 = Slot_ReelPatternGridGet( main, 2, 3-offs );
	
	if( pat0 == pat1 && pat0 == pat2 ){
		return( TRUE );
	}
	
	//1-2-3�`�F�b�N
	pat0 = Slot_ReelPatternGridGet( main, 0, 1-slip0 );
	pat1 = Slot_ReelPatternGridGet( main, 1, 2-slip1 );
	pat2 = Slot_ReelPatternGridGet( main, 2, 3-offs );
	
	if( pat0 == pat1 && pat0 == pat2 ){
		return( TRUE );
	}
	
	//3-2-1�`�F�b�N
	pat0 = Slot_ReelPatternGridGet( main, 0, 3-slip0 );
	pat1 = Slot_ReelPatternGridGet( main, 1, 2-slip1 );
	pat2 = Slot_ReelPatternGridGet( main, 2, 1-offs );
	
	if( pat0 == pat1 && pat0 == pat2 ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ���[���O�@�P���q���@�w�肳�ꂽ�I�t�Z�b�g�œ����肪���邩�B���O�ɂQ�~�܂��Ă��鎖������
 * @param	reel	REELCONTROL
 * @param	main	SLOTMAIN
 * @param	offs	�I�t�Z�b�g
 * @retval	int		TRUE=�A��
 */
//--------------------------------------------------------------
static int Reel0SlipBonus_OffsetHitCheck( REELCONTROL *reel, SLOTMAIN *main, int offs )
{
	u32 pat0,pat1,pat2;
	int slip1 = main->reelcont[REEL_1].reel_slip_grid_y;
	int slip2 = main->reelcont[REEL_2].reel_slip_grid_y;
	
	//2-2-2�`�F�b�N
	pat0 = Slot_ReelPatternGridGet( main, 0, 2-offs );
	pat1 = Slot_ReelPatternGridGet( main, 1, 2-slip1 );
	pat2 = Slot_ReelPatternGridGet( main, 2, 2-slip2 );
	
	if( (pat0 == REEL_CHERRY) || pat0 == pat1 && pat0 == pat2 ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ���[���P�@�P���q���@�w�肳�ꂽ�I�t�Z�b�g�œ����肪���邩�B���O�ɂQ�~�܂��Ă��鎖������
 * @param	reel	REELCONTROL
 * @param	main	SLOTMAIN
 * @param	offs	�I�t�Z�b�g
 * @retval	int		TRUE=�A��
 */
//--------------------------------------------------------------
static int Reel1SlipBonus_OffsetHitCheck( REELCONTROL *reel, SLOTMAIN *main, int offs )
{
	u32 pat0,pat1,pat2;
	int slip0 = main->reelcont[REEL_0].reel_slip_grid_y;
	int slip2 = main->reelcont[REEL_2].reel_slip_grid_y;
	
	//2-2-2�`�F�b�N
	pat0 = Slot_ReelPatternGridGet( main, 0, 2-slip0 );
	pat1 = Slot_ReelPatternGridGet( main, 1, 2-offs );
	pat2 = Slot_ReelPatternGridGet( main, 2, 2-slip2 );
	
	if( pat0 == pat1 && pat0 == pat2 ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ���[���Q�@�P���q���@�w�肳�ꂽ�I�t�Z�b�g�œ����肪���邩�B���O�ɂQ�~�܂��Ă��鎖������
 * @param	reel	REELCONTROL
 * @param	main	SLOTMAIN
 * @param	offs	�I�t�Z�b�g
 * @retval	int		TRUE=�A��
 */
//--------------------------------------------------------------
static int Reel2SlipBonus_OffsetHitCheck( REELCONTROL *reel, SLOTMAIN *main, int offs )
{
	u32 pat0,pat1,pat2;
	int slip0 = main->reelcont[REEL_0].reel_slip_grid_y;
	int slip1 = main->reelcont[REEL_1].reel_slip_grid_y;
	
	//2-2-2�`�F�b�N
	pat0 = Slot_ReelPatternGridGet( main, 0, 2-slip0 );
	pat1 = Slot_ReelPatternGridGet( main, 1, 2-slip1 );
	pat2 = Slot_ReelPatternGridGet( main, 2, 2-offs );
	
	if( pat0 == pat1 && pat0 == pat2 ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ���[���O�@�w�肳�ꂽ�I�t�Z�b�g�ŕ��������肪���邩�B���O�ɂQ�~�܂��Ă��鎖������
 * @param	reel	REELCONTROL
 * @param	main	SLOTMAIN
 * @param	offs	�I�t�Z�b�g
 * @retval	int		�q�b�g�J�E���g 0=�����薳�� 1=������ 2 <=����
 */
//--------------------------------------------------------------
static int Reel0Slip_OffsetHitCountGet( REELCONTROL *reel, SLOTMAIN *main, int offs )
{
	u32 pat0,pat1,pat2;
	int count = 0;
	int slip1 = main->reelcont[REEL_1].reel_slip_grid_y;
	int slip2 = main->reelcont[REEL_2].reel_slip_grid_y;
	
	//1-1-1�`�F�b�N
	pat0 = Slot_ReelPatternGridGet( main, 0, 1-offs );
	pat1 = Slot_ReelPatternGridGet( main, 1, 1-slip1 );
	pat2 = Slot_ReelPatternGridGet( main, 2, 1-slip2 );
	
	if( (pat0 == pat1 && pat0 == pat2) ){
		if( pat0 != REEL_CHERRY ){
			count++;
		}
	}
	
	//2-2-2�`�F�b�N
	pat0 = Slot_ReelPatternGridGet( main, 0, 2-offs );
	pat1 = Slot_ReelPatternGridGet( main, 1, 2-slip1 );
	pat2 = Slot_ReelPatternGridGet( main, 2, 2-slip2 );
	
	if( (pat0 == pat1 && pat0 == pat2) ){
		count++;
	}
	
	//3-3-3�`�F�b�N
	pat0 = Slot_ReelPatternGridGet( main, 0, 3-offs );
	pat1 = Slot_ReelPatternGridGet( main, 1, 3-slip1 );
	pat2 = Slot_ReelPatternGridGet( main, 2, 3-slip2 );
	
	if( (pat0 == pat1 && pat0 == pat2) ){
		if( pat0 != REEL_CHERRY ){
			count++;
		}
	}
	
	//1-2-3�`�F�b�N
	pat0 = Slot_ReelPatternGridGet( main, 0, 1-offs );
	pat1 = Slot_ReelPatternGridGet( main, 1, 2-slip1 );
	pat2 = Slot_ReelPatternGridGet( main, 2, 3-slip2 );
	
	if( pat0 == REEL_CHERRY || (pat0 == pat1 && pat0 == pat2) ){
		count++;
	}
	
	
	//3-2-1�`�F�b�N
	pat0 = Slot_ReelPatternGridGet( main, 0, 3-offs );
	pat1 = Slot_ReelPatternGridGet( main, 1, 2-slip1 );
	pat2 = Slot_ReelPatternGridGet( main, 2, 1-slip2 );
	
	if( pat0 == REEL_CHERRY || (pat0 == pat1 && pat0 == pat2) ){
		count++;
	}
	
	return( count );
}

//--------------------------------------------------------------
/**
 * ���[��1�@�w�肳�ꂽ�I�t�Z�b�g�ŕ��������肪���邩�B���O�ɂQ�~�܂��Ă��鎖������
 * @param	reel	REELCONTROL
 * @param	main	SLOTMAIN
 * @param	offs	�I�t�Z�b�g
 * @retval	int		�q�b�g�J�E���g 0=�����薳�� 1=������ 2 <=����
 */
//--------------------------------------------------------------
static int Reel1Slip_OffsetHitCountGet( REELCONTROL *reel, SLOTMAIN *main, int offs )
{
	u32 pat0,pat1,pat2;
	int count = 0;
	int slip0 = main->reelcont[REEL_0].reel_slip_grid_y;
	int slip2 = main->reelcont[REEL_2].reel_slip_grid_y;
	
	//1-1-1�`�F�b�N
	pat0 = Slot_ReelPatternGridGet( main, 0, 1-slip0 );
	pat1 = Slot_ReelPatternGridGet( main, 1, 1-offs );
	pat2 = Slot_ReelPatternGridGet( main, 2, 1-slip2 );
	
	if( pat0 == pat1 && pat0 == pat2 ){
		if( pat0 != REEL_CHERRY ){
			count++;
		}
	}
	
	//2-2-2�`�F�b�N
	pat0 = Slot_ReelPatternGridGet( main, 0, 2-slip0 );
	pat1 = Slot_ReelPatternGridGet( main, 1, 2-offs );
	pat2 = Slot_ReelPatternGridGet( main, 2, 2-slip2 );
	
	if( pat0 == pat1 && pat0 == pat2 ){
		count++;
	}
	
	//3-3-3�`�F�b�N
	pat0 = Slot_ReelPatternGridGet( main, 0, 3-slip0 );
	pat1 = Slot_ReelPatternGridGet( main, 1, 3-offs );
	pat2 = Slot_ReelPatternGridGet( main, 2, 3-slip2 );
	
	if( pat0 == pat1 && pat0 == pat2 ){
		if( pat0 != REEL_CHERRY ){
			count++;
		}
	}
	
	//1-2-3�`�F�b�N
	pat0 = Slot_ReelPatternGridGet( main, 0, 1-slip0 );
	pat1 = Slot_ReelPatternGridGet( main, 1, 2-offs );
	pat2 = Slot_ReelPatternGridGet( main, 2, 3-slip2 );
	
	if( pat0 == REEL_CHERRY || (pat0 == pat1 && pat0 == pat2) ){
		count++;
	}
	
	//3-2-1�`�F�b�N
	pat0 = Slot_ReelPatternGridGet( main, 0, 3-slip0 );
	pat1 = Slot_ReelPatternGridGet( main, 1, 2-offs );
	pat2 = Slot_ReelPatternGridGet( main, 2, 1-slip2 );
	
	if( pat0 == REEL_CHERRY || (pat0 == pat1 && pat0 == pat2) ){
		count++;
	}
	
	return( count );
}

//--------------------------------------------------------------
/**
 * ���[��1�@�w�肳�ꂽ�I�t�Z�b�g�ŕ��������肪���邩�B���O�ɂQ�~�܂��Ă��鎖������
 * @param	reel	REELCONTROL
 * @param	main	SLOTMAIN
 * @param	offs	�I�t�Z�b�g
 * @retval	int		�q�b�g�J�E���g 0=�����薳�� 1=������ 2 <=����
 */
//--------------------------------------------------------------
static int Reel2Slip_OffsetHitCountGet( REELCONTROL *reel, SLOTMAIN *main, int offs )
{
	u32 pat0,pat1,pat2;
	int count = 0;
	int slip0 = main->reelcont[REEL_0].reel_slip_grid_y;
	int slip1 = main->reelcont[REEL_1].reel_slip_grid_y;
	
	//1-1-1�`�F�b�N
	pat0 = Slot_ReelPatternGridGet( main, 0, 1-slip0 );
	pat1 = Slot_ReelPatternGridGet( main, 1, 1-slip1 );
	pat2 = Slot_ReelPatternGridGet( main, 2, 1-offs );
	
	if( pat0 == pat1 && pat0 == pat2 ){
		if( pat0 != REEL_CHERRY ){
			count++;
		}
	}
	
	//2-2-2�`�F�b�N
	pat0 = Slot_ReelPatternGridGet( main, 0, 2-slip0 );
	pat1 = Slot_ReelPatternGridGet( main, 1, 2-slip1 );
	pat2 = Slot_ReelPatternGridGet( main, 2, 2-offs );
	
	if( pat0 == pat1 && pat0 == pat2 ){
		count++;
	}
	
	//3-3-3�`�F�b�N
	pat0 = Slot_ReelPatternGridGet( main, 0, 3-slip0 );
	pat1 = Slot_ReelPatternGridGet( main, 1, 3-slip1 );
	pat2 = Slot_ReelPatternGridGet( main, 2, 3-offs );
	
	if( pat0 == pat1 && pat0 == pat2 ){
		if( pat0 != REEL_CHERRY ){
			count++;
		}
	}
	
	//1-2-3�`�F�b�N
	pat0 = Slot_ReelPatternGridGet( main, 0, 1-slip0 );
	pat1 = Slot_ReelPatternGridGet( main, 1, 2-slip1 );
	pat2 = Slot_ReelPatternGridGet( main, 2, 3-offs );
	
	if( pat0 == REEL_CHERRY || (pat0 == pat1 && pat0 == pat2) ){
		count++;
	}
	
	//3-2-1�`�F�b�N
	pat0 = Slot_ReelPatternGridGet( main, 0, 3-slip0 );
	pat1 = Slot_ReelPatternGridGet( main, 1, 2-slip1 );
	pat2 = Slot_ReelPatternGridGet( main, 2, 1-offs );
	
	if( pat0 == REEL_CHERRY || (pat0 == pat1 && pat0 == pat2) ){
		count++;
	}
	
	return( count );
}

//==============================================================================
//	���[����]
//==============================================================================
//--------------------------------------------------------------
/**
 * ���[����]
 * @param	main	SLOTMAIN
 * @param	no		REEL_NUM
 * @param	y		�ړ���
 * @retval	nothing
 */
//--------------------------------------------------------------
static void ReelScroll( SLOTMAIN *main, REEL_NUM no, fx32 y )
{
	main->reel_dot_y[no] += y;
	main->reel_dot_y[no] %= NUM_FX32( REEL_SCROLL_MAX );
	main->reel_grid_y[no] = REEL_PT_MAX - REEL_PT_V_DG32( main->reel_dot_y[no] );
}

//--------------------------------------------------------------
/**
 * ���[����]�@�O���b�h
 * @param	main	SLOTMAIN
 * @param	no		REEL_NUM
 * @param	y		�ړ���
 * @retval	fx32	�O���b�h�]��
 */
//--------------------------------------------------------------
static fx32 ReelScrollGrid( SLOTMAIN *main, REEL_NUM no, fx32 y )
{
	fx32 d;
	
	d = main->reel_dot_y[no] % NUM_FX32( REEL_PT_V_SIZE );
	
	if( d ){
		if( d < y ){
			y = d;
		}
		
		ReelScroll( main, no, y );
		d = main->reel_dot_y[no] % NUM_FX32( REEL_PT_V_SIZE );
	}
	
	return( d );
}

//==============================================================================
//	���I
//==============================================================================
//--------------------------------------------------------------
/**
 * ���I�m���̌����擾
 * @param	main	SLOTMAIN
 * @retval	u32		��
 */
//--------------------------------------------------------------
static u32 LotteryProbGet( SLOTMAIN *main )
{
	u32 prob = ((u32)gf_rand()) % 100;
	return( prob );
}

//--------------------------------------------------------------
/**
 * ���I�ƌ����Z
 * @param	hit		�q�b�g�m��
 * @param	prob	���I��
 * @retval	int		TRUE=�q�b�g
 */
//--------------------------------------------------------------
static int LotteryProbCheck( u32 hit, u32 *mprob )
{
	u32 prob = *mprob;
	(*mprob) -= hit;
	
	if( (int)(*mprob) < 0 ){
		(*mprob) = 0;
	}
	
	if( prob < hit ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ��{���I A
 * @param	main	SLOTMAIN
 * @retval	int		TRUE=�q�b�g
 */
//--------------------------------------------------------------
static int LotteryCheck_Basic( SLOTMAIN *main )
{
	u32 prob = LotteryProbGet( main );
	u32 hit = DATA_SlotBasicLotteryA[main->hard];
	
//	OS_Printf( "���IA HIT=0x%x,PROB=0x%x\n", hit, prob );
	
	if( hit > prob ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �q�𒊑I�@A
 * @param	main	SLOTMAIN
 * @retval	int		TRUE=�q�b�g
 */
//--------------------------------------------------------------
static int LotterySet_SmallA( SLOTMAIN *main )
{
	main->lottery_bit = LOTTERY_HITBIT_NON;
	
#ifdef DEBUG_ON_SLOT
	{
		if( main->d_work.debug_lottery_bit != LOTTERY_HITBIT_NON ){
			main->lottery_bit = main->d_work.debug_lottery_bit;
			main->d_work.debug_lottery_bit = LOTTERY_HITBIT_NON;
			return( TRUE );
		}
	}
#endif
	
#ifdef DEBUG_LOTTERY_S_FORCE
	main->lottery_bit = DEBUG_LOTTERY_S_FORCE;
	return( TRUE );
#endif
	
#ifdef DEBUG_LOTTERY_S_RND
	{
		u32 hit[4] = {
			LOTTERY_HITBIT_REPLAY,
			LOTTERY_HITBIT_CHERRY,
			LOTTERY_HITBIT_BELL,
			LOTTERY_HITBIT_SUIKA };
		main->lottery_bit = hit[gf_rand()%4];
		return( TRUE );
	}
#endif
	
	if( LotteryCheck_Basic(main) == TRUE ){
		u32 prob = LotteryProbGet( main );
		const LT_SMALLDATA *lt = &DATA_SlotSmallLotteryA[main->hard];
		
		main->kihon_a_count++;
		
		if( LotteryProbCheck(lt->cherry.lt_bonus,&prob) ){
			main->lottery_bit |= LOTTERY_HITBIT_CHERRY_B;
			main->cherry_hit_b_count++;
			return( TRUE );
		}
		
		if( LotteryProbCheck(lt->cherry.lt_small,&prob) ){
			main->lottery_bit |= LOTTERY_HITBIT_CHERRY;
			main->cherry_hit_count++;
			return( TRUE );
		}
		
		if( LotteryProbCheck(lt->suika.lt_bonus,&prob) ){
			main->lottery_bit |= LOTTERY_HITBIT_SUIKA_B;
			main->suika_hit_b_count++;
			return( TRUE );
		}
		
		if( LotteryProbCheck(lt->suika.lt_small,&prob) ){
			main->lottery_bit |= LOTTERY_HITBIT_SUIKA;
			main->suika_hit_count++;
			return( TRUE );
		}
		
		if( LotteryProbCheck(lt->bell.lt_bonus,&prob) ){
			main->lottery_bit |= LOTTERY_HITBIT_BELL_B;
			main->bell_hit_b_count++;
			return( TRUE );
		}
		
		if( LotteryProbCheck(lt->bell.lt_small,&prob) ){
			main->lottery_bit |= LOTTERY_HITBIT_BELL;
			main->bell_hit_count++;
			return( TRUE );
		}
		
		if( LotteryProbCheck(lt->replay.lt_bonus,&prob) ){
			main->lottery_bit |= LOTTERY_HITBIT_REPLAY_B;
			main->replay_hit_b_count++;
			return( TRUE );
		}
		
		main->lottery_bit |= LOTTERY_HITBIT_REPLAY;
		main->replay_hit_count++;
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ���I�@�ʏ�i�r�����`�F�b�N
 * @param	main	SLOTMAIN
 * @retval	int		TRUE=����,FALSE=�n�Y��
 */
//--------------------------------------------------------------
static int LotteryCheck_Navi( SLOTMAIN *main )
{
	u32 prob = LotteryProbGet( main );
	u32 nabi = DATA_LotteryNavi[main->hard];
	
	if( prob < nabi ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �p��������U��
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void LotterySet_BonusContinueBase( SLOTMAIN *main )
{
	int i;
	u32 prob = LotteryProbGet( main );
	const LT_CONT_BONUS *cb = DATA_LotteryContinueBonus[main->hard];
	
	for( i = 0; i < CONT_BONUS_TYPE_MAX; i++ ){
		if( LotteryProbCheck(cb[i].prob,&prob) == TRUE ){
			main->bonus_continue_type = cb[i].type;
			main->bonus_continue_prob_type = cb[i].prob_type;
			main->bonus_continue_prob = DATA_ContinueBonusTypeParam[main->bonus_continue_type];
			
			switch( main->bonus_continue_prob_type ){
			case CONT_BONUS_50: main->keizoku_50_count++; break;
			case CONT_BONUS_70: main->keizoku_70_count++; break;
			case CONT_BONUS_90: main->keizoku_90_count++; break;
			}
			
			return;
		}
	}
	
	//�{���A���鎖�͖���
	i--;
	main->bonus_continue_type = cb[i].type;
	main->bonus_continue_prob_type = cb[i].prob_type;
	main->bonus_continue_prob = DATA_ContinueBonusTypeParam[main->bonus_continue_type];
	
	OS_Printf( "�p�����ُ�\n" );
	GF_ASSERT( 0 && "LotterySet_BonusContinueBase() prob error" );
}

//--------------------------------------------------------------
/**
 * �s�b�s�^�C�v���I
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void LotterySet_PipType( SLOTMAIN *main )
{
	u32 i = 0,prob = LotteryProbGet( main );
	const LT_POKE_ENTRY *lt = DATA_LotteryPokeEntry[main->hard][main->bonus_continue_prob_type];
	
#ifdef DEBUG_ON_SLOT
	{
		if( main->d_work.debug_pip_type != PIP_MAX ){
			int i;
			PIPTYPE type = main->d_work.debug_pip_type;
			main->d_work.debug_pip_type = PIP_MAX;
			
			for( i = 0; i < PIP_MAX; i++ ){
				if( lt[i].type == type ){
					main->ddispcont.piptype = lt[i].type;
					return;
				}
			}
		}
	}
#endif
	
	do{
		if( LotteryProbCheck(lt[i].prob,&prob) == TRUE ){
			main->ddispcont.piptype = lt[i].type;
			
			switch( main->ddispcont.piptype ){
			case PIP_NORMAL: main->pippi_count++; break;
			case PIP_META: main->metamon_count++; break;
			case PIP_RARE: main->rare_pippi_count++; break;
			}
			
			return;
		}
		i++;
	}while( i < PIP_MAX );
	
	main->ddispcont.piptype = PIP_META;
	GF_ASSERT( 0 && "LotterySet_PipType() error" );
}

//--------------------------------------------------------------
/**
 * ��{���IB
 * @param	main	SLOTMAIN *
 * @retval	int		TRUE=���I FALSE=���I
 */
//--------------------------------------------------------------
static int LotteryCheck_BasicLotteryB( SLOTMAIN *main )
{
	u32 hit = DATA_SlotBasicLotteryB[main->hard];
	u32 prob = LotteryProbGet( main );
	
	if( prob < hit ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �q�𒊑IB
 * @param	main	SLOTMAIN *
 * @retval	int		TRUE=�q�b�g
 */
//--------------------------------------------------------------
static void LotterySet_BasicLotteryB( SLOTMAIN *main )
{
	u32 i;
	const u32 *lot = DATA_SlotSmallLotteryB[main->hard];
	u32 prob = LotteryProbGet( main );
	
	main->lottery_bit = LOTTERY_HITBIT_NON;
	
#ifdef DEBUG_ON_SLOT
	{
		if( main->d_work.debug_lottery_bit != LOTTERY_HITBIT_NON ){
			main->lottery_bit = main->d_work.debug_lottery_bit;
			main->d_work.debug_lottery_bit = LOTTERY_HITBIT_NON;
			return;
		}
	}
#endif
	
	if( LotteryCheck_BasicLotteryB(main) == FALSE ){
		main->kihon_b_count++;
		
		switch( main->bonus_continue_type ){
		case CONT_777_50:
		case CONT_777_70:
		case CONT_777_90:
			main->lottery_bit |= LOTTERY_HITBIT_RED7;
			main->seven_hit_count++;
			return;
		case CONT_GGG_50:
		case CONT_GGG_70:
		case CONT_GGG_90:
			main->lottery_bit |= LOTTERY_HITBIT_BLACK7;
			main->ginga_hit_count++;
			return;
		}
		
		GF_ASSERT( 0 && "LotterySet_BasicLotteryB() lottery 7 error" );
		main->lottery_bit |= LOTTERY_HITBIT_RED7;
		return;
	}
	
	if( LotteryProbCheck(lot[0],&prob) == TRUE ){	//�`�F���[
		main->lottery_bit |= LOTTERY_HITBIT_CHERRY;
		main->cherry_hit_count++;
		return;
	}
	
	if( LotteryProbCheck(lot[1],&prob) == TRUE ){	//�X�C�J
		main->lottery_bit |= LOTTERY_HITBIT_SUIKA;
		main->suika_hit_count++;
		return;
	}
	
	if( LotteryProbCheck(lot[1],&prob) == TRUE ){	//�x��
		main->lottery_bit |= LOTTERY_HITBIT_BELL;
		main->bell_hit_count++;
		return;
	}
	
	main->lottery_bit = LOTTERY_HITBIT_REPLAY;
	main->replay_hit_count++;
}

//--------------------------------------------------------------
/**
 * �����t���b�V�����I
 * @param	main	SLOTMAIN
 * @retval	int		TRUE=���I
 */
//--------------------------------------------------------------
static int LotteryCheck_MoonLight( SLOTMAIN *main )
{
	u32 prob = LotteryProbGet( main );
	u32 hit = DATA_LotteryMoonLight[main->hard];
	if( prob < hit ){ return( TRUE ); }
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �Ԃ������I
 * @param	main	SLOTMAIN
 * @retval	int		TRUE=���I
 */
//--------------------------------------------------------------
static int LotteryCheck_MoonLightRed( SLOTMAIN *main )
{
	u32 prob = LotteryProbGet( main );
	u32 hit = DATA_LotteryMoonLightRed[main->hard];
	if( prob < hit ){ return( TRUE ); }
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �{�[�i�X�p���`�F�b�N
 * @param	main	SLOTMAIN
 * @retval	int		TRUE=�p�� FALSE=�I��
 */
//--------------------------------------------------------------
static int LotteryCheck_BonusContinue( SLOTMAIN *main )
{
	u32 hit = main->bonus_continue_prob;
	u32 prob = LotteryProbGet( main );
	OS_Printf( "�{�[�i�X�p���`�F�b�N�@�p����=%d,����l=%d ", hit, prob );
	if( prob < hit ){ OS_Printf("�p��\n"); return( TRUE ); }
	OS_Printf( "�͂���\n" );
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �p�����_�E��
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void LotterySet_BonusContinueDown( SLOTMAIN *main )
{
	u32 bonus = main->bonus_continue_prob;
	u32 prob = LotteryProbGet( main );
	const u32 *lot = DATA_LotteryBonusContinue[main->hard];
	
	if( main->bonus_moonlight_red_flag == MOONRED_SUCCESS ){
		bonus -= 10;	//10% down
	}else{
		if( LotteryProbCheck(lot[0],&prob) == TRUE ){
			bonus -= 10;	//10% down
		}else if( LotteryProbCheck(lot[1],&prob) == TRUE ){
			bonus -= 5;		//5% down
		}
	}
	
	if( (int)bonus < 0 ){
		bonus = 0;
	}
	
	OS_Printf( "�p�����_�E������@����=%d,�����=%d\n", main->bonus_continue_prob, bonus );
	main->bonus_continue_prob = bonus;
}

//--------------------------------------------------------------
/**
 * �p�����o�擾
 * @param	main	SLOTMAIN
 * @retval	BCEFF	BCEFF
 */
//--------------------------------------------------------------
static BCEFF LotteryGet_BonusContinueEffect( SLOTMAIN *main )
{
	int i;
	u32 bonus = main->bonus_continue_prob;
	u32 prob = LotteryProbGet( main );
	const LT_CONTBONUSEND *lot = DATA_LotteryContinueBonusEnd[main->hard];
	
	for( i = 0; i < CONT_BONUSEND_NUM_MAX; i++ ){
		if( bonus >= lot[i].prec_bonus ){
			if( LotteryProbCheck(lot[i].prec_back,&prob) == TRUE ){
				return( BCEFF_BACK );
			}
			
			if( LotteryProbCheck(lot[i].prec_non,&prob) == TRUE ){
				return( BCEFF_NON );
			}
			
			return( BCEFF_ANENCORE );
		}
	}
	
	OS_Printf( "�p�����o�G���[ prec=0x%x\n", main->bonus_continue_prob );
	GF_ASSERT( 0 && "LotteryGet_BonusContinueEffect() bonus prec erroe" );
	return( BCEFF_NON );
}

//--------------------------------------------------------------
/**
 * �w�����^�C�v�Z�b�g
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void LotterySet_Yubisashi( SLOTMAIN *main )
{
	main->yubisashi_type = gf_rand() % YUBI_MAX;
}

//==============================================================================
//	�x��������
//==============================================================================
//--------------------------------------------------------------
/**
 * �x�������䏈���Z�b�g
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slot_PayOutControlSet( SLOTMAIN *main )
{
	PAYOUTCONTROL *payoutcont = &main->payoutcont;
	payoutcont->seq_no = 0;
	payoutcont->end_flag = FALSE;
	payoutcont->main = main;
	payoutcont->tcb = TCB_Add( PayOutControlTCB, payoutcont, TCBPRI_PAYOUTCONTROL );
}

//--------------------------------------------------------------
/**
 * �x�������䏈���폜
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slot_PayOutControlDelete( SLOTMAIN *main )
{
	TCB_Delete( main->payoutcont.tcb );
}

//--------------------------------------------------------------
/**
 * �x��������@�x������
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void PayOutControlPayOutSet( SLOTMAIN *main )
{
	main->payoutcont.end_flag = FALSE;
	main->payoutcont.frame = 0;
	main->payoutcont.seq_no = 1;
}

//--------------------------------------------------------------
/**
 * �x��������@�x�����I���`�F�b�N
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static int PayOutControlEndCheck( SLOTMAIN *main )
{
	return( main->payoutcont.end_flag );
}

//--------------------------------------------------------------
/**
 * �x�������䓮��
 * @param	tcb		TCB_PTR
 * @param	wk		tcb work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void PayOutControlTCB( TCB_PTR tcb, void *wk )
{
	int and;
	PAYOUTCONTROL *work= wk;
	SLOTMAIN *main = work->main;
	
	switch( work->seq_no ){
	case 0:
		break;
	case 1:
		PayOutLineAnimeSet( work );
		work->seq_no++;
		break;
	case 2:
		if( (work->eoa_reelanm0 != NULL &&
			PlttEff_EoaLineHitAnmRetGet(work->eoa_reelanm0) != LINERET_UP) ||
			(work->eoa_reelanm1 != NULL &&
			PlttEff_EoaLineHitAnmRetGet(work->eoa_reelanm1) != LINERET_UP) ){
			break;
		}
		
		work->seq_no++;
	case 3:
#ifdef DEBUG_ON_SLOT
		if( DEBUG_AutoPlayCheck(main) ){
			Snd_SePlay( SEQ_SE_DP_DENSI16 );
			main->credit += main->payout;
			
			if( main->credit >= SLOT_COIN_MAX ){
				main->credit = SLOT_COIN_MAX;
			}
			
			if( main->bonus_game_flag == TRUE ){
				main->bonus_get_coin += main->payout;
			}
			
			main->payout = 0;
			
			if( work->eoa_reelanm0 != NULL ){
				EOA_Delete( work->eoa_reelanm0 );
				work->eoa_reelanm0 = NULL;
			}
			
			if( work->eoa_reelanm1 != NULL ){
				EOA_Delete( work->eoa_reelanm1 );
				work->eoa_reelanm1 = NULL;
			}
			
			work->end_flag = TRUE;
			work->seq_no = 0;
			return;
		}
#endif
		if( keyTrg(PAD_PAYOUT_SKIP) || main->payout == 0 ){
			Snd_SePlay( SEQ_SE_DP_DENSI16 );
			main->credit += main->payout;
			
			if( main->credit >= SLOT_COIN_MAX ){
				main->credit = SLOT_COIN_MAX;
			}
			
			if( main->bonus_game_flag == TRUE ){
				main->bonus_get_coin += main->payout;
			}
			
			main->payout = 0;
			
			if( work->eoa_reelanm0 != NULL ){
				EOA_Delete( work->eoa_reelanm0 );
				work->eoa_reelanm0 = NULL;
			}
			
			if( work->eoa_reelanm1 != NULL ){
				EOA_Delete( work->eoa_reelanm1 );
				work->eoa_reelanm1 = NULL;
			}
			
			work->end_flag = TRUE;
			work->seq_no = 0;
			return;
		}
		
		and = 0x03;
		
		if( sys.cont & (PAD_BUTTON_A|PAD_BUTTON_B|PAD_BUTTON_X|PAD_BUTTON_Y) ){
			and = 0x01;
		}
	
		work->frame++;
	
		if( (work->frame & and) == 0 ){
			main->payout--;
			main->credit++;
			
			if( main->credit >= SLOT_COIN_MAX ){
				main->credit = SLOT_COIN_MAX;
			}
			
			Snd_SePlay( SEQ_SE_DP_DENSI16 );
			
			if( main->bonus_game_flag == TRUE ){
				main->bonus_get_coin++;
			}
		}
	}
}

//--------------------------------------------------------------
/**
 * �y�C�A�E�g�@���C���A�j���Z�b�g
 * @param	work	PAYOUTCONTROL
 * @retval	nothing
 */
//--------------------------------------------------------------
static void PayOutLineAnimeSet( PAYOUTCONTROL *work )
{
	int i;
	SLOTMAIN *main = work->main;
	u32 bit = main->reel_hit_line_bit;
	
	GF_ASSERT( bit != LINEBIT_NON && "SLOT ERROR LINE ANIME NOHIT" );
	
#ifdef DEBUG_ON_SLOT
	DEBUG_SlotHitLineCount( main );
#endif
	
	for( i = 0; i < LINE_MAX; i++, bit >>= 1 ){
		if( (bit & 0x01) ){
			if( work->eoa_reelanm0 == NULL ){
				work->eoa_reelanm0 = PlttEff_EoaLineHitAnm( main, i, main->payout );
			}else if( work->eoa_reelanm1 == NULL ){
				work->eoa_reelanm1 = PlttEff_EoaLineHitAnm( main, i, main->payout );
			}else{
				GF_ASSERT( 0 && "SLOT ERROR LINE ANIME SET" );
			}		
		}
	}
}

//==============================================================================
//	����ʐ���
//==============================================================================
static void DDispCont_ControlTCB( TCB_PTR tcb, void *wk );

//--------------------------------------------------------------
/**
 * ����ʐ��䏈���Z�b�g
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slot_DDispControlSet( SLOTMAIN *main )
{
	DDISPCONTROL *ddcont = &main->ddispcont;
	ddcont->move_type = 0;
	ddcont->seq_no = 0;
	ddcont->main = main;
	
#ifdef DEBUG_DDISPTEST
	DDC_BonusFontSet( main );
	SlotSubEoa_MoonFontInit( main, 9 );
#endif
	
	ddcont->tcb = TCB_Add( DDispCont_ControlTCB, ddcont, TCBPRI_DDISPCONTROL );
}

//--------------------------------------------------------------
/**
 * ����ʐ��䏈���폜
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slot_DDispControlDelete( SLOTMAIN *main )
{
	DDISPCONTROL *ddcont = &main->ddispcont;
	TCB_Delete( ddcont->tcb );
}

//--------------------------------------------------------------
/**
 * ����ʐ���ύX�@�p�����^�ݒ�͎��O��
 * @param	main	SLOTMAIN
 * @param	type	DDISP_NON��
 * @retval	nothing
 */
//--------------------------------------------------------------
static void DDC_TypeChange( SLOTMAIN *main, u32 type )
{
	DDISPCONTROL *work = &main->ddispcont;
	work->move_type = type;
	work->seq_no = 0;
	work->end_flag = FALSE;
	work->frame = 0;
}

//--------------------------------------------------------------
/**
 * ����ʐ���I���`�F�b�N
 * @param	main	SLOTMAIN
 * @param	type	DDISP_NON��
 * @retval	nothing
 */
//--------------------------------------------------------------
static int DDC_EndCheck( SLOTMAIN *main )
{
	DDISPCONTROL *work = &main->ddispcont;
	return( work->end_flag );
}

//--------------------------------------------------------------
/**
 * ����ʁ@�{�[�i�X�Q�[���t�H���g�Z�b�g
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void DDC_BonusFontSet( SLOTMAIN *main )
{
	main->ddispcont.bonus_font_vanish_flag = FALSE;
	main->ddispcont.eoa_font_bonus = SlotSubEoa_BonusFontInit( main );
	main->ddispcont.eoa_font_get = SlotSubEoa_GetFontInit( main );
	main->ddispcont.eoa_font_bcount = SlotSubEoa_BCountFontInit( main );
	main->ddispcont.eoa_font_getcoin = SlotSubEoa_GetCountFontInit( main );
}

//--------------------------------------------------------------
/**
 * ����ʁ@�{�[�i�X�Q�[���t�H���g�폜
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void DDC_BonusFontDelete( SLOTMAIN *main )
{
	main->ddispcont.bonus_font_vanish_flag = TRUE;
	EOA_Delete( main->ddispcont.eoa_font_bonus );
	EOA_Delete( main->ddispcont.eoa_font_get );
	EOA_Delete( main->ddispcont.eoa_font_bcount );
	EOA_Delete( main->ddispcont.eoa_font_getcoin );
}

//--------------------------------------------------------------
/**
 * ����ʐ��䓮��
 * @param	tcb			TCB_PTR
 * @param	work		tcb work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void DDispCont_ControlTCB( TCB_PTR tcb, void *wk )
{
	int ret;
	DDISPCONTROL *work = wk;
	int (* const * movetbl)( DDISPCONTROL * );
	
	do{
		movetbl = DATA_DDCM_Tbl[work->move_type];
		ret = movetbl[work->seq_no]( work );
	}while( ret == TRUE );
}

//--------------------------------------------------------------
/**
 * ����ʐ���@�����X�^�[�{�[�������]�@������
 * @param	work	DDISPCONTROL
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int DDCM_MBallSpinStart_Init( DDISPCONTROL *work )
{
	work->eoa_mball = SlotSubEoa_MBallSet( work->main, work->balltype );
	work->seq_no++;
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ����ʐ���@�����X�^�[�{�[�������]�@�������҂�
 * @param	work	DDISPCONTROL
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int DDCM_MBallSpinStart_InitWait( DDISPCONTROL *work )
{
	if( SlotSubEoa_MBallMoveEndCheck(work->eoa_mball) == FALSE ){
		return( FALSE );
	}
	
	SlotSubEoa_MBallMoveTypeChange( work->eoa_mball, MBALLMT_SPIN_START );
	work->seq_no++;
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ����ʐ���@�����X�^�[�{�[���]����I���҂�
 * @param	work	DDISPCONTROL
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int DDCM_MBallSpinStart_Wait( DDISPCONTROL *work )
{
	if( SlotSubEoa_MBallMoveEndCheck(work->eoa_mball) == FALSE ){
		return( FALSE );
	}
	
	SlotSubEoa_MBallMoveTypeChange( work->eoa_mball, MBALLMT_SHAKE );
	work->end_flag = TRUE;
	work->seq_no++;
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ����ʐ���@�I���@����
 * @param	work	DDISPCONTROL
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int DDCM_End( DDISPCONTROL *work )
{
	return( FALSE );
}

//--------------------------------------------------------------
///	����ʐ���@����
//--------------------------------------------------------------
static int (* const DDCM_Non[])( DDISPCONTROL *work ) =
{
	DDCM_End,
};

//--------------------------------------------------------------
///	����ʐ���@�����X�^�[�{�[���ǉ��Ɖ�]
//--------------------------------------------------------------
static int (* const DDCM_MBallSpinStart[])( DDISPCONTROL *work ) =
{
	DDCM_MBallSpinStart_Init,
	DDCM_MBallSpinStart_InitWait,
	DDCM_MBallSpinStart_Wait,
	DDCM_End,
};

//--------------------------------------------------------------
/**
 * ����ʐ���@�����X�^�[�{�[����ʊO�ց@������
 * @param	work	DDISPCONTROL
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int DDCM_MBallSpinOut_Init( DDISPCONTROL *work )
{
	SlotSubEoa_MBallMoveTypeChange( work->eoa_mball, MBALLMT_SPIN_OUT );
	work->seq_no++;
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ����ʐ���@�����X�^�[�{�[����ʊO�ց@�ړ��I���҂�
 * @param	work	DDISPCONTROL
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int DDCM_MBallSpinOut_Wait( DDISPCONTROL *work )
{
	if( SlotSubEoa_MBallMoveEndCheck(work->eoa_mball) == TRUE ){
		EOA_Delete( work->eoa_mball );
		work->end_flag = TRUE;
		work->seq_no++;
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
///	����ʐ���@�����X�^�[�{�[����ʊO��
//--------------------------------------------------------------
static int (* const DDCM_MBallSpinOut[])( DDISPCONTROL *work ) =
{
	DDCM_MBallSpinOut_Init,
	DDCM_MBallSpinOut_Wait,
	DDCM_End,
};

//--------------------------------------------------------------
/**
 * ����ʐ���@�s�b�s�o��@�{�[���I�[�v���@������
 * @param	work	DDISPCONTROL
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int DDCM_PipStart_Init( DDISPCONTROL *work )
{
	SlotSubEoa_MBallMoveTypeChange( work->eoa_mball, MBALLMT_OPEN );
	work->seq_no++;
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ����ʐ���@�s�b�s�o��@�{�[���I�[�v���@�҂�
 * @param	work	DDISPCONTROL
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int DDCM_PipStart_BallOpenWait( DDISPCONTROL *work )
{
	if( SlotSubEoa_MBallMoveEndCheck(work->eoa_mball) == TRUE ){
		work->eoa_balleff = SlotSubEoa_BallEffSet( work->main );
		work->eoa_pip = SlotSubEoa_PipSet( work->main, work->piptype );
		work->seq_no++;
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ����ʐ���@�s�b�s�o��@���ƃs�b�s�o��@������
 * @param	work	DDISPCONTROL
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int DDCM_PipStart_KemuriPipInit( DDISPCONTROL *work )
{
	if( SlotSubEoa_PipMoveEndCheck(work->eoa_pip) == TRUE ){
		SlotSubEoa_PipMoveTypeChange( work->eoa_pip, PIPMT_START );
		SlotSubEoa_MBallVanishSet( work->eoa_mball, TRUE );
		work->seq_no++;
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ����ʐ���@�s�b�s�o��@���ƃs�b�s�o��@�҂�
 * @param	work	DDISPCONTROL
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int DDCM_PipStart_KemuriPipWait( DDISPCONTROL *work )
{
	if( SlotSubEoa_PipMoveEndCheck(work->eoa_pip) == TRUE ){
		EOA_Delete( work->eoa_balleff );	//���폜
		work->end_flag = TRUE;
		work->seq_no++;
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
///	����ʐ���@�s�b�s�o��
//--------------------------------------------------------------
static int (* const DDCM_PipStart[])( DDISPCONTROL *work ) =
{
	DDCM_PipStart_Init,
	DDCM_PipStart_BallOpenWait,
	DDCM_PipStart_KemuriPipInit,
	DDCM_PipStart_KemuriPipWait,
	DDCM_End,
};

//--------------------------------------------------------------
/**
 * ����ʐ���@�s�b�s����@������
 * @param	work	DDISPCONTROL
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int DDCM_PipBack_Init( DDISPCONTROL *work )
{
	work->eoa_balleff = SlotSubEoa_BallEffSet( work->main );
	SlotSubEoa_PipMoveTypeChange( work->eoa_pip, PIPMT_BACK );
	work->seq_no++;
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ����ʐ���@�s�b�s����@�s�b�s�҂�
 * @param	work	DDISPCONTROL
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int DDCM_PipBack_PipWait( DDISPCONTROL *work )
{
	if( SlotSubEoa_PipMoveEndCheck(work->eoa_pip) == TRUE ){
		EOA_Delete( work->eoa_pip );
		EOA_Delete( work->eoa_balleff );
		SlotSubEoa_MBallVanishSet( work->eoa_mball, FALSE );
		SlotSubEoa_MBallMoveTypeChange( work->eoa_mball, MBALLMT_CLOSE );
		work->seq_no++;
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ����ʐ���@�s�b�s����@�{�[������
 * @param	work	DDISPCONTROL
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int DDCM_PipBack_BallCloseWait( DDISPCONTROL *work )
{
	if( SlotSubEoa_MBallMoveEndCheck(work->eoa_mball) == TRUE ){
		SlotSubEoa_MBallMoveTypeChange( work->eoa_mball, MBALLMT_SPIN_OUT );
		work->seq_no++;
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ����ʐ���@�s�b�s����@�{�[������
 * @param	work	DDISPCONTROL
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int DDCM_PipBack_BallOutWait( DDISPCONTROL *work )
{
	if( SlotSubEoa_MBallMoveEndCheck(work->eoa_mball) == TRUE ){
		EOA_Delete( work->eoa_mball );
		work->end_flag = TRUE;
		work->seq_no++;
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
///	����ʐ���@�s�b�s����
//--------------------------------------------------------------
static int (* const DDCM_PipBack[])( DDISPCONTROL *work ) =
{
	DDCM_PipBack_Init,
	DDCM_PipBack_PipWait,
	DDCM_PipBack_BallCloseWait,
	DDCM_PipBack_BallOutWait,
	DDCM_End,
};

//--------------------------------------------------------------
/**
 * ����ʐ���@�A���R�[���@������
 * @param	work	DDISPCONTROL
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int DDCM_Anencore_Init( DDISPCONTROL *work )
{
	SlotSubEoa_PipMoveTypeChange( work->eoa_pip, PIPMT_STAND );
	work->eoa_pika = SlotSubEoa_PikaSet( work->main );
	work->frame = 0;
	work->seq_no++;
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ����ʐ���@�A���R�[���@�s�J�`���E�o��
 * @param	work	DDISPCONTROL
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int DDCM_Anencore_PikaStart( DDISPCONTROL *work )
{
	work->frame++;
	
	if( work->frame >= 48 ){
		work->frame = 0;
		work->seq_no++;
		Snd_PMVoicePlay( MONSNO_PIPPI );
		SlotSubEoa_PipMoveTypeChange( work->eoa_pip, PIPMT_PATAPATA );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ����ʐ���@�A���R�[���@�p�^�p�^
 * @param	work	DDISPCONTROL
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int DDCM_Anencore_PataWait( DDISPCONTROL *work )
{
	if( SlotSubEoa_PikaEndCheck(work->eoa_pika) == TRUE ){
		SlotSubEoa_PipMoveTypeChange( work->eoa_pip, PIPMT_STAND );
		EOA_Delete( work->eoa_pika );
		work->seq_no++;
		work->frame = 0;
		work->end_flag = TRUE;
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
///	����ʐ���@�A���R�[��
//--------------------------------------------------------------
static int (* const DDCM_Anencore[])( DDISPCONTROL *work ) =
{
	DDCM_Anencore_Init,
	DDCM_Anencore_PikaStart,
	DDCM_Anencore_PataWait,
	DDCM_End,
};

//--------------------------------------------------------------
/**
 * ����ʐ���@�s�b�s�w�����@������
 * @param	work	DDISPCONTROL
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int DDCM_PipYubi_Init( DDISPCONTROL *work )
{
	const PIPNAVI *navi = &DATA_BonusGamePipNaveTbl[work->main->yubisashi_type];
	
	work->seq_no++;
	work->count = 0;
	SlotSubEoa_PipMoveTypeChange( work->eoa_pip, navi->pipmt[work->count] );
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ����ʐ���@�s�b�s�w�����@�Z�b�g
 * @param	work	DDISPCONTROL
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int DDCM_PipYubi_Set( DDISPCONTROL *work )
{
	int i,count = 0;
	
	for( i = 0; i < REEL_MAX; i++ ){
		if( work->main->reel_status[i] != REEL_ST_SCROLL ){
			count++;
		}
	}
	
	if( work->count < 2 && work->count != count ){
		const PIPNAVI *navi = &DATA_BonusGamePipNaveTbl[work->main->yubisashi_type];
		
		work->count = count;
		SlotSubEoa_PipMoveTypeChange( work->eoa_pip, navi->pipmt[work->count] );
	}
		
	return( FALSE );
}

//--------------------------------------------------------------
///	����ʐ���@�s�b�s�w����
//--------------------------------------------------------------
static int (* const DDCM_Yubi[])( DDISPCONTROL *work ) =
{
	DDCM_PipYubi_Init,
	DDCM_PipYubi_Set,
	DDCM_End,
};

//--------------------------------------------------------------
/**
 * ����ʐ���@�s�b�s��~�@������
 * @param	work	DDISPCONTROL
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int DDCM_PipStop_Init( DDISPCONTROL *work )
{
	SlotSubEoa_PipMoveTypeChange( work->eoa_pip, PIPMT_STAND );
	work->seq_no++;
	return( FALSE );
}

//--------------------------------------------------------------
///	����ʐ���@�s�b�s��~
//--------------------------------------------------------------
static int (* const DDCM_PipStop[])( DDISPCONTROL *work ) =
{
	DDCM_PipStop_Init,
	DDCM_End,
};

//--------------------------------------------------------------
/**
 * ����ʐ���@�{�[�i�X�I���@������
 * @param	work	DDISPCONTROL
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int DDCM_BonusEnd_Init( DDISPCONTROL *work )
{
	DDC_BonusFontDelete( work->main );
	work->eoa_balleff = SlotSubEoa_BallEffSet( work->main );
	SlotSubEoa_PipMoveTypeChange( work->eoa_pip, PIPMT_BACK );
	work->seq_no++;
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ����ʐ���@�{�[�i�X�I���@�s�b�s����@�s�b�s�҂�
 * @param	work	DDISPCONTROL
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int DDCM_BonusEnd_PipWait( DDISPCONTROL *work )
{
	if( SlotSubEoa_PipMoveEndCheck(work->eoa_pip) == TRUE ){
		EOA_Delete( work->eoa_pip );
		EOA_Delete( work->eoa_balleff );
		SlotSubEoa_MBallVanishSet( work->eoa_mball, FALSE );
		SlotSubEoa_MBallMoveTypeChange( work->eoa_mball, MBALLMT_CLOSE );
		work->seq_no++;
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ����ʐ���@�{�[�i�X�I���@�{�[������
 * @param	work	DDISPCONTROL
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int DDCM_BonusEnd_BallCloseWait( DDISPCONTROL *work )
{
	if( SlotSubEoa_MBallMoveEndCheck(work->eoa_mball) == TRUE ){
		SlotSubEoa_BigBonusFontInit( work->main );
		SlotSubEoa_BigGetFontInit( work->main );
		SlotSubEoa_BigCountFont( work->main, BIGFONT_COUNT );
		SlotSubEoa_BigCountFont( work->main, BIGFONT_GET );
		work->seq_no++;
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ����ʐ���@�{�[�i�X�I���@���ʕ\���҂�
 * @param	work	DDISPCONTROL
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int DDCM_PipBack_ReultWait( DDISPCONTROL *work )
{
	work->frame++;
	
	if( work->frame >= 45 ){
		work->frame = 0;
		SlotSubEoa_MBallMoveTypeChange( work->eoa_mball, MBALLMT_SPIN_OUT );
		work->seq_no++;
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ����ʐ���@�{�[�i�X�I���@�{�[������
 * @param	work	DDISPCONTROL
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int DDCM_BonusEnd_BallOutWait( DDISPCONTROL *work )
{
	if( SlotSubEoa_MBallMoveEndCheck(work->eoa_mball) == TRUE ){
		EOA_Delete( work->eoa_mball );
		work->end_flag = TRUE;
		work->seq_no++;
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
///	����ʐ���@�{�[�i�X�I��
//--------------------------------------------------------------
static int (* const DDCM_BonusEnd[])( DDISPCONTROL *work ) =
{
	DDCM_BonusEnd_Init,
	DDCM_BonusEnd_PipWait,
	DDCM_BonusEnd_BallCloseWait,
	DDCM_PipBack_ReultWait,
	DDCM_BonusEnd_BallOutWait,
	DDCM_End,
};

//--------------------------------------------------------------
/**
 * ����ʐ���@�s�b�s�p�^�p�^�@������
 * @param	work	DDISPCONTROL
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int DDCM_PipPataPata_Init( DDISPCONTROL *work )
{
	SlotSubEoa_PipMoveTypeChange( work->eoa_pip, PIPMT_PATAPATA );
	work->end_flag = TRUE;
	work->seq_no++;
	return( FALSE );
}

//--------------------------------------------------------------
///	����ʐ���@�s�b�s�p�^�p�^
//--------------------------------------------------------------
static int (* const DDCM_PipPataPata[])( DDISPCONTROL *work ) =
{
	DDCM_PipPataPata_Init,
	DDCM_End,
};

//--------------------------------------------------------------
/**
 * ����ʐ���@�s�b�s���΁@������
 * @param	work	DDISPCONTROL
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int DDCM_PipBanzai_Init( DDISPCONTROL *work )
{
	SlotSubEoa_PipMoveTypeChange( work->eoa_pip, PIPMT_BANZAI );
	work->end_flag = TRUE;
	work->seq_no++;
	return( FALSE );
}

//--------------------------------------------------------------
///	����ʐ���@�s�b�s����
//--------------------------------------------------------------
static int (* const DDCM_PipBanzai[])( DDISPCONTROL *work ) =
{
	DDCM_PipBanzai_Init,
	DDCM_End,
};

//--------------------------------------------------------------
/**
 * ����ʐ���@�����X�^�[�{�[����~�@������
 * @param	work	DDISPCONTROL
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int DDCM_MBallStop_Init( DDISPCONTROL *work )
{
	SlotSubEoa_MBallMoveTypeChange( work->eoa_mball, MBALLMT_STOP );
	work->seq_no++;
	work->end_flag = TRUE;
	return( FALSE );
}

//--------------------------------------------------------------
///	����ʐ���@�����X�^�[�{�[����~
//--------------------------------------------------------------
static int (* const DDCM_MBallStop[])( DDISPCONTROL *work ) =
{
	DDCM_MBallStop_Init,
	DDCM_End,
};

//--------------------------------------------------------------
/**
 * ����ʐ���@�s�b�s�����@�������@�s�b�s�߂�
 * @param	work	DDISPCONTROL
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int DDCM_PipRecover_Init( DDISPCONTROL *work )
{
	work->eoa_balleff = SlotSubEoa_BallEffSet( work->main );
	SlotSubEoa_PipMoveTypeChange( work->eoa_pip, PIPMT_BACK );
	work->bonus_font_vanish_flag = TRUE;
	work->seq_no++;
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ����ʐ���@�s�b�s�����@�s�b�s�߂蒬
 * @param	work	DDISPCONTROL
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int DDCM_PipRecover_PipWait( DDISPCONTROL *work )
{
	if( SlotSubEoa_PipMoveEndCheck(work->eoa_pip) == TRUE ){
		EOA_Delete( work->eoa_balleff );
		EOA_Delete( work->eoa_pip );
		SlotSubEoa_MBallVanishSet( work->eoa_mball, FALSE );
		SlotSubEoa_MBallMoveTypeChange( work->eoa_mball, MBALLMT_CLOSE );
		work->frame = 0;
		work->seq_no++;
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ����ʐ���@�s�b�s�����@�{�[���i�[��ꐡ�҂�
 * @param	work	DDISPCONTROL
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int DDCM_PipRecover_BallInWait( DDISPCONTROL *work )
{
	work->frame++;
	
	if( work->frame >= 30 ){
		work->frame = 0;
		work->seq_no++;
		SlotSubEoa_MBallMoveTypeChange( work->eoa_mball, MBALLMT_OPEN );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ����ʐ���@�s�b�s�����@�{�[���I�[�v���@�҂�
 * @param	work	DDISPCONTROL
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int DDCM_PipRecover_BallOpenWait( DDISPCONTROL *work )
{
	if( SlotSubEoa_MBallMoveEndCheck(work->eoa_mball) == TRUE ){
		work->eoa_balleff = SlotSubEoa_BallEffSet( work->main );
		work->eoa_pip = SlotSubEoa_PipSet( work->main, work->piptype );
		work->bonus_font_vanish_flag = FALSE;
		work->seq_no++;
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ����ʐ���@�s�b�s�����@���ƃs�b�s�ēo��@������
 * @param	work	DDISPCONTROL
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int DDCM_PipRecover_KemuriPipInit( DDISPCONTROL *work )
{
	if( SlotSubEoa_PipMoveEndCheck(work->eoa_pip) == TRUE ){
		SlotSubEoa_PipMoveTypeChange( work->eoa_pip, PIPMT_START );
		SlotSubEoa_MBallVanishSet( work->eoa_mball, TRUE );
		work->seq_no++;
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ����ʐ���@�s�b�s�����@���ƃs�b�s�o��@�҂�
 * @param	work	DDISPCONTROL
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int DDCM_PipRecover_KemuriPipWait( DDISPCONTROL *work )
{
	if( SlotSubEoa_PipMoveEndCheck(work->eoa_pip) == TRUE ){
		EOA_Delete( work->eoa_balleff );	//���폜
		work->end_flag = TRUE;
		work->seq_no++;
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
///	����ʐ���@�s�b�s����
//--------------------------------------------------------------
static int (* const DDCM_PipRecover[])( DDISPCONTROL *work ) =
{
	DDCM_PipRecover_Init,
	DDCM_PipRecover_PipWait,
	DDCM_PipRecover_BallInWait,
	DDCM_PipRecover_BallOpenWait,
	DDCM_PipRecover_KemuriPipInit,
	DDCM_PipRecover_KemuriPipWait,
	DDCM_End,
};

//--------------------------------------------------------------
///	����ʐ���@����e�[�u��
//--------------------------------------------------------------
static int (* const * const DATA_DDCM_Tbl[DDISP_MAX])( DDISPCONTROL *work ) =
{
	DDCM_Non,
	DDCM_MBallSpinStart,
	DDCM_MBallSpinOut,
	DDCM_PipStart,
	DDCM_PipBack,
	DDCM_Anencore,
	DDCM_Yubi,
	DDCM_PipStop,
	DDCM_BonusEnd,
	DDCM_PipPataPata,
	DDCM_PipBanzai,
	DDCM_MBallStop,
	DDCM_PipRecover,
};

//==============================================================================
//	�p���b�g����
//==============================================================================
//--------------------------------------------------------------
/**
 * �p���b�g����@������
 * @param	main
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slot_PlttControlSet( SLOTMAIN *main )
{
	void *buf;
	NNSG2dPaletteData *pPltt;
	PLTTCONTROL *cont = &main->plttcont;
	cont->main = main;
	
	buf = SlotArc_DataLoad( main, NARC_slot_slot_mount_NCLR, FALSE );
	NNS_G2dGetUnpackedPaletteData( buf, &pPltt );
	PlttCopy( pPltt, BGPLTTNO_MOUNT_SKY, cont->plttbase_mount );
	PlttCopy( pPltt, BGPLTTNO_LINE_1, cont->plttbase_line[LINE_1] );
	PlttCopy( pPltt, BGPLTTNO_LINE_2_0, cont->plttbase_line[LINE_2_0] );
	PlttCopy( pPltt, BGPLTTNO_LINE_2_0, cont->plttbase_line[LINE_2_1] );
	PlttCopy( pPltt, BGPLTTNO_LINE_3_0, cont->plttbase_line[LINE_3_0] );
	PlttCopy( pPltt, BGPLTTNO_LINE_3_0, cont->plttbase_line[LINE_3_1] );
	sys_FreeMemoryEz( buf );
	
	buf = SlotArc_DataLoad( main, NARC_slot_slot_mount_kurai_NCLR, FALSE );
	NNS_G2dGetUnpackedPaletteData( buf, &pPltt );
	PlttCopy( pPltt, 0, cont->plttkurai_mount );
	sys_FreeMemoryEz( buf );
	
	buf = SlotArc_DataLoad( main, NARC_slot_slot_mount_flash_NCLR, FALSE );
	NNS_G2dGetUnpackedPaletteData( buf, &pPltt );
	PlttCopy( pPltt, 0, cont->plttflash_mount );
	sys_FreeMemoryEz( buf );
	
	buf = SlotArc_DataLoad( main, NARC_slot_slot_mount_flash_red_NCLR, FALSE );
	NNS_G2dGetUnpackedPaletteData( buf, &pPltt );
	PlttCopy( pPltt, 0, cont->plttflash_red_mount );
	sys_FreeMemoryEz( buf );
	
	buf = SlotArc_DataLoad( main, NARC_slot_line1_flash_NCLR, FALSE );
	NNS_G2dGetUnpackedPaletteData( buf, &pPltt );
	PlttCopy( pPltt, 0, cont->plttflash_line[LINE_1] );
	sys_FreeMemoryEz( buf );
	
	buf = SlotArc_DataLoad( main, NARC_slot_line2_flash_NCLR, FALSE );
	NNS_G2dGetUnpackedPaletteData( buf, &pPltt );
	PlttCopy( pPltt, 0, cont->plttflash_line[LINE_2_0] );
	PlttCopy( pPltt, 0, cont->plttflash_line[LINE_2_1] );
	sys_FreeMemoryEz( buf );
	
	buf = SlotArc_DataLoad( main, NARC_slot_line3_flash_NCLR, FALSE );
	NNS_G2dGetUnpackedPaletteData( buf, &pPltt );
	PlttCopy( pPltt, 0, cont->plttflash_line[LINE_3_0] );
	PlttCopy( pPltt, 0, cont->plttflash_line[LINE_3_1] );
	sys_FreeMemoryEz( buf );
}

//--------------------------------------------------------------
/**
 * �p���b�g����@�폜
 * @param	main
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slot_PlttControlDelete( SLOTMAIN *main )
{
}

//--------------------------------------------------------------
/**
 * NNSG2dPaletteData�̐��p���b�g���R�s�[
 * @param	pPltt	NNSG2dPaletteData
 * @param	offs	���Ԗڂ�
 * @param	dest	�R�s�[��
 * @retval	nothing
 */
//--------------------------------------------------------------
static void PlttCopy( NNSG2dPaletteData *pPltt, int offs, u16 *dest )
{
	int i;
	u16 *base = pPltt->pRawData;
	base = &base[offs*16];
	
	for( i = 0; i < 16; i++ ){
		dest[i] = base[i];
	}
}

//--------------------------------------------------------------
/**
 * �w��F�ύX
 * @param	base		���p���b�g
 * @param	target		�ڕW�p���b�g
 * @param	evy			0-16  0=�� 8=���� 16=�ڕW
 * @param	dest		���ʊi�[��
 * @retval	nothing
 */
//--------------------------------------------------------------
static void ColorTargetFade( u16 base, u16 target, u16 evy, u16 *dest )
{
	const PLTT *pbase = (PLTT *)&base;
	const PLTT *ptarget = (PLTT *)&target;
	
	if( evy > 16 ){
		evy = 16;
	}
	
	(*dest) = FADE_CHANGE( pbase->red, ptarget->red, evy ) |
		(FADE_CHANGE( pbase->green, ptarget->green, evy ) << 5) |
		(FADE_CHANGE( pbase->blue, ptarget->blue, evy ) << 10);
}

//--------------------------------------------------------------
/**
 * �w��F�ύX 16�F
 * @param	base		���p���b�g
 * @param	target		�ڕW�p���b�g
 * @param	evy			0-16  0=�� 8=���� 16=�ڕW
 * @param	dest		���ʊi�[��
 * @retval	nothing
 */
//--------------------------------------------------------------
static void ColorTargetFade16( const u16 *base, const u16 *target, u16 evy, u16 *dest )
{
	int i = 0;
	
	do{ ColorTargetFade( base[i], target[i], evy, &dest[i] ); i++; }while( i < 16 );
}

//--------------------------------------------------------------
/**
 * �w��BG�փp���b�g�Z�b�g
 * @param	main	SLOTMAIN
 * @param	fram	BG�t���[��
 * @param	no		�Z�b�g����p���b�g�ԍ�
 * @param	pltt	�Z�b�g�p���b�g
 * @retval	nothing
 */
//--------------------------------------------------------------
static void PaletteBGSet( SLOTMAIN *main, u32 frame, int no, u16 *pltt )
{
	GF_BGL_PaletteSet( frame, pltt, 32, 32*no );
}

//==============================================================================
//	���[���p���b�g����
//==============================================================================
//--------------------------------------------------------------
///	�x�b�g���C���ʃp���b�g
//--------------------------------------------------------------
static int DATA_LinePlttNoTbl[LINE_MAX] =
{
	BGPLTTNO_LINE_1,
	BGPLTTNO_LINE_2_0,
	BGPLTTNO_LINE_2_1,
	BGPLTTNO_LINE_3_0,
	BGPLTTNO_LINE_3_1,
};

//--------------------------------------------------------------
/**
 * �x�b�g���C���_��
 * @param	main	SLOTMAIN
 * @param	no		LINENO
 * @retval	nothing
 */
//--------------------------------------------------------------
static void PlttEff_LineLightON( SLOTMAIN *main, LINENO no )
{
	PLTTCONTROL *cont = &main->plttcont;
	int pno = DATA_LinePlttNoTbl[no];
	PaletteBGSet( main, BGFRAME_SLOT, pno, cont->plttflash_line[no] );
}

//--------------------------------------------------------------
/**
 * �x�b�g���C������
 * @param	main	SLOTMAIN
 * @param	no		LINENO
 * @retval	nothing
 */
//--------------------------------------------------------------
static void PlttEff_LineLightOFF( SLOTMAIN *main, LINENO no )
{
	PLTTCONTROL *cont = &main->plttcont;
	int pno = DATA_LinePlttNoTbl[no];
	PaletteBGSet( main, BGFRAME_SLOT, pno, cont->plttbase_line[no] );
}

//--------------------------------------------------------------
/**
 * �x�b�g���C���@�x�b�g�F��
 * @param	main	SLOTMAIN
 * @param	no		LINENO
 * @retval	nothing
 */
//--------------------------------------------------------------
static void PlttEff_LineLightBet( SLOTMAIN *main, LINENO no )
{
	PLTTCONTROL *cont = &main->plttcont;
	int pno = DATA_LinePlttNoTbl[no];
	const u16 *base = cont->plttbase_line[no];
	const u16 *target = cont->plttflash_line[no];
	u16 *buf = cont->plttbuf_line[no];
	
	ColorTargetFade16( base, target, LINE_EVY_BET, buf );
	PaletteBGSet( main, BGFRAME_SLOT, pno, buf );
}

//--------------------------------------------------------------
/**
 * �x�b�g���C���@�x�b�g�F�ց@�ꖇ�|����p�ł�����ƔZ����
 * @param	main	SLOTMAIN
 * @param	no		LINENO
 * @retval	nothing
 */
//--------------------------------------------------------------
static void PlttEff_LineLightBetOne( SLOTMAIN *main, LINENO no )
{
	PLTTCONTROL *cont = &main->plttcont;
	int pno = DATA_LinePlttNoTbl[no];
	const u16 *base = cont->plttbase_line[no];
	const u16 *target = cont->plttflash_line[no];
	u16 *buf = cont->plttbuf_line[no];
	
	ColorTargetFade16( base, target, LINE_EVY_BET_1, buf );
	PaletteBGSet( main, BGFRAME_SLOT, pno, buf );
}

//--------------------------------------------------------------
/**
 * �S���C���_��
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void PlttEff_LineLightONAll( SLOTMAIN *main )
{
	int i = LINE_1; do{ PlttEff_LineLightON(main,i); i++; }while( i < LINE_MAX );
}

//--------------------------------------------------------------
/**
 * �S���C������
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void PlttEff_LineLightOFFAll( SLOTMAIN *main )
{
	int i = LINE_1; do{ PlttEff_LineLightOFF(main,i); i++; }while( i < LINE_MAX );
}

//--------------------------------------------------------------
/**
 * �S���C���x�b�g�_��
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void PlttEff_LineLightBetAll( SLOTMAIN *main )
{
	int i = LINE_1; do{ PlttEff_LineLightBet(main,i); i++; }while( i < LINE_MAX );
}

//--------------------------------------------------------------
///	LINEANMH
//--------------------------------------------------------------
typedef struct
{
	LINENO no;
	u32 payout;
	SLOTMAIN *main;
}LINEANMH;

//--------------------------------------------------------------
///	LINEANMWORK
//--------------------------------------------------------------
typedef struct
{
	int seq_no;
	int count;
	int frame;
	int ret;
	LINENO line_no;
	u32 payout;
	fx32 evy;
	SLOTMAIN *main;
	PLTTCONTROL *cont;
}LINEANMWORK;

static const EOA_H_NPP DATA_EoaH_LineAnm;

//--------------------------------------------------------------
/**
 * EOA �x�b�g���C���q�b�g�A�j��
 */
//--------------------------------------------------------------
static EOA_PTR PlttEff_EoaLineHitAnm( SLOTMAIN *main, LINENO no, u32 payout )
{
	EOA_PTR eoa;
	VecFx32 mtx = {0,0,0};
	LINEANMH head;
	
	head.no = no;
	head.payout = payout;
	head.main = main;
	
	eoa = EOA_Add_NPP(
		main->eoa_sys, &DATA_EoaH_LineAnm, &mtx, 0, &head, TCBPRI_PLTTEFF );
	return( eoa );
}

//--------------------------------------------------------------
/**
 * EOA �x�b�g���C���q�b�g�A�j���@�߂�l
 */
//--------------------------------------------------------------
static int PlttEff_EoaLineHitAnmRetGet( EOA_PTR eoa )
{
	LINEANMWORK *work = EOA_LocalWorkGet( eoa );
	return( work->ret );
}

//--------------------------------------------------------------
/**
 * EOA �x�b�g���C���q�b�g�A�j���@������
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	int		TRUE=���평����
 */
//--------------------------------------------------------------
static int eoaLineHitAnm_Init( EOA_PTR eoa, void *wk )
{
	const LINEANMH *head;
	LINEANMWORK *work = wk;
	head = (const LINEANMH *)EOA_AddPtrGet( eoa );
	work->main = head->main;
	work->line_no = head->no;
	work->payout = head->payout;
	work->cont = &work->main->plttcont;
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA �x�b�g���C���q�b�g�A�j���@�폜
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaLineHitAnm_Delete( EOA_PTR eoa, void *wk )
{
	LINEANMWORK *work = wk;
	PlttEff_LineLightOFF( work->main, work->line_no );
}

//--------------------------------------------------------------
/**
 * EOA �x�b�g���C���q�b�g�A�j���@����
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaLineHitAnm_Move( EOA_PTR eoa, void *wk )
{
	int evy;
	LINEANMWORK *work = wk;
	int no = DATA_LinePlttNoTbl[work->line_no];
	u16 *buf = work->cont->plttbuf_line[work->line_no];
	const u16 *base = work->cont->plttbase_line[work->line_no];
	const u16 *target = work->cont->plttflash_line[work->line_no];
	
	switch( work->seq_no ){
	case 0:
		work->evy += 0x4000;
		if( work->evy > NUM_FX32(16) ){ work->evy = NUM_FX32(16); }
		evy = FX32_NUM( work->evy );
		if( evy == 16 ){ work->seq_no++; }
		ColorTargetFade16( base, target, evy, buf );
		PaletteBGSet( work->main, BGFRAME_SLOT, no, buf );
		break;
	case 1:
		work->evy -= 0x4000;
		if( work->evy < NUM_FX32(0) ){ work->evy = NUM_FX32(0); }
		evy = FX32_NUM( work->evy );
		
		if( evy == 0 ){
			work->count++;
			
			if( work->count >= 4 ){
				if( work->payout ){				//�x��������
					work->seq_no++;
					work->ret = LINERET_UP;
				}else{							//�x��������(���v���C��
					work->seq_no = 4;
					work->ret = LINERET_UP;
				}
			}else{
				work->seq_no--;
			}
		}
		
		ColorTargetFade16( base, target, evy, buf );
		PaletteBGSet( work->main, BGFRAME_SLOT, no, buf );
		break;
	case 2:
		work->evy += 0x8000;
		if( work->evy > NUM_FX32(16) ){ work->evy = NUM_FX32(16); }
		evy = FX32_NUM( work->evy );
		if( evy == 16 ){ work->seq_no++; }
		ColorTargetFade16( base, target, evy, buf );
		PaletteBGSet( work->main, BGFRAME_SLOT, no, buf );
		break;
	case 3:
		work->evy -= 0x8000;
		if( work->evy < NUM_FX32(0) ){ work->evy = NUM_FX32(0); }
		evy = FX32_NUM( work->evy );
		if( evy == 0 ){ work->seq_no--; }
		ColorTargetFade16( base, target, evy, buf );
		PaletteBGSet( work->main, BGFRAME_SLOT, no, buf );
		break;
	case 4:
		break;
	}
}

//--------------------------------------------------------------
///	EOA_H ���C���p���b�g�A�j��
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_LineAnm =
{
	sizeof(LINEANMWORK),
	eoaLineHitAnm_Init,
	eoaLineHitAnm_Delete,
	eoaLineHitAnm_Move,
	EOA_DrawProcDummy,
};

//--------------------------------------------------------------
///	LINEBETANMWORK
//--------------------------------------------------------------
typedef struct
{
	int seq_no;
	int anmno;
	int init_flag;
	fx32 wait;
	LINENO line_no;
	fx32 evy[LINE_MAX];
	SLOTMAIN *main;
	PLTTCONTROL *cont;
}LINEBETANMWORK;

typedef struct
{
	u32 bit_line;
	fx32 start_evy;
	fx32 target_evy;
	fx32 speed_evy;
}LINEBETANM;

static const EOA_H_NPP DATA_EoaH_LineBetAnm;

//--------------------------------------------------------------
/**
 * EOA �x�b�g�����A�j���Z�b�g
 */
//--------------------------------------------------------------
static void PlttEff_EoaLineBetAnmStart( SLOTMAIN *main )
{
	VecFx32 mtx = {0,0,0};
	
	GF_ASSERT( main->payoutcont.eoa_reelanm0 == NULL );
	main->payoutcont.eoa_reelanm0 = EOA_Add_NPP(
		main->eoa_sys, &DATA_EoaH_LineBetAnm, &mtx, 0, main, TCBPRI_PLTTEFF );
}

//--------------------------------------------------------------
/**
 * EOA �x�b�g�����A�j���폜
 */
//--------------------------------------------------------------
static void PlttEff_EoaLineBetAnmDelete( SLOTMAIN *main )
{
	if( main->payoutcont.eoa_reelanm0 != NULL ){
		EOA_Delete( main->payoutcont.eoa_reelanm0 );
		main->payoutcont.eoa_reelanm0 = NULL;
	}
	
	PlttEff_LineLightOFFAll( main );
}

#define LB1 	(1<<0)
#define LB2_0	(1<<1)
#define LB2_1	(1<<2)
#define LB3_0	(1<<3)
#define LB3_1	(1<<4)
#define LB_WAIT (1<<5)
#define LB_LOOP (1<<6)

#define LB_WAIT_DATA(wait) LB_WAIT, NUM_FX32(wait), 0, 0
#define LBW_ON (2)
#define LBW_OFF (8)
#define LBW_ONH (1)
#define LBW_OFFH (2)
#define LBW_NEXT (16)
#define LBV_N (0x4000)
#define LBE_MAX (14)

static const LINEBETANM DATA_LineBetAnmTbl[] =
{
	{ LB_WAIT_DATA(30) },
	
	{ LB1, NUM_FX32(0), NUM_FX32(LBE_MAX), LBV_N },{ LB_WAIT_DATA(LBW_ON) },
	{ LB1, NUM_FX32(LBE_MAX), NUM_FX32(0), LBV_N },{ LB_WAIT_DATA(LBW_OFF) },
	{ LB2_0|LB2_1, NUM_FX32(0), NUM_FX32(LBE_MAX), LBV_N },{ LB_WAIT_DATA(LBW_ON) },
	{ LB2_0|LB2_1, NUM_FX32(LBE_MAX), NUM_FX32(0), LBV_N },{ LB_WAIT_DATA(LBW_OFF) },
	{ LB3_0|LB3_1, NUM_FX32(0), NUM_FX32(LBE_MAX), LBV_N },{ LB_WAIT_DATA(LBW_ON) },
	{ LB3_0|LB3_1, NUM_FX32(LBE_MAX), NUM_FX32(0), LBV_N },{ LB_WAIT_DATA(LBW_NEXT) },
	
	{ LB3_0|LB3_1, NUM_FX32(0), NUM_FX32(LBE_MAX), LBV_N },{ LB_WAIT_DATA(LBW_ON) },
	{ LB3_0|LB3_1, NUM_FX32(LBE_MAX), NUM_FX32(0), LBV_N },{ LB_WAIT_DATA(LBW_OFF) },
	{ LB2_0|LB2_1, NUM_FX32(0), NUM_FX32(LBE_MAX), LBV_N },{ LB_WAIT_DATA(LBW_ON) },
	{ LB2_0|LB2_1, NUM_FX32(LBE_MAX), NUM_FX32(0), LBV_N },{ LB_WAIT_DATA(LBW_OFF) },
	{ LB1, NUM_FX32(0), NUM_FX32(LBE_MAX), LBV_N },{ LB_WAIT_DATA(LBW_ON) },
	{ LB1, NUM_FX32(LBE_MAX), NUM_FX32(0), LBV_N },{ LB_WAIT_DATA(LBW_NEXT) },
	
	{ LB2_0, NUM_FX32(0), NUM_FX32(LBE_MAX), LBV_N },{ LB_WAIT_DATA(LBW_ON) },
	{ LB2_0, NUM_FX32(LBE_MAX), NUM_FX32(0), LBV_N },{ LB_WAIT_DATA(LBW_OFF) },
	{ LB3_1, NUM_FX32(0), NUM_FX32(LBE_MAX), LBV_N },{ LB_WAIT_DATA(LBW_ON) },
	{ LB3_1, NUM_FX32(LBE_MAX), NUM_FX32(0), LBV_N },{ LB_WAIT_DATA(LBW_OFF) },
	{ LB2_1, NUM_FX32(0), NUM_FX32(LBE_MAX), LBV_N },{ LB_WAIT_DATA(LBW_ON) },
	{ LB2_1, NUM_FX32(LBE_MAX), NUM_FX32(0), LBV_N },{ LB_WAIT_DATA(LBW_OFF) },
	{ LB3_0, NUM_FX32(0), NUM_FX32(LBE_MAX), LBV_N },{ LB_WAIT_DATA(LBW_ON) },
	{ LB3_0, NUM_FX32(LBE_MAX), NUM_FX32(0), LBV_N },{ LB_WAIT_DATA(LBW_OFF) },
	{ LB1, NUM_FX32(0), NUM_FX32(LBE_MAX), LBV_N },{ LB_WAIT_DATA(LBW_ON) },
	{ LB1, NUM_FX32(LBE_MAX), NUM_FX32(0), LBV_N },{ LB_WAIT_DATA(LBW_NEXT) },
	
	{ LB3_0, NUM_FX32(0), NUM_FX32(LBE_MAX), LBV_N },{ LB_WAIT_DATA(LBW_ONH) },
	{ LB3_0, NUM_FX32(LBE_MAX), NUM_FX32(0), LBV_N },{ LB_WAIT_DATA(LBW_OFFH) },
	{ LB2_0, NUM_FX32(0), NUM_FX32(LBE_MAX), LBV_N },{ LB_WAIT_DATA(LBW_ONH) },
	{ LB2_0, NUM_FX32(LBE_MAX), NUM_FX32(0), LBV_N },{ LB_WAIT_DATA(LBW_OFFH) },
	{ LB1, NUM_FX32(0), NUM_FX32(LBE_MAX), LBV_N },{ LB_WAIT_DATA(LBW_ONH) },
	{ LB1, NUM_FX32(LBE_MAX), NUM_FX32(0), LBV_N },{ LB_WAIT_DATA(LBW_OFFH) },
	{ LB2_1, NUM_FX32(0), NUM_FX32(LBE_MAX), LBV_N },{ LB_WAIT_DATA(LBW_ONH) },
	{ LB2_1, NUM_FX32(LBE_MAX), NUM_FX32(0), LBV_N },{ LB_WAIT_DATA(LBW_OFFH) },
	{ LB3_1, NUM_FX32(0), NUM_FX32(LBE_MAX), LBV_N },{ LB_WAIT_DATA(LBW_ONH) },
	{ LB3_1, NUM_FX32(LBE_MAX), NUM_FX32(0), LBV_N },{ LB_WAIT_DATA(LBW_OFF) },
	{ LB2_1, NUM_FX32(0), NUM_FX32(LBE_MAX), LBV_N },{ LB_WAIT_DATA(LBW_ONH) },
	{ LB2_1, NUM_FX32(LBE_MAX), NUM_FX32(0), LBV_N },{ LB_WAIT_DATA(LBW_OFFH) },
	{ LB1, NUM_FX32(0), NUM_FX32(LBE_MAX), LBV_N },{ LB_WAIT_DATA(LBW_ONH) },
	{ LB1, NUM_FX32(LBE_MAX), NUM_FX32(0), LBV_N },{ LB_WAIT_DATA(LBW_OFFH) },
	{ LB2_0, NUM_FX32(0), NUM_FX32(LBE_MAX), LBV_N },{ LB_WAIT_DATA(LBW_ONH) },
	{ LB2_0, NUM_FX32(LBE_MAX), NUM_FX32(0), LBV_N },{ LB_WAIT_DATA(LBW_OFFH) },
	{ LB3_0, NUM_FX32(0), NUM_FX32(LBE_MAX), LBV_N },{ LB_WAIT_DATA(LBW_ONH) },
	{ LB3_0, NUM_FX32(LBE_MAX), NUM_FX32(0), LBV_N },{ LB_WAIT_DATA(LBW_NEXT) },
	
	{ LB_LOOP, 1,0,0 },
};

static void LB_Anime( LINEBETANMWORK *work )
{
	u32 bit;
	int no,end,palno;
	u16 *buf;
	const u16 *base, *target;
	const LINEBETANM *data = &DATA_LineBetAnmTbl[work->anmno];
	
	for( no = 0, end = TRUE, bit = LB1; bit <= LB3_1; no++, bit <<= 1 ){
		if( (data->bit_line & bit) ){
			if( work->init_flag == FALSE ){
				work->evy[no] = data->start_evy;
				end = FALSE;
			}else{
				if( data->start_evy < data->target_evy ){
					work->evy[no] += data->speed_evy;
					if( work->evy[no] >= data->target_evy ){
						work->evy[no] = data->target_evy;
					}else{
						end = FALSE;
					}
				}else{
					work->evy[no] -= data->speed_evy;
					if( work->evy[no] <= data->target_evy ){
						work->evy[no] = data->target_evy;
					}else{
						end = FALSE;
					}
				}
			}
			
			palno = DATA_LinePlttNoTbl[no];
			base = work->cont->plttbase_line[no];
			target = work->cont->plttflash_line[no];
			buf = work->cont->plttbuf_line[no];
				
			ColorTargetFade16( base, target, FX32_NUM(work->evy[no]), buf );
			PaletteBGSet( work->main, BGFRAME_SLOT, palno, buf );
		}
	}
	
	for( ; bit <= LB_WAIT; bit <<= 1 ){
		if( (data->bit_line & LB_WAIT) ){
			work->wait += FX32_ONE;
			
			if( work->wait >= data->start_evy ){
				work->wait = 0;
			}else{
				end = FALSE;
			}
			
		}
	}
	
	work->init_flag = TRUE;
	
	if( end == TRUE ){
		work->init_flag = FALSE;
		work->anmno++;
		data = &DATA_LineBetAnmTbl[work->anmno];
		
		if( data->bit_line == LB_LOOP ){
			work->anmno = (int)data->start_evy;
			work->anmno = 0;
		}
	}
}

//--------------------------------------------------------------
/**
 * EOA �x�b�g�A�j���@������
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	int		TRUE=���평����
 */
//--------------------------------------------------------------
static int eoaLineBetAnm_Init( EOA_PTR eoa, void *wk )
{
	LINEBETANMWORK *work = wk;
	work->main = (SLOTMAIN *)EOA_AddPtrGet( eoa );
	work->cont = &work->main->plttcont;
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA �x�b�g�A�j���@�폜
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaLineBetAnm_Delete( EOA_PTR eoa, void *wk )
{
}

//--------------------------------------------------------------
/**
 * EOA �x�b�g�A�j���@����
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaLineBetAnm_Move( EOA_PTR eoa, void *wk )
{
	LINEBETANMWORK *work = wk;
	LB_Anime( work );
}

//--------------------------------------------------------------
///	EOA_H ���C���x�b�g�p���b�g�A�j��
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_LineBetAnm =
{
	sizeof(LINEBETANMWORK),
	eoaLineBetAnm_Init,
	eoaLineBetAnm_Delete,
	eoaLineBetAnm_Move,
	EOA_DrawProcDummy,
};

//==============================================================================
//	�p���b�g�G�t�F�N�g�@�����
//==============================================================================
//--------------------------------------------------------------
///	PLTTC_MOUNT
//--------------------------------------------------------------
typedef struct
{
	int seq_no;
	fx32 evy;
	MOONTYPE moon_type;
	SLOTMAIN *main;
}PLTTC_MOUNT;

static void MountKurakuTcb( TCB_PTR tcb, void *wk );
static void MountAkarukuTcb( TCB_PTR tcb, void *wk );
static void MountMoonLightTcb( TCB_PTR tcb, void *wk );

//--------------------------------------------------------------
/**
 * ����ʈÂ�
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void PlttEff_MountKuraku( SLOTMAIN *main )
{
	PLTTC_MOUNT *work = sys_AllocMemoryLo( HEAPID_SLOT, sizeof(PLTTC_MOUNT) );
	work->seq_no = 0;
	work->evy = 0;
	work->main = main;
	TCB_Add( MountKurakuTcb, work, TCBPRI_PLTTEFF );
}

//--------------------------------------------------------------
/**
 * ����ʖ��邭
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void PlttEff_MountAkaruku( SLOTMAIN *main )
{
	PLTTC_MOUNT *work = sys_AllocMemoryLo( HEAPID_SLOT, sizeof(PLTTC_MOUNT) );
	work->seq_no = 0;
	work->evy = 0;
	work->main = main;
	TCB_Add( MountAkarukuTcb, work, TCBPRI_PLTTEFF );
}

//--------------------------------------------------------------
/**
 * ����ʌ���
 * @param	main	SLOTMAIN
 * @param	type	MOONTYPE
 * @retval	nothing
 */
//--------------------------------------------------------------
static void PlttEff_MountMoonLight( SLOTMAIN *main, MOONTYPE type )
{
	PLTTC_MOUNT *work = sys_AllocMemoryLo( HEAPID_SLOT, sizeof(PLTTC_MOUNT) );
	work->seq_no = 0;
	work->moon_type = type;
	work->evy = NUM_FX32( 8 );
	work->main = main;
	TCB_Add( MountMoonLightTcb, work, TCBPRI_PLTTEFF );
	Snd_SePlay( SE_SLOT_MOON_LIGHT );
}

//--------------------------------------------------------------
/**
 * ����ʈÂ��@TCB����
 * @param	tcb		TCB_PTR
 * @param	wk		tcb work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void MountKurakuTcb( TCB_PTR tcb, void *wk )
{
	PLTTC_MOUNT *work = wk;
	PLTTCONTROL *cont = &work->main->plttcont;
	const u16 *base = cont->plttbase_mount;
	const u16 *target = cont->plttkurai_mount;
	u16 *buf = cont->plttbuf_mount;
	u16 evy;
	
	work->evy += 0x800;
	evy = FX32_NUM( work->evy );
	
	if( evy > 16 ){
		evy = 16;
	}
	
	ColorTargetFade16( base, target, evy, buf );
	PaletteBGSet( work->main, BGFRAME_BGSUB, BGPLTTNO_MOUNT_SKY, buf );
	
	if( evy == 16 ){
		sys_FreeMemoryEz( work );
		TCB_Delete( tcb );
	}
}

//--------------------------------------------------------------
/**
 * ����ʖ��邭�@TCB����
 * @param	tcb		TCB_PTR
 * @param	wk		tcb work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void MountAkarukuTcb( TCB_PTR tcb, void *wk )
{
	PLTTC_MOUNT *work = wk;
	PLTTCONTROL *cont = &work->main->plttcont;
	const u16 *base = cont->plttkurai_mount;
	const u16 *target = cont->plttbase_mount;
	u16 *buf = cont->plttbuf_mount;
	u16 evy;
	
	work->evy += 0x800;
	evy = FX32_NUM( work->evy );
	
	if( evy > 16 ){
		evy = 16;
	}
	
	ColorTargetFade16( base, target, evy, buf );
	PaletteBGSet( work->main, BGFRAME_BGSUB, BGPLTTNO_MOUNT_SKY, buf );
	
	if( evy == 16 ){
		sys_FreeMemoryEz( work );
		TCB_Delete( tcb );
	}
}

//--------------------------------------------------------------
/**
 * ����ʌ����t���b�V���@TCB����
 * @param	tcb		TCB_PTR
 * @param	wk		tcb work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void MountMoonLightTcb( TCB_PTR tcb, void *wk )
{
	PLTTC_MOUNT *work = wk;
	PLTTCONTROL *cont = &work->main->plttcont;
	const u16 *target,*base = cont->plttkurai_mount;
	u16 *buf = cont->plttbuf_mount;
	int evy;
	
	if( work->moon_type == MOON_LIGHT ){
		target = cont->plttflash_mount;
	}else{
		target = cont->plttflash_red_mount;
	}
	
	switch( work->seq_no ){
	case 0:
		work->evy += 0x1000;
		evy = FX32_NUM( work->evy );
	
		if( evy > 16 ){
			evy = 16;
			work->seq_no++;
		}
	
		ColorTargetFade16( base, target, evy, buf );
		PaletteBGSet( work->main, BGFRAME_BGSUB, BGPLTTNO_MOUNT_SKY, buf );
		break;
	case 1:
		work->evy -= 0x400;
		evy = FX32_NUM( work->evy );
	
		if( evy < 0 ){
			evy = 0;
		}
	
		ColorTargetFade16( base, target, evy, buf );
		PaletteBGSet( work->main, BGFRAME_BGSUB, BGPLTTNO_MOUNT_SKY, buf );
		
		if( evy == 0 ){
			sys_FreeMemoryEz( work );
			TCB_Delete( tcb );
		}
	}
}

//==============================================================================
//	�p�[�c
//==============================================================================
//--------------------------------------------------------------
/**
 * ���[���G���擾
 * @param	no		REEL_NUM
 * @param	offs	�I�t�Z�b�g�@�O���b�h�P��
 * @retval	REEL_PATTERN	REEL_PATTERN
 */
//--------------------------------------------------------------
REEL_PATTERN Slot_ReelPatternGet( SLOTMAIN *main, REEL_NUM no, int offs )
{
	int pos = (main->reel_grid_y[no] + offs) % REEL_PT_MAX;
	
	if( pos < 0 ){
		pos = REEL_PT_MAX + pos;
	}
	
	return( DATA_SlotDataReelPattern[no][pos] );
}

//--------------------------------------------------------------
/**
 * ���[���G���擾�@�O���b�h�␳�A��
 * @param	no		REEL_NUM
 * @param	offs	�I�t�Z�b�g�@�O���b�h�P��
 * @retval	REEL_PATTERN	REEL_PATTERN
 */
//--------------------------------------------------------------
REEL_PATTERN Slot_ReelPatternGridGet( SLOTMAIN *main, REEL_NUM no, int offs )
{
	int diff = 0;
	
	if( (main->reel_dot_y[no] % NUM_FX32(REEL_PT_V_SIZE)) ){
		diff--;
	}
	
	return( Slot_ReelPatternGet(main,no,offs+diff) );
}

//--------------------------------------------------------------
/**
 * �L�[�g���K�`�F�b�N
 * @param	pad		PAD_BUTTON_A��
 * @retval	PADRET	PADRET
 */
//--------------------------------------------------------------
static PADRET keyTrg( u32 pad )
{
	u32 ret = sys.trg & pad;
	
	if( ret == pad ){ return( PAD_SAME ); }
	if( (ret & pad) ){ return( PAD_ON ); }
	return( PAD_NON );
}

//--------------------------------------------------------------
/**
 * �q�b�g�r�b�g->������G��
 * @param	bit	LOTTERY_HITBIT_REPLAY��
 * @retval	REEL_PATTERN REEL_PATTERN
 */
//--------------------------------------------------------------
static REEL_PATTERN lotteryHitBitPattern( u32 bit )
{
	if( bit & (LOTTERY_HITBIT_REPLAY|LOTTERY_HITBIT_REPLAY_B) ){
		return( REEL_REPLAY );
	}
	
	if( bit & (LOTTERY_HITBIT_CHERRY|LOTTERY_HITBIT_CHERRY_B) ){
		return( REEL_CHERRY );
	}
	
	if( bit & (LOTTERY_HITBIT_BELL|LOTTERY_HITBIT_BELL_B) ){
		return( REEL_BELL );
	}
	
	if( bit & (LOTTERY_HITBIT_SUIKA|LOTTERY_HITBIT_SUIKA_B) ){
		return( REEL_SUIKA );
	}
	
	if( bit & (LOTTERY_HITBIT_BLACK7) ){
		return( REEL_BLACK7 );
	}
	
	if( bit & (LOTTERY_HITBIT_RED7) ){
		return( REEL_RED7 );
	}
	
	return( REEL_PATTERN_MAX );
}

//--------------------------------------------------------------
/**
 * 1-1-1������G���擾
 * @param	main	SLOTMAIN
 * @retval	REEL_PATTERN	REEL_PATTERN_MAX=����
 */
//--------------------------------------------------------------
static REEL_PATTERN reelHitPatternGet_111( SLOTMAIN *main )
{
	u32 pat0,pat1,pat2;
	
	pat0 = Slot_ReelPatternGridGet( main, 0, 1 );
	pat1 = Slot_ReelPatternGridGet( main, 1, 1 );
	pat2 = Slot_ReelPatternGridGet( main, 2, 1 );
	
	if( pat0 == REEL_CHERRY || (pat0 == pat1 && pat0 == pat2) ){
		return( pat0 );
	}
	
	return( REEL_PATTERN_MAX );
}

//--------------------------------------------------------------
/**
 * 2-2-2������G���擾
 * @param	main	SLOTMAIN
 * @retval	REEL_PATTERN	REEL_PATTERN_MAX=����
 */
//--------------------------------------------------------------
static REEL_PATTERN reelHitPatternGet_222( SLOTMAIN *main )
{
	u32 pat0,pat1,pat2;
	
	pat0 = Slot_ReelPatternGridGet( main, 0, 2 );
	pat1 = Slot_ReelPatternGridGet( main, 1, 2 );
	pat2 = Slot_ReelPatternGridGet( main, 2, 2 );
	
	if( pat0 == REEL_CHERRY || (pat0 == pat1 && pat0 == pat2) ){
		return( pat0 );
	}
	
	return( REEL_PATTERN_MAX );
}

//--------------------------------------------------------------
/**
 * 3-3-3������G���擾
 * @param	main	SLOTMAIN
 * @retval	REEL_PATTERN	REEL_PATTERN_MAX=����
 */
//--------------------------------------------------------------
static REEL_PATTERN reelHitPatternGet_333( SLOTMAIN *main )
{
	u32 pat0,pat1,pat2;
	
	pat0 = Slot_ReelPatternGridGet( main, 0, 3 );
	pat1 = Slot_ReelPatternGridGet( main, 1, 3 );
	pat2 = Slot_ReelPatternGridGet( main, 2, 3 );
	
	if( pat0 == REEL_CHERRY || (pat0 == pat1 && pat0 == pat2) ){
		return( pat0 );
	}
	
	return( REEL_PATTERN_MAX );
}

//--------------------------------------------------------------
/**
 * 1-2-3������G���擾
 * @param	main	SLOTMAIN
 * @retval	REEL_PATTERN	REEL_PATTERN_MAX=����
 */
//--------------------------------------------------------------
static REEL_PATTERN reelHitPatternGet_123( SLOTMAIN *main )
{
	u32 pat0,pat1,pat2;
	
	pat0 = Slot_ReelPatternGridGet( main, 0, 1 );
	pat1 = Slot_ReelPatternGridGet( main, 1, 2 );
	pat2 = Slot_ReelPatternGridGet( main, 2, 3 );
	
	if( pat0 == REEL_CHERRY || (pat0 == pat1 && pat0 == pat2) ){
		return( pat0 );
	}
	
	return( REEL_PATTERN_MAX );
}

//--------------------------------------------------------------
/**
 * 3-2-1������G���擾
 * @param	main	SLOTMAIN
 * @retval	REEL_PATTERN	REEL_PATTERN_MAX=����
 */
//--------------------------------------------------------------
static REEL_PATTERN reelHitPatternGet_321( SLOTMAIN *main )
{
	u32 pat0,pat1,pat2;
	
	pat0 = Slot_ReelPatternGridGet( main, 0, 3 );
	pat1 = Slot_ReelPatternGridGet( main, 1, 2 );
	pat2 = Slot_ReelPatternGridGet( main, 2, 1 );
	
	if( pat0 == REEL_CHERRY || (pat0 == pat1 && pat0 == pat2) ){
		return( pat0 );
	}
	
	return( REEL_PATTERN_MAX );
}

//--------------------------------------------------------------
/**
 * ���Ֆʓ�����G���擾
 * @param	main	SLOTMAIN
 * @param	lottery_bit	LOTTERY_HITBIT_NON��
 * @retval	REEL_PATTERN	REEL_PATTERN_MAX=����
 */
//--------------------------------------------------------------
static REEL_PATTERN reelHitPatternGet( SLOTMAIN *main, u32 lottery_bit, u32 *line )
{
	u32 pat,hit;
	
#ifdef PM_DEBUG
	DEBUG_reelHitPatternCheck( main, lottery_bit );
#endif
	
	*line = LINEBIT_NON;
	hit = REEL_PATTERN_MAX;
	
	pat = reelHitPatternGet_111( main );
	if( pat != REEL_PATTERN_MAX ){ hit = pat; *line |= LINEBIT_2_0; }
	pat = reelHitPatternGet_222( main );
	if( pat != REEL_PATTERN_MAX ){ hit = pat; *line |= LINEBIT_1; }
	pat = reelHitPatternGet_333( main );
	if( pat != REEL_PATTERN_MAX ){ hit = pat; *line |= LINEBIT_2_1; }
	pat = reelHitPatternGet_123( main );
	if( pat != REEL_PATTERN_MAX ){ hit = pat; *line |= LINEBIT_3_0; }
	pat = reelHitPatternGet_321( main );
	if( pat != REEL_PATTERN_MAX ){ hit = pat; *line |= LINEBIT_3_1; }
	
	return( hit );
}

//--------------------------------------------------------------
/**
 * ���Ֆʓ�����G���擾�@�{�[�i�X�P�R
 * @param	main	SLOTMAIN
 * @param	lottery_bit	LOTTERY_HITBIT_NON��
 * @retval	REEL_PATTERN	REEL_PATTERN_MAX=����
 */
//--------------------------------------------------------------
static REEL_PATTERN reelHitPatternGetBonus( SLOTMAIN *main, u32 lottery_bit, u32 *line )
{
	u32 pat;
	
	*line = LINEBIT_NON;
	pat = reelHitPatternGet_222( main );
	
	if( pat != REEL_PATTERN_MAX ){
		GF_ASSERT( pat == REEL_REPLAY && "SLOT ERROR MISS HIT BONUS" );
		*line |= LINEBIT_1;
	}
	
	return( pat );
}

//--------------------------------------------------------------
/**
 * ���I�r�b�g����{�[���^�C�v�擾
 * @param	bit		LOTTERY_HITBIT_REPLAY��
 * @retval	BALLTYPE	BALLTYPE
 */
//--------------------------------------------------------------
static BALLTYPE Lottery_NaviBallGet( u32 bit )
{
	if( bit & (LOTTERY_HITBIT_REPLAY|LOTTERY_HITBIT_REPLAY_B) ){
		return( BALL_SUP );
	}
	
	if( bit & (LOTTERY_HITBIT_CHERRY|LOTTERY_HITBIT_CHERRY_B) ){
		return( BALL_MON );
	}
	
	if( bit & (LOTTERY_HITBIT_BELL|LOTTERY_HITBIT_BELL_B) ){
		return( BALL_HYP );
	}
	
	if( bit & (LOTTERY_HITBIT_SUIKA|LOTTERY_HITBIT_SUIKA_B) ){
		return( BALL_SAF );
	}
	
	GF_ASSERT( 0 && "Lottery_NaviBallGet() non bit error" );
	return( BALL_PRE );
}

//--------------------------------------------------------------
/**
 * ��~�{�^���N���A
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void StopButtonClear( SLOTMAIN *main )
{
	int i = 0; do{ main->reel_stop_btn[i] = 0; i++; }while( i < REEL_MAX );
}

//--------------------------------------------------------------
/**
 * ��~�{�^���i�[
 * @param	main	SLOTMAIN
 * @param	btn		�i�[����{�^��
 * @retval	nothing
 */
//--------------------------------------------------------------
static void StopButtonSet( SLOTMAIN *main, u32 btn )
{
	int i = 0;
	do{ if( main->reel_stop_btn[i] == 0 ){ break; } i++; }while( i < REEL_MAX );
	GF_ASSERT( i < REEL_MAX && "StopButtonSet() error" );
	main->reel_stop_btn[i] = btn;
}

//--------------------------------------------------------------
/**
 * ��~�{�^���`�F�b�N 012
 * @param	main	SLOTMAIN
 * @retval	int		TRUE=012
 */
//--------------------------------------------------------------
static int StopButtonCheck012( SLOTMAIN *main )
{
	int i = 0;
	u32 tbl[REEL_MAX] = { PAD_REELPUSH0, PAD_REELPUSH1, PAD_REELPUSH2 };
	
	do{
		if( main->reel_stop_btn[i] != 0 && main->reel_stop_btn[i] != tbl[i] ){
			return( FALSE );
		}
		i++;
	}while( i < REEL_MAX );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * ��~�{�^���`�F�b�N �w����
 * @param	main	SLOTMAIN
 * @retval	int		TRUE=012
 */
//--------------------------------------------------------------
static int StopButtonCheckYubisashi( SLOTMAIN *main )
{
	int i = 0;
	const PIPNAVI *navi = &DATA_BonusGamePipNaveTbl[main->yubisashi_type];
	
	do{
		if( main->reel_stop_btn[i] != 0 && main->reel_stop_btn[i] != navi->btn[i] ){
			return( FALSE );
		}
		i++;
	}while( i < REEL_MAX );
	
	return( TRUE );
}

#ifdef DEBUG_ON_SLOT
//--------------------------------------------------------------
/**
 * ��~�{�^���`�F�b�N �w�����@�f�o�b�O�p
 * @param	main	SLOTMAIN
 * @retval	int		TRUE=012
 */
//--------------------------------------------------------------
static u32 DEBUG_StopButtonGetYubisashi( SLOTMAIN *main )
{
	const PIPNAVI *navi = &DATA_BonusGamePipNaveTbl[main->yubisashi_type];
	
	if( main->d_work.auto_play_replay_avoid_flag == FALSE ){
		int i = 0;
		
		do{
			if( main->reel_stop_btn[i] == 0 ){
				return( navi->btn[i] );
			}
			i++;
		}while( i < REEL_MAX );
	}else{
		if( main->bonus_moonlight_red_flag == MOONRED_HIT ){
			int btn = 0;
			int i = REEL_MAX - 1;
		
			do{
				if( main->reel_stop_btn[btn] == 0 ){
					return( navi->btn[i] );
				}
				btn++;
				i--;
			}while( i >= REEL_0 );
		}else{
			int i = 0;
		
			do{
				if( main->reel_stop_btn[i] == 0 ){
					return( navi->btn[i] );
				}
				i++;
			}while( i < REEL_MAX );
		}
	}
	
	return( 0 );
}
#endif

//--------------------------------------------------------------
/**
 * �{�^���A�g���r���[�g�@������
 * @param	main	SLOTMAIN
 * @param	no		REEL_NUM
 * @retval	nothing
 */
//--------------------------------------------------------------
static void ReelButtonAttr_ON( SLOTMAIN *main, REEL_NUM no )
{
	const int *pos = DATA_ButtonPos[no];
	GF_BGL_ScrPalChange( main->bgl, BGFRAME_SLOT, pos[0], pos[1], 3, 2, 6 );
	GF_BGL_LoadScreenV_Req( main->bgl, BGFRAME_SLOT );
}

//--------------------------------------------------------------
/**
 * �{�^���A�g���r���[�g�@������Ă��Ȃ�
 * @param	main	SLOTMAIN
 * @param	no		REEL_NUM
 * @retval	nothing
 */
//--------------------------------------------------------------
static void ReelButtonAttr_OFF( SLOTMAIN *main, REEL_NUM no )
{
	const int *pos = DATA_ButtonPos[no];
	GF_BGL_ScrPalChange( main->bgl, BGFRAME_SLOT, pos[0], pos[1], 3, 2, 5 );
	GF_BGL_LoadScreenV_Req( main->bgl, BGFRAME_SLOT );
}

//--------------------------------------------------------------
/**
 * �x�����@��{�q��
 * @param	main	SLOTMAIN *
 * @retval	u32 �x������
 */
//--------------------------------------------------------------
static u32 PayOutCoinGet_Small( SLOTMAIN *main )
{
	int i,payout;
	REEL_PATTERN pat = main->reel_hit_pattern;
	u32 bit = main->reel_hit_line_bit;
	
	GF_ASSERT( pat != REEL_PATTERN_MAX && "SLOT ERROR PAYOUT COIN GET S" );
	
	for( i = 0, payout = 0; i < LINE_MAX; i++, bit >>= 1 ){
		if( (bit & 0x01) ){
			payout += DATA_SlotPayOutSmall[pat];
		}
	}
	
	return( payout );
}

//==============================================================================
//	data
//==============================================================================
//--------------------------------------------------------------
///	CONT_BONUS_TYPE->LOTTERY_HITBIT
//--------------------------------------------------------------
static const u32 DATA_ContBonusTypeHitBit[CONT_BONUS_TYPE_MAX] =
{
	LOTTERY_HITBIT_RED7,
	LOTTERY_HITBIT_RED7,
	LOTTERY_HITBIT_RED7,
	LOTTERY_HITBIT_BLACK7,
	LOTTERY_HITBIT_BLACK7,
	LOTTERY_HITBIT_BLACK7,
};

//--------------------------------------------------------------
///	�w�����e�[�u��
//--------------------------------------------------------------
static const PIPNAVI DATA_BonusGamePipNaveTbl[YUBI_MAX] =
{
	{
		{PAD_REELPUSH0,PAD_REELPUSH1,PAD_REELPUSH2},
		{PIPMT_LEFT,PIPMT_NAKA,PIPMT_RIGHT},
	},
	{
		{PAD_REELPUSH0,PAD_REELPUSH2,PAD_REELPUSH1},
		{PIPMT_LEFT,PIPMT_RIGHT,PIPMT_NAKA},
	},
	{
		{PAD_REELPUSH1,PAD_REELPUSH0,PAD_REELPUSH2},
		{PIPMT_NAKA,PIPMT_LEFT,PIPMT_RIGHT},
	},
	{
		{PAD_REELPUSH1,PAD_REELPUSH2,PAD_REELPUSH0},
		{PIPMT_NAKA,PIPMT_RIGHT,PIPMT_LEFT},
	},
	{
		{PAD_REELPUSH2,PAD_REELPUSH0,PAD_REELPUSH1},
		{PIPMT_RIGHT,PIPMT_LEFT,PIPMT_NAKA},
	},
	{
		{PAD_REELPUSH2,PAD_REELPUSH1,PAD_REELPUSH0},
		{PIPMT_RIGHT,PIPMT_NAKA,PIPMT_LEFT},
	},
};

//--------------------------------------------------------------
///	�{�^���ʒu
//--------------------------------------------------------------
static const int DATA_ButtonPos[3][2] =
{
	{ 0x07, 0x11 },
	{ 0x0f, 0x11 },
	{ 0x16, 0x11 },
};

//==============================================================================
//	�f�o�b�O
//==============================================================================
//----
#ifdef PM_DEBUG
//----
//--------------------------------------------------------------
///	�f�o�b�O�@���I�G���`�F�b�N
//--------------------------------------------------------------
static void DEBUG_reelHitPatternCheck( SLOTMAIN *main, u32 lottery_bit )
{
	int flag;
	u32 count = 0;
	REEL_PATTERN hit111,hit222,hit333,hit123,hit321,lt_hit;
	
	//����������`�F�b�N
	hit111 = reelHitPatternGet_111( main );
	if( hit111 != REEL_PATTERN_MAX ){ count++; }
	hit222 = reelHitPatternGet_222( main );
	if( hit222 != REEL_PATTERN_MAX ){ count++; }
	hit333 = reelHitPatternGet_333( main );
	if( hit333 != REEL_PATTERN_MAX ){ count++; }
	
	hit123 = reelHitPatternGet_123( main );
	if( hit123 != REEL_PATTERN_MAX && hit123 != REEL_CHERRY ){ count++; }
	hit321 = reelHitPatternGet_321( main );
	if( hit321 != REEL_PATTERN_MAX && hit321 != REEL_CHERRY ){ count++; }
	
	if( count > 1 ){
		OS_Printf( "SLOT DEBUG PLURAL HIT BIT=0x%x\n", lottery_bit );
		GF_ASSERT( 0 && "SLOT ERROR HIT PLURAL" );
	}
	
	if( count == 0 ){			//�����薳��
		return;
	}
	
	//���I���ꂽ�����肩�ǂ���
	lt_hit = lotteryHitBitPattern( lottery_bit );
		
	if( lt_hit == REEL_PATTERN_MAX ){
		OS_Printf( "SLOT DEBUG NOBIT HIT�@PTN=%d\n", lt_hit );
		GF_ASSERT( 0 && "SLOT ERROR MISS HIT" );
	}
	
	flag = FALSE;
			
	if( hit111 != REEL_PATTERN_MAX && hit111 != lt_hit ){ flag = TRUE; }
	if( hit222 != REEL_PATTERN_MAX && hit222 != lt_hit ){ flag = TRUE; }
	if( hit333 != REEL_PATTERN_MAX && hit333 != lt_hit ){ flag = TRUE; }
	if( hit123 != REEL_PATTERN_MAX && hit123 != lt_hit ){ flag = TRUE; }
	if( hit321 != REEL_PATTERN_MAX && hit321 != lt_hit ){ flag = TRUE; }
	
	if( flag == TRUE ){
		OS_Printf( "SLOT DEBUG HITBIT NOT HITPTN BIT=0x%x, PTN=%d\n", lottery_bit, lt_hit );
		GF_ASSERT( 0 && "SLOT ERROR MISS HIT" );
	}
}

//--------------------------------------------------------------
//	��ʃe�X�g
//--------------------------------------------------------------
#ifdef DEBUG_DDISPTEST
static int DEBUG_DDispTest( SLOTMAIN *main )
{
	if( keyTrg(PAD_END) ){
		return( TRUE );
	}
		
	switch( DEBUG_SeqNoDDispTest ){
	case 0:
		main->ddispcont.balltype = BALL_PRE;
		DDC_TypeChange( main, DDISP_MBALL_SPIN_START );
		DEBUG_SeqNoDDispTest++;
		break;
	case 1:
		if( DDC_EndCheck(main) == FALSE ){
			break;
		}
			
		if( DEBUG_DDispTestFrame&0x01 ){
			main->ddispcont.piptype = PIP_NORMAL;
		}else{
			main->ddispcont.piptype = PIP_RARE;
		}
			
		DEBUG_DDispTestFrame++;
		DDC_TypeChange( main, DDISP_PIP_START );
		DEBUG_SeqNoDDispTest++;
		break;
	case 2:
		if( DDC_EndCheck(main) == FALSE ){
			break;
		}
			
		DDC_TypeChange( main, DDISP_PIP_ANENCORE );
		DEBUG_SeqNoDDispTest++;
		break;
	case 3:	
		if( DDC_EndCheck(main) == FALSE ){
			break;
		}
		
		DDC_TypeChange( main, DDISP_PIP_OUT );
		DEBUG_SeqNoDDispTest++;
		break;
	case 4:
		if( DDC_EndCheck(main) == FALSE ){
			break;
		}
		
		DEBUG_SeqNoDDispTest = 0;
		break;
	}
	
	return( FALSE );
}
#endif	//DEBUG_DDISPTEST

//--------------------------------------------------------------
//	�f�o�b�O�E�B���h�E
//--------------------------------------------------------------
#ifdef DEBUG_ON_SLOT
static void DebugCharPut(u16 *screen, char c, int x, int y)
{
	if(c==0x20){
		c = 0x29;
	}
	if(c=='='){
		c = 0x30+10;
	}
	if(c=='-'){   // �}�C�i�X�\�����o�Ă��Ȃ������̂�M�ɒu��
		c = 'M';
	}
	screen[x+y*32] = (BGF_SLOT_PANO_FONT<<12)+(c-0x2F);
}

static void DebugStrPut( GF_BGL_INI *ini, char *str,int x, int y)
{
	int  n=0;
	u16  *screen;
	screen = GF_BGL_ScreenAdrsGet( ini, BGFRAME_SUB_DEBUG );
	
	while(str[n]!=0){
		DebugCharPut(screen,str[n],x+n,y);
		n++;
	}
}

typedef struct
{
	u32 lottery_bit;
	const char *str;
}D_YAKU;

enum
{
	DATA_YAKU_KIHON_MAX = 9,
	DATA_YAKU_BIG_AUTO,
	DATA_YAKU_GINGA_AUTO,
	DATA_YAKU_PIP_NORMAL,
	DATA_YAKU_PIP_META,
	DATA_YAKU_PIP_RARE,
	DATA_YAKU_BONUS_END,
	DATA_YAKU_BONUS_GASE,
	DATA_YAKU_BONUS_ANENCORE,
	DATA_YAKU_BONUS_NORMAL,
	DATA_YAKU_MOONLIGHT,
	DATA_YAKU_MOONRED,
	DATA_YAKU_MAX,
};

static const D_YAKU DATA_YakuTbl[DATA_YAKU_MAX] =
{
	{ LOTTERY_HITBIT_REPLAY, "REPLAY" },
	{ LOTTERY_HITBIT_REPLAY_B, "REPLAY BONUS" },
	{ LOTTERY_HITBIT_CHERRY, "CHERRY" },
	{ LOTTERY_HITBIT_CHERRY_B, "CHERRY BONUS" },
	{ LOTTERY_HITBIT_BELL, "BELL" },
	{ LOTTERY_HITBIT_BELL_B, "BELL BONUS" },
	{ LOTTERY_HITBIT_SUIKA, "SUIKA" },
	{ LOTTERY_HITBIT_SUIKA_B, "SUIKA BONUS" },
	{ LOTTERY_HITBIT_BLACK7, "GINGA" },
	{ LOTTERY_HITBIT_RED7, "SEVEN" },
	{ LOTTERY_HITBIT_RED7, "SEVEN AUTO" },
	{ LOTTERY_HITBIT_BLACK7, "GINGA AUTO" },
	{ 0, "PIPPI" },
	{ 0, "PIPPI META" },
	{ 0, "PIPPI RARE" },
	{ 0, "BONUS FORCE END" },	
	{ 0, "BONUS EFF GASE" },
	{ 0, "BONUS EFF ANENCORE" },
	{ 0, "BONUS EFF NORMAL" },
	{ 0, "MOON LIGHT" },
	{ 0, "MOON RED" },
};

static void DEBUG_SlotDataLotteryPrint( SLOTMAIN *main, int no )
{
	char str[256];
	GF_BGL_INI *bgl = main->bgl;
	const D_YAKU *yaku = &DATA_YakuTbl[no];
	
	sprintf( str, yaku->str );
	DebugStrPut( bgl, str, 0, 0 );
	
	sprintf( str, "PUSH LR CHANGE LOTTERY" );
	DebugStrPut( bgl, str, 0, 2 );
	sprintf( str, "PUSH A SET LOTTERY" );
	DebugStrPut( bgl, str, 0, 3 );
	sprintf( str, "PUSH B EXIT" );
	DebugStrPut( bgl, str, 0, 4 );
	
	GF_BGL_LoadScreenReq( main->bgl, BGFRAME_SUB_DEBUG );
}

static void DEBUG_SlotDataCoinPrint( SLOTMAIN *main )
{
	char str[256];
	GF_BGL_INI *bgl = main->bgl;
	
	sprintf( str, "CREDIT %d", main->credit );
	DebugStrPut( bgl, str, 0, 0 );
	
	sprintf( str, "PUSH LR KEY UP DOWN 10" );
	DebugStrPut( bgl, str, 0, 2 );
	sprintf( str, "PUSH LR BUTTON UP DOWN 100" );
	DebugStrPut( bgl, str, 0, 3 );
	sprintf( str, "PUSH UP KEY 50000" );
	DebugStrPut( bgl, str, 0, 4 );
	sprintf( str, "PUSH DOWN KEY 3" );
	DebugStrPut( bgl, str, 0, 5 );
	sprintf( str, "PUSH B EXIT" );
	DebugStrPut( bgl, str, 0, 6 );
	
	GF_BGL_LoadScreenReq( main->bgl, BGFRAME_SUB_DEBUG );
}

static void DEBUG_SlotDataPrint( SLOTMAIN *main )
{
	char str[256];
	GF_BGL_INI *bgl = main->bgl;
	
	sprintf( str, "HARD %d", main->hard+1 );
	DebugStrPut( bgl, str, 0, 0 );
	
	sprintf( str, "GAME   %05d", main->game_count );
	DebugStrPut( bgl, str, 0, 1 );
	
	sprintf( str, "PAYOUT %05d", main->payout_total );
	DebugStrPut( bgl, str, 0, 2 );
	
	sprintf( str, "BET    %05d", main->bet_total );
	DebugStrPut( bgl, str, 0, 3 );
	
	sprintf( str, "NGAME  %05d", main->ngame_count );
	DebugStrPut( bgl, str, 0, 4 );
	
	sprintf( str, "BMODE  %05d", main->bmode_count );
	DebugStrPut( bgl, str, 0, 5 );
	
	sprintf( str, "BGAME  %05d", main->bgame_count );
	DebugStrPut( bgl, str, 0, 6 );
	
	sprintf( str, "BONUS MAX %03d", main->bonus_continue_count_max );
	DebugStrPut( bgl, str, 0, 7 );
	
	sprintf( str, "KIHON A %04d", main->kihon_a_count );
	DebugStrPut( bgl, str, 0, 8 );
	
	sprintf( str, "KIHON B %04d", main->kihon_b_count );
	DebugStrPut( bgl, str, 0, 9 );
	
	sprintf( str, "KEIZOKU 50 %03d", main->keizoku_50_count );
	DebugStrPut( bgl, str, 0, 10 );
	
	sprintf( str, "KEIZOKU 70 %03d", main->keizoku_70_count );
	DebugStrPut( bgl, str, 0, 11 );
	
	sprintf( str, "KEIZOKU 90 %03d", main->keizoku_90_count );
	DebugStrPut( bgl, str, 0, 12 );
	
	sprintf( str, "METAMON %04d", main->metamon_count );
	DebugStrPut( bgl, str, 0, 13 );
	
	sprintf( str, "PIPPI   %04d", main->pippi_count );
	DebugStrPut( bgl, str, 0, 14 );
	
	sprintf( str, "R PIPPI %04d", main->rare_pippi_count );
	DebugStrPut( bgl, str, 0, 15 );
	
	sprintf( str, "NAVI    %04d", main->navi_hit_count );
	DebugStrPut( bgl, str, 0, 16 );
	
	sprintf( str, "PUSH LR SET HARD" );
	DebugStrPut( bgl, str, 0, 18 );
	sprintf( str, "PUSH A SET COIN" );
	DebugStrPut( bgl, str, 0, 19 );
	sprintf( str, "PUSH SELECT SET LOTTERY" );
	DebugStrPut( bgl, str, 0, 20 );
	sprintf( str, "PUSH START OR X AUTO" );
	DebugStrPut( bgl, str, 0, 21 );
	sprintf( str, "PUSH B EXIT" );
	DebugStrPut( bgl, str, 0, 22 );
	//----
	
	sprintf( str, "REPLAY %04d %04d", main->replay_hit_count, main->replay_hit_b_count );
	DebugStrPut( bgl, str, 15, 0 );
	sprintf( str, "CHERRY %04d %04d", main->cherry_hit_count, main->cherry_hit_b_count );
	DebugStrPut( bgl, str, 15, 1 );
	sprintf( str, "BELL   %04d %04d", main->bell_hit_count, main->bell_hit_b_count );
	DebugStrPut( bgl, str, 15, 2 );
	sprintf( str, "SUIKA  %04d %04d", main->suika_hit_count, main->suika_hit_b_count );
	DebugStrPut( bgl, str, 15, 3 );
	sprintf( str, "GINGA  %04d", main->ginga_hit_count );
	DebugStrPut( bgl, str, 15, 4 );
	sprintf( str, "SEVEN  %04d", main->seven_hit_count );
	DebugStrPut( bgl, str, 15, 5 );
	//----
	
	sprintf( str, "KEIZOKURITU %03d", main->bonus_continue_prob );
	DebugStrPut( bgl, str, 15, 7 );
	sprintf( str, "MOONLIGHT %04d", main->moonlight_count );
	DebugStrPut( bgl, str, 15, 8 );
	sprintf( str, "MOONRED   %04d", main->moonred_count );
	DebugStrPut( bgl, str, 15, 9 );
	//----
	
	GF_BGL_LoadScreenReq( main->bgl, BGFRAME_SUB_DEBUG );
}

static void DEBUG_SlotDataHitLineCountPrint( SLOTMAIN *main )
{
	char str[256];
	GF_BGL_INI *bgl = main->bgl;
	D_SLOTWORK *work = &main->d_work;
		
	sprintf( str, "HIT LINE 1    %d", work->hitline[LINE_1] );
	DebugStrPut( bgl, str, 0, 0 );
	sprintf( str, "HIT LINE 2X0  %d", work->hitline[LINE_2_0] );
	DebugStrPut( bgl, str, 0, 1 );
	sprintf( str, "HIT LINE 2X1  %d", work->hitline[LINE_2_1] );
	DebugStrPut( bgl, str, 0, 2 );
	sprintf( str, "HIT LINE 3X0  %d", work->hitline[LINE_3_0] );
	DebugStrPut( bgl, str, 0, 3 );
	sprintf( str, "HIT LINE 3X1  %d", work->hitline[LINE_3_1] );
	DebugStrPut( bgl, str, 0, 4 );
	
	sprintf( str, "PUSH B EXIT" );
	DebugStrPut( bgl, str, 0, 6 );
	
	GF_BGL_LoadScreenReq( main->bgl, BGFRAME_SUB_DEBUG );
}

static int DEBUG_DebugKeyCheck( SLOTMAIN *main )
{
	if( keyTrg(PAD_BUTTON_SELECT) ){
		D_SLOTWORK *work = &main->d_work;
		work->seq_no = 1;
		return( TRUE );
	}
	
	return( FALSE );
}

static int DEBUG_DebugProc( SLOTMAIN *main )
{
	D_SLOTWORK *work = &main->d_work; 
	switch( work->seq_no ){
	case 0:
		break;
	case 1:
		GF_BGL_ScrClear( main->bgl, BGFRAME_SUB_DEBUG );
		GF_BGL_LoadScreenReq( main->bgl, BGFRAME_SUB_DEBUG );
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
		work->seq_no++;
		return( TRUE );
	case 2:	//�f�o�b�O���
		if( keyTrg(PAD_BUTTON_B) ){
			GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );
			work->seq_no = 0;
			return( TRUE );
		}else if( keyTrg(PAD_BUTTON_SELECT) ){
			work->seq_no = 3;
			GF_BGL_ScrClear( main->bgl, BGFRAME_SUB_DEBUG );
			GF_BGL_LoadScreenReq( main->bgl, BGFRAME_SUB_DEBUG );
			return( TRUE );
		}else if( keyTrg(PAD_BUTTON_A) ){
			work->seq_no = 4;
			GF_BGL_ScrClear( main->bgl, BGFRAME_SUB_DEBUG );
			GF_BGL_LoadScreenReq( main->bgl, BGFRAME_SUB_DEBUG );
			return( TRUE );
		}else if( keyTrg(PAD_BUTTON_L) ){
			work->seq_no = 5;
			GF_BGL_ScrClear( main->bgl, BGFRAME_SUB_DEBUG );
			GF_BGL_LoadScreenReq( main->bgl, BGFRAME_SUB_DEBUG );
			return( TRUE );
		}
		
		if( keyTrg(PAD_BUTTON_START) ){
			work->seq_no = 0;
			work->auto_flag = TRUE;
			work->auto_play_replay_avoid_flag = FALSE;
			GF_BGL_ScrClear( main->bgl, BGFRAME_SUB_DEBUG );
			GF_BGL_LoadScreenReq( main->bgl, BGFRAME_SUB_DEBUG );
			return( FALSE );
		}
		
		if( keyTrg(PAD_BUTTON_X) ){
			work->seq_no = 0;
			work->auto_flag = TRUE;
			work->auto_play_replay_avoid_flag = TRUE;
			GF_BGL_ScrClear( main->bgl, BGFRAME_SUB_DEBUG );
			GF_BGL_LoadScreenReq( main->bgl, BGFRAME_SUB_DEBUG );
			return( FALSE );
		}
		
		if( keyTrg(PAD_KEY_LEFT) ){
			main->hard--;
			if( (int)main->hard < 0 ){ main->hard = SLOT_HARD_5; }
		}else if( keyTrg(PAD_KEY_RIGHT) ){
			main->hard++;
			if( main->hard > SLOT_HARD_5 ){ main->hard = SLOT_HARD_0; }
		}
		
		DEBUG_SlotDataPrint( main );
		return( TRUE );
	case 3:	//���I�t���O�@����
		if( keyTrg(PAD_BUTTON_A) ){
			switch( work->lottery_no ){
			case DATA_YAKU_BONUS_END:
				work->debug_bonus_end = TRUE;
				break;
			case DATA_YAKU_PIP_NORMAL:
				work->debug_pip_type = PIP_NORMAL;
				break;
			case DATA_YAKU_PIP_META:
				work->debug_pip_type = PIP_META;
				break;
			case DATA_YAKU_PIP_RARE:
				work->debug_pip_type = PIP_RARE;
				break;
			case DATA_YAKU_MOONLIGHT:
				work->debug_moon_light = TRUE;
				break;
			case DATA_YAKU_MOONRED:
				work->debug_moon_red = TRUE;
				break;
			case DATA_YAKU_BONUS_GASE:
				work->debug_bonus_end_effect = BCEFF_BACK;
				break;
			case DATA_YAKU_BONUS_ANENCORE:
				work->debug_bonus_end_effect = BCEFF_ANENCORE;
				break;
			case DATA_YAKU_BONUS_NORMAL:
				work->debug_bonus_end_effect = BCEFF_NON;
				break;
			default:
				if( work->lottery_no <= DATA_YAKU_GINGA_AUTO ){
					work->debug_lottery_bit = DATA_YakuTbl[work->lottery_no].lottery_bit;
					if( work->lottery_no == (DATA_YAKU_BIG_AUTO) ||
						work->lottery_no == (DATA_YAKU_GINGA_AUTO) ){
						work->debug_auto_set = TRUE;
					}
				}else{
					work->debug_auto_set = FALSE;
				}
			}
			
			GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );
			work->seq_no = 0;
			return( TRUE );
		}else if( keyTrg(PAD_BUTTON_B) ){
			work->debug_lottery_bit = LOTTERY_HITBIT_NON;
			work->debug_auto_set = FALSE;
			GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );
			work->seq_no = 0;
			return( TRUE );
		}
		
		if( keyTrg(PAD_KEY_LEFT) ){
			work->lottery_no--;
			if( (int)work->lottery_no < 0 ){ work->lottery_no = DATA_YAKU_MAX-1; }
			GF_BGL_ScrClear( main->bgl, BGFRAME_SUB_DEBUG );
			GF_BGL_LoadScreenReq( main->bgl, BGFRAME_SUB_DEBUG );
		}else if( keyTrg(PAD_KEY_RIGHT) ){
			work->lottery_no++;
			if( (int)work->lottery_no >= DATA_YAKU_MAX ){ work->lottery_no = 0; }
			GF_BGL_ScrClear( main->bgl, BGFRAME_SUB_DEBUG );
			GF_BGL_LoadScreenReq( main->bgl, BGFRAME_SUB_DEBUG );
		}
		
		DEBUG_SlotDataLotteryPrint( main, work->lottery_no );
		return( TRUE );
	case 4:	//�R�C������
		if( keyTrg(PAD_BUTTON_B) ){
			GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );
			work->seq_no = 0;
			return( TRUE );
		}
		
		if( keyTrg(PAD_KEY_LEFT) ){
			main->credit -= 10;
			if( (int)main->credit <= 3 ){ main->credit = 3; }
			GF_BGL_ScrClear( main->bgl, BGFRAME_SUB_DEBUG );
			GF_BGL_LoadScreenReq( main->bgl, BGFRAME_SUB_DEBUG );
		}else if( keyTrg(PAD_KEY_RIGHT) ){
			main->credit += 10;
			if( main->credit > SLOT_COIN_MAX ){ main->credit = SLOT_COIN_MAX; }
			GF_BGL_ScrClear( main->bgl, BGFRAME_SUB_DEBUG );
			GF_BGL_LoadScreenReq( main->bgl, BGFRAME_SUB_DEBUG );
		}else if( keyTrg(PAD_BUTTON_L) ){
			main->credit -= 100;
			if( (int)main->credit <= 3 ){ main->credit = 3; }
			GF_BGL_ScrClear( main->bgl, BGFRAME_SUB_DEBUG );
			GF_BGL_LoadScreenReq( main->bgl, BGFRAME_SUB_DEBUG );
		}else if( keyTrg(PAD_BUTTON_R) ){
			main->credit += 100;
			if( main->credit > SLOT_COIN_MAX ){ main->credit = SLOT_COIN_MAX; }
			GF_BGL_ScrClear( main->bgl, BGFRAME_SUB_DEBUG );
			GF_BGL_LoadScreenReq( main->bgl, BGFRAME_SUB_DEBUG );
		}else if( keyTrg(PAD_KEY_UP) ){
			main->credit = SLOT_COIN_MAX;
			GF_BGL_ScrClear( main->bgl, BGFRAME_SUB_DEBUG );
			GF_BGL_LoadScreenReq( main->bgl, BGFRAME_SUB_DEBUG );
		}else if( keyTrg(PAD_KEY_DOWN) ){
			main->credit = 3;
			GF_BGL_ScrClear( main->bgl, BGFRAME_SUB_DEBUG );
			GF_BGL_LoadScreenReq( main->bgl, BGFRAME_SUB_DEBUG );
		}
		
		DEBUG_SlotDataCoinPrint( main );
		return( TRUE );
	case 5:	//�q�b�g���C���J�E���g���\��
		if( keyTrg(PAD_BUTTON_B) ){
			GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );
			work->seq_no = 0;
			return( TRUE );
		}
		
		DEBUG_SlotDataHitLineCountPrint( main );
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �f�o�b�O�I�[�g�v���C�@�L�[�`�F�b�N
 * @param	main	SLOTMAIN
 * @retval	int		TRUE=�I�[�g
 */
//--------------------------------------------------------------
static int DEBUG_AutoPlayEndCheck( SLOTMAIN *main )
{
	D_SLOTWORK *work = &main->d_work;
	
	if( work->auto_flag == TRUE && (sys.cont & PAD_BUTTON_B) == 0 ){
		return( FALSE );
	}
	
	work->auto_flag = FALSE;
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �f�o�b�O�I�[�g�v���C�@������
 * @param	main	SLOTMAIN
 * @retval	int		TRUE=�I�[�g
 */
//--------------------------------------------------------------
static void DEBUG_AutoPlayInit( SLOTMAIN *main )
{
	D_SLOTWORK *work = &main->d_work;
	work->auto_stop_count = 0;
	work->auto_stop_frame = 0;
}

//--------------------------------------------------------------
/**
 * �f�o�b�O�I�[�g�v���C�`�F�b�N
 * @param	main	SLOTMAIN
 * @retval	int		TRUE=�I�[�g
 */
//--------------------------------------------------------------
static int DEBUG_AutoPlayCheck( SLOTMAIN *main )
{
	D_SLOTWORK *work = &main->d_work;
	
	if( work->auto_flag == TRUE ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �f�o�b�O�I�[�g�v���C�@�{�^�������`�F�b�N
 * @param	main	SLOTMAIN
 * @retval	int		TRUE=������
 */
//--------------------------------------------------------------
static int DEBUG_AutoPlayPushCheck( SLOTMAIN *main )
{
	D_SLOTWORK *work = &main->d_work;
	
	if( work->auto_stop_frame == 0 ){
		work->auto_stop_frame = 8 + (gf_rand() % 30);
	}
	
	work->auto_stop_frame--;
	
	if( work->auto_stop_frame <= 0 ){
		work->auto_stop_frame = 0;
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
///	������
//--------------------------------------------------------------
static void DEBUG_SlotInit( SLOTMAIN *main )
{
	D_SLOTWORK *work = &main->d_work;
	work->debug_pip_type = PIP_MAX;
	work->debug_bonus_end_effect = BCEFF_MAX;
}

//--------------------------------------------------------------
/**
 * �q�b�g���C���J�E���g
 */
//--------------------------------------------------------------
static void DEBUG_SlotHitLineCount( SLOTMAIN *main )
{
	int i;
	D_SLOTWORK *work = &main->d_work;
	REEL_PATTERN hit = main->reel_hit_pattern;
	u32 bit = main->reel_hit_line_bit;
	
	if( main->bonus_game_flag == FALSE ){
		for( i = LINE_1; i < LINE_MAX; i++, bit >>= 1 ){
			if( i < LINE_3_0 ){
				if( (bit & 0x01) ){
					work->hitline[i]++;
				}
			}else{
				if( (bit & 0x01) && hit != REEL_CHERRY ){
					work->hitline[i]++;
				}
			}
		}
	}
}
#endif	//DEBUG_ON_SLOT

//----
#endif	//PM_DEBUG
//----
