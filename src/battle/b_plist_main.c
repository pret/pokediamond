//============================================================================================
/**
 * @file	b_plist_main.c
 * @brief	�퓬�p�|�P�������X�g���
 * @author	Hiroyuki Nakamura
 * @date	05.02.01
 */
//============================================================================================
#include "common.h"
#include "gflib/touchpanel.h"
#include "system/procsys.h"
#include "system/palanm.h"
#include "system/window.h"
#include "system/lib_pack.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/fontproc.h"
#include "system/msgdata.h"
#include "system/numfont.h"
#include "system/wordset.h"
#include "system/font_arc.h"
#include "system/clact_tool.h"
#include "system/snd_tool.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_b_plist.h"
#include "battle/battle_common.h"
#include "battle/fight_tool.h"
#include "poketool/pokeparty.h"
#include "poketool/waza_tool.h"
#include "poketool/status_rcv.h"
#include "contest/contest.h"
#include "contest/con_tool.h"
#include "itemtool/item.h"
#include "itemtool/myitem.h"
#include "application/p_status.h"
#include "application/app_tool.h"
#include "b_bag.h"
#include "b_app_tool.h"

#define	B_PLIST_H_GLOBAL
#define	B_PLIST_MAIN_H_GLOBAL
#include "b_plist.h"
#include "b_plist_main.h"
#include "b_plist_obj.h"
#include "b_plist_anm.h"
#include "b_plist_bmp.h"
#include "b_plist_bmp_def.h"
#include "b_plist_gra.naix"


//============================================================================================
//	�萔��`
//============================================================================================
// ���C���V�[�P���X
enum {
	SEQ_BPL_INIT = 0,		// ������
	SEQ_BPL_SELECT,			// �|�P�����I����ʃR���g���[��
	SEQ_BPL_IREKAE,			// ����ւ��y�[�W�R���g���[��
	SEQ_BPL_ST_MAIN,		// �X�e�[�^�X���C����ʃR���g���[��
	SEQ_BPL_ST_WAZASEL,		// �X�e�[�^�X�Z�I����ʃR���g���[��
	SEQ_BPL_ST_SKILL,		// �X�e�[�^�X�Z��ʃR���g���[��

	SEQ_BPL_PAGE1_CHG,			// �|�P�����I����
	SEQ_BPL_PAGECHG_IREKAE,		// ����ւ��y�[�W��
	SEQ_BPL_PAGECHG_STMAIN,		// �X�e�[�^�X�ڍׂ�
	SEQ_BPL_PAGECHG_WAZASEL,	// �X�e�[�^�X�Z�I����
	SEQ_BPL_PAGECHG_WAZAINFO,	// �X�e�[�^�X�Z�ڍ׉�ʂ�
	SEQ_BPL_PAGECHG_WAZASET_S,	// �Z�Y��I����ʂ�
	SEQ_BPL_PAGECHG_WAZASET_I,	// �Z�Y�ꌈ���
	SEQ_BPL_PAGECHG_PPRCV,		// �Z�񕜂�

	SEQ_BPL_POKECHG,		// �|�P�����؂�ւ�
	SEQ_BPL_CHG_ERR_SET,	// ����ւ��G���[�Z�b�g
	SEQ_BPL_IREKAE_ERR,		// ����ւ��G���[�I���҂�

	SEQ_BPL_MSG_WAIT,		// ���b�Z�[�W�\��
	SEQ_BPL_TRG_WAIT,		// ���b�Z�[�W�\����̃L�[�҂�

	SEQ_BPL_WAZADEL_SEL,	// �Z�Y��I��
	SEQ_BPL_WAZADEL_MAIN,	// �Z�Y�ꌈ��

	SEQ_BPL_WAZARCV_SEL,	// �Z�񕜑I��

	SEQ_BPL_BUTTON_WAIT,	// �{�^���A�j���I���҂�

	SEQ_BPL_STRCV,			// �X�e�[�^�X��
	SEQ_BPL_PPALLRCV,		// PP�S��

	SEQ_BPL_ENDSET,			// �I���t�F�[�h�Z�b�g
	SEQ_BPL_END,			// �I��
};

#define	TMP_MSG_BUF_SIZ		( 512 )		// �e���|�������b�Z�[�W�T�C�Y

#define	PLATE_BG_SX		( 16 )		// �v���[�gBG�T�C�YX
#define	PLATE_BG_SY		( 6 )		// �v���[�gBG�T�C�YY
#define	PLATE_BG_P_PX	( 0 )		// �|�P����������ꍇ�̃v���[�gBG�Q��X���W
#define	PLATE_BG_P_PY	( 0 )		// �|�P����������ꍇ�̃v���[�gBG�Q��Y���W
#define	PLATE_BG_N_PX	( 16 )		// �|�P���������Ȃ��ꍇ�̃v���[�gBG�Q��X���W
#define	PLATE_BG_N_PY	( 13 )		// �|�P���������Ȃ��ꍇ�̃v���[�gBG�Q��Y���W

#define	PLATE_POKE1_PX	( 0 )		// �|�P�����P�̃v���[�gBGX���W
#define	PLATE_POKE1_PY	( 0 )		// �|�P�����P�̃v���[�gBGY���W
#define	PLATE_POKE2_PX	( 16 )		// �|�P�����Q�̃v���[�gBGX���W
#define	PLATE_POKE2_PY	( 1 )		// �|�P�����Q�̃v���[�gBGY���W
#define	PLATE_POKE3_PX	( 0 )		// �|�P�����R�̃v���[�gBGX���W
#define	PLATE_POKE3_PY	( 6 )		// �|�P�����R�̃v���[�gBGY���W
#define	PLATE_POKE4_PX	( 16 )		// �|�P�����S�̃v���[�gBGX���W
#define	PLATE_POKE4_PY	( 7 )		// �|�P�����S�̃v���[�gBGY���W
#define	PLATE_POKE5_PX	( 0 )		// �|�P�����T�̃v���[�gBGX���W
#define	PLATE_POKE5_PY	( 12 )		// �|�P�����T�̃v���[�gBGY���W
#define	PLATE_POKE6_PX	( 16 )		// �|�P�����U�̃v���[�gBGX���W
#define	PLATE_POKE6_PY	( 13 )		// �|�P�����U�̃v���[�gBGY���W

#define	P2_EXPGAGE_PX	( 32+14 )	// �y�[�W�Q�̌o���l�Q�[�W��������X���W
#define	P2_EXPGAGE_PY	( 5 )		// �y�[�W�Q�̌o���l�Q�[�W��������Y���W
#define	P3_EXPGAGE_PX	( 10 )		// �y�[�W�R�̌o���l�Q�[�W��������X���W
#define	P3_EXPGAGE_PY	( 8 )		// �y�[�W�R�̌o���l�Q�[�W��������Y���W

#define	EXP_CGX			( 0x16 )	// �o���l�Q�[�W�L�����ԍ�
#define	EXP_DOT_CHR_MAX	( 8 )		// �o���l�Q�[�W�̃L������
#define	EXP_DOT_MAX		( 64 )		// �o���l�Q�[�W�̍ő�h�b�g��


//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================
static void BattlePokeList_Main( TCB_PTR tcb, void * work );

static u8 BPL_SeqInit( BPLIST_WORK * wk );
static u8 BPL_SeqPokeSelect( BPLIST_WORK * wk );
static u8 BPL_SeqPokeIrekae( BPLIST_WORK * wk );
static u8 BPL_SeqStatusMain( BPLIST_WORK * wk );
static u8 BPL_SeqChgErrSet( BPLIST_WORK * wk );
static u8 BPL_SeqIrekaeErr( BPLIST_WORK * wk );
static u8 BPL_SeqMsgWait( BPLIST_WORK * wk );
static u8 BPL_SeqTrgWait( BPLIST_WORK * wk );
static u8 BPL_SeqPokeChange( BPLIST_WORK * wk );
static u8 BPL_SeqStInfoWaza( BPLIST_WORK * wk );
static u8 BPL_SeqWazaDelSelect( BPLIST_WORK * wk );
static u8 BPL_SeqWazaDelMain( BPLIST_WORK * wk );
static u8 BPL_SeqWazaRcvSelect( BPLIST_WORK * wk );
static u8 BPL_SeqButtonWait( BPLIST_WORK * wk );
static u8 BPL_SeqPage1Chg( BPLIST_WORK * wk );
static u8 BPL_SeqPageChgIrekae( BPLIST_WORK * wk );
static u8 BPL_SeqPageChgStWazaSel( BPLIST_WORK * wk );
static u8 BPL_SeqPageChgStatus( BPLIST_WORK * wk );
static u8 BPL_SeqPageChgWazaInfo( BPLIST_WORK * wk );
static u8 BPL_SeqPageChgWazaSetSel( BPLIST_WORK * wk );
static u8 BPL_SeqPageChgWazaSetEnter( BPLIST_WORK * wk );
static u8 BPL_SeqPageChgPPRcv( BPLIST_WORK * wk );
static u8 BPL_SeqStRcv( BPLIST_WORK * wk );
static u8 BPL_SeqPPAllRcv( BPLIST_WORK * wk );
static u8 BPL_SeqEndSet( BPLIST_WORK * wk );
static u8 BPL_SeqEnd( TCB_PTR tcb, BPLIST_WORK * wk );
static u8 BPL_SeqWazaSelect( BPLIST_WORK * wk );

static u8 BPL_PokeItemUse( BPLIST_WORK * wk );

//static void BPL_VramInit(void);
static void BPL_BgInit( BPLIST_WORK * dat );
static void BPL_BgExit( GF_BGL_INI * ini );
static void BPL_BgGraphicSet( BPLIST_WORK * wk );
static void BPL_MsgManSet( BPLIST_WORK * wk );
static void BPL_MsgManExit( BPLIST_WORK * wk );
static void BPL_PokeDataMake( BPLIST_WORK * wk );

static u8 BPL_PokemonSelect( BPLIST_WORK * wk );
static u8 BPL_IrekaeSelect( BPLIST_WORK * wk );
static u8 BPL_StatusMainSelect( BPLIST_WORK * wk );
static u8 BPL_StInfoWazaSelect( BPLIST_WORK * wk );
static u8 BPL_StWazaSelect( BPLIST_WORK * wk );
static int BPL_TPCheck( BPLIST_WORK * wk, const RECT_HIT_TBL * tbl );
static void BPL_PageChange( BPLIST_WORK * wk, u8 next_page );
static void BPL_PageChgBgScreenChg( BPLIST_WORK * wk, u8 page );
static u8 BPL_IrekaeCheck( BPLIST_WORK * wk );
static u8 BPL_NextPokeGet( BPLIST_WORK * wk, s32 pos, s32 mv );
static void BPL_PokePlateSet( BPLIST_WORK * wk );
static void BPL_ExpGagePut( BPLIST_WORK * wk, u8 page );
//static void BPL_P2_ExpGagePut( BPLIST_WORK * wk, u16 cgx, u16 px, u16 py );
static void BPL_P3_ExpGagePut( BPLIST_WORK * wk, u16 cgx, u16 px, u16 py );
static void BPL_ContestWazaHeartPut( BPLIST_WORK * wk, u8 page );
static u8 BPL_HidenCheck( BPLIST_WORK * wk );
static void BPL_HidenOff_Battle( BPLIST_WORK * wk );
static void BPL_HidenOff_Contest( BPLIST_WORK * wk );
static u8 BPL_TamagoCheck( BPLIST_WORK * wk );

static void BattleBag_SubItem( BATTLE_WORK * bw, u16 item, u16 page, u32 heap );


//============================================================================================
//	�O���[�o���ϐ�
//============================================================================================
// �v���[�g�\���ʒu
static const u8 PlatePos[][2] =
{
	{ PLATE_POKE1_PX, PLATE_POKE1_PY },
	{ PLATE_POKE2_PX, PLATE_POKE2_PY },
	{ PLATE_POKE3_PX, PLATE_POKE3_PY },
	{ PLATE_POKE4_PX, PLATE_POKE4_PY },
	{ PLATE_POKE5_PX, PLATE_POKE5_PY },
	{ PLATE_POKE6_PX, PLATE_POKE6_PY }
};

// �|�P�����I����ʈړ��e�[�u��
static const POINTER_WORK NormalMoveTable[] =
{
	{  0,  0, 16, 6,	6,2,0,1 },		// 0
	{ 16,  1, 16, 6,	4,3,0,1 },		// 1
	{  0,  6, 16, 6,	0,4,2,3 },		// 2
	{ 16,  7, 16, 6,	1,5,2,3 },		// 3
	{  0, 12, 16, 6,	2,1,4,5 },		// 4
	{ 16, 13, 16, 6,	3,6,4,5 },		// 5
	{ 25, 19,  7, 5,	5,0,6,6 },		// 6�i�߂�j
};

// �y�[�W�P�̃^�b�`�p�l�����W
static const RECT_HIT_TBL Page1_HitRect[] =
{
	{  0*8,  6*8-1,  0*8, 16*8-1 },
	{  1*8,  7*8-1, 16*8, 32*8-1 },
	{  6*8, 12*8-1,  0*8, 16*8-1 },
	{  7*8, 13*8-1, 16*8, 32*8-1 },
	{ 12*8, 18*8-1,  0*8, 16*8-1 },
	{ 13*8, 19*8-1, 16*8, 32*8-1 },
	{ 19*8, 24*8-1, 27*8, 32*8-1 },
	{ RECT_HIT_END, 0, 0, 0 }
};

static const RECT_HIT_TBL ChgPage_HitRect[] =
{
	{  1*8, 18*8-1,  1*8, 31*8-1 },		// 0 : ����ւ�
	{ 19*8, 24*8-1,  0*8, 13*8-1 },		// 1 : ����������
	{ 19*8, 24*8-1, 13*8, 26*8-1 },		// 2 : �Z������
	{ 19*8, 24*8-1, 27*8, 32*8-1 },		// 3 : �߂�
	{ RECT_HIT_END, 0, 0, 0 }
};

// �X�e�[�^�X���C���y�[�W�̃^�b�`�p�l�����W
static const RECT_HIT_TBL StMainPage_HitRect[] =
{
	{ 19*8, 24*8-1,  0*8,  5*8-1 },		// 0 : �O�̃|�P������
	{ 19*8, 24*8-1,  5*8, 10*8-1 },		// 1 : ���̃|�P������
	{ 19*8, 24*8-1, 12*8, 25*8-1 },		// 2 : �Z������
	{ 19*8, 24*8-1, 27*8, 32*8-1 },		// 3 : �߂�
	{ RECT_HIT_END, 0, 0, 0 }
};

// �X�e�[�^�X�Z�I���y�[�W�̃^�b�`�p�l�����W
static const RECT_HIT_TBL StWazaSelPage_HitRect[] =
{
	{  6*8, 12*8-1,  0*8, 16*8-1 },		// 0 : �Z�P
	{  6*8, 12*8-1, 16*8, 32*8-1 },		// 1 : �Z�Q
	{ 12*8, 18*8-1,  0*8, 16*8-1 },		// 2 : �Z�R
	{ 12*8, 18*8-1, 16*8, 32*8-1 },		// 3 : �Z�S
	{ 19*8, 24*8-1,  0*8,  5*8-1 },		// 4 : �O�̃|�P������
	{ 19*8, 24*8-1,  5*8, 10*8-1 },		// 5 : ���̃|�P������
	{ 19*8, 24*8-1, 12*8, 25*8-1 },		// 6 : ����������
	{ 19*8, 24*8-1, 27*8, 32*8-1 },		// 7 : �߂�
	{ RECT_HIT_END, 0, 0, 0 }
};


// �X�e�[�^�X�Z�I���y�[�W�̃^�b�`�p�l�����W
static const RECT_HIT_TBL StWazaInfoPage_HitRect[] =
{
	{ 19*8, 21*8-1, 11*8, 16*8-1 },		// 0 : �Z�P
	{ 19*8, 21*8-1, 16*8, 21*8-1 },		// 1 : �Z�Q
	{ 21*8, 23*8-1, 11*8, 16*8-1 },		// 2 : �Z�R
	{ 21*8, 23*8-1, 16*8, 21*8-1 },		// 3 : �Z�S
	{ 19*8, 24*8-1, 27*8, 32*8-1 },		// 4 : �߂�
	{ RECT_HIT_END, 0, 0, 0 }
};

// �Z�Y��I���y�[�W�̃^�b�`�p�l�����W
static const RECT_HIT_TBL Page5_HitRect[] =
{
	{  6*8, 12*8-1,  0*8, 16*8-1 },		// 0 : �Z�P��ʂ�
	{  6*8, 12*8-1, 16*8, 32*8-1 },		// 1 : �Z�Q��ʂ�
	{ 12*8, 18*8-1,  0*8, 16*8-1 },		// 2 : �Z�R��ʂ�
	{ 12*8, 18*8-1, 16*8, 32*8-1 },		// 3 : �Z�S��ʂ�
	{ 18*8, 24*8-1,  8*8, 24*8-1 },		// 4 : �Z�T��ʂ�
	{  0*8,  5*8-1, 23*8, 32*8-1 },		// 5 : �퓬<->�R���e�X�g�̐؂�ւ�
	{ 19*8, 24*8-1, 27*8, 32*8-1 },		// 6 : �߂�
	{ RECT_HIT_END, 0, 0, 0 }
};

// �Z�Y�ꌈ��y�[�W�̃^�b�`�p�l�����W
static const RECT_HIT_TBL Page6_HitRect[] =
{
	{ 19*8, 24*8-1,  0*8, 26*8-1 },		// 0 : �퓬��
	{  0*8,  5*8-1, 23*8, 32*8-1 },		// 1 : �퓬<->�R���e�X�g�̐؂�ւ�
	{ 19*8, 24*8-1, 27*8, 32*8-1 },		// 2 : �߂�
	{ RECT_HIT_END, 0, 0, 0 }
};

// �Z�񕜃y�[�W�̃^�b�`�p�l�����W
static const RECT_HIT_TBL PPRcvPage_HitRect[] =
{
	{  6*8, 12*8-1,  0*8, 16*8-1 },		// 0 : �Z�P��
	{  6*8, 12*8-1, 16*8, 32*8-1 },		// 1 : �Z�Q��
	{ 12*8, 18*8-1,  0*8, 16*8-1 },		// 2 : �Z�R��
	{ 12*8, 18*8-1, 16*8, 32*8-1 },		// 3 : �Z�S��
	{ 19*8, 24*8-1, 27*8, 32*8-1 },		// 4 : �߂�
	{ RECT_HIT_END, 0, 0, 0 }
};


//--------------------------------------------------------------------------------------------
/**
 * �퓬�p�|�P�������X�g�^�X�N�ǉ�
 *
 * @param	dat		���X�g�f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BattlePokeList_TaskAdd( BPLIST_DATA * dat )
{
	BPLIST_WORK * wk;

	if( dat->sel_poke > 5 ){ dat->sel_poke = 0; }

	wk = TCB_GetWork( PMDS_taskAdd(BattlePokeList_Main,sizeof(BPLIST_WORK),0,dat->heap) );

	memset( wk, 0, sizeof(BPLIST_WORK) );
	wk->dat = dat;
	wk->bgl = BattleWorkGF_BGL_INIGet( dat->bw );
	wk->pfd = BattleWorkPfdGet( dat->bw );
	wk->seq = SEQ_BPL_INIT;
	wk->init_poke = dat->sel_poke;
	wk->ev_contest = BattleWorkContestSeeFlagGet( dat->bw );

	wk->multi_pos = BattleWorkClientTypeGet( dat->bw, dat->client_no );
// CLIENT_TYPE_A : �O�q
// CLIENT_TYPE_C : ��q


/*** �e�X�g ***/
//	wk->dat->chg_waza = 20;
//	wk->dat->mode = BPL_MODE_WAZASET;
//	wk->page = BPLIST_PAGE_PP_RCV;		// PP�񕜋Z�I���y�[�W
//	wk->ev_contest = 1;
/**************/
}

//--------------------------------------------------------------------------------------------
/**
 * ���C���^�X�N
 *
 * @param	tcb
 * @param	work
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BattlePokeList_Main( TCB_PTR tcb, void * work )
{
	BPLIST_WORK * wk = (BPLIST_WORK *)work;

	switch( wk->seq ){
	case SEQ_BPL_INIT:		// ������
		wk->seq = BPL_SeqInit( wk );
		break;

	case SEQ_BPL_SELECT:	// �|�P�����I����ʃR���g���[��
		wk->seq = BPL_SeqPokeSelect( wk );
		break;

	case SEQ_BPL_IREKAE:
		wk->seq = BPL_SeqPokeIrekae( wk );
		break;

	case SEQ_BPL_ST_MAIN:	// �X�e�[�^�X���C����ʃR���g���[��
		wk->seq = BPL_SeqStatusMain( wk );
		break;

	case SEQ_BPL_ST_WAZASEL:	// �X�e�[�^�X�Z�I����ʃR���g���[��
		wk->seq = BPL_SeqWazaSelect( wk );
		break;

	case SEQ_BPL_ST_SKILL:		// �Z��ʃR���g���[��
		wk->seq = BPL_SeqStInfoWaza( wk );
		break;

	case SEQ_BPL_PAGE1_CHG:
		wk->seq = BPL_SeqPage1Chg( wk );
		break;

	case SEQ_BPL_PAGECHG_IREKAE:	// ����ւ��y�[�W��
		wk->seq = BPL_SeqPageChgIrekae( wk );
		break;

	case SEQ_BPL_PAGECHG_STMAIN:	// �X�e�[�^�X�ڍׂ�
		wk->seq = BPL_SeqPageChgStatus( wk );
		break;

	case SEQ_BPL_PAGECHG_WAZASEL:	// �Z�I����
		wk->seq = BPL_SeqPageChgStWazaSel( wk );
		break;

	case SEQ_BPL_PAGECHG_WAZAINFO:
		wk->seq = BPL_SeqPageChgWazaInfo( wk );
		break;

	case SEQ_BPL_PAGECHG_WAZASET_S:	// �Z�Y��I����ʂ�
		wk->seq = BPL_SeqPageChgWazaSetSel( wk );
		break;

	case SEQ_BPL_PAGECHG_WAZASET_I:
		wk->seq = BPL_SeqPageChgWazaSetEnter( wk );
		break;

	case SEQ_BPL_PAGECHG_PPRCV:	// �Z�񕜂�
		wk->seq = BPL_SeqPageChgPPRcv( wk );
		break;

	case SEQ_BPL_POKECHG:		// �|�P�����؂�ւ�
		wk->seq = BPL_SeqPokeChange( wk );
		break;

	case SEQ_BPL_CHG_ERR_SET:	// ����ւ��G���[�Z�b�g
		wk->seq = BPL_SeqChgErrSet( wk );
		break;

	case SEQ_BPL_IREKAE_ERR:	// ����ւ��G���[�I���҂�
		wk->seq = BPL_SeqIrekaeErr( wk );
		break;

	case SEQ_BPL_MSG_WAIT:	// ���b�Z�[�W�E�F�C�g
		wk->seq = BPL_SeqMsgWait( wk );
		break;

	case SEQ_BPL_TRG_WAIT:	// ���b�Z�[�W�\����̃L�[�҂�
		wk->seq = BPL_SeqTrgWait( wk );
		break;

	case SEQ_BPL_WAZADEL_SEL:	// �Z�Y��I��
		wk->seq = BPL_SeqWazaDelSelect( wk );
		break;

	case SEQ_BPL_WAZADEL_MAIN:	// �Z�Y�ꌈ��
		wk->seq = BPL_SeqWazaDelMain( wk );
		break;

	case SEQ_BPL_WAZARCV_SEL:	// �Z�񕜑I��
		wk->seq = BPL_SeqWazaRcvSelect( wk );
		break;

	case SEQ_BPL_BUTTON_WAIT:	// �{�^���A�j���I���҂�
		wk->seq = BPL_SeqButtonWait( wk );
		break;

	case SEQ_BPL_STRCV:			// �X�e�[�^�X��
		wk->seq = BPL_SeqStRcv( wk );
		break;

	case SEQ_BPL_PPALLRCV:		// PP�S��
		wk->seq = BPL_SeqPPAllRcv( wk );
		break;

	case SEQ_BPL_ENDSET:	// �I���t�F�[�h�Z�b�g
		wk->seq = BPL_SeqEndSet( wk );
		break;

	case SEQ_BPL_END:		// �I��
		if( BPL_SeqEnd( tcb, wk ) == TRUE ){
			return;
		}
	}

	BPL_PokeIconAnime( wk );

	CATS_Draw( wk->crp );
	BattlePokeList_ButtonAnmMain( wk );
}

//--------------------------------------------------------------------------------------------
/**
 * �������V�[�P���X
 *
 * @param	wk		���[�N
 *
 * @return	�ڍs����V�[�P���X
 */
//--------------------------------------------------------------------------------------------
static u8 BPL_SeqInit( BPLIST_WORK * wk )
{
	u8	ret;

	G2S_BlendNone();

	if( wk->dat->mode == BPL_MODE_WAZASET ){
		wk->page = BPLIST_PAGE_WAZASET_BS;
		ret = SEQ_BPL_WAZADEL_SEL;
	}else{
		wk->page = BPLIST_PAGE_SELECT;
		ret = SEQ_BPL_SELECT;
	}

	wk->cmv_wk = BAPP_CursorMoveWorkAlloc( wk->dat->heap );

	BPL_PokeDataMake( wk );

//	BPL_VramInit();
	BPL_BgInit( wk );
	BPL_BgGraphicSet( wk );
	BPL_MsgManSet( wk );

	FontProc_LoadFont( FONT_BUTTON, wk->dat->heap );

	BPL_PageChgBgScreenChg( wk, wk->page );
//	BPL_PokePlateSet( wk );
	BattlePokeList_ButtonPageScreenInit( wk, wk->page );
	BattlePokeList_ButtonPalSet( wk, wk->page );

	BattlePokeList_ObjInit( wk );
	BattlePokeList_PageObjSet( wk, wk->page );

	BattlePokeList_BmpInit( wk );
	BattlePokeList_BmpWrite( wk, wk->page );

//	wk->dat->cursor_flg = 1;
	if( wk->dat->cursor_flg != 0 ){
		BAPP_CursorMvWkSetFlag( wk->cmv_wk, 1 );
	}

	// �}���`�̂Ƃ��̏����ʒu�␳
	if( wk->page == BPLIST_PAGE_SELECT &&
		BattlePokeList_MultiPosCheck( wk, 0 ) == TRUE ){
		wk->dat->sel_poke = 1;
	}

	BattlePokeList_CursorMoveSet( wk, wk->page );

	BPL_ExpGagePut( wk, wk->page );

	PaletteFadeReq( wk->pfd, PF_BIT_SUB_ALL, 0xffff, BATTLE_BAGLIST_FADE_SPEED, 16, 0, 0 );

	return ret;
}

//--------------------------------------------------------------------------------------------
/**
 * �|�P�����I���y�[�W�̃R���g���[���V�[�P���X
 *
 * @param	wk		���[�N
 *
 * @return	�ڍs����V�[�P���X
 */
//--------------------------------------------------------------------------------------------
static u8 BPL_SeqPokeSelect( BPLIST_WORK * wk )
{
	if( PaletteFadeCheck( wk->pfd ) != 0 ){ return SEQ_BPL_SELECT; }

	if( BPL_PokemonSelect( wk ) == TRUE ){
		if( wk->dat->sel_poke == BPL_SEL_EXIT ){
			if( wk->dat->mode != BPL_MODE_NO_CANCEL ){
				Snd_SePlay( SEQ_SE_DP_DECIDE );
				BattlePokeList_ButtonAnmInit( wk, BPL_BUTTON_RET );
				return SEQ_BPL_ENDSET;
			}
		}else{
			Snd_SePlay( SEQ_SE_DP_DECIDE );
			BattlePokeList_ButtonAnmInit( wk, BPL_BUTTON_POKE1+wk->dat->sel_poke );
			if( wk->dat->mode == BPL_MODE_ITEMUSE ){
				return BPL_PokeItemUse( wk );
			}else{
				wk->ret_seq = SEQ_BPL_PAGECHG_IREKAE;
			}
			return SEQ_BPL_BUTTON_WAIT;
		}
	}

	return SEQ_BPL_SELECT;
}

static u8 BPL_PokeItemUse( BPLIST_WORK * wk )
{
	BPLIST_DATA * dat = wk->dat;

	// �����������Ŏg�p�s��
	if( ( dat->sel_poke == 0 && dat->skill_item_use[0] != 0 ) ||
		( dat->sel_poke == 1 && dat->skill_item_use[1] != 0 ) ){
		BattlePokeList_ItemUseSkillErrMsgSet( wk );
		BattlePokeList_TalkMsgSet( wk );
		wk->dat->sel_poke = BPL_SEL_EXIT;
		wk->ret_seq = SEQ_BPL_ENDSET;
		return SEQ_BPL_MSG_WAIT;
	}

	// �P�̋Z��PP��
	if( ItemParamGet( dat->item, ITEM_PRM_PP_RCV, dat->heap ) != 0 &&
		ItemParamGet( dat->item, ITEM_PRM_ALL_PP_RCV, dat->heap ) == 0 &&
		wk->poke[dat->sel_poke].egg == 0 ){

		wk->ret_seq = SEQ_BPL_PAGECHG_PPRCV;
		return SEQ_BPL_BUTTON_WAIT;
	}

	if( BattleWorkStatusRecover(dat->bw,dat->client_no,dat->list_row[dat->sel_poke],0,dat->item) == TRUE ){
		// �S�ZPP��
		if( ItemParamGet( dat->item, ITEM_PRM_ALL_PP_RCV, dat->heap ) != 0 ){
			wk->ret_seq = SEQ_BPL_PAGECHG_PPRCV;
		}else{
			// �퓬�ɏo�Ă���|�P�����ŁA�m���񕜈ȊO
			if( BattlePokeList_PokeSetCheck( wk, dat->sel_poke ) == 1 &&
				ItemParamGet( dat->item, ITEM_PRM_DEATH_RCV, dat->heap ) == 0 ){
				BattleBag_SubItem( dat->bw, dat->item, dat->bag_page, dat->heap );
				wk->poke[dat->sel_poke].pp =
					BattleWorkPokemonParamGet( dat->bw, dat->client_no, dat->list_row[dat->sel_poke] );
				dat->hp_rcv = PokeParaGet( wk->poke[dat->sel_poke].pp, ID_PARA_hp, NULL );
				dat->hp_rcv -= wk->poke[dat->sel_poke].hp;
				wk->ret_seq = SEQ_BPL_ENDSET;
			}else{
				wk->ret_seq = SEQ_BPL_STRCV;
			}
		}
/*
		if( ItemParamGet( dat->item, ITEM_PRM_ALL_PP_RCV, dat->heap ) == 0 ){
			if( BattlePokeList_PokeSetCheck( wk, dat->sel_poke ) == 1 ){
				BattleBag_SubItem( dat->bw, dat->item, dat->bag_page, dat->heap );
				wk->poke[dat->sel_poke].pp =
					BattleWorkPokemonParamGet( dat->bw, dat->client_no, dat->list_row[dat->sel_poke] );
				dat->hp_rcv = PokeParaGet( wk->poke[dat->sel_poke].pp, ID_PARA_hp, NULL );
				dat->hp_rcv -= wk->poke[dat->sel_poke].hp;
				wk->ret_seq = SEQ_BPL_ENDSET;
			}else{
				wk->ret_seq = SEQ_BPL_STRCV;
			}
		}else{
			wk->ret_seq = SEQ_BPL_PAGECHG_PPRCV;
		}
*/
		wk->rcv_seq = 0;
		return SEQ_BPL_BUTTON_WAIT;
	}else{
		MSGMAN_GetString( wk->mman, mes_b_plist_m06, wk->msg_buf );
		BattlePokeList_TalkMsgSet( wk );
		wk->dat->sel_poke = BPL_SEL_EXIT;
		wk->ret_seq = SEQ_BPL_ENDSET;
		return SEQ_BPL_MSG_WAIT;
	}
	return SEQ_BPL_MSG_WAIT;
}

//--------------------------------------------------------------------------------------------
/**
 * ����ւ��y�[�W�̃R���g���[���V�[�P���X
 *
 * @param	wk		���[�N
 *
 * @return	�ڍs����V�[�P���X
 */
//--------------------------------------------------------------------------------------------
static u8 BPL_SeqPokeIrekae( BPLIST_WORK * wk )
{
	u8	ret = BPL_IrekaeSelect( wk );

	switch( ret ){
	case 0:		// ����ւ���
		Snd_SePlay( SEQ_SE_DP_DECIDE );
		BattlePokeList_ButtonAnmInit( wk, BPL_BUTTON_POKE_CHG );
		if( BPL_IrekaeCheck( wk ) == TRUE ){
			return SEQ_BPL_ENDSET;
		}
		wk->ret_seq = SEQ_BPL_CHG_ERR_SET;
		return SEQ_BPL_BUTTON_WAIT;

	case 1:		// ����������
		if( BPL_TamagoCheck( wk ) == TRUE ){ break; }
		Snd_SePlay( SEQ_SE_DP_DECIDE );
		BattlePokeList_ButtonAnmInit( wk, BPL_BUTTON_STATUS1 );
		wk->ret_seq = SEQ_BPL_PAGECHG_STMAIN;
		return SEQ_BPL_BUTTON_WAIT;

	case 2:		// �Z������
		if( BPL_TamagoCheck( wk ) == TRUE ){ break; }
		Snd_SePlay( SEQ_SE_DP_DECIDE );
		BattlePokeList_ButtonAnmInit( wk, BPL_BUTTON_WAZASEL1 );
		wk->ret_seq = SEQ_BPL_PAGECHG_WAZASEL;
		return SEQ_BPL_BUTTON_WAIT;

	case 3:		// �߂�
		Snd_SePlay( SEQ_SE_DP_DECIDE );
		BattlePokeList_ButtonAnmInit( wk, BPL_BUTTON_RET );
		wk->ret_seq = SEQ_BPL_PAGE1_CHG;
		return SEQ_BPL_BUTTON_WAIT;
	}

	return SEQ_BPL_IREKAE;
}

//--------------------------------------------------------------------------------------------
/**
 * �X�e�[�^�X���C���y�[�W�̃R���g���[���V�[�P���X
 *
 * @param	wk		���[�N
 *
 * @return	�ڍs����V�[�P���X
 */
//--------------------------------------------------------------------------------------------
static u8 BPL_SeqStatusMain( BPLIST_WORK * wk )
{
	u8	ret = BPL_StatusMainSelect( wk );

	switch( ret ){
	case 0:		// �O�̃|�P������
		{
			u8 pos = BPL_NextPokeGet( wk, wk->dat->sel_poke, -1 );
			if( pos == 0xff ){ break; }
			wk->dat->sel_poke = pos;
		}
		Snd_SePlay( SEQ_SE_DP_DECIDE );
		BattlePokeList_ButtonAnmInit( wk, BPL_BUTTON_UP );
		wk->ret_seq = SEQ_BPL_POKECHG;
		return SEQ_BPL_BUTTON_WAIT;

	case 1:		// ���̃|�P������
		{
			u8 pos = BPL_NextPokeGet( wk, wk->dat->sel_poke, 1 );
			if( pos == 0xff ){ break; }
			wk->dat->sel_poke = pos;
		}
		Snd_SePlay( SEQ_SE_DP_DECIDE );
		BattlePokeList_ButtonAnmInit( wk, BPL_BUTTON_DOWN );
		wk->ret_seq = SEQ_BPL_POKECHG;
		return SEQ_BPL_BUTTON_WAIT;

	case 2:		// �Z������
		Snd_SePlay( SEQ_SE_DP_DECIDE );
		BattlePokeList_ButtonAnmInit( wk, BPL_BUTTON_WAZASEL2 );
		wk->ret_seq = SEQ_BPL_PAGECHG_WAZASEL;
		return SEQ_BPL_BUTTON_WAIT;

	case 3:		// �߂�
		Snd_SePlay( SEQ_SE_DP_DECIDE );
		BattlePokeList_ButtonAnmInit( wk, BPL_BUTTON_RET );
		wk->chg_page_cp = 1;		// ����ւ��y�[�W�̃J�[�\���ʒu���u����������v��
		wk->ret_seq = SEQ_BPL_PAGECHG_IREKAE;
		return SEQ_BPL_BUTTON_WAIT;
	}

	return SEQ_BPL_ST_MAIN;
}

//--------------------------------------------------------------------------------------------
/**
 * �X�e�[�^�X�Z�I���y�[�W�̃R���g���[���V�[�P���X
 *
 * @param	wk		���[�N
 *
 * @return	�ڍs����V�[�P���X
 */
//--------------------------------------------------------------------------------------------
static u8 BPL_SeqWazaSelect( BPLIST_WORK * wk )
{
	u8	ret = BPL_StWazaSelect( wk );

	switch( ret ){
	case 0:		// �Z�P
	case 1:		// �Z�Q
	case 2:		// �Z�R
	case 3:		// �Z�S
		if( wk->poke[wk->dat->sel_poke].waza[ret].id == 0 ){
			break;
		}
		Snd_SePlay( SEQ_SE_DP_DECIDE );
		BattlePokeList_ButtonAnmInit( wk, BPL_BUTTON_WAZA1+ret );
		wk->dat->sel_wp = ret;
		wk->ret_seq = SEQ_BPL_PAGECHG_WAZAINFO;
		return SEQ_BPL_BUTTON_WAIT;

	case 4:		// �O�̃|�P������
		{
			u8 pos = BPL_NextPokeGet( wk, wk->dat->sel_poke, -1 );
			if( pos == 0xff ){ break; }
			wk->dat->sel_poke = pos;
		}
		Snd_SePlay( SEQ_SE_DP_DECIDE );
		BattlePokeList_ButtonAnmInit( wk, BPL_BUTTON_UP );
		wk->ret_seq = SEQ_BPL_POKECHG;
		return SEQ_BPL_BUTTON_WAIT;

	case 5:		// ���̃|�P������
		{
			u8 pos = BPL_NextPokeGet( wk, wk->dat->sel_poke, 1 );
			if( pos == 0xff ){ break; }
			wk->dat->sel_poke = pos;
		}
		Snd_SePlay( SEQ_SE_DP_DECIDE );
		BattlePokeList_ButtonAnmInit( wk, BPL_BUTTON_DOWN );
		wk->ret_seq = SEQ_BPL_POKECHG;
		return SEQ_BPL_BUTTON_WAIT;

	case 6:		// ����������
		Snd_SePlay( SEQ_SE_DP_DECIDE );
		BattlePokeList_ButtonAnmInit( wk, BPL_BUTTON_STATUS2 );
		wk->ret_seq = SEQ_BPL_PAGECHG_STMAIN;
		return SEQ_BPL_BUTTON_WAIT;

	case 7:		// �߂�
		Snd_SePlay( SEQ_SE_DP_DECIDE );
		BattlePokeList_ButtonAnmInit( wk, BPL_BUTTON_RET );
		wk->chg_page_cp = 2;		// ����ւ��y�[�W�̃J�[�\���ʒu���u�Z������v��
		wk->ret_seq = SEQ_BPL_PAGECHG_IREKAE;
		return SEQ_BPL_BUTTON_WAIT;
	}

	return SEQ_BPL_ST_WAZASEL;
}


//--------------------------------------------------------------------------------------------
/**
 * �X�e�[�^�X�Z�ڍ׃y�[�W�̃R���g���[���V�[�P���X
 *
 * @param	wk		���[�N
 *
 * @return	�ڍs����V�[�P���X
 */
//--------------------------------------------------------------------------------------------
static u8 BPL_SeqStInfoWaza( BPLIST_WORK * wk )
{
	u8	ret = BPL_StInfoWazaSelect( wk );

	switch( ret ){
	case 0:		// �Z�P
	case 1:		// �Z�Q
	case 2:		// �Z�R
	case 3:		// �Z�S
		if( wk->dat->sel_wp != ret &&
			wk->poke[wk->dat->sel_poke].waza[ret].id == 0 ){
			break;
		}
		Snd_SePlay( SEQ_SE_DP_DECIDE );
		wk->dat->sel_wp = ret;
		return SEQ_BPL_PAGECHG_WAZAINFO;

	case 4:		// �߂�
		Snd_SePlay( SEQ_SE_DP_DECIDE );
		BattlePokeList_ButtonAnmInit( wk, BPL_BUTTON_RET );
		wk->ret_seq = SEQ_BPL_PAGECHG_WAZASEL;
		return SEQ_BPL_BUTTON_WAIT;
	}

	return SEQ_BPL_ST_SKILL;
}

//--------------------------------------------------------------------------------------------
/**
 * �y�[�W�T�̃R���g���[���V�[�P���X
 *
 * @param	wk		���[�N
 *
 * @return	�ڍs����V�[�P���X
 */
//--------------------------------------------------------------------------------------------
static u8 BPL_SeqWazaDelSelect( BPLIST_WORK * wk )
{
	int	ret = BPL_TPCheck( wk, Page5_HitRect );

	if( ret == RECT_HIT_NONE ){
		ret = BAPP_CursorMove( wk->cmv_wk );
		if( ret == BAPP_CMV_CANCEL ){
			ret = 6;
		}
	}else{
//		Snd_SePlay( SEQ_SE_DP_DECIDE );
		BattlePokeList_CursorOff( wk );
	}

	switch( ret ){
	case 0:		// �Z
	case 1:
	case 2:
	case 3:
	case 4:
		wk->dat->sel_wp = (u8)ret;
		wk->wws_page_cp = (u8)ret;
		Snd_SePlay( SEQ_SE_DP_DECIDE );
		BattlePokeList_ButtonAnmInit( wk, BPL_BUTTON_WAZADEL1+ret );
		wk->ret_seq = SEQ_BPL_PAGECHG_WAZASET_I;
		return SEQ_BPL_BUTTON_WAIT;

	case 5:		// �퓬<->�R���e�X�g�؂�ւ�
		if( wk->ev_contest == 0 ){ break; }
		wk->bc_put ^= 1;
		wk->wws_page_cp = (u8)ret;
		Snd_SePlay( SEQ_SE_DP_DECIDE );
		BattlePokeList_ButtonAnmInit( wk, BPL_BUTTON_CONTEST );
		wk->ret_seq = SEQ_BPL_PAGECHG_WAZASET_S;
		return SEQ_BPL_BUTTON_WAIT;

	case 6:		// �L�����Z��
		wk->dat->sel_wp = BPL_SEL_WP_CANCEL;
		Snd_SePlay( SEQ_SE_DP_DECIDE );
		BattlePokeList_ButtonAnmInit( wk, BPL_BUTTON_RET );
		wk->ret_seq = SEQ_BPL_ENDSET;
		return SEQ_BPL_BUTTON_WAIT;
	}
	return SEQ_BPL_WAZADEL_SEL;
}

//--------------------------------------------------------------------------------------------
/**
 * �y�[�W�U�̃R���g���[���V�[�P���X
 *
 * @param	wk		���[�N
 *
 * @return	�ڍs����V�[�P���X
 */
//--------------------------------------------------------------------------------------------
static u8 BPL_SeqWazaDelMain( BPLIST_WORK * wk )
{
	int	ret = BPL_TPCheck( wk, Page6_HitRect );

	if( ret == RECT_HIT_NONE ){
		ret = BAPP_CursorMove( wk->cmv_wk );
		if( ret == BAPP_CMV_CANCEL ){
			ret = 2;
		}
	}else{
//		Snd_SePlay( SEQ_SE_DP_DECIDE );
		BattlePokeList_CursorOff( wk );
	}

	switch( ret ){
	case 0:		// �킷���
		Snd_SePlay( SEQ_SE_DP_DECIDE );
		if( wk->bc_put == 0 ){
			BattlePokeList_ButtonAnmInit( wk, BPL_BUTTON_WAZADEL_B );
		}else{
			BattlePokeList_ButtonAnmInit( wk, BPL_BUTTON_WAZADEL_C );
		}
		if( BPL_HidenCheck( wk ) == TRUE ){
			BPL_HidenMsgPut( wk );
			if( wk->bc_put == 0 ){
				BPL_HidenOff_Battle( wk );
			}else{
				BPL_HidenOff_Contest( wk );
			}
			wk->ret_seq = SEQ_BPL_WAZADEL_MAIN;
		}else{
			wk->ret_seq = SEQ_BPL_ENDSET;
		}
		return SEQ_BPL_BUTTON_WAIT;

	case 1:		// �퓬<->�R���e�X�g�؂�ւ�
		if( wk->ev_contest == 0 ){ break; }
		Snd_SePlay( SEQ_SE_DP_DECIDE );
		BattlePokeList_ButtonAnmInit( wk, BPL_BUTTON_CONTEST );
		wk->bc_put ^= 1;
		wk->wwm_page_cp = (u8)ret;
		wk->ret_seq = SEQ_BPL_PAGECHG_WAZASET_I;
		return SEQ_BPL_BUTTON_WAIT;

	case 2:		// �L�����Z��
		Snd_SePlay( SEQ_SE_DP_DECIDE );
		BattlePokeList_ButtonAnmInit( wk, BPL_BUTTON_RET );
		wk->wwm_page_cp = 0;
		wk->ret_seq = SEQ_BPL_PAGECHG_WAZASET_S;
		return SEQ_BPL_BUTTON_WAIT;

	}
	return SEQ_BPL_WAZADEL_MAIN;
}

//--------------------------------------------------------------------------------------------
/**
 * �Z�񕜑I���y�[�W�̃R���g���[���V�[�P���X
 *
 * @param	wk		���[�N
 *
 * @return	�ڍs����V�[�P���X
 */
//--------------------------------------------------------------------------------------------
static u8 BPL_SeqWazaRcvSelect( BPLIST_WORK * wk )
{
	BPLIST_DATA * dat;
	int	ret;

	dat = wk->dat;
	ret = BPL_TPCheck( wk, PPRcvPage_HitRect );
	if( ret == RECT_HIT_NONE ){
		ret = BAPP_CursorMove( wk->cmv_wk );
		if( ret == BAPP_CMV_CANCEL ){
			ret = 4;
		}
	}else{
//		Snd_SePlay( SEQ_SE_DP_DECIDE );
		BattlePokeList_CursorOff( wk );
	}

	switch( ret ){
	case 0:		// �Z
	case 1:
	case 2:
	case 3:
		if( wk->poke[dat->sel_poke].waza[ret].id == 0 ){ break; }
		wk->dat->sel_wp = (u8)ret;
		Snd_SePlay( SEQ_SE_DP_DECIDE );
		BattlePokeList_ButtonAnmInit( wk, BPL_BUTTON_WAZARCV1+ret );
		if( BattleWorkStatusRecover(dat->bw,dat->client_no,dat->list_row[dat->sel_poke],ret,dat->item) == TRUE ){
			wk->rcv_seq = 0;
			wk->ret_seq = SEQ_BPL_STRCV;
			return SEQ_BPL_BUTTON_WAIT;
		}else{
			MSGMAN_GetString( wk->mman, mes_b_plist_m06, wk->msg_buf );
			BattlePokeList_TalkMsgSet( wk );
			wk->dat->sel_poke = BPL_SEL_EXIT;
			wk->ret_seq = SEQ_BPL_ENDSET;
			return SEQ_BPL_MSG_WAIT;
		}
		break;

	case 4:		// �L�����Z��
		Snd_SePlay( SEQ_SE_DP_DECIDE );
		BattlePokeList_ButtonAnmInit( wk, BPL_BUTTON_RET );
		wk->ret_seq = SEQ_BPL_PAGE1_CHG;
		return SEQ_BPL_BUTTON_WAIT;
	}
	return SEQ_BPL_WAZARCV_SEL;
}


static u8 BPL_SeqPage1Chg( BPLIST_WORK * wk )
{
	BPL_PageChange( wk, BPLIST_PAGE_SELECT );
	return SEQ_BPL_SELECT;
}

static u8 BPL_SeqPageChgIrekae( BPLIST_WORK * wk )
{
	BPL_PageChange( wk, BPLIST_PAGE_POKE_CHG );
	return SEQ_BPL_IREKAE;
}

static u8 BPL_SeqPageChgStatus( BPLIST_WORK * wk )
{
	BPL_PageChange( wk, BPLIST_PAGE_MAIN );
	return SEQ_BPL_ST_MAIN;
}

static u8 BPL_SeqPageChgStWazaSel( BPLIST_WORK * wk )
{
	BPL_PageChange( wk, BPLIST_PAGE_WAZA_SEL );
	return SEQ_BPL_ST_WAZASEL;
}

static u8 BPL_SeqPageChgWazaInfo( BPLIST_WORK * wk )
{
	BPL_PageChange( wk, BPLIST_PAGE_SKILL );
	return SEQ_BPL_ST_SKILL;
}

static u8 BPL_SeqPageChgWazaSetSel( BPLIST_WORK * wk )
{
	if( wk->bc_put == 0 ){
		BPL_PageChange( wk, BPLIST_PAGE_WAZASET_BS );
	}else{
		BPL_PageChange( wk, BPLIST_PAGE_WAZASET_CS );
	}
	return SEQ_BPL_WAZADEL_SEL;
}

static u8 BPL_SeqPageChgWazaSetEnter( BPLIST_WORK * wk )
{
	BattlePokelist_WazaTypeSet( wk );
	if( wk->bc_put == 0 ){
		BPL_PageChange( wk, BPLIST_PAGE_WAZASET_BI );
	}else{
		BPL_PageChange( wk, BPLIST_PAGE_WAZASET_CI );
	}
	return SEQ_BPL_WAZADEL_MAIN;
}

static u8 BPL_SeqPageChgPPRcv( BPLIST_WORK * wk )
{
	BPL_PageChange( wk, BPLIST_PAGE_PP_RCV );

	if( ItemParamGet( wk->dat->item, ITEM_PRM_ALL_PP_RCV, wk->dat->heap ) != 0 ){
		return SEQ_BPL_PPALLRCV;
	}
	return SEQ_BPL_WAZARCV_SEL;
}

//--------------------------------------------------------------------------------------------
/**
 * �|�P�������肩���V�[�P���X
 *
 * @param	wk		���[�N
 *
 * @return	�ڍs����V�[�P���X
 */
//--------------------------------------------------------------------------------------------
static u8 BPL_SeqPokeChange( BPLIST_WORK * wk )
{
	BattlePokeList_PageObjSet( wk, wk->page );
	BattlePokeList_BmpWrite( wk, wk->page );
	BattlePokeList_ButtonPageScreenInit( wk, wk->page );
	BPL_ExpGagePut( wk, wk->page );
	if( wk->page == BPLIST_PAGE_MAIN ){
		return SEQ_BPL_ST_MAIN;
	}
	return SEQ_BPL_ST_WAZASEL;
}

//--------------------------------------------------------------------------------------------
/**
 * ����ւ��G���[�Z�b�g
 *
 * @param	wk		���[�N
 *
 * @return	�ڍs����V�[�P���X
 */
//--------------------------------------------------------------------------------------------
static u8 BPL_SeqChgErrSet( BPLIST_WORK * wk )
{
	BattlePokeList_TalkMsgSet( wk );
	wk->ret_seq = SEQ_BPL_IREKAE_ERR;
	return SEQ_BPL_MSG_WAIT;
}

//--------------------------------------------------------------------------------------------
/**
 * ����ւ��G���[���b�Z�[�W�I���҂��V�[�P���X
 *
 * @param	wk		���[�N
 *
 * @return	�ڍs����V�[�P���X
 */
//--------------------------------------------------------------------------------------------
static u8 BPL_SeqIrekaeErr( BPLIST_WORK * wk )
{
	BmpTalkWinClear( &wk->win[WIN_TALK], WINDOW_TRANS_ON );
	return SEQ_BPL_IREKAE;
}

//--------------------------------------------------------------------------------------------
/**
 * ���b�Z�[�W�\���V�[�P���X
 *
 * @param	wk		���[�N
 *
 * @return	�ڍs����V�[�P���X
 */
//--------------------------------------------------------------------------------------------
static u8 BPL_SeqMsgWait( BPLIST_WORK * wk )
{
	if( GF_MSG_PrintEndCheck( wk->midx ) == 0 ){
		return SEQ_BPL_TRG_WAIT;
	}
	return SEQ_BPL_MSG_WAIT;
}

//--------------------------------------------------------------------------------------------
/**
 * ���b�Z�[�W�\����̃L�[�҂��V�[�P���X
 *
 * @param	wk		���[�N
 *
 * @return	�ڍs����V�[�P���X
 */
//--------------------------------------------------------------------------------------------
static u8 BPL_SeqTrgWait( BPLIST_WORK * wk )
{
	if( ( sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL) ) || GF_TP_GetTrg() == TRUE ){
		return wk->ret_seq;
	}
	return SEQ_BPL_TRG_WAIT;
}

//--------------------------------------------------------------------------------------------
/**
 * �{�^���A�j���I���҂��V�[�P���X
 *
 * @param	wk		���[�N
 *
 * @return	�ڍs����V�[�P���X
 */
//--------------------------------------------------------------------------------------------
static u8 BPL_SeqButtonWait( BPLIST_WORK * wk )
{
	if( wk->btn_flg == 0 ){
		return wk->ret_seq;
	}
	return SEQ_BPL_BUTTON_WAIT;
}


static u8 BPL_SeqStRcv( BPLIST_WORK * wk )
{
	BPLIST_DATA * dat = wk->dat;

	switch( wk->rcv_seq ){
	case 0:
		wk->poke[dat->sel_poke].pp =
			BattleWorkPokemonParamGet( dat->bw, dat->client_no, dat->list_row[dat->sel_poke] );
		BattlePokeList_ItemUseMsgSet( wk );
		if( wk->page == BPLIST_PAGE_PP_RCV ){
			wk->rcv_pp[0] = (u16)PokeParaGet(wk->poke[dat->sel_poke].pp,ID_PARA_pp1+dat->sel_wp,NULL);
			wk->rcv_seq = 2;
		}else{
			wk->poke[dat->sel_poke].st = BadStatusIconAnmGet( wk->poke[dat->sel_poke].pp );
			if( wk->poke[dat->sel_poke].st == ST_ICON_NONE ){
				CATS_ObjectEnableCap( wk->cap[BPL_CA_STATUS1+dat->sel_poke], 0 );
				BattlePokeList_P1_LvPut( wk, dat->sel_poke );
			}
			wk->rcv_hp = PokeParaGet( wk->poke[dat->sel_poke].pp, ID_PARA_hp, NULL );
			wk->rcv_seq = 4;
		}
		Snd_SePlay( SEQ_SE_DP_KAIFUKU );
		break;

	case 1:		// HP��
		if( wk->poke[dat->sel_poke].hp != wk->rcv_hp ){
			wk->poke[dat->sel_poke].hp++;
			BattlePokeList_P1_HPPut( wk, dat->sel_poke );
			break;
		}
		wk->rcv_seq = 3;
		break;

	case 2:		// PP��
		if( wk->poke[dat->sel_poke].waza[dat->sel_wp].pp != wk->rcv_pp[0] ){
			wk->poke[dat->sel_poke].waza[dat->sel_wp].pp++;
			BattlePokeList_PPRcv( wk, WIN_P7_SKILL1+dat->sel_wp, dat->sel_wp );
			break;
		}
		wk->rcv_seq = 3;
		break;

	case 3:
//		MyItem_SubItem( dat->myitem, dat->item, 1, dat->heap );
		BattleBag_SubItem( dat->bw, dat->item, dat->bag_page, dat->heap );
		BattlePokeList_TalkMsgSet( wk );
		wk->ret_seq = SEQ_BPL_ENDSET;
		return SEQ_BPL_MSG_WAIT;

	case 4:		// �m���񕜂̂��߂ɂP�x�����Ă�
		if( wk->poke[dat->sel_poke].hp != wk->rcv_hp ){
			wk->poke[dat->sel_poke].hp++;
			BattlePokeList_P1_HPPut( wk, dat->sel_poke );
			BPL_HPRcvButtonPut( wk );
		}
		wk->rcv_seq = 1;
		break;

	}
	return SEQ_BPL_STRCV;
}


static u8 BPL_SeqPPAllRcv( BPLIST_WORK * wk )
{
	BPLIST_DATA * dat = wk->dat;
	u32	i, j;

	switch( wk->rcv_seq ){
	case 0:
		wk->poke[dat->sel_poke].pp =
			BattleWorkPokemonParamGet( dat->bw, dat->client_no, dat->list_row[dat->sel_poke] );
		for( i=0; i<4; i++ ){
			if( wk->poke[dat->sel_poke].waza[i].id == 0 ){ continue; }
			wk->rcv_pp[i] = (u16)PokeParaGet(wk->poke[dat->sel_poke].pp,ID_PARA_pp1+i,NULL);
		}
		BattlePokeList_ItemUseMsgSet( wk );
		Snd_SePlay( SEQ_SE_DP_KAIFUKU );
		wk->rcv_seq = 1;
		break;

	case 1:		// PP��
		j = 0;
		for( i=0; i<4; i++ ){
			if( wk->poke[dat->sel_poke].waza[i].id == 0 ){
				j++;
				continue;
			}
			if( wk->poke[dat->sel_poke].waza[i].pp != wk->rcv_pp[i] ){
				wk->poke[dat->sel_poke].waza[i].pp++;
				BattlePokeList_PPRcv( wk, WIN_P7_SKILL1+i, i );
			}else{
				j++;
			}
		}
		if( j == 4 ){ wk->rcv_seq = 2; }
		break;

	case 2:
		BattleBag_SubItem( dat->bw, dat->item, dat->bag_page, dat->heap );
		BattlePokeList_TalkMsgSet( wk );
		wk->ret_seq = SEQ_BPL_ENDSET;
		return SEQ_BPL_MSG_WAIT;
	}

	return SEQ_BPL_PPALLRCV;
}


//--------------------------------------------------------------------------------------------
/**
 * �I���t�F�[�h�Z�b�g�V�[�P���X
 *
 * @param	wk		���[�N
 *
 * @return	�ڍs����V�[�P���X
 */
//--------------------------------------------------------------------------------------------
static u8 BPL_SeqEndSet( BPLIST_WORK * wk )
{
	PaletteFadeReq( wk->pfd, PF_BIT_SUB_ALL, 0xffff, BATTLE_BAGLIST_FADE_SPEED, 0, 16, 0 );
	return SEQ_BPL_END;
}

//--------------------------------------------------------------------------------------------
/**
 * �I���V�[�P���X
 *
 * @param	wk		���[�N
 *
 * @retval	"TRUE = �I��"
 * @retval	"FALSE = �t�F�[�h��"
 */
//--------------------------------------------------------------------------------------------
static u8 BPL_SeqEnd( TCB_PTR tcb, BPLIST_WORK * wk )
{
	if( PaletteFadeCheck( wk->pfd ) != 0 ){ return FALSE; }

	BPL_MsgManExit( wk );
	BattlePokeList_ObjFree( wk );
	BattlePokeList_BmpFreeAll( wk );
	BPL_BgExit( wk->bgl );

	wk->dat->cursor_flg = BAPP_CursorMvWkGetFlag( wk->cmv_wk );

	BAPP_CursorMoveWorkFree( wk->cmv_wk );

	FontProc_UnloadFont( FONT_BUTTON );

	wk->dat->end_flg = 1;
	PMDS_taskDel( tcb );

	return TRUE;
}


//--------------------------------------------------------------------------------------------
/**
 * VRAM������
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
/*
static void BPL_VramInit(void)
{
	GF_BGL_DISPVRAM	tbl = {
		GX_VRAM_BG_128_A,				// ���C��2D�G���W����BG
		GX_VRAM_BGEXTPLTT_NONE,			// ���C��2D�G���W����BG�g���p���b�g
		GX_VRAM_SUB_BG_128_C,			// �T�u2D�G���W����BG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		// �T�u2D�G���W����BG�g���p���b�g
		GX_VRAM_OBJ_64_E,				// ���C��2D�G���W����OBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// ���C��2D�G���W����OBJ�g���p���b�g
		GX_VRAM_SUB_OBJ_16_I,			// �T�u2D�G���W����OBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// �T�u2D�G���W����OBJ�g���p���b�g
		GX_VRAM_TEX_0_B,				// �e�N�X�`���C���[�W�X���b�g
		GX_VRAM_TEXPLTT_01_FG			// �e�N�X�`���p���b�g�X���b�g
	};
	GF_Disp_SetBank( &tbl );
}
*/

//--------------------------------------------------------------------------------------------
/**
 * BG������
 *
 * @param	dat		���X�g�f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_BgInit( BPLIST_WORK * wk )
{
	{	// BG SYSTEM
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_3D,
		};
		GF_BGL_InitBGDisp( &BGsys_data, GF_BGL_SUB_DISP );
	}

	{	// BG (CHAR)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x08000, GX_BG_EXTPLTT_23,
			3, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( wk->bgl, GF_BGL_FRAME3_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
	}

	{	// BG2 (CHAR)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x0800, GX_BG_CHARBASE_0x08000, GX_BG_EXTPLTT_23,
			2, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( wk->bgl, GF_BGL_FRAME2_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
	}

	{	// PARAM FONT (BMP)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x1000, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( wk->bgl, GF_BGL_FRAME1_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( wk->bgl, GF_BGL_FRAME1_S );
	}

	{	// WINDOW (BMP)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x1800, GX_BG_CHARBASE_0x18000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( wk->bgl, GF_BGL_FRAME0_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( wk->bgl, GF_BGL_FRAME0_S );
	}
	GF_BGL_ClearCharSet( GF_BGL_FRAME1_S, 32, 0, wk->dat->heap );
	GF_BGL_ClearCharSet( GF_BGL_FRAME0_S, 32, 0, wk->dat->heap );
	GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME1_S );
	GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME0_S );
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
static void BPL_BgExit( GF_BGL_INI * ini )
{
	GF_Disp_GXS_VisibleControl(
		GX_PLANEMASK_BG0 | GX_PLANEMASK_BG1 |
		GX_PLANEMASK_BG2 | GX_PLANEMASK_BG3 |
		GX_PLANEMASK_OBJ, VISIBLE_OFF );

	GF_BGL_BGControlExit( ini, GF_BGL_FRAME0_S );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME1_S );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME2_S );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME3_S );
}

//--------------------------------------------------------------------------------------------
/**
 * �O���t�B�b�N�f�[�^�Z�b�g
 *
 * @param	wk		�|�P�������X�g��ʂ̃��[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
/*
#define	PCOL_N_BLUE		( GF_PRINTCOLOR_MAKE( 7, 8, 0 ) )		// �t�H���g�J���[�F��
#define	PCOL_N_RED		( GF_PRINTCOLOR_MAKE( 3, 4, 0 ) )		// �t�H���g�J���[�F��

#define	PCOL_B_BLUE		( GF_PRINTCOLOR_MAKE( 10, 11, 0 ) )		// �t�H���g�J���[�F�{�^���p��
#define	PCOL_B_RED		( GF_PRINTCOLOR_MAKE( 12, 13, 0 ) )		// �t�H���g�J���[�F�{�^���p��
*/
#define	SFNT_COL_BLUE	( 7 )
#define	SFNT_COL_RED	( 3 )
#define	BFNT_COL_BLUE	( 10 )
#define	BFNT_COL_RED	( 12 )

static void BPL_BgGraphicSet( BPLIST_WORK * wk )
{
	ArcUtil_BgCharSet(
		ARC_BPLIST_GRA, NARC_b_plist_gra_b_plist_NCGR,
		wk->bgl, GF_BGL_FRAME3_S, 0, 0, 0, wk->dat->heap );

	{
		NNSG2dScreenData * dat;
		void * buf;
		
		buf = ArchiveDataLoadMalloc(
					ARC_BPLIST_GRA, NARC_b_plist_gra_b_plist_anm_NSCR, wk->dat->heap );
		NNS_G2dGetUnpackedScreenData( buf, &dat );
		BattlePokeList_ButtonScreenMake( wk, (u16 *)dat->rawData );
		sys_FreeMemoryEz( buf );

		buf = ArchiveDataLoadMalloc(
					ARC_BPLIST_GRA, NARC_b_plist_gra_b_plist_anm2_NSCR, wk->dat->heap );
		NNS_G2dGetUnpackedScreenData( buf, &dat );
		BattlePokeList_ButtonScreenMake2( wk, (u16 *)dat->rawData );
		sys_FreeMemoryEz( buf );
	}

	PaletteWorkSet_Arc(
		wk->pfd, ARC_BPLIST_GRA, NARC_b_plist_gra_b_plist_NCLR,
		wk->dat->heap, FADE_SUB_BG, 0x20*16, 0 );

	{
		u16 * pltt = PaletteWorkDefaultWorkGet( wk->pfd, FADE_SUB_BG );

		memcpy( wk->wb_pal, &pltt[BPL_PAL_B_GREEN*16], 0x20*2 );
	}

	// �V�X�e���t�H���g�p���b�g�Z�b�g
	PaletteWorkSet_Arc(
		wk->pfd, ARC_FONT, NARC_font_system_ncrl,
		wk->dat->heap, FADE_SUB_BG, 0x20, BPL_PAL_SYS_FONT*16 );

	// ��b�t�H���g�p���b�g�Z�b�g
	PaletteWorkSet_Arc(
		wk->pfd, ARC_FONT, NARC_font_talk_ncrl,
		wk->dat->heap, FADE_SUB_BG, 0x20, BPL_PAL_TALK_FONT*16 );

	// ��b�E�B���h�E�Z�b�g
	{
		WINTYPE	wt = BattleWorkConfigWinTypeGet( wk->dat->bw );
		ArcUtil_BgCharSet(
			ARC_WINFRAME, TalkWinCgxArcGet(wt), wk->bgl,
			GF_BGL_FRAME0_S, TALK_WIN_CGX_POS, 0, 0, wk->dat->heap );
		PaletteWorkSet_Arc(
			wk->pfd, ARC_WINFRAME, TalkWinPalArcGet(wt),
			wk->dat->heap, FADE_SUB_BG, 0x20, BPL_PAL_TALK_WIN*16 );
	}

	{	// �{�^���t�H���g�p�p���b�g�̐ƐԂ��V�X�e���t�H���g�p�̃p���b�g�ɃR�s�[
		u16 * pal = PaletteWorkDefaultWorkGet( wk->pfd, FADE_SUB_BG );
		u16	* buf = sys_AllocMemory( wk->dat->heap, 0x20 );

		memcpy( buf, &pal[BPL_PAL_SYS_FONT*16], 0x20 );
		memcpy( &buf[SFNT_COL_BLUE], &pal[BPL_PAL_HPGAGE*16+BFNT_COL_BLUE], 4 );
		memcpy( &buf[SFNT_COL_RED], &pal[BPL_PAL_HPGAGE*16+BFNT_COL_RED], 4 );
		PaletteWorkSet( wk->pfd, buf, FADE_SUB_BG, BPL_PAL_SYS_FONT*16, 0x20 );
		sys_FreeMemoryEz( buf );
	}
}


//--------------------------------------------------------------------------------------------
/**
 * ���b�Z�[�W�֘A�Z�b�g
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_MsgManSet( BPLIST_WORK * wk )
{
	wk->mman = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_b_plist_dat, wk->dat->heap );
	wk->nfnt = NUMFONT_Create( 15, 14, FBMP_COL_NULL, wk->dat->heap );
	wk->wset = WORDSET_Create( wk->dat->heap );

	wk->msg_buf = STRBUF_Create( TMP_MSG_BUF_SIZ, wk->dat->heap );
}

//--------------------------------------------------------------------------------------------
/**
 * ���b�Z�[�W�֘A�폜
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_MsgManExit( BPLIST_WORK * wk )
{
	MSGMAN_Delete( wk->mman );
	NUMFONT_Delete( wk->nfnt );
	WORDSET_Delete( wk->wset );

	STRBUF_Delete( wk->msg_buf );
}

//--------------------------------------------------------------------------------------------
/**
 * �|�P�����f�[�^�쐬
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_PokeDataMake( BPLIST_WORK * wk )
{
	u16	i, j;

	for( i=0; i<PokeParty_GetPokeCount(wk->dat->pp); i++ ){
		wk->poke[i].pp = PokeParty_GetMemberPointer( wk->dat->pp, i );
		wk->poke[i].mons = PokeParaGet( wk->poke[i].pp, ID_PARA_monsno, NULL );
		
		if( wk->poke[i].mons == 0 ){ continue; }
		
		wk->poke[i].pow = PokeParaGet( wk->poke[i].pp, ID_PARA_pow, NULL );
		wk->poke[i].def = PokeParaGet( wk->poke[i].pp, ID_PARA_def, NULL );
		wk->poke[i].agi = PokeParaGet( wk->poke[i].pp, ID_PARA_agi, NULL );
		wk->poke[i].spp = PokeParaGet( wk->poke[i].pp, ID_PARA_spepow, NULL );
		wk->poke[i].spd = PokeParaGet( wk->poke[i].pp, ID_PARA_spedef, NULL );
		wk->poke[i].hp  = PokeParaGet( wk->poke[i].pp, ID_PARA_hp, NULL );
		wk->poke[i].mhp = PokeParaGet( wk->poke[i].pp, ID_PARA_hpmax, NULL );

		wk->poke[i].type1 = (u8)PokeParaGet( wk->poke[i].pp, ID_PARA_type1, NULL );
		wk->poke[i].type2 = (u8)PokeParaGet( wk->poke[i].pp, ID_PARA_type2, NULL );

		wk->poke[i].lv  = (u8)PokeParaGet( wk->poke[i].pp, ID_PARA_level, NULL );
		if( PokeParaGet( wk->poke[i].pp, ID_PARA_nidoran_nickname, NULL ) == TRUE ){
			wk->poke[i].sex_put = 0;
		}else{
			wk->poke[i].sex_put = 1;
		}
		wk->poke[i].sex = PokeSexGet( wk->poke[i].pp );
		wk->poke[i].st  = BadStatusIconAnmGet( wk->poke[i].pp );
		wk->poke[i].egg = (u8)PokeParaGet( wk->poke[i].pp, ID_PARA_tamago_flag, NULL );

		wk->poke[i].spa  = (u16)PokeParaGet( wk->poke[i].pp, ID_PARA_speabino, NULL );
		wk->poke[i].item = (u16)PokeParaGet( wk->poke[i].pp, ID_PARA_item, NULL );

		wk->poke[i].now_exp     = PokeParaGet( wk->poke[i].pp, ID_PARA_exp, NULL );
		wk->poke[i].now_lv_exp  = PokeLevelExpGet( wk->poke[i].mons, wk->poke[i].lv );
		if( wk->poke[i].lv == 100 ){
			wk->poke[i].next_lv_exp = wk->poke[i].now_lv_exp;
		}else{
			wk->poke[i].next_lv_exp = PokeLevelExpGet( wk->poke[i].mons, wk->poke[i].lv+1 );
		}

		wk->poke[i].style     = (u8)PokeParaGet( wk->poke[i].pp, ID_PARA_style, NULL );
		wk->poke[i].beautiful = (u8)PokeParaGet( wk->poke[i].pp, ID_PARA_beautiful, NULL );
		wk->poke[i].cute      = (u8)PokeParaGet( wk->poke[i].pp, ID_PARA_cute, NULL );
		wk->poke[i].clever    = (u8)PokeParaGet( wk->poke[i].pp, ID_PARA_clever, NULL );
		wk->poke[i].strong    = (u8)PokeParaGet( wk->poke[i].pp, ID_PARA_strong, NULL );

		wk->poke[i].cb = (u16)PokeParaGet( wk->poke[i].pp, ID_PARA_cb_id, NULL );
		wk->poke[i].form = (u8)PokeParaGet( wk->poke[i].pp, ID_PARA_form_no, NULL );

		for( j=0; j<4; j++ ){
			BPL_POKEWAZA * waza = &wk->poke[i].waza[j];

			waza->id   = PokeParaGet( wk->poke[i].pp, ID_PARA_waza1+j, NULL );
			if( waza->id == 0 ){ continue; }
			waza->pp   = PokeParaGet( wk->poke[i].pp, ID_PARA_pp1+j, NULL );
			waza->mpp  = PokeParaGet( wk->poke[i].pp, ID_PARA_pp_count1+j, NULL );
			waza->mpp  = WT_PPMaxGet( waza->id, waza->mpp );
			waza->type = WT_WazaDataParaGet( waza->id, ID_WTD_wazatype );
			waza->kind = WT_WazaDataParaGet( waza->id, ID_WTD_kind );
			waza->hit  = WT_WazaDataParaGet( waza->id, ID_WTD_hitprobability );
			waza->pow  = WT_WazaDataParaGet( waza->id, ID_WTD_damage );
		}
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �|�P�����I��
 *
 * @param	wk		���[�N
 *
 * @retval	"TRUE = �I�����ꂽ"
 * @retval	"FALSE = ���I��"
 */
//--------------------------------------------------------------------------------------------
static u8 BPL_PokemonSelect( BPLIST_WORK * wk )
{
	int	ret = BPL_TPCheck( wk, Page1_HitRect );

	if( ret == RECT_HIT_NONE ){
		ret = BAPP_CursorMove( wk->cmv_wk );
		if( ret == BAPP_CMV_CANCEL ){
			ret = BPL_SEL_EXIT;
		}else if( ret == BAPP_CMV_NONE ){
			return FALSE;
		}
		if( ret == BPL_SEL_EXIT || BattlePokeList_PokeSetCheck( wk, ret ) != 0 ){
			wk->dat->sel_poke = (u8)ret;
			return TRUE;
		}
	}else{
		if( ret == BPL_SEL_EXIT || BattlePokeList_PokeSetCheck( wk, ret ) != 0 ){
			wk->dat->sel_poke = (u8)ret;
//			Snd_SePlay( SEQ_SE_DP_DECIDE );
			BattlePokeList_CursorOff( wk );
			return TRUE;
		}
	}

	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * ����ւ��y�[�W�I��
 *
 * @param	wk		���[�N
 *
 * @retval	"0xff != �I�����ꂽ"
 * @retval	"0xff = ���I��"
 */
//--------------------------------------------------------------------------------------------
static u8 BPL_IrekaeSelect( BPLIST_WORK * wk )
{
	int	ret = BPL_TPCheck( wk, ChgPage_HitRect );

	if( ret == RECT_HIT_NONE ){
		ret = BAPP_CursorMove( wk->cmv_wk );
		if( ret == BAPP_CMV_CANCEL ){
			ret = 3;
		}else if( ret == BAPP_CMV_NONE ){
			return 0xff;
		}
	}else{
//		Snd_SePlay( SEQ_SE_DP_DECIDE );
		BattlePokeList_CursorOff( wk );
	}
	return (u8)ret;
}

//--------------------------------------------------------------------------------------------
/**
 * �X�e�[�^�X�I��
 *
 * @param	wk		���[�N
 *
 * @retval	"0xff != �I�����ꂽ"
 * @retval	"0xff = ���I��"
 */
//--------------------------------------------------------------------------------------------
static u8 BPL_StatusMainSelect( BPLIST_WORK * wk )
{
	int	ret = BPL_TPCheck( wk, StMainPage_HitRect );

	if( ret == RECT_HIT_NONE ){
		ret = BAPP_CursorMove( wk->cmv_wk );
		if( ret == BAPP_CMV_CANCEL ){
			ret = 3;
		}else if( ret == BAPP_CMV_NONE ){
			return 0xff;
		}
	}else{
//		Snd_SePlay( SEQ_SE_DP_DECIDE );
		BattlePokeList_CursorOff( wk );
	}
	return (u8)ret;
}

//--------------------------------------------------------------------------------------------
/**
 * �X�e�[�^�X�Z�I��
 *
 * @param	wk		���[�N
 *
 * @retval	"0xff != �I�����ꂽ"
 * @retval	"0xff = ���I��"
 */
//--------------------------------------------------------------------------------------------
static u8 BPL_StWazaSelect( BPLIST_WORK * wk )
{
	int	ret = BPL_TPCheck( wk, StWazaSelPage_HitRect );

	if( ret == RECT_HIT_NONE ){
		ret = BAPP_CursorMove( wk->cmv_wk );
		if( ret == BAPP_CMV_CANCEL ){
			ret = 7;
		}else if( ret == BAPP_CMV_NONE ){
			return 0xff;
		}
	}else{
//		Snd_SePlay( SEQ_SE_DP_DECIDE );
		BattlePokeList_CursorOff( wk );
	}
	return (u8)ret;
}

//--------------------------------------------------------------------------------------------
/**
 * �X�e�[�^�X�Z�ڍבI��
 *
 * @param	wk		���[�N
 *
 * @retval	"0xff != �I�����ꂽ"
 * @retval	"0xff = ���I��"
 */
//--------------------------------------------------------------------------------------------
static u8 BPL_StInfoWazaSelect( BPLIST_WORK * wk )
{
	int	ret = BPL_TPCheck( wk, StWazaInfoPage_HitRect );

	if( ret == RECT_HIT_NONE ){
		ret = BAPP_CursorMove( wk->cmv_wk );
		if( ret == BAPP_CMV_CANCEL ){
			ret = 4;
		}else if( ret == BAPP_CMV_NONE ){
			return 0xff;
		}
	}else{
//		Snd_SePlay( SEQ_SE_DP_DECIDE );
		BattlePokeList_CursorOff( wk );
	}
	return (u8)ret;
}


//--------------------------------------------------------------------------------------------
/**
 * �^�b�`�p�l���̃{�^����������
 *
 * @param	wk		���[�N
 * @param	tbl		TP�f�[�^�e�[�u��
 *
 * @retval	"RECT_HIT_NONE = ������Ă��Ȃ�"
 * @retval	"RECT_HIT_NONE != �������{�^���ԍ�"
 */
//--------------------------------------------------------------------------------------------
static int BPL_TPCheck( BPLIST_WORK * wk, const RECT_HIT_TBL * tbl )
{
	int	ret = GF_TP_RectHitTrg( tbl );
/*
	if( ret != RECT_HIT_NONE ){
		u16	pat = 0xfffe;
		if( GF_BGL_DotCheck( wk->bgl, GF_BGL_FRAME3_S, sys.tp_x, sys.tp_y, &pat ) == FALSE ){
			return RECT_HIT_NONE;
		}
	}
*/
/*
	if( ret != RECT_HIT_NONE ){
		Snd_SePlay( SEQ_SE_DP_DECIDE );
	}
*/

	return ret;
}

//--------------------------------------------------------------------------------------------
/**
 * �w��ʒu�Ƀ|�P���������݂��邩
 *
 * @param	wk		���[�N
 * @param	pos		�ʒu
 *
 * @retval	"0 = ���Ȃ�"
 * @retval	"1 = �퓬��"
 * @retval	"2 = �T��"
 */
//--------------------------------------------------------------------------------------------
u8 BattlePokeList_PokeSetCheck( BPLIST_WORK * wk, s32 pos )
{
	if( wk->poke[pos].mons == 0 ){
		return 0;
	}
	if( pos == 0 ||
		( (BattlePokeList_DoubleCheck(wk)||BattlePokeList_MultiCheck(wk)) && pos == 1 ) ){
		return 1;
	}
	return 2;
}

//--------------------------------------------------------------------------------------------
/**
 * ���̃|�P�������擾
 *
 * @param	wk		���[�N
 * @param	pos		���݈ʒu
 * @param	mv		�ړ�����
 *
 * @retval	"0xff = ���̃|�P�����Ȃ�"
 * @retval	"0xff != ���̃|�P�����̈ʒu"
 */
//--------------------------------------------------------------------------------------------
static u8 BPL_NextPokeGet( BPLIST_WORK * wk, s32 pos, s32 mv )
{
	s32	now = pos;

	if( BattlePokeList_MultiCheck( wk ) == TRUE ){
		u8 check_tbl[] = { 0, 2, 4, 1, 3, 5 };

		for( pos=0; pos<6; pos++ ){
			if( now == check_tbl[pos] ){ break; }
		}

		while( 1 ){
			pos += mv;

			if( pos < 0 ){
				pos = 5;
			}else if( pos >= 6 ){
				pos = 0;
			}
			if( now == check_tbl[pos] ){ break; }
			if( BattlePokeList_PokeSetCheck( wk, check_tbl[pos] ) != 0 ){
				if( wk->poke[ check_tbl[pos] ].egg == 0 ){
					return check_tbl[pos];
				}
			}
		}
	}else{
		while( 1 ){
			pos += mv;
			if( pos < 0 ){
				pos = 5;
			}else if( pos >= 6 ){
				pos = 0;
			}
			if( now == pos ){ break; }
			if( BattlePokeList_PokeSetCheck( wk, pos ) != 0 ){
				if( wk->poke[pos].egg == 0 ){
					return (u8)pos;
				}
			}
		}
	}

	return 0xff;
}

//--------------------------------------------------------------------------------------------
/**
 * �v���[�g��������
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
/*
static void BPL_PokePlateSet( BPLIST_WORK * wk )
{
	s16	i, j;

	if( wk->dat->mode == BPL_MODE_WAZASET ){ return; }

	for( i=0; i<6; i++ ){
		j = BattlePokeList_PokeSetCheck( wk, i );
		if( j == 1 ){
			GF_BGL_ScrWrite(
				wk->bgl, GF_BGL_FRAME2_S, wk->btn_plate1[0],
				PlatePos[i][0], PlatePos[i][1], PLATE_BG_SX, PLATE_BG_SY );
		}else if( j == 2 ){
			GF_BGL_ScrWrite(
				wk->bgl, GF_BGL_FRAME2_S, wk->btn_plate2[0],
				PlatePos[i][0], PlatePos[i][1], PLATE_BG_SX, PLATE_BG_SY );
		}
	}
	GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME2_S );
}
*/

//--------------------------------------------------------------------------------------------
/**
 * �o���l�Q�[�W��������
 *
 * @param	wk		���[�N
 * @param	page	�y�[�W�ԍ�
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_ExpGagePut( BPLIST_WORK * wk, u8 page )
{
	BPL_POKEDATA * pd;
	u32	max;
	u32	now;
	u16	cgx;
	u16	px, py;
	u8	dot;
	u8	i;

	if( page != BPLIST_PAGE_MAIN ){ return; }

	pd = &wk->poke[wk->dat->sel_poke];

/* ���r�T�t�@�̈�ĉ���Lv100�ȏ�̌o���l�ɂȂ邽�߁A�}�C�i�X�\���ɂȂ��Ă��܂��s��Ώ� */
#if T1653_060815_FIX	// �Ώ���
	if( pd->lv < 100 ){
		max = pd->next_lv_exp - pd->now_lv_exp;
		now = pd->now_exp - pd->now_lv_exp;
	}else{
		max = 0;
		now = 0;
	}
#else					// �Ώ��O
	max = pd->next_lv_exp - pd->now_lv_exp;
	now = pd->now_exp - pd->now_lv_exp;
#endif	// T1653_060815_FIX
	dot = GetNumDotto( now, max, EXP_DOT_MAX );

	for( i=0; i<EXP_DOT_CHR_MAX; i++ ){
		if( dot >= 8 ){
			cgx = EXP_CGX + 8;
		}else{
			cgx = EXP_CGX + dot;
		}

		BPL_P3_ExpGagePut( wk, cgx, P3_EXPGAGE_PX+i, P3_EXPGAGE_PY );

		if( dot < 8 ){
			dot = 0;
		}else{
			dot -= 8;
		}
	}

	GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME3_S );
}

/*
static void BPL_P2_ExpGagePut( BPLIST_WORK * wk, u16 cgx, u16 px, u16 py )
{
	GF_BGL_ScrFill( wk->bgl, GF_BGL_FRAME3_S, cgx, px, py, 1, 1, GF_BGL_SCRWRT_PALNL );
	GF_BGL_ScrFill( wk->bgl, GF_BGL_FRAME3_S, cgx+32, px, py+1, 1, 1, GF_BGL_SCRWRT_PALNL );
}
*/

static void BPL_P3_ExpGagePut( BPLIST_WORK * wk, u16 cgx, u16 px, u16 py )
{
	GF_BGL_ScrFill( wk->bgl, GF_BGL_FRAME3_S, cgx, px, py, 1, 1, GF_BGL_SCRWRT_PALNL );
}

//--------------------------------------------------------------------------------------------
/**
 * �R���e�X�g�Z�̃n�[�g��������
 *
 * @param	wk		���[�N
 * @param	page	�y�[�W�ԍ�
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
#define	HEART1_CHR_NUM	( 0x140 )
#define	HEART2_CHR_NUM	( 0x125 )
#define	HEART_PX		( 2 )
#define	HEART_PY		( 14 )
#define	HEART_MAX		( 6 )

static void BPL_ContestWazaHeartPutMain( BPLIST_WORK * wk, u16 chr, u8 num )
{
	GF_BGL_ScrFill(
		wk->bgl, GF_BGL_FRAME3_S, chr,
		HEART_PX+num*2, HEART_PY, 1, 1, GF_BGL_SCRWRT_PALNL );
	GF_BGL_ScrFill(
		wk->bgl, GF_BGL_FRAME3_S, chr+1,
		HEART_PX+num*2+1, HEART_PY, 1, 1, GF_BGL_SCRWRT_PALNL );
	GF_BGL_ScrFill(
		wk->bgl, GF_BGL_FRAME3_S, chr+32,
		HEART_PX+num*2, HEART_PY+1, 1, 1, GF_BGL_SCRWRT_PALNL );
	GF_BGL_ScrFill(
		wk->bgl, GF_BGL_FRAME3_S, chr+33,
		HEART_PX+num*2+1, HEART_PY+1, 1, 1, GF_BGL_SCRWRT_PALNL );
}

static void BPL_ContestWazaHeartInit( BPLIST_WORK * wk )
{
	u16	i;

	for( i=0; i<HEART_MAX; i++ ){
		BPL_ContestWazaHeartPutMain( wk, HEART2_CHR_NUM, i );
	}
}

static void BPL_ContestWazaHeartPut( BPLIST_WORK * wk, u8 page )
{
	u32	ap_no;
	u16	i;
	u16	waza;
	s8	point;

	if( page != BPLIST_PAGE_WAZASET_CI ){
		return;
	}

	BPL_ContestWazaHeartInit( wk );

	if( wk->dat->sel_wp < 4 ){
		BPL_POKEWAZA * wd = &wk->poke[wk->dat->sel_poke].waza[wk->dat->sel_wp];
		waza = wd->id;
	}else{
		waza = wk->dat->chg_waza;
	}

	ap_no = WT_WazaDataParaGet( waza, ID_WTD_ap_no );
	point = ConTool_GetAPWaza_App( ap_no ) / APP_APPEAL_ICON_ONE_POINT;
	for( i=0; i<point; i++ ){
		BPL_ContestWazaHeartPutMain( wk, HEART1_CHR_NUM, i );
	}
	GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME3_S );
}





//--------------------------------------------------------------------------------------------
/**
 * �y�[�W�؂�ւ�
 *
 * @param	wk			���[�N
 * @param	next_page	���̃y�[�W
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_PageChange( BPLIST_WORK * wk, u8 next_page )
{
	BPL_PageChgBgScreenChg( wk, next_page );

	GF_BGL_ScrClearCodeVReq( wk->bgl, GF_BGL_FRAME0_S, 0 );
	GF_BGL_ScrClearCodeVReq( wk->bgl, GF_BGL_FRAME1_S, 0 );

	BattlePokeList_PageObjSet( wk, next_page );
	BattlePokeList_BmpFree( wk );
	BattlePokeList_BmpAdd( wk, next_page );
	BattlePokeList_BmpWrite( wk, next_page );
	BPL_ExpGagePut( wk, next_page );

	BPL_ContestWazaHeartPut( wk, next_page );

	BattlePokeList_CursorMoveSet( wk, next_page );

	BattlePokeList_ButtonPageScreenInit( wk, next_page );
	BattlePokeList_ButtonPalSet( wk, next_page );

	wk->page = next_page;
}

//--------------------------------------------------------------------------------------------
/**
 * BG�X�N���[����������
 *
 * @param	wk		���[�N
 * @param	page	���̃y�[�W
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static const u32 ScreenArc[][2] =
{
	{ NARC_b_plist_gra_poke_sel_t_NSCR, NARC_b_plist_gra_poke_sel_u_NSCR },				// �|�P�����I���y�[�W
	{ NARC_b_plist_gra_poke_chg_t_NSCR, NARC_b_plist_gra_poke_chg_u_NSCR },				// �|�P��������ւ��y�[�W
	{ NARC_b_plist_gra_st_main_t_NSCR, NARC_b_plist_gra_st_main_u_NSCR },				// �X�e�[�^�X���C���y�[�W
	{ NARC_b_plist_gra_st_waza_sel_t_NSCR, NARC_b_plist_gra_st_waza_sel_u_NSCR },		// �X�e�[�^�X�ڍ׃y�[�W
	{ NARC_b_plist_gra_st_waza_main_t_NSCR, NARC_b_plist_gra_st_waza_main_u_NSCR },		// �X�e�[�^�X�Z�y�[�W
	{ NARC_b_plist_gra_item_waza_t_NSCR, NARC_b_plist_gra_item_waza_u_NSCR },			// PP�񕜋Z�I���y�[�W
	{ NARC_b_plist_gra_waza_delb_sel_t_NSCR, NARC_b_plist_gra_waza_delb_sel_u_NSCR },	// �X�e�[�^�X�Z�Y��P�y�[�W�i�퓬�Z�I���j
	{ NARC_b_plist_gra_waza_delb_main_t_NSCR, NARC_b_plist_gra_waza_delb_main_u_NSCR },	// �X�e�[�^�X�Z�Y��Q�y�[�W�i�퓬�Z�ڍׁj
	{ NARC_b_plist_gra_waza_delc_sel_t_NSCR, NARC_b_plist_gra_waza_delc_sel_u_NSCR },	// �X�e�[�^�X�Z�Y��R�y�[�W�i�R���e�X�g�Z�ڍׁj
	{ NARC_b_plist_gra_waza_delc_main_t_NSCR, NARC_b_plist_gra_waza_delc_main_u_NSCR },	// �X�e�[�^�X�Z�Y��S�y�[�W�i�R���e�X�g�Z�I���j
};

static void BPL_PageChgBgScreenChg( BPLIST_WORK * wk, u8 page )
{
	NNSG2dScreenData * dat;
	void * buf;
	u32	i;

	for( i=0; i<2; i++ ){
		buf = ArchiveDataLoadMalloc( ARC_BPLIST_GRA, ScreenArc[page][i], wk->dat->heap );
		NNS_G2dGetUnpackedScreenData( buf, &dat );
		GF_BGL_ScrWrite( wk->bgl, GF_BGL_FRAME2_S+i, (u16 *)dat->rawData, 0, 0, 32, 24 );
		GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME2_S+i );
		sys_FreeMemoryEz( buf );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * ����ւ��`�F�b�N
 *
 * @param	wk		���[�N
 *
 * @retval	"TRUE = ����ւ���"
 * @retval	"FALSE = ����ւ��s��"
 */
//--------------------------------------------------------------------------------------------
static u8 BPL_IrekaeCheck( BPLIST_WORK * wk )
{
	BPL_POKEDATA * dat;
	STRBUF * str;

	dat = &wk->poke[wk->dat->sel_poke];

	// ���l
	if( BattlePokeList_MultiPosCheck( wk, wk->dat->sel_poke ) == TRUE ){
		str = MSGMAN_AllocString( wk->mman, mes_b_plist_m05 );
		{
			int	pcn;

			pcn = BattleWorkPartnerClientNoGet( wk->dat->bw, wk->dat->client_no );
//			WORDSET_RegisterPlayerName( wk->wset, 0, BattleWorkMyStatusGet(wk->dat->bw,pcn) );
			WORDSET_RegisterTrainerNameBattle(
				wk->wset, 0, BattleWorkTrainerDataGet(wk->dat->bw,pcn) );
		}
		WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
		STRBUF_Delete( str );
		return FALSE;
	}

	// �m��
	if( dat->hp == 0 ){
		str = MSGMAN_AllocString( wk->mman, mes_b_plist_m02 );
		WORDSET_RegisterPokeNickName( wk->wset, 0, PPPPointerGet(dat->pp) );
		WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
		STRBUF_Delete( str );
		return FALSE;
	}

	// �o�Ă���
//	if( BattlePokeList_PokeSetCheck( wk, wk->dat->sel_poke ) == 1 ){
	if( wk->dat->list_row[wk->dat->sel_poke] == wk->dat->fight_poke1 ||
		wk->dat->list_row[wk->dat->sel_poke] == wk->dat->fight_poke2 ){

		str = MSGMAN_AllocString( wk->mman, mes_b_plist_m01 );
		WORDSET_RegisterPokeNickName( wk->wset, 0, PPPPointerGet(dat->pp) );
		WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
		STRBUF_Delete( str );
		return FALSE;
	}

	// �^�}�S
	if( BPL_TamagoCheck( wk ) == TRUE ){
		MSGMAN_GetString( wk->mman, mes_b_plist_m04, wk->msg_buf );
		return FALSE;
	}

	// �I������Ă���
	if( wk->dat->double_sel != 6 && wk->dat->list_row[wk->dat->sel_poke] == wk->dat->double_sel ){
		dat = &wk->poke[wk->dat->sel_poke];
		str = MSGMAN_AllocString( wk->mman, mes_b_plist_m18 );
		WORDSET_RegisterPokeNickName( wk->wset, 0, PPPPointerGet(dat->pp) );
		WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
		STRBUF_Delete( str );
		return FALSE;
	}

	// �Z
	if( wk->dat->chg_waza != 0 ){
		dat = &wk->poke[wk->init_poke];
		str = MSGMAN_AllocString( wk->mman, mes_b_plist_m03 );
		WORDSET_RegisterPokeNickName( wk->wset, 0, PPPPointerGet(dat->pp) );
		WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
		STRBUF_Delete( str );
		return FALSE;
	}

	return TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * �^�}�S�`�F�b�N
 *
 * @param	wk		���[�N
 *
 * @retval	"TRUE = �^�}�S"
 * @retval	"FALSE = �^�}�S�ȊO"
 */
//--------------------------------------------------------------------------------------------
static u8 BPL_TamagoCheck( BPLIST_WORK * wk )
{
	if( wk->poke[wk->dat->sel_poke].egg != 0 ){
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * �_�u���o�g���`�F�b�N
 *
 * @param	wk		���[�N
 *
 * @retval	"TRUE = �_�u���o�g��"
 * @retval	"FALSE = �_�u���o�g���ȊO"
 */
//--------------------------------------------------------------------------------------------
u8 BattlePokeList_DoubleCheck( BPLIST_WORK * wk )
{
	u32	type = BattleWorkFightTypeGet(wk->dat->bw);

	if( type != FIGHT_TYPE_2vs2_YASEI && type != FIGHT_TYPE_AI_MULTI &&
		(type & (FIGHT_TYPE_2vs2|FIGHT_TYPE_TAG)) ){
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * �}���`�o�g���`�F�b�N
 *
 * @param	wk		���[�N
 *
 * @retval	"TRUE = �}���`�o�g��"
 * @retval	"FALSE = �}���`�o�g���ȊO"
 */
//--------------------------------------------------------------------------------------------
u8 BattlePokeList_MultiCheck( BPLIST_WORK * wk )
{
	u32	type = BattleWorkFightTypeGet(wk->dat->bw);

	if( type != FIGHT_TYPE_2vs2_YASEI && type != FIGHT_TYPE_AI_MULTI && (type&FIGHT_TYPE_MULTI) ){
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * �}���`�o�g���Ńp�[�g�i�[�̃|�P�������`�F�b�N
 *
 * @param	wk		���[�N
 * @param	pos		�ʒu
 *
 * @retval	"TRUE = �͂�"
 * @retval	"FALSE = ������"
 */
//--------------------------------------------------------------------------------------------
u8 BattlePokeList_MultiPosCheck( BPLIST_WORK * wk, u8 pos )
{
	if( BattlePokeList_MultiCheck( wk ) == TRUE ){
		if( wk->multi_pos == CLIENT_TYPE_A ){
			if( ( pos & 1 ) != 0 ){	return TRUE; }
		}else{
			if( ( pos & 1 ) == 0 ){	return TRUE; }
		}
	}
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * ��`�Z�`�F�b�N
 *
 * @param	wk		���[�N
 *
 * @retval	"TRUE = ��`�Z"
 * @retval	"FALSE = ��`�Z�ȊO"
 */
//--------------------------------------------------------------------------------------------
static u8 BPL_HidenCheck( BPLIST_WORK * wk )
{
	u16	waza;

	if( wk->dat->sel_wp == 4 ){
		waza = wk->dat->chg_waza;
	}else{
		waza = wk->poke[wk->dat->sel_poke].waza[wk->dat->sel_wp].id;
	}
	return HidenWazaCheck( waza );
}


static void BPL_HidenOff_Battle( BPLIST_WORK * wk )
{
	// ���ރA�C�R��
	CATS_ObjectEnableCap( wk->cap[BPL_CA_BUNRUI], 0 );

	// ����
	GF_BGL_BmpWinOffVReq( &wk->add_win[WIN_P6_BRNAME] );

	// ����
	GF_BGL_BmpWinOffVReq( &wk->add_win[WIN_P6_HITNUM] );

	// �З�
	GF_BGL_BmpWinOffVReq( &wk->add_win[WIN_P6_POWNUM] );
}

static void BPL_HidenOff_Contest( BPLIST_WORK * wk )
{
	// �n�[�g
	BPL_ContestWazaHeartInit( wk );
	GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME3_S );
}


static void BattleBag_SubItem( BATTLE_WORK * bw, u16 item, u16 page, u32 heap )
{
	if( item != ITEM_AOIBIIDORO && item != ITEM_AKAIBIIDORO && item != ITEM_KIIROBIIDORO ){
		MyItem_SubItem( BattleWorkMyItemGet(bw), item, 1, heap );
	}
	MyItem_BattleBagLastItemSet( BattleWorkBagCursorGet(bw), item, page );
}
