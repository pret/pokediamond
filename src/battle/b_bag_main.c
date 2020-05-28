//============================================================================================
/**
 * @file	b_bag_main.c
 * @brief	�퓬�p�o�b�O���
 * @author	Hiroyuki Nakamura
 * @date	05.02.10
 */
//============================================================================================
#include "common.h"
#include "gflib/touchpanel.h"
#include "system/lib_pack.h"
#include "system/palanm.h"
#include "system/window.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/fontproc.h"
#include "system/msgdata.h"
#include "system/numfont.h"
#include "system/wordset.h"
#include "system/font_arc.h"
#include "system/snd_tool.h"
#include "battle/battle_common.h"
#include "battle/fight_tool.h"
#include "battle/server_tool.h"
#include "battle/battle_server.h"
#include "battle/wazano_def.h"
#include "application/app_tool.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_b_bag.h"
#include "msgdata/msg_common_scr.h"
#include "itemtool/item.h"
#include "itemtool/myitem.h"
#include "itemtool/itemuse_def.h"
#include "b_app_tool.h"

/*
#include "system/procsys.h"
#include "system/clact_tool.h"
#include "poketool/pokeparty.h"
#include "poketool/waza_tool.h"
#include "application/p_status.h"
*/

#define	B_BAG_H_GLOBAL
#define	B_BAG_MAIN_H_GLOBAL
#include "b_bag.h"
#include "b_bag_main.h"
#include "b_bag_bmp.h"
#include "b_bag_item.h"
#include "b_bag_obj.h"
#include "b_bag_anm.h"
#include "b_bag_bmp_def.h"
#include "b_bag_gra.naix"



//============================================================================================
//	�萔��`
//============================================================================================
enum {
	SEQ_BBAG_INIT = 0,		// ������
	SEQ_BBAG_POCKET,		// �|�P�b�g�I��
	SEQ_BBAG_ITEM,			// �A�C�e���I��
	SEQ_BBAG_USE,			// �A�C�e���g�p

	SEQ_BBAG_PAGE1_CHG,		// �|�P�b�g�I����
	SEQ_BBAG_PAGE2_CHG,		// �A�C�e���I����
	SEQ_BBAG_PAGE3_CHG,		// �A�C�e���g�p��

	SEQ_BBAG_ITEMSEL_NEXT,	// ���̃A�C�e���y�[�W��

	SEQ_BBAG_ERR,			// �G���[���b�Z�[�W�I���҂�
	SEQ_BBAG_MSG_WAIT,		// ���b�Z�[�W�\��
	SEQ_BBAG_TRG_WAIT,		// �g���K�[�E�F�C�g

	SEQ_BBAG_BUTTON_WAIT,	// �{�^���A�j���I���҂�

	SEQ_BBAG_GETDEMO,		// �ߊl�f���p

	SEQ_BBAG_ENDSET,		// �I���t�F�[�h�Z�b�g
	SEQ_BBAG_END			// �I��
};

#define	TMP_MSG_BUF_SIZ		( 512 )		// �e���|�������b�Z�[�W�T�C�Y


//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================
static void BattleBag_Main( TCB_PTR tcb, void * work );

static u8 BBAG_SeqInit( BBAG_WORK * wk );
static u8 BBAG_SeqPokeSelect( BBAG_WORK * wk );
static u8 BBAG_SeqItemSelect( BBAG_WORK * wk );
static u8 BBAG_SeqUseSelect( BBAG_WORK * wk );
static u8 BBAG_SeqPage1Chg( BBAG_WORK * wk );
static u8 BBAG_SeqPage2Chg( BBAG_WORK * wk );
static u8 BBAG_SeqPage3Chg( BBAG_WORK * wk );
static u8 BBAG_SeqItemSelNext( BBAG_WORK * wk );
static u8 BBAG_SeqError( BBAG_WORK * wk );
static u8 BBAG_SeqMsgWait( BBAG_WORK * wk );
static u8 BBAG_SeqTrgWait( BBAG_WORK * wk );
static u8 BBAG_SeqButtonWait( BBAG_WORK * wk );
static u8 BBAG_SeqGetDemoMain( BBAG_WORK * wk );
static u8 BBAG_SeqEndSet( BBAG_WORK * wk );
static u8 BBAG_SeqEnd( TCB_PTR tcb, BBAG_WORK * wk );

//static void BBAG_VramInit(void);
static void BBAG_BgInit( BBAG_WORK * wk );
static void BBAG_BgExit( GF_BGL_INI * ini );
static void BBAG_BgGraphicSet( BBAG_WORK * wk );
static void BBAG_MsgManSet( BBAG_WORK * wk );
static void BBAG_MsgManExit( BBAG_WORK * wk );
static u8 BBAG_ItemUse( BBAG_WORK * wk );

static void BBAG_PageChgBgScroll( BBAG_WORK * wk, u8 page );
static void BBAG_PageChange( BBAG_WORK * wk, u8 next_page );
static int BBAG_TPCheck( BBAG_WORK * wk, const RECT_HIT_TBL * tbl );

static void BattleBag_SubItem( BATTLE_WORK * bw, u16 item, u16 page, u32 heap );


//============================================================================================
//	�O���[�o���ϐ�
//============================================================================================
// �|�P�b�g�I����ʂ̃^�b�`�p�l�����W
static const RECT_HIT_TBL Page1_HitRect[] =
{
	{  1*8, 10*8-1,  0*8, 16*8-1 },	// HP�񕜃|�P�b�g
	{ 10*8, 19*8-1,  0*8, 16*8-1 },	// ��ԉ񕜃|�P�b�g
	{  1*8, 10*8-1, 16*8, 32*8-1 },	// �{�[���|�P�b�g
	{ 10*8, 19*8-1, 16*8, 32*8-1 },	// �퓬�p�|�P�b�g
	{ 19*8, 24*8-1,  0*8, 26*8-1 },	// �Ō�Ɏg�p��������
	{ 19*8, 24*8-1, 27*8, 32*8-1 },	// �߂�
	{ RECT_HIT_END, 0, 0, 0 }
};

// �A�C�e���I����ʂ̃^�b�`�p�l�����W
static const RECT_HIT_TBL Page2_HitRect[] =
{
	{  1*8,  7*8-1,  0*8, 16*8-1 },	// �A�C�e���P
	{  1*8,  7*8-1, 16*8, 32*8-1 },	// �A�C�e���Q
	{  7*8, 13*8-1,  0*8, 16*8-1 },	// �A�C�e���R
	{  7*8, 13*8-1, 16*8, 32*8-1 },	// �A�C�e���S
	{ 13*8, 19*8-1,  0*8, 16*8-1 },	// �A�C�e���T
	{ 13*8, 19*8-1, 16*8, 32*8-1 },	// �A�C�e���U
	{ 19*8, 24*8-1,  0*8,  5*8-1 },	// �O��
	{ 19*8, 24*8-1,  5*8, 10*8-1 },	// ����
	{ 19*8, 24*8-1, 27*8, 32*8-1 },	// �߂�
	{ RECT_HIT_END, 0, 0, 0 }
};

// �A�C�e���I����ʂ̃^�b�`�p�l�����W
static const RECT_HIT_TBL Page3_HitRect[] =
{
	{ 19*8, 24*8-1,  0*8, 26*8-1 },	// �g��
	{ 19*8, 24*8-1, 27*8, 32*8-1 },	// �߂�
	{ RECT_HIT_END, 0, 0, 0 }
};



//--------------------------------------------------------------------------------------------
/**
 * �퓬�p�o�b�O�^�X�N�ǉ�
 *
 * @param	dat		�o�b�O�f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BattleBag_TaskAdd( BBAG_DATA * dat )
{
	BBAG_WORK * wk;

	wk = TCB_GetWork( PMDS_taskAdd(BattleBag_Main,sizeof(BBAG_WORK),100,dat->heap) );

	memset( wk, 0, sizeof(BBAG_WORK) );
	wk->dat = dat;
	wk->bgl = BattleWorkGF_BGL_INIGet( dat->bw );
	wk->pfd = BattleWorkPfdGet( dat->bw );
	wk->seq = SEQ_BBAG_INIT;

	{
		BAG_CURSOR * cur;
		u8	i;

		cur = BattleWorkBagCursorGet( dat->bw );
		for( i=0; i<5; i++ ){
			MyItem_BattleBagCursorGet( cur, i, &wk->dat->item_pos[i], &wk->dat->item_scr[i] );
		}
		wk->dat->used_item = MyItem_BattleBagLastItemGet( cur );
		wk->dat->used_poke = MyItem_BattleBagLastPageGet( cur );
	}

	BattleBag_UsedItemChack( wk );

	if( BattleWorkFightTypeGet(wk->dat->bw) & FIGHT_TYPE_GET_DEMO ){
		wk->dat->mode = BBAG_MODE_GETDEMO;
	}

/** �f�o�b�O���� **/
//	wk->dat->myitem = MyItem_AllocWork( wk->dat->heap );
//	Debug_MyItem_MakeBag( wk->dat->myitem, wk->dat->heap );
//	wk->dat->mode = BBAG_MODE_GETDEMO;
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
static void BattleBag_Main( TCB_PTR tcb, void * work )
{
	BBAG_WORK * wk = (BBAG_WORK *)work;

	switch( wk->seq ){
	case SEQ_BBAG_INIT:		// ������
		wk->seq = BBAG_SeqInit( wk );
		break;

	case SEQ_BBAG_POCKET:	// �|�P�b�g�I��
		wk->seq = BBAG_SeqPokeSelect( wk );
		break;

	case SEQ_BBAG_ITEM:		// �A�C�e���I��
		wk->seq = BBAG_SeqItemSelect( wk );
		break;

	case SEQ_BBAG_USE:		// �A�C�e���g�p
		wk->seq = BBAG_SeqUseSelect( wk );
		break;

	case SEQ_BBAG_PAGE1_CHG:	// �|�P�b�g�I����
		wk->seq = BBAG_SeqPage1Chg( wk );
		break;
	
	case SEQ_BBAG_PAGE2_CHG:	// �A�C�e���I����
		wk->seq = BBAG_SeqPage2Chg( wk );
		break;

	case SEQ_BBAG_PAGE3_CHG:	// �A�C�e���g�p��
		wk->seq = BBAG_SeqPage3Chg( wk );
		break;

	case SEQ_BBAG_ITEMSEL_NEXT:	// ���̃A�C�e���y�[�W��
		wk->seq = BBAG_SeqItemSelNext( wk );
		break;

	case SEQ_BBAG_ERR:			// �G���[���b�Z�[�W�I���҂�
		wk->seq = BBAG_SeqError( wk );
		break;

	case SEQ_BBAG_MSG_WAIT:		// ���b�Z�[�W�\��
		wk->seq = BBAG_SeqMsgWait( wk );
		break;

	case SEQ_BBAG_TRG_WAIT:		// �g���K�[�E�F�C�g
		wk->seq = BBAG_SeqTrgWait( wk );
		break;

	case SEQ_BBAG_BUTTON_WAIT:	// �{�^���A�j���I���҂�
		wk->seq = BBAG_SeqButtonWait( wk );
		break;

	case SEQ_BBAG_GETDEMO:		// �ߊl�f���p
		wk->seq = BBAG_SeqGetDemoMain( wk );
		break;

	case SEQ_BBAG_ENDSET:		// �I���t�F�[�h�Z�b�g
		wk->seq = BBAG_SeqEndSet( wk );
		break;

	case SEQ_BBAG_END:		// �I��
		if( BBAG_SeqEnd( tcb, wk ) == TRUE ){
			return;
		}
	}

	BattleBag_ButtonAnmMain( wk );
//	BattleBag_GetDemoCursorAnm( wk );
	CATS_Draw( wk->crp );
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
static u8 BBAG_SeqInit( BBAG_WORK * wk )
{
	G2S_BlendNone();

	wk->cmv_wk = BAPP_CursorMoveWorkAlloc( wk->dat->heap );

//	BBAG_VramInit();
	BBAG_BgInit( wk );
	BBAG_BgGraphicSet( wk );
	BBAG_MsgManSet( wk );

	FontProc_LoadFont( FONT_BUTTON, wk->dat->heap );

	wk->poke_id = (u8)MyItem_BattleBagPocketPagePosGet( BattleWorkBagCursorGet(wk->dat->bw) );

	BattleBag_PocketInit( wk );

	BattleBag_ButtonPageScreenInit( wk, wk->page );

	BattleBag_BmpInit( wk );
	BattleBag_BmpWrite( wk, wk->page );

	BattleBag_ObjInit( wk );
	BattleBag_PageObjSet( wk, wk->page );

//	wk->dat->enc_double = 1;
//	wk->dat->cursor_flg = 1;
	if( wk->dat->cursor_flg != 0 ){
		BAPP_CursorMvWkSetFlag( wk->cmv_wk, 1 );
	}
	BattleBag_CursorMoveSet( wk, wk->page );
	BBAG_GetDemoCursorSet( wk, wk->page );

	PaletteFadeReq( wk->pfd, PF_BIT_SUB_ALL, 0xffff, BATTLE_BAGLIST_FADE_SPEED, 16, 0, 0 );

	if( wk->dat->mode == BBAG_MODE_GETDEMO ){
		return SEQ_BBAG_GETDEMO;
	}
	return SEQ_BBAG_POCKET;
}

//--------------------------------------------------------------------------------------------
/**
 * �y�[�W�P�̃R���g���[���V�[�P���X
 *
 * @param	wk		���[�N
 *
 * @return	�ڍs����V�[�P���X
 */
//--------------------------------------------------------------------------------------------
static u8 BBAG_SeqPokeSelect( BBAG_WORK * wk )
{
	if( PaletteFadeCheck( wk->pfd ) != 0 ){ return SEQ_BBAG_POCKET; }

	{
		int	ret = BBAG_TPCheck( wk, Page1_HitRect );

		if( ret == RECT_HIT_NONE ){
			ret = BAPP_CursorMove( wk->cmv_wk );
			if( ret == BAPP_CMV_CANCEL ){
				ret = BBAG_P1_RETURN;
			}
		}else{
			BattleBag_CursorOff( wk );
		}

		switch( ret ){
		case BBAG_POKE_HPRCV:		// HP�񕜃|�P�b�g
		case BBAG_POKE_STRCV:		// ��ԉ񕜃|�P�b�g
		case BBAG_POKE_BALL:		// �{�[���|�P�b�g
		case BBAG_POKE_BATTLE:		// �퓬�p�|�P�b�g
			Snd_SePlay( SEQ_SE_DP_DECIDE );
			wk->poke_id = (u8)ret;
			wk->ret_seq = SEQ_BBAG_PAGE2_CHG;
			BattleBag_ButtonAnmInit(
				wk, BBAG_BTNANM_PAGE1+ret-BBAG_POKE_HPRCV, BBAG_BTNANM_MODE_END );
			return SEQ_BBAG_BUTTON_WAIT;

		case BBAG_P1_LASTITEM:		// �Ō�Ɏg�p��������
			if( wk->dat->used_item != 0 ){
				Snd_SePlay( SEQ_SE_DP_DECIDE );
				wk->poke_id = wk->dat->used_poke;
				wk->ret_seq = SEQ_BBAG_PAGE3_CHG;
				BattleBag_CorsorReset( wk );
				BattleBag_ButtonAnmInit( wk, BBAG_BTNANM_LAST, BBAG_BTNANM_MODE_END );
				return SEQ_BBAG_BUTTON_WAIT;
			}
			break;

		case BBAG_P1_RETURN:		// �߂�
			Snd_SePlay( SEQ_SE_DP_DECIDE );
			wk->dat->ret_item = 0;
			wk->dat->ret_page = BBAG_POKE_MAX;
			BattleBag_ButtonAnmInit( wk, BBAG_BTNANM_RET1, BBAG_BTNANM_MODE_END );
			return SEQ_BBAG_ENDSET;
		}
	}

	return SEQ_BBAG_POCKET;
}

//--------------------------------------------------------------------------------------------
/**
 * �y�[�W�Q�̃R���g���[���V�[�P���X
 *
 * @param	wk		���[�N
 *
 * @return	�ڍs����V�[�P���X
 */
//--------------------------------------------------------------------------------------------
static u8 BBAG_SeqItemSelect( BBAG_WORK * wk )
{
	{
		int	ret = BBAG_TPCheck( wk, Page2_HitRect );

		if( ret == RECT_HIT_NONE ){
			ret = BAPP_CursorMove( wk->cmv_wk );
			if( ret == BAPP_CMV_CANCEL ){
				ret = 8;
			}
		}else{
			BattleBag_CursorOff( wk );
		}

		switch( ret ){
		case 0:		// �A�C�e���P
		case 1:		// �A�C�e���Q
		case 2:		// �A�C�e���R
		case 3:		// �A�C�e���S
		case 4:		// �A�C�e���T
		case 5:		// �A�C�e���U
			if( BattleBag_PosItemCheck( wk, ret ) != 0 ){
				Snd_SePlay( SEQ_SE_DP_DECIDE );
				wk->dat->item_pos[wk->poke_id] = (u8)ret;
				wk->ret_seq = SEQ_BBAG_PAGE3_CHG;
				BattleBag_ButtonAnmInit( wk, BBAG_BTNANM_ITEM1+ret, BBAG_BTNANM_MODE_END );
				return SEQ_BBAG_BUTTON_WAIT;
			}
			break;

		case 6:		// �O��
			if( wk->scr_max[wk->poke_id] != 0 ){
				Snd_SePlay( SEQ_SE_DP_DECIDE );
				wk->ret_seq = SEQ_BBAG_ITEMSEL_NEXT;
				wk->page_mv = -1;
				BattleBag_ButtonAnmInit( wk, BBAG_BTNANM_UP, BBAG_BTNANM_MODE_END );
				return SEQ_BBAG_BUTTON_WAIT;
			}
			break;

		case 7:		// ����
			if( wk->scr_max[wk->poke_id] != 0 ){
				Snd_SePlay( SEQ_SE_DP_DECIDE );
				wk->ret_seq = SEQ_BBAG_ITEMSEL_NEXT;
				wk->page_mv = 1;
				BattleBag_ButtonAnmInit( wk, BBAG_BTNANM_DOWN, BBAG_BTNANM_MODE_END );
				return SEQ_BBAG_BUTTON_WAIT;
			}
			break;

		case 8:		// �߂�
			Snd_SePlay( SEQ_SE_DP_DECIDE );
			wk->ret_seq = SEQ_BBAG_PAGE1_CHG;
			BattleBag_ButtonAnmInit( wk, BBAG_BTNANM_RET2, BBAG_BTNANM_MODE_END );
			return SEQ_BBAG_BUTTON_WAIT;
		}
	}

	return SEQ_BBAG_ITEM;
}

static u8 BBAG_SeqItemSelNext( BBAG_WORK * wk )
{
	s8	scr = wk->dat->item_scr[wk->poke_id];

	wk->dat->item_pos[wk->poke_id] = 0;
	scr += wk->page_mv;
	if( scr > wk->scr_max[wk->poke_id] ){
		wk->dat->item_scr[wk->poke_id] = 0;
	}else if( scr < 0 ){
		wk->dat->item_scr[wk->poke_id] = wk->scr_max[wk->poke_id];
	}else{
		wk->dat->item_scr[wk->poke_id] = scr;
	}
	BattleBag_Page2_StrItemPut( wk );
	BattleBag_Page2_StrPageNumPut( wk );
	BattleBag_PageObjSet( wk, wk->page );
	BattleBag_ButtonPageScreenInit( wk, wk->page );
//	BBAG_P2CursorMvTblMake( wk );
	return SEQ_BBAG_ITEM;
}


//--------------------------------------------------------------------------------------------
/**
 * �y�[�W�R�̃R���g���[���V�[�P���X
 *
 * @param	wk		���[�N
 *
 * @return	�ڍs����V�[�P���X
 */
//--------------------------------------------------------------------------------------------
static u8 BBAG_SeqUseSelect( BBAG_WORK * wk )
{
	{
		int	ret = BBAG_TPCheck( wk, Page3_HitRect );

		if( ret == RECT_HIT_NONE ){
			ret = BAPP_CursorMove( wk->cmv_wk );
			if( ret == BAPP_CMV_CANCEL ){
				ret = 1;
			}
		}else{
			BattleBag_CursorOff( wk );
		}

		switch( ret ){
		case 0:		// �g��
			Snd_SePlay( SEQ_SE_DP_DECIDE );
			wk->dat->ret_item = BattleBag_PosItemCheck( wk, wk->dat->item_pos[wk->poke_id] );
			wk->dat->ret_page = wk->poke_id;
			BattleBag_ButtonAnmInit( wk, BBAG_BTNANM_USE, BBAG_BTNANM_MODE_END );
			return BBAG_ItemUse( wk );

		case 1:		// �߂�
			Snd_SePlay( SEQ_SE_DP_DECIDE );
			wk->ret_seq = SEQ_BBAG_PAGE2_CHG;
			BattleBag_ButtonAnmInit( wk, BBAG_BTNANM_RET3, BBAG_BTNANM_MODE_END );
			return SEQ_BBAG_BUTTON_WAIT;
		}
	}

	return SEQ_BBAG_USE;
}

static u8 BBAG_ItemUse( BBAG_WORK * wk )
{
	BBAG_DATA * dat = wk->dat;

	if( wk->poke_id == BBAG_POKE_BATTLE ){
		int	smn = BattleBag_SelMonsNoGet( wk );
		u32	prm = ItemParamGet( dat->ret_item, ITEM_PRM_BATTLE, dat->heap );

		// ����������
		if( dat->skill_item_use != 0 && dat->ret_item != ITEM_EFEKUTOGAADO && prm != ITEMUSE_BTL_ESCAPE ){

			POKEMON_PARAM * pp;
			STRBUF * str;

			pp  = BattleWorkPokemonParamGet( dat->bw, dat->client_no, smn );
			str = MSGMAN_AllocString( wk->mman, mes_b_bag_m13 );
			WORDSET_RegisterPokeNickName( wk->wset, 0, PPPPointerGet(pp) );
			WORDSET_RegisterWazaName( wk->wset, 1, WAZANO_SASIOSAE );
			WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
			STRBUF_Delete( str );
			BattleBag_TalkMsgSet( wk );
			wk->ret_seq = SEQ_BBAG_ERR;
			return SEQ_BBAG_MSG_WAIT;
		}

		if( BattleWorkStatusRecover(dat->bw,dat->client_no,smn,0,dat->ret_item) == TRUE ){
			BattleBag_SubItem( dat->bw, dat->ret_item, wk->poke_id, dat->heap );
			return SEQ_BBAG_ENDSET;
		}else if( prm == ITEMUSE_BTL_ESCAPE ){
			if( !(BattleWorkFightTypeGet(dat->bw) & FIGHT_TYPE_TRAINER) ){
				BattleBag_SubItem( dat->bw, dat->ret_item, wk->poke_id, dat->heap );
				return SEQ_BBAG_ENDSET;
			}else{
				MSGDATA_MANAGER * mman;
				STRBUF * str;
				mman = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_common_scr_dat, dat->heap );
				str  = MSGMAN_AllocString( mman, msg_item_ng_01 );
				WORDSET_RegisterPlayerName( wk->wset, 0, dat->myst );
				WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
				STRBUF_Delete( str );
				MSGMAN_Delete( mman );
				BattleBag_TalkMsgSet( wk );
				wk->ret_seq = SEQ_BBAG_ERR;
				return SEQ_BBAG_MSG_WAIT;
			}
		}else{
			MSGMAN_GetString( wk->mman, mes_b_bag_m01, wk->msg_buf );
			BattleBag_TalkMsgSet( wk );
			wk->ret_seq = SEQ_BBAG_ERR;
			return SEQ_BBAG_MSG_WAIT;
		}
	}else if( wk->poke_id == BBAG_POKE_BALL ){
		// �쐶�_�u��
		if( dat->enc_double == 1 ){
			MSGMAN_GetString( wk->mman, mes_b_bag_m11, wk->msg_buf );
			BattleBag_TalkMsgSet( wk );
			wk->ret_seq = SEQ_BBAG_ERR;
			return SEQ_BBAG_MSG_WAIT;
		}

		// ����ԂƂ�
		if( dat->waza_vanish == 1 ){
			MSGMAN_GetString( wk->mman, mes_b_bag_m14, wk->msg_buf );
			BattleBag_TalkMsgSet( wk );
			wk->ret_seq = SEQ_BBAG_ERR;
			return SEQ_BBAG_MSG_WAIT;
		}

		// �g����
		if( dat->waza_migawari == 1 ){
			MSGMAN_GetString( wk->mman, mes_b_bag_m15, wk->msg_buf );
			BattleBag_TalkMsgSet( wk );
			wk->ret_seq = SEQ_BBAG_ERR;
			return SEQ_BBAG_MSG_WAIT;
		}

		{	// �莝���E�{�b�N�X�����ς�
			POKEPARTY * party = BattleWorkPokePartyGet( dat->bw, dat->client_no );
			BOX_DATA * box = BattleWorkBoxDataGet( dat->bw );

			if( PokeParty_GetPokeCount( party ) == 6 &&
				BOXDAT_GetEmptyTrayNumber( box ) == BOXDAT_TRAYNUM_ERROR ){

				MSGMAN_GetString( wk->mman, mes_b_bag_m12, wk->msg_buf );
				BattleBag_TalkMsgSet( wk );
				wk->ret_seq = SEQ_BBAG_ERR;
				return SEQ_BBAG_MSG_WAIT;
			}
		}
	}
	return SEQ_BBAG_ENDSET;
}

static u8 BBAG_SeqPage1Chg( BBAG_WORK * wk )
{
	BBAG_PageChange( wk, BBAG_PAGE_POCKET );
	return SEQ_BBAG_POCKET;
}

static u8 BBAG_SeqPage2Chg( BBAG_WORK * wk )
{
	BBAG_PageChange( wk, BBAG_PAGE_MAIN );
	return SEQ_BBAG_ITEM;
}

static u8 BBAG_SeqPage3Chg( BBAG_WORK * wk )
{
	BBAG_PageChange( wk, BBAG_PAGE_ITEM );
	return SEQ_BBAG_USE;
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
static u8 BBAG_SeqError( BBAG_WORK * wk )
{
	BmpTalkWinClear( &wk->talk_win, WINDOW_TRANS_ON );
	return SEQ_BBAG_USE;
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
static u8 BBAG_SeqMsgWait( BBAG_WORK * wk )
{
	if( GF_MSG_PrintEndCheck( wk->midx ) == 0 ){
		return SEQ_BBAG_TRG_WAIT;
	}
	return SEQ_BBAG_MSG_WAIT;
}

//--------------------------------------------------------------------------------------------
/**
 * �g���K�[�E�F�C�g�V�[�P���X
 *
 * @param	wk		���[�N
 *
 * @return	�ڍs����V�[�P���X
 */
//--------------------------------------------------------------------------------------------
static u8 BBAG_SeqTrgWait( BBAG_WORK * wk )
{
	if( ( sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL) ) || GF_TP_GetTrg() == TRUE ){
		return wk->ret_seq;
	}
	return SEQ_BBAG_TRG_WAIT;
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
static u8 BBAG_SeqButtonWait( BBAG_WORK * wk )
{
/*
	if( wk->btn_flg == 0 ){
		return wk->ret_seq;
	}
*/
	if( wk->btn_seq == 2 ){
		return wk->ret_seq;
	}
	return SEQ_BBAG_BUTTON_WAIT;
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
static u8 BBAG_SeqEndSet( BBAG_WORK * wk )
{
	PaletteFadeReq( wk->pfd, PF_BIT_SUB_ALL, 0xffff, BATTLE_BAGLIST_FADE_SPEED, 0, 16, 0 );
	return SEQ_BBAG_END;
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
static u8 BBAG_SeqEnd( TCB_PTR tcb, BBAG_WORK * wk )
{
	if( PaletteFadeCheck( wk->pfd ) != 0 ){ return FALSE; }

	BattleBag_ObjFree( wk );
	BattleBag_BmpFreeAll( wk );
	BBAG_MsgManExit( wk );
	BBAG_BgExit( wk->bgl );

	wk->dat->cursor_flg = BAPP_CursorMvWkGetFlag( wk->cmv_wk );

	BAPP_CursorMoveWorkFree( wk->cmv_wk );

	FontProc_UnloadFont( FONT_BUTTON );

	if( wk->dat->ret_item != 0 ){
		BAG_CURSOR * cur;
		u8	i;

		cur = BattleWorkBagCursorGet( wk->dat->bw );
		for( i=0; i<5; i++ ){
			MyItem_BattleBagCursorSet( cur, i, wk->dat->item_pos[i], wk->dat->item_scr[i] );
		}
		MyItem_BattleBagPocketPagePosSet( cur, wk->poke_id );
	}

	wk->dat->end_flg = 1;
	PMDS_taskDel( tcb );

	return TRUE;
}




#define	BBAG_GETDEMO_WAIT_COUNT		( 60 )		// �ߊl�f���E�F�C�g

static u8 BBAG_SeqGetDemoMain( BBAG_WORK * wk )
{
	if( PaletteFadeCheck( wk->pfd ) != 0 ){ return SEQ_BBAG_GETDEMO; }

	switch( wk->get_seq ){
	case 0:		// wait 2 sec
//		if( wk->get_cnt == BBAG_GETDEMO_WAIT_COUNT ){
		if( FINGER_TouchAnimeCheck( wk->finger ) == TRUE ){
			Snd_SePlay( SEQ_SE_DP_DECIDE );
			wk->poke_id = BBAG_POKE_BALL;
			wk->ret_seq = SEQ_BBAG_GETDEMO;
			BattleBag_ButtonAnmInit( wk, BBAG_BTNANM_PAGE3, BBAG_BTNANM_MODE_END );
//			BattleBag_GetDemoCursorPush( wk );
//			wk->get_anm = 1;
			wk->get_cnt = 0;
			wk->get_seq++;
			return SEQ_BBAG_BUTTON_WAIT;
		}else{
			wk->get_cnt++;
		}
		break;
	case 1:		// page change
//		wk->get_anm = 0;
		BBAG_SeqPage2Chg( wk );
		wk->get_seq++;
		break;

	case 2:		// wait 2 sec
//		if( wk->get_cnt == BBAG_GETDEMO_WAIT_COUNT ){
		if( FINGER_TouchAnimeCheck( wk->finger ) == TRUE ){
			Snd_SePlay( SEQ_SE_DP_DECIDE );
			wk->dat->item_pos[wk->poke_id] = 0;
			wk->ret_seq = SEQ_BBAG_GETDEMO;
			BattleBag_ButtonAnmInit( wk, BBAG_BTNANM_ITEM1, BBAG_BTNANM_MODE_END );
//			BattleBag_GetDemoCursorPush( wk );
//			wk->get_anm = 1;
			wk->get_cnt = 0;
			wk->get_seq++;
			return SEQ_BBAG_BUTTON_WAIT;
		}else{
			wk->get_cnt++;
		}
		break;
	case 3:		// page change
//		wk->get_anm = 0;
		BBAG_SeqPage3Chg( wk );
		wk->get_seq++;
		break;

	case 4:		// wait 2 sec
//		if( wk->get_cnt == BBAG_GETDEMO_WAIT_COUNT ){
		if( FINGER_TouchAnimeCheck( wk->finger ) == TRUE ){
			Snd_SePlay( SEQ_SE_DP_DECIDE );
			wk->dat->ret_item = BattleBag_PosItemCheck( wk, wk->dat->item_pos[wk->poke_id] );
			wk->dat->ret_page = wk->poke_id;
			BattleBag_ButtonAnmInit( wk, BBAG_BTNANM_USE, BBAG_BTNANM_MODE_END );
//			BattleBag_GetDemoCursorPush( wk );
//			wk->get_anm = 1;
			return BBAG_ItemUse( wk );
		}else{
			wk->get_cnt++;
		}
		break;
	}

	return SEQ_BBAG_GETDEMO;
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
static void BBAG_VramInit(void)
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
static void BBAG_BgInit( BBAG_WORK * wk )
{
	{	// BG SYSTEM
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_3D,
		};
		GF_BGL_InitBGDisp( &BGsys_data, GF_BGL_SUB_DISP );
	}

	{	// BG (CHAR)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x2000, 0, GF_BGL_SCRSIZ_512x512, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xd000, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_23,
			3, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( wk->bgl, GF_BGL_FRAME2_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
	}

	{	// PARAM FONT (BMP)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( wk->bgl, GF_BGL_FRAME1_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( wk->bgl, GF_BGL_FRAME1_S );
	}

	{	// WINDOW (BMP)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
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
static void BBAG_BgExit( GF_BGL_INI * ini )
{
	GF_Disp_GXS_VisibleControl(
		GX_PLANEMASK_BG0 | GX_PLANEMASK_BG1 | GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ, VISIBLE_OFF );

	GF_BGL_BGControlExit( ini, GF_BGL_FRAME0_S );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME1_S );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME2_S );
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
static void BBAG_BgGraphicSet( BBAG_WORK * wk )
{
	ArcUtil_BgCharSet(
		ARC_BBAG_GRA, NARC_b_bag_gra_b_bag_bg_NCGR,
		wk->bgl, GF_BGL_FRAME2_S, 0, 0, 0, wk->dat->heap );

	ArcUtil_ScrnSet(
		ARC_BBAG_GRA, NARC_b_bag_gra_b_bag_bg00_NSCR,
		wk->bgl, GF_BGL_FRAME2_S, 0, 0, 0, wk->dat->heap );

	{
		NNSG2dScreenData * dat;
		void * buf;
		u16 * scrn;
		
		buf = ArchiveDataLoadMalloc(
					ARC_BBAG_GRA, NARC_b_bag_gra_b_bag_anm_NSCR, wk->dat->heap );
		NNS_G2dGetUnpackedScreenData( buf, &dat );
		scrn = (u16 *)dat->rawData;
		BattleBag_ButtonScreenMake( wk, scrn );
		sys_FreeMemoryEz( buf );
	}

	PaletteWorkSet_Arc(
		wk->pfd, ARC_BBAG_GRA, NARC_b_bag_gra_b_bag_bg_NCLR,
		wk->dat->heap, FADE_SUB_BG, 0x20*12, 0 );

/*
	// �V�X�e���t�H���g�p���b�g�Z�b�g
	PaletteWorkSet_Arc(
		wk->pfd, ARC_FONT, NARC_font_system_ncrl,
		wk->dat->heap, FADE_SUB_BG, 0x20, BBAG_PAL_SYS_FONT*16 );
*/

	// ��b�t�H���g�p���b�g�Z�b�g
	PaletteWorkSet_Arc(
		wk->pfd, ARC_FONT, NARC_font_talk_ncrl,
		wk->dat->heap, FADE_SUB_BG, 0x20, BBAG_PAL_TALK_FONT*16 );

	// ��b�E�B���h�E�Z�b�g
	{
		WINTYPE	wt = BattleWorkConfigWinTypeGet( wk->dat->bw );

		ArcUtil_BgCharSet(
			ARC_WINFRAME, TalkWinCgxArcGet(wt), wk->bgl,
			GF_BGL_FRAME0_S, TALK_WIN_CGX_POS, 0, 0, wk->dat->heap );
		PaletteWorkSet_Arc(
			wk->pfd, ARC_WINFRAME, TalkWinPalArcGet(wt),
			wk->dat->heap, FADE_SUB_BG, 0x20, BBAG_PAL_TALK_WIN*16 );
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
static void BBAG_MsgManSet( BBAG_WORK * wk )
{
	wk->mman = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_b_bag_dat, wk->dat->heap );
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
static void BBAG_MsgManExit( BBAG_WORK * wk )
{
	MSGMAN_Delete( wk->mman );
	NUMFONT_Delete( wk->nfnt );
	WORDSET_Delete( wk->wset );

	STRBUF_Delete( wk->msg_buf );
}














//--------------------------------------------------------------------------------------------
/**
 * BG�X�N���[��
 *
 * @param	wk		���[�N
 * @param	page	���̃y�[�W
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BBAG_PageChgBgScroll( BBAG_WORK * wk, u8 page )
{
	switch( page ){
	case BBAG_PAGE_POCKET:		// �|�P�b�g�I���y�[�W
		GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME2_S, GF_BGL_SCROLL_X_SET, 0 );
		GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME2_S, GF_BGL_SCROLL_Y_SET, 0 );
		break;
	case BBAG_PAGE_MAIN:		// �A�C�e���I���y�[�W
		GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME2_S, GF_BGL_SCROLL_X_SET, 256 );
		GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME2_S, GF_BGL_SCROLL_Y_SET, 0 );
		break;
	case BBAG_PAGE_ITEM:		// �A�C�e���g�p�y�[�W
		GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME2_S, GF_BGL_SCROLL_X_SET, 0 );
		GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME2_S, GF_BGL_SCROLL_Y_SET, 256 );
		break;
	}
}

#define	ITEM_PAGE_NAME_BG_PX	( 2 )
#define	ITEM_PAGE_NAME_BG_PY	( 35 )
#define	ITEM_PAGE_NAME_BG_SX	( 28 )
#define	ITEM_PAGE_NAME_BG_SY	( 4 )
#define	ITEM_PAGE_INFO_BG_PX	( 2 )
#define	ITEM_PAGE_INFO_BG_PY	( 40 )
#define	ITEM_PAGE_INFO_BG_SX	( 28 )
#define	ITEM_PAGE_INFO_BG_SY	( 8 )

static void BBAG_PageBgPalChg( BBAG_WORK * wk, u8 page )
{
	if( page != BBAG_PAGE_ITEM ){ return; }

	GF_BGL_ScrPalChange(
		wk->bgl, GF_BGL_FRAME2_S, ITEM_PAGE_NAME_BG_PX,
		ITEM_PAGE_NAME_BG_PY, ITEM_PAGE_NAME_BG_SX, ITEM_PAGE_NAME_BG_SY, 8+wk->poke_id );
	GF_BGL_ScrPalChange(
		wk->bgl, GF_BGL_FRAME2_S, ITEM_PAGE_INFO_BG_PX,
		ITEM_PAGE_INFO_BG_PY, ITEM_PAGE_INFO_BG_SX, ITEM_PAGE_INFO_BG_SY, 8+wk->poke_id );
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
static void BBAG_PageChange( BBAG_WORK * wk, u8 next_page )
{
	BBAG_PageBgPalChg( wk, next_page );
	BBAG_PageChgBgScroll( wk, next_page );

	GF_BGL_ScrClearCodeVReq( wk->bgl, GF_BGL_FRAME0_S, 0 );
	GF_BGL_ScrClearCodeVReq( wk->bgl, GF_BGL_FRAME1_S, 0 );

	BattleBag_BmpFree( wk );
	BattleBag_BmpAdd( wk, next_page );
	BattleBag_BmpWrite( wk, next_page );

	BattleBag_ButtonPageScreenInit( wk, next_page );

	BattleBag_CursorMoveSet( wk, next_page );
	BBAG_GetDemoCursorSet( wk, next_page );

	wk->page = next_page;

	BattleBag_PageObjSet( wk, wk->page );
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
static int BBAG_TPCheck( BBAG_WORK * wk, const RECT_HIT_TBL * tbl )
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


int BattleBag_SelMonsNoGet( BBAG_WORK * wk )
{
	int	ret;

	ret = ST_ServerParamDataGet(
			wk->dat->bw,
			BattleWorkServerParamGet(wk->dat->bw), ID_SP_sel_mons_no, wk->dat->client_no );
	return ret;
}


static void BattleBag_SubItem( BATTLE_WORK * bw, u16 item, u16 page, u32 heap )
{
	MyItem_SubItem( BattleWorkMyItemGet(bw), item, 1, heap );
	MyItem_BattleBagLastItemSet( BattleWorkBagCursorGet(bw), item, page );
}
