//============================================================================================
/**
 * @file	tradelist.c
 * @bfief	�|�P�����������X�g���
 * @author	Akito Mori
 * @date	05.12.08
 */
//============================================================================================

// �R�����g���͂����Ɓu�������񂷂�v����ڂ̑I�����ɂȂ�

#ifdef PM_DEBUG
//#define DEBUG_PAD_ON
//#define DEBUG_TIMEOUT
#endif

#include "common.h"
#include "system/procsys.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/pm_str.h"
#include "system/clact_tool.h"
#include "system/msgdata_util.h"
#include "system/wordset.h"
#include "msgdata/msg.naix"
#include "system/wipe.h"
#include "system/brightness.h"
#include "system/fontproc.h"
#include "system/lib_pack.h"
#include "system/fontoam.h"
#include "system/softsprite.h"
#include "system/gra_tool.h"
#include "system/bmp_menu.h"
#include "system/bmp_list.h"
#include "savedata/savedata.h"
#include "system/window.h"
#include "gflib/msg_print.h"
#include "gflib/touchpanel.h"
#include "poketool/monsno.h"
#include "poketool/pokeicon.h"
#include "poketool/poke_memo.h"
#include "application/tradelist.h"
#include "system/snd_tool.h"
#include "system/snd_perap.h"
#include "poketool/monsno.h"
#include "gflib/strbuf_family.h"
#include "communication/communication.h"
#include "communication/comm_save.h"
#include "communication/wm_icon.h"
#include "poketool/poke_tool.h"
#include "poketool/pokeparty.h"
#include "itemtool/item.h"
#include "field/comm_union_beacon.h"
#include "savedata/friendlist.h"
#include "savedata/friendlist_local.h"
#include "communication/comm_wifihistory.h"
#include "savedata/get_poke.h"

#include "system/pm_rtc.h"			//GF_RTC_IsNightTime

#include "msgdata/msg_connect.h"
#include "msgdata/msg_dstrade.h"

#include "tradelist_bmp.h"

#include "comm_command_tradelist.h"
#include "itemtool/myitem.h"

#include "wifi/dwc_rapfriend.h"
#include "msgdata/msg_wifi_note.h"

#define FIRST_NATUKIDO  (70)				///�������ꂽ�|�P�����ɓ����Ȃ��x


#define NAMEIN_MOVE_SE		(SEQ_SE_DP_SELECT)
#define NAMEIN_DECIDE_SE	(SEQ_SE_DP_SELECT)
#define NAMEIN_BS_SE		(SEQ_SE_DP_SELECT)

#define POKEICON_VRAM_OFFSET ( 4*32+18  )
#define POKEICON_TRANS_CELL  ( 4*4      )
#define POKEICON_TRANS_SIZE	 ( POKEICON_TRANS_CELL*0x20 )
#define POKEICON_PAL_OFFSET	 ( 10 )

#define POKEGRA_VRAM_OFFSET  ( 0 )
#define POKEGRA_VRAM_SIZE     ( 0x20*10*10 )

#define TRADELISTSTR_MAX	 ( 12*2 )		  // ������ʂň�ԃL���������Ԃ̂�12�L�����Ȃ̂ł��̔{������o�b�t�@������Ă���
#define TRADELIST_CACT_MAX   ( 2+12+12+12+2+2+2+1) // �J�[�\���Q�@
												   // �|�P�����P�Q�@
												   // �A�C�e���P�Q�@
												   // �J�X�^���{�[���P�Q�@
												   // ���|�P�����Q�@
												   // ���Q
													

// nce�ɓo�^����Ă��郂���X�^�[�{�[���̃A�j��NO�i���̌��Ɋe�X�̃����X�^�[�{�[���������j
#define CELL_MONSTER_BALL_NO	 ( 6 )

#define CELL_SEX_ICON_NO		 ( 22 )

#define TIMEOUT_LIMIT			( 30*60 )			// �^�C���A�E�g�܂�2���ɂ���

#include "tradelist.naix"			// �O���t�B�b�N�A�[�J�C�u��`
//============================================================================================
//	�萔��`
//============================================================================================
enum {
	SEQ_IN = 0,
	SEQ_MAIN,
	SEQ_OUT,
};

enum{
	MODE_NORMAL=0,
	MODE_TRADE_SELECT,
	MODE_END_SELECT,
	MODE_STATUS_SELECT,
};

enum{
	TRADELIST_SEQ_POKEMON_EXCHANGE,
	TRADELIST_SEQ_MAIN,
	TRADELIST_SEQ_END,
	TRADELIST_SEQ_STATUS_INFADE,
	TRADELIST_SEQ_STATUS_INFADE_WAIT,
	TRADELIST_SEQ_STATUS,
	TRADELIST_SEQ_STATUS_OUTFADE,
	TRADELIST_SEQ_STATUS_OUTFADE_WAIT,
	
};


typedef struct{
	CLACT_WORK_PTR parent;
	CLACT_WORK_PTR child;
	int dx;
	int id;
}FUNC_BUTTON_TASK_WORK;


#define TRADELIST_CURSOR_1_X (  0*8 )
#define TRADELIST_CURSOR_2_X (  8*8 )
#define TRADELIST_CURSOR_3_X ( 16*8 )
#define TRADELIST_CURSOR_4_X ( 24*8 )
#define TRADELIST_CURSOR_1_Y (  4*8 )
#define TRADELIST_CURSOR_2_Y (  9*8 )
#define TRADELIST_CURSOR_3_Y ( 14*8 )
#define TRADELIST_CURSOR_END_X	(24*8 )
#define TRADELIST_CURSOR_END_Y	(20*8 )


#define SUB_POKEMON1_POS_X	 (  63 )
#define SUB_POKEMON2_POS_X	 ( 192 )
#define SUB_POKEMON_POS_Y	 (  96-8 )
#define SUB_ARROW_POS_X		 ( 118 )
#define SUB_ARROW1_POS_Y	 ( 72 )
#define SUB_ARROW2_POS_Y	 ( 108 )
#define SUB_BALL_POS_X		 ( 2*8 )
#define SUB_BALL_POS_Y		 ( 1*8 )
#define SUB_BALL2_POS_X		 ( 18*8 )
#define SUB_SEX_ICON_X		 ( 12*8+3 )
#define SUB_SEX_ICON2_X		 ( (12+16)*8+3 )
#define SUB_SEX_ICON_Y		 (    8 )

static const main_cursor_pos[][2]={
	{TRADELIST_CURSOR_1_X,TRADELIST_CURSOR_1_Y, },
	{TRADELIST_CURSOR_2_X,TRADELIST_CURSOR_1_Y, },
	{TRADELIST_CURSOR_1_X,TRADELIST_CURSOR_2_Y, },
	{TRADELIST_CURSOR_2_X,TRADELIST_CURSOR_2_Y, },
	{TRADELIST_CURSOR_1_X,TRADELIST_CURSOR_3_Y, },
	{TRADELIST_CURSOR_2_X,TRADELIST_CURSOR_3_Y, },
	{TRADELIST_CURSOR_3_X,TRADELIST_CURSOR_1_Y, },
	{TRADELIST_CURSOR_4_X,TRADELIST_CURSOR_1_Y, },
	{TRADELIST_CURSOR_3_X,TRADELIST_CURSOR_2_Y, },
	{TRADELIST_CURSOR_4_X,TRADELIST_CURSOR_2_Y, },
	{TRADELIST_CURSOR_3_X,TRADELIST_CURSOR_3_Y, },
	{TRADELIST_CURSOR_4_X,TRADELIST_CURSOR_3_Y, },
	{TRADELIST_CURSOR_END_X,TRADELIST_CURSOR_END_Y, },

};

static const sub_icon_pos[][3]={
	{SUB_POKEMON1_POS_X, SUB_POKEMON_POS_Y, 0},						//�|�P����
	{SUB_POKEMON2_POS_X, SUB_POKEMON_POS_Y, 1},
	{SUB_BALL_POS_X,   SUB_BALL_POS_Y,      CELL_MONSTER_BALL_NO},	// �����X�^�[�{�[��
	{SUB_BALL2_POS_X,  SUB_BALL_POS_Y,      CELL_MONSTER_BALL_NO},
	{SUB_SEX_ICON_X, SUB_SEX_ICON_Y,CELL_SEX_ICON_NO},				// ����
	{SUB_SEX_ICON2_X,SUB_SEX_ICON_Y,CELL_SEX_ICON_NO},
};


#define POKEICON_DIFFX	(16)
#define POKEICON_DIFFY	(-6)
#define POKEITEM_DIFFX	(16+20)
#define POKEITEM_DIFFY	(16)
#define POKECBALL_DIFFX (16+20+8)


#include "tradelist_def.h"


//============================================================================================
//	AGB���玝���Ă����f�[�^
//============================================================================================
//�J�[�\���ړ��p�̃e�[�u��
//�㉺���E�̏��ɒ�`���Ă���܂�
//  �O �P    �U  �V
//  �Q �R    �W  �X
//  �S �T  �P�O�P�P
//             �P�Q
static const u8 movepostbl[][4][6]={
									//   0 �̈ʒu�����4�����̍s������̗D��xð���(�㉺���E�̏�)
									//   ���Ȃ������̕����D��x������
	{{ 4, 2,12,12},{ 2, 4,12,12},{ 7, 6, 1, 0},{ 1, 6, 7, 0},},		//0
	{{ 5, 3,12,12},{ 3, 5,12,12},{ 0, 7, 6, 1},{ 6, 7, 0, 1},},		
	{{ 0, 0, 0, 0},{ 4, 0, 0, 0},{ 9, 8, 7, 6},{ 3, 1,     },},		
	{{ 1, 1, 1, 1},{ 5, 1, 1, 1},{ 2, 9, 8, 7},{ 8, 9, 6, 6},},		
	{{ 2, 2, 2, 2},{ 0, 0, 0, 0},{11,10,9,8,7,6},{ 5,3,1,  },},		
	{{ 3, 3, 3, 3},{ 1, 1, 1, 1},{ 4, 4, 4, 4},{10, 8, 6,  },},		//5
	{{10, 8,12,  },{ 8,10,12,  },{ 1, 0,     },{ 7, 0, 1,  },},		
	{{12,        },{ 9,12,     },{ 6,        },{ 0,        },},		
	{{ 6,        },{10, 6,     },{ 3, 2, 1, 0},{ 9, 7,     },},		
	{{ 7,        },{11,12,     },{ 8,        },{ 2, 0, 1,  },},		
	{{ 8,        },{ 6,        },{ 5, 4, 3, 2,1,0},{11, 9, 7, },},	//10
	{{ 9,        },{12,        },{10,        },{ 4, 2, 0,  },},		
	{{11, 9, 7, 6},{ 7, 6,     },{12,        },{12,        },},		

};


static const int trade_msg_table[][4]=
{
	{mes_dstrade_02_01,   0, 0, },
	{mes_dstrade_02_02,   1, mes_dstrade_03_01,  3 },
	{mes_dstrade_02_02,   1, mes_dstrade_03_02,  4 },
	{mes_dstrade_04_01,   2, 0,0,   },
	{mes_dstrade_04_03,   2, 0,0,   },
	{mes_dstrade_04_04,   2, 0,0,   },
	{mes_dstrade_04_07,   2, 0,0,   },
	{mes_dstrade_04_08,   2, 0,0,   },
};


//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================
/*** �֐��v���g�^�C�v ***/
static void TransPokeIconCharaPal( NNSG2dCharacterData *chara, int pokeno, int form, int tamago, int no , CLACT_WORK_PTR icon);
static void TrainerNamePrint( GF_BGL_BMPWIN *win );
static void PokemonInfoSubPrint( TRADELIST_WORK *wk, int page );
static void VBlankFunc( void * work );
static void VramBankSet(void);
static void BgInit( GF_BGL_INI * ini );
static void char_pltt_manager_init(void);
static void InitWork(TRADELIST_WORK *wk, PROC * proc);
static void BgExit( GF_BGL_INI * ini );
static void TradeListMakeScreenSet(GF_BGL_INI *bgl, int mynum, int friendnum);
static void BgGraphicSet( TRADELIST_WORK * wk );
static void InitCellActor(TRADELIST_WORK *wk);
static void SetCellActor(TRADELIST_WORK *wk);
static void DebugOBJPOSGet(TRADELIST_WORK *wk);
static int AroundWork(int w, int min, int max);
static void ControlCursor(u32 *CommWork);
static void TouchFunc(TRADELIST_WORK *wk);
static void CursorColTrans(u16 *CursorCol);
static int NextCursorSearch(int pos, int arrow, POKE_INFO *info);
static void CursorPosChange(int pos, CLACT_WORK_PTR CursorAct, int side);
static int  ViewChange(u32 *Command, int *pos, CLACT_WORK_PTR CusorAct, POKE_INFO *info, int side);
static int  TransPokeGra_SubLcd(int side, POKEMON_PARAM *pp, u8 *char_work, SOFT_SPRITE_ARC *ssa);
static void SetFnoteData( FNOTE_DATA *fnote, POKEMON_PARAM *pp );
static void CommSendPerapVoice( PERAPVOICE *pv );
static void TimeIconAdd( TRADELIST_WORK *tlw );
static void TimeIconDel( TRADELIST_WORK *tlw );
static int  TradeTemochiCheck( TRADELIST_WORK *wk );
static void TimeoutStart( TRADELIST_WORK *wk );
static void TimeoutErrorCheck( TRADELIST_WORK *wk );



static void Regist_WordSetPokeName(WORDSET *wordset, POKEPARTY *party, int start );
static void Print_MainPokeName(GF_BGL_BMPWIN *win, WORDSET *wordset, MSGDATA_MANAGER *manager, POKEPARTY *party, int start );
static void TransPokeStr_SubLcd(GF_BGL_BMPWIN *win, int side, POKEPARTY *party, int pos, TRADELIST_WORK *wk);
static void PokemonDataExchange(POKEPARTY *my, POKEPARTY *your, int mysel, int yoursel, TRADELIST_PARAM *param);
static void FreeClact( TRADELIST_WORK *wk );
static void PokemonName_Get_Write( TRADELIST_WORK *wk);
static void PokeIconFree( TRADELIST_WORK *wk );
static void CursorSubLcd_Update(TRADELIST_WORK *wk);
static void PokeStr_SubLcdOff(GF_BGL_BMPWIN *win, int side, TRADELIST_WORK *wk);
static void GetPokeInfo( POKEMON_PARAM *pp, POKE_INFO* info );
static void Clact_SetPos( CLACT_WORK_PTR clact, int x, int y );
static int NidoranSpecialCheck( POKE_INFO *info, POKEPARTY *party, int pos, int sex );
static void TradeListCommSpRibbonDate(  SAVEDATA *sv );


static int TradeListPokemonExchange( TRADELIST_WORK *wk );
static int TradeListMain( TRADELIST_WORK *wk );
static void LoadPokeIcon(POKEPARTY *party, int start, TRADELIST_WORK *wk);


static int trade_seq_normal(TRADELIST_WORK *wk);
static int trade_seq_end(TRADELIST_WORK *wk );
static int trade_seq_mypoke(TRADELIST_WORK *wk );
static int trade_seq_friendpoke(TRADELIST_WORK *wk );
static int trade_seq_endyesno_wait(TRADELIST_WORK *wk);
static int trade_seq_endyesno(TRADELIST_WORK *wk );
static int trade_seq_mypoke_menu(TRADELIST_WORK *wk );
static int trade_seq_decide(TRADELIST_WORK *wk );
static int trade_seq_decide_wait(TRADELIST_WORK *wk );
static int trade_seq_friend_menu(TRADELIST_WORK *wk );
static int trade_seq_return_wait(TRADELIST_WORK *wk);
static int trade_seq_return(TRADELIST_WORK *wk);
static int trade_seq_trade_yesno(TRADELIST_WORK *wk );
static int trade_seq_trade_yesno_wait(TRADELIST_WORK *wk);
static int trade_seq_trade_yesno_result( TRADELIST_WORK *wk );
static int trade_seq_go_next( TRADELIST_WORK *wk );
static int trade_seq_save_text( TRADELIST_WORK *wk );
static int trade_seq_save_func( TRADELIST_WORK *wk );
static int trade_seq_save_wait( TRADELIST_WORK *wk );
static int trade_seq_icon_move( TRADELIST_WORK *wk );
static int trade_seq_icon_move_wait( TRADELIST_WORK *wk );
static int trade_seq_customball_yesno_wait(TRADELIST_WORK *wk);
static int trade_seq_customball_yesno(TRADELIST_WORK *wk );


static void trade_icon_reappear( TRADELIST_WORK *wk );

static void AnimePosSet(VecFx32 animpos[], int sx, int sy, int ex, int ey);
static void PokeIconPosSet( CLACT_WORK_PTR icon, CLACT_WORK_PTR item, CLACT_WORK_PTR cball, int count, VecFx32 pos[], POKE_INFO *info );
static void SubLcd_RightPanelOn( TRADELIST_WORK *wk, int pos );


static void SubLCD_ScrollFunc( TRADELIST_WORK *wk );
static void PokeNamePrint( GF_BGL_BMPWIN *win, POKEPARTY *party, int pos, int width, int print_sw );

static int trade_seq_friend_regist_del_yesno(TRADELIST_WORK* wk);
static int trade_seq_friend_regist_yesno(TRADELIST_WORK* wk);
static int trade_seq_friend_regist_init(TRADELIST_WORK* wk);
static int trade_seq_friend_regist_delmenu_init( TRADELIST_WORK* wk );
static int MainFunc( TRADELIST_WORK *wk );
static void poke_status_setup( TRADELIST_WORK *wk, int side );


static void CommSendFriendList( MYSTATUS *mystatus, FRIEND_LIST *friendlist, FRIEND_LIST *sendbuf );


static void ArcUtil_ScrnSetNoTrans(u32 fileIdx, u32 dataIdx, GF_BGL_INI* bgl, u32 frm, u32 offs, u32 transSize, BOOL compressedFlag, u32 heapID);

//============================================================================================
//	�O���[�o���ϐ�
//============================================================================================


#define POKE_NICKNAME_LEN	(10+1)

//============================================================================================
//	�v���Z�X�֐�
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
PROC_RESULT TradeListProc_Init( PROC * proc, int * seq )
{
	TRADELIST_WORK * wk;

	sys_VBlankFuncChange( NULL, NULL );	// VBlank�Z�b�g
	sys_HBlankIntrStop();	//HBlank���荞�ݒ�~

	GF_Disp_GX_VisibleControlInit();
	GF_Disp_GXS_VisibleControlInit();
	GX_SetVisiblePlane( 0 );
	GXS_SetVisiblePlane( 0 );

	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_TRADELIST, 0x50000+0x20000+2000 );

	wk = PROC_AllocWork( proc, sizeof(TRADELIST_WORK), HEAPID_TRADELIST );
	MI_CpuClearFast( wk, sizeof(TRADELIST_WORK) );
	wk->bgl = GF_BGL_BglIniAlloc( HEAPID_TRADELIST );
	
	// ������}�l�[�W���[����
	wk->PokeNameWordSet  = WORDSET_CreateEx( 12, POKE_NICKNAME_LEN*2, HEAPID_TRADELIST );
	wk->WindowStrWordSet = WORDSET_Create( HEAPID_TRADELIST );
	wk->SubLcdWordSet    = WORDSET_Create( HEAPID_TRADELIST );

	wk->MsgManager = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_dstrade_dat, HEAPID_TRADELIST );
	wk->subproc    = NULL;

	// ���[�N������
	InitWork(wk,proc);

	// �L�[���s�[�g�Ԋu�ύX
	sys_KeyRepeatSpeedSet( 4, 8 );

	VramBankSet();
	BgInit( wk->bgl );
	// �P�x�ύX�Z�b�g
	WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, 16, 1, HEAPID_TRADELIST);



	BgGraphicSet( wk );

	// VBlank�֐��Z�b�g
	sys_VBlankFuncChange( VBlankFunc, wk );	



	// OBJ�L�����A�p���b�g�}�l�[�W���[������
	char_pltt_manager_init();

	// CellActor�V�X�e��������
	InitCellActor(wk);
	
	// CellActro�\���o�^
	SetCellActor(wk);

	// BMPWIN�o�^�E�`��
	TradeList_BmpMessageSet(wk->bgl,wk->TradeListWin, wk->param->config);

	//FIELDSYS_WORK��tradelist_work��o�^
	wk->fsys = wk->param->fsys;
	SetFieldSys_in_TradeWorkPtr(wk->fsys, wk);

	// �ʐM�ҋ@���c
	TradeListWindowPrint(
		&wk->TradeListWin[BMP_M_MES3_WIN],
		mes_dstrade_04_01,
		FONT_TALK,
		wk->MsgManager,
		wk->PokeNameWordSet
	);

	// �ʐM�R�}���h���������X�g�p�ɕύX
	CommCommandTradeListInitialize(wk->fsys);

	// �e��������u��������ʐM���v�Ƀr�[�R����������
//	if(CommGetCurrentID()==0){
//		Union_BeaconChange( UNION_PARENT_MODE_TRADENOW );
//	}
		
	GF_BGL_VisibleSet( GF_BGL_FRAME0_M, VISIBLE_ON );
	GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);	//OBJ�ʂn�m
	
	CommErrorCheck(HEAPID_TRADELIST, wk->bgl);

	WirelessIconEasy();


	// �T�E���h�f�[�^�Z�b�g(�V�[�����ύX����Ȃ����͉������Ȃ�)
	// "�Đ�����BGM���Œ�ɂ��Ă���̂ŁA"
	// "�|�P�����������X�g��ʂ����j�I�����[���ȊO����Ă΂�邱�Ƃ������Ă̓_���I"
	if( GF_RTC_IsNightTime() == FALSE ){			//FALSE=���ATRUE=��
		Snd_DataSetByScene( SND_SCENE_FIELD, SEQ_PC_01, 1 );
	}else{
		Snd_DataSetByScene( SND_SCENE_FIELD, SEQ_PC_02, 1 );
	}

	return PROC_RES_FINISH;
}


//------------------------------------------------------------------
/**
 * �|�P�����A�C�R����]������i�|�P�����̖��O�̎������j
 *
 * @param   chara	�L�����N�^�[�t�@�C���A�h���X
 * @param   pal		�p���b�g�t�@�C���A�h���X
 * @param   pokeno	�|�P�����̊J��NO
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void TransPokeIconCharaPal( NNSG2dCharacterData *chara, int pokeno, int form, int tamago, int no, CLACT_WORK_PTR icon)
{
	u8 *pokepal;

	// �L�����N�^�[�]��
	GX_LoadOBJ(chara->pRawData, (POKEICON_VRAM_OFFSET+no*POKEICON_TRANS_CELL)*0x20, POKEICON_TRANS_SIZE);
	OS_Printf("�A�C�R���L�����]��NO. %d\n",no);
	
	
	// �p���b�g�ݒ�
	CLACT_PaletteOffsetChg( icon,  PokeIconPalNumGet( pokeno, form, tamago )+POKEICON_PAL_OFFSET);

//	pokepal = (u8*)pal->pRawData;
//	GX_LoadOBJPltt((void*)(pokepal + PokeIconPaletteIDGet(pokeno)*0x20), (POKEICON_PAL_OFFSET+no)*0x20, 0x20);

}

static const STRCODE endstr[]={ya_,me_,ru_,EOM_};

//------------------------------------------------------------------
/**
 * �����̒ʐM����̖��O�`��
 *
 * @param   bgl		
 * @param   win		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void TrainerNamePrint( GF_BGL_BMPWIN *win )
{
	STRBUF *MyNameBuf, *FriendNameBuf, *EndBuf;
	// Todo ���O�̎擾���@�̃C���^�[�t�F�[�X���͂����肵���g�ݑւ���
	// 
	MYSTATUS *mystatus, *friendstatus;

	

	mystatus     = CommInfoGetMyStatus(CommGetCurrentID());
	friendstatus = CommInfoGetMyStatus(CommGetCurrentID()^1);
	
	MyNameBuf     = MyStatus_CreateNameString(mystatus,     HEAPID_TRADELIST);
	FriendNameBuf = MyStatus_CreateNameString(friendstatus, HEAPID_TRADELIST);

	EndBuf    = STRBUF_Create( TRADELISTSTR_MAX, HEAPID_TRADELIST );
	STRBUF_SetStringCode( EndBuf, endstr );
	

	// �����̖��O
	TradeListPrint(&win[BMP_M_MYNAME_WIN], MyNameBuf, TRADELIST_NAME_W, MSG_ALLPUT, CENTER_PRINT,1);
	// ����̖��O
	TradeListPrint(&win[BMP_M_FRIENDNAME_WIN], FriendNameBuf, TRADELIST_NAME_W, MSG_ALLPUT, CENTER_PRINT,1);
	// �u�����v
	TradeListPrint(&win[BMP_M_ENDSTR_WIN], EndBuf, TRADELIST_ENDSTR_W, MSG_ALLPUT, CENTER_PRINT,1);

	STRBUF_Delete( EndBuf );
	STRBUF_Delete( FriendNameBuf );
	STRBUF_Delete( MyNameBuf);
}

static const STRCODE testname[]={HU_,SI_,GI_,DA_,NE_,EOM_};
static const STRCODE testlevel[]={L__,v__,spc_,n1_,n0_,n0_,EOM_};
static const STRCODE testmotimono[]={mo_,ti_,mo_,no_,EOM_};
static const STRCODE testitem[]={HA_,bou_,BA_,bou_,ME_,bou_,RU_,EOM_};

//------------------------------------------------------------------
/**
 * $brief   ����ʕ����\��
 *
 * @param   win			
 * @param   cardno		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void PokemonInfoSubPrint( TRADELIST_WORK *wk, int page )
{
	STRBUF *MotimonoBuf;

	// ��������
	MotimonoBuf = MSGMAN_AllocString( wk->MsgManager, mes_dstrade_05_05 );

	TradeListPrint(&wk->TradeListWin[BMP_S_MOTIMONO0_WIN+page], MotimonoBuf, SUB_MOTIMONOSTR_W, MSG_ALLPUT, LEFT_PRINT,0);

	STRBUF_Delete( MotimonoBuf );
	               
}




//------------------------------------------------------------------
/**
 * @brief   �X�e�[�^�X��ʂ���̕��A�p����
 *
 * @param   wk		
 *
 * @retval  none	
 */
//------------------------------------------------------------------
static void TradeListReturn( TRADELIST_WORK *wk )
{
	// VRAM�ݒ�
	VramBankSet();

	// BG�o���N�Đݒ�
	BgInit( wk->bgl );

	// �O���t�B�b�N�]��
	BgGraphicSet( wk );

	// �|�P�������`��
	PokemonName_Get_Write( wk );

	// �g���[�i�[��
	TrainerNamePrint( wk->TradeListWin );

	// ���C����ʂ̉�b�E�C���h�E����
	TalkWinGraphicSet( wk->bgl, GF_BGL_FRAME0_M, TALKWIN_FRAME_OFFSET, 10, CONFIG_GetWindowType(wk->param->config), HEAPID_TRADELIST );           
	MenuWinGraphicSet( wk->bgl, GF_BGL_FRAME0_M, MENUWIN_FRAME_OFFSET, 11, 0, HEAPID_TRADELIST );


	// �|�P������I��ł�������
	TradeListWindowPrint(
		&wk->TradeListWin[BMP_M_MES1_WIN],
		mes_dstrade_02_01,FONT_TALK,
		wk->MsgManager,
		wk->PokeNameWordSet
	);


	// ����ON
	GF_BGL_VisibleSet( GF_BGL_FRAME0_S, VISIBLE_ON );
	GF_BGL_VisibleSet( GF_BGL_FRAME1_S, VISIBLE_ON );
	GF_BGL_VisibleSet( GF_BGL_FRAME2_S, VISIBLE_ON );
	GF_Disp_GXS_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);	//OBJ�ʂn�m

	// �����ON
	GF_BGL_VisibleSet( GF_BGL_FRAME0_M, VISIBLE_ON );
	GF_BGL_VisibleSet( GF_BGL_FRAME1_M, VISIBLE_ON );
	GF_BGL_VisibleSet( GF_BGL_FRAME2_M, VISIBLE_ON );
	GF_BGL_VisibleSet( GF_BGL_FRAME3_M, VISIBLE_ON );
	GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ,  VISIBLE_ON);	//OBJ�ʂn�m



	// �L�����p���b�g�}�l�[�W���[������
	char_pltt_manager_init();

	// CellActor�V�X�e��������
	InitCellActor(wk);

	// CellActro�\���o�^
	SetCellActor(wk);


	// �A�C�R���f�[�^��ǂݍ���œ]��
	LoadPokeIcon( wk->MyPokeParty,     0, wk);
	LoadPokeIcon( wk->FriendPokeParty, 6, wk);

	// �J�[�\���\��ON
	CLACT_SetDrawFlag(wk->clActWork[0], 1);
	CLACT_SetDrawFlag(wk->clActWork[1], 1);

	// VBlank�֐��Z�b�g
	sys_VBlankFuncChange( VBlankFunc, wk );	

}

//------------------------------------------------------------------
/**
 * @brief   �|�P�������O�擾���`��
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void PokemonName_Get_Write( TRADELIST_WORK *wk)
{

	// �|�P�������O�o�^
	Regist_WordSetPokeName(wk->PokeNameWordSet, wk->MyPokeParty,     0 );
	Regist_WordSetPokeName(wk->PokeNameWordSet, wk->FriendPokeParty, 6 );
	
	// �|�P�������OBmp�`��
	Print_MainPokeName(&wk->TradeListWin[BMP_M_MYPOKENAME0_WIN],wk->PokeNameWordSet,wk->MsgManager,wk->MyPokeParty,     0);
	Print_MainPokeName(&wk->TradeListWin[BMP_M_FRIENDPOKENAME0_WIN],wk->PokeNameWordSet,wk->MsgManager,wk->FriendPokeParty, 6);

	TradeListMakeScreenSet(wk->bgl, PokeParty_GetPokeCount(wk->MyPokeParty), PokeParty_GetPokeCount(wk->FriendPokeParty));

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

PROC_RESULT TradeListProc_Main( PROC * proc, int * seq )
{
	TRADELIST_WORK * wk  = PROC_GetWork( proc );
	PROC_RESULT    proc_result = PROC_RES_CONTINUE;

	switch( *seq ){
	case SEQ_IN:
		if( WIPE_SYS_EndCheck()){
			*seq = SEQ_MAIN;
			TrainerNamePrint( wk->TradeListWin );
			OS_Printf("�|�P�p�[�e�B�[ = %d\n",PokeParty_GetPokeCount(wk->MyPokeParty));
		}
		break;

	case SEQ_MAIN:
		switch(wk->tradeseq){
		// �|�P�����f�[�^����
		case TRADELIST_SEQ_POKEMON_EXCHANGE:
			wk->tradeseq = TradeListPokemonExchange(wk);
			break;
		//���C�����[�v
		case TRADELIST_SEQ_MAIN:
			wk->tradeseq = TradeListMain(wk);
			TouchFunc(wk);
			break;
		// �������X�g�I��
		case TRADELIST_SEQ_END:
			WIPE_SYS_Start(WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, 8, 1, HEAPID_TRADELIST);
			*seq = SEQ_OUT;
			break;

		// �X�e�[�^�X�J�ڗp�t�F�[�h
		case TRADELIST_SEQ_STATUS_INFADE:
			WIPE_SYS_Start(WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, 8, 1, HEAPID_TRADELIST);
			wk->tradeseq = TRADELIST_SEQ_STATUS_INFADE_WAIT;
			break;
		// �t�F�[�h�҂�
		case TRADELIST_SEQ_STATUS_INFADE_WAIT:
			if( WIPE_SYS_EndCheck() ){	
				
				PokeIconFree( wk );
				FreeClact( wk );
				BgExit( wk->bgl );
				wk->subseqflag = 1;
				wk->tradeseq = TRADELIST_SEQ_STATUS;

				OS_Printf("CursorPos0 = %d, CursorPos1 = %d\n", wk->cursor_pos[0], wk->cursor_pos[1]);
				poke_status_setup( wk, wk->cursor_pos[0]/6 );
			}
			break;
		// �X�e�[�^�X��ʎ��s
		case TRADELIST_SEQ_STATUS:
			if( ProcMain( wk->subproc ) ){
				PROC_Delete( wk->subproc );
				
				// BG�OAM�V�X�e���č\�z
				TradeListReturn(wk);
				wk->subseqflag = 0;
				wk->cursor_pos[0] = wk->statusParam.pos+wk->status_side*6;

				// �J�[�\���E����ʔ��f
				CursorSubLcd_Update(wk);
				CursorPosChange(wk->cursor_pos[0],wk->clActWork[0], 0);

				WirelessIconEasy();
				
				wk->tradeseq = TRADELIST_SEQ_STATUS_OUTFADE;
			}
			break;

		// ���A�t�F�[�h
		case TRADELIST_SEQ_STATUS_OUTFADE:
			WIPE_SYS_Start(WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, 8, 1, HEAPID_TRADELIST);
			wk->tradeseq = TRADELIST_SEQ_STATUS_OUTFADE_WAIT;
			break;

		// ���A�t�F�[�h�҂�
		case TRADELIST_SEQ_STATUS_OUTFADE_WAIT:
			if( WIPE_SYS_EndCheck() ){	
				wk->tradeseq = TRADELIST_SEQ_MAIN;
			}
			break;
		}

		break;

	// ���C���V�[�P���X�I��
	case SEQ_OUT:
		if( WIPE_SYS_EndCheck() ){
			proc_result = PROC_RES_FINISH;
		}
		break;
	}
	
	// �X�e�[�^�X��ʂ��Ă΂�Ă���Ƃ��͎��s���Ȃ�
	if(!wk->subseqflag){
		// �T�u���BG3�ʃX�N���[������
		SubLCD_ScrollFunc( wk );
		// �Z���A�N�^�[�풓�֐�
		CLACT_Draw( wk->clactSet );
	}

	CommErrorCheck(HEAPID_TRADELIST, wk->bgl);					// �ʐM�G���[�`�F�b�N

	return proc_result;
}


//------------------------------------------------------------------
/**
 * WordSet�Ƀ|�P�����̖��O��o�^����
 *
 * @param   wordset		
 * @param   party		
 * @param   start		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void Regist_WordSetPokeName(WORDSET *wordset, POKEPARTY *party, int start )
{
	int i;
	for(i=0;i<PokeParty_GetPokeCount(party);i++){
		WORDSET_RegisterPokeNickName( wordset, i+start, PPPPointerGet(PokeParty_GetMemberPointer(party, i)));
	}
}

//------------------------------------------------------------------
/**
 * �|�P�����P�Q�̕���]������
 *
 * @param   win		
 * @param   wordset		
 * @param   manager		
 * @param   party		
 * @param   start		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void Print_MainPokeName(GF_BGL_BMPWIN *win, WORDSET *wordset, MSGDATA_MANAGER *manager, POKEPARTY *party, int start )
{
	int i;
	for(i=0;i<PokeParty_GetPokeCount(party);i++){
		STRBUF *name = MSGDAT_UTIL_AllocExpandString( wordset, manager, mes_dstrade_01_02+start+i, HEAPID_TRADELIST );
		TradeListPrint(&win[i], name, TRADELIST_POKENAME_W, MSG_ALLPUT, CENTER_PRINT,0);
		STRBUF_Delete( name );
	}
}

//------------------------------------------------------------------
/**
 * @brief   �|�P�����A�C�R���̓]��
 *
 * @param   party		
 * @param   start		
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void LoadPokeIcon(POKEPARTY *party, int start, TRADELIST_WORK *wk)
{
	int i;
	int pos;
	
	for(i=0;i<PokeParty_GetPokeCount(party);i++){
		pos = i+start;

		wk->PokeIconBuf[pos] = ArcUtil_CharDataGet( ARC_POKEICON, 
			PokeIconCgxArcIndexGetByMonsNumber( wk->pokeInfo[pos].exist, wk->pokeInfo[pos].tamago, wk->pokeInfo[pos].form ), 
			0, 
			&wk->PokeIconCharaDat[pos], 
			HEAPID_TRADELIST );
//		OS_Printf("pos %d: PokeIconBuf size = %d\n",pos,sys_GetMemoryBlockSize(wk->PokeIconBuf[pos]));
		DC_FlushRange(wk->PokeIconCharaDat[pos]->pRawData,0x20*4*4);
		TransPokeIconCharaPal(wk->PokeIconCharaDat[pos], wk->pokeInfo[pos].exist, 
							  wk->pokeInfo[pos].form, 
							  wk->pokeInfo[pos].tamago, 
							  pos, wk->PokeIconActWork[pos]);
		CLACT_SetDrawFlag(wk->PokeIconActWork[pos], 1);

		// �A�C�e���A�C�R���̕\���E���[���E�A�C�e���̂ǂ��炩
		if(wk->pokeInfo[pos].item==0){
			// �A�C�e���͖����̂Ŕ�\��
			CLACT_SetDrawFlag(wk->PokeItemActWork[pos], 0);
		}else{
			// �A�C�e�������[���ɂ��킹�ĉ摜�`�F���W
			CLACT_SetDrawFlag(wk->PokeItemActWork[pos], 1);
			CLACT_AnmChg( wk->PokeItemActWork[pos], 3+wk->pokeInfo[pos].item-1 );
		}
		
		// �{�[���J�X�^�}�C�Y�����Ă��邩�H
		if(wk->pokeInfo[pos].customball==0){
			CLACT_SetDrawFlag(wk->PokeCBallActWork[pos], 0);
		}else{
			// ���Ă�i�J�X�^���{�[���\���j
			CLACT_SetDrawFlag(wk->PokeCBallActWork[pos], 1);
			CLACT_AnmChg( wk->PokeCBallActWork[pos], 21 );
		}
	}
	
	// �c��͑S�Ĕ�\��
	for(;i<6;i++){
		CLACT_SetDrawFlag(wk->PokeIconActWork[i+start], 0);
		CLACT_SetDrawFlag(wk->PokeItemActWork[i+start], 0);
		CLACT_SetDrawFlag(wk->PokeCBallActWork[i+start], 0);
	}
}

enum{
	EXCHANGE_SEQ_BEFORE_SYNCRO=0,
	EXCHANGE_SEQ_BEFORE_SYNCRO_WAIT,
	EXCHANGE_SEQ_SAVE_WAIT_RECV,
	EXCHANGE_SEQ_SAVE_WAIT_CLEAR,
	EXCHANGE_SEQ_SAVE_START,
	EXCHANGE_SEQ_SAVE_WAIT,
	EXCHANGE_SEQ_START_PRE_SYNC,
	EXCHANGE_SEQ_START_PRE_SYNC_WAIT,
	EXCHANGE_SEQ_START,
	EXCHANGE_SEQ_WAIT,
	EXCHANGE_SEQ_FINISH,
	EXCHANGE_SEQ_DATA_SETUP,
	EXCHANGE_SEQ_FRIENDLIST,
	EXCHANGE_SEQ_FRIENDLIST_END,
	EXCHANGE_SEQ_PERAPVOICE,
	EXCHANGE_SEQ_PERAPVOICE_END,

	EXCHANGE_SEQ_IN,
	EXCHANGE_SEQ_FADE1,
	EXCHANGE_SEQ_FADE2,
	EXCHANGE_SEQ_FADE3,
	EXCHANGE_SEQ_FADE4,
};

#define TRADELIST_COMM_SYNCHRONIZE1_NO	( 80 )
#define TRADELIST_COMM_SYNCHRONIZE2_NO	( 81 )

#define TRADE_PARENT_WAIT				( 60 )
//------------------------------------------------------------------
/**
 * �������X�g�|�P�����f�[�^���L����
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int TradeListPokemonExchange( TRADELIST_WORK *wk )
{
	// �^�C���A�E�g����
	TimeoutErrorCheck( wk );
	
	
	switch(wk->exchangeseq){

	// �����s���O�ɒʐM����������i�Z�[�u���Ȃ��̂ŁA�����Ō����f����҂j
	case EXCHANGE_SEQ_BEFORE_SYNCRO:
		CommTimingSyncStart( TRADELIST_COMM_SYNCHRONIZE1_NO );

		// �\�t�g���Z�b�g�s�\�ɂ���
		sys.DontSoftReset = 1;
		
		// ���ԃA�C�R���\��
		TimeIconAdd( wk );

		wk->exchangeseq++;
		break;

	// �ŏ��̒ʐM�����҂�
	case EXCHANGE_SEQ_BEFORE_SYNCRO_WAIT:
		if(CommIsTimingSync(TRADELIST_COMM_SYNCHRONIZE1_NO)){
			OS_Printf("�������X�g�Ăяo�� %d���\n",wk->param->times);
			if(wk->param->times==0){
				wk->exchangeseq = EXCHANGE_SEQ_START_PRE_SYNC;
				OS_Printf("�Z�[�u�����Ńf�[�^���M\n");
			}else{
				wk->exchangeseq = EXCHANGE_SEQ_SAVE_WAIT_RECV;
				OS_Printf("�Z�[�u��\n");
			}

			if(CommGetCurrentID()==0){
				// �P�b�ȓ��ŃZ�[�u�܂ł̃Y���𐶐�����
				TradeListCommSend( CommGetCurrentID(), CT_SAVE_WAIT_TIME, gf_p_rand(TRADE_PARENT_WAIT)+3);
				OS_Printf("�e�@�Ȃ̂ŃZ�[�u���炵�R�}���h���M\n");
			}
			TradeListCommSpRibbonDate(  wk->savedata );
			OS_Printf("���{����񑗐M\n");

			// �^�C���A�E�g�J�E���g�J�n
			TimeoutStart(wk);
#ifdef DEBUG_TIMEOUT
			wk->exchangeseq = 300;
#endif

		}
		break;
	// �Z�[�u���s�����͂܂��͐e�@����Z�[�u�܂ł̑ҋ@���Ԃ���M���Ă��邩�m�F����
	case EXCHANGE_SEQ_SAVE_WAIT_RECV:
		if(wk->savePreWait!=0){
			OS_Printf("savePreWait = %d\n", wk->savePreWait);
			wk->exchangeseq++;
		}
		break;
	case EXCHANGE_SEQ_SAVE_WAIT_CLEAR:

		// �Z�[�u�܂ł̑ҋ@���Ԃ͐e�@�������œn�����߃^�C�~���O������x�ɃY����
		wk->savePreWait--;
		if(wk->savePreWait==0){
			wk->exchangeseq = EXCHANGE_SEQ_SAVE_START;
			OS_Printf("�Z�[�u�����҂��I��\n");
		}
		break;

	// 2��ڈȍ~�̌������X�g�̓Z�[�u���s��
	case EXCHANGE_SEQ_SAVE_START:
		OS_Printf("�Z�[�u�J�n\n");
		CommSyncronizeSaveInit( &wk->commSaveSeq );
		wk->exchangeseq++;
		break;
	case EXCHANGE_SEQ_SAVE_WAIT:
		if(CommSyncronizeSave( wk->savedata, SVBLK_ID_MAX, &wk->commSaveSeq )){
			wk->exchangeseq++;
		}
		break;

	// �|�P�����f�[�^���M�J�n�O�̓���
	case EXCHANGE_SEQ_START_PRE_SYNC:
        CommSetWifiBothNet(TRUE); // wifi�̒ʐM��񓯊����瓯���� ohno
		CommTimingSyncStart( TRADELIST_COMM_SYNCHRONIZE2_NO );
		wk->exchangeseq++;
		break;
	case EXCHANGE_SEQ_START_PRE_SYNC_WAIT:
		if(CommIsTimingSync(TRADELIST_COMM_SYNCHRONIZE2_NO)){
			wk->exchangeseq++;
		}
		break;

	// �f�[�^����M�J�n
	case EXCHANGE_SEQ_START:
		wk->exchange_work         = 0;
		wk->exchange_finish       = 0;
		wk->exchange_friend_count = 0;
		if(CommGetCurrentID()==1){
			// ��e�ʑ��M�J�n
			TradeListCommSendPokeData(CommGetCurrentID(), wk->MyPokeParty, wk->exchange_work);
			wk->exchange_work++;
		}
		wk->exchangeseq++;
//		wk->exchangeseq = EXCHANGE_SEQ_IN;

		break;
	case EXCHANGE_SEQ_WAIT:
		if(wk->exchange_finish!=0){
//			if(CommGetCurrentID()==0){
//				TradeListCommSend(CommGetCurrentID(),CT_TRADE_START, 0);
//			}
			wk->exchangeseq = EXCHANGE_SEQ_FINISH;
		}
		break;
	case EXCHANGE_SEQ_FINISH:
//		if(wk->exchange_finish==2){
			wk->exchangeseq++;

			// �|�P�����̖��O�擾��BMP�`��
			PokemonName_Get_Write(wk);

//		}
		break;
	// �擾�����f�[�^�����ɕ\���p�f�[�^���W�߂�
	case EXCHANGE_SEQ_DATA_SETUP:
		{
				int i,item;
				for(i=0;i<13;i++){
					wk->pokeInfo[i].exist = 0;
				}
				for(i=0;i<PokeParty_GetPokeCount(wk->MyPokeParty);i++){
					POKEMON_PARAM *pp = PokeParty_GetMemberPointer(wk->MyPokeParty, i);

					// �����̃|�P����
					GetPokeInfo(pp, &wk->pokeInfo[i]);
//					OS_Printf("%d cball = %d\n", i, wk->pokeInfo[i].customball);
					
				}
				for(i=0;i<PokeParty_GetPokeCount(wk->FriendPokeParty);i++){
					POKEMON_PARAM *pp = PokeParty_GetMemberPointer(wk->FriendPokeParty, i);

					// ����̃|�P����
					GetPokeInfo( pp, &wk->pokeInfo[i+6] );
//					OS_Printf("%d cball = %d\n", i+6, wk->pokeInfo[i+6].customball);
				}
				wk->pokeInfo[12].exist = 1;
		}
		wk->exchangeseq++;
		break;
	case EXCHANGE_SEQ_FRIENDLIST:
		CommSendFriendList( CommInfoGetMyStatus(CommGetCurrentID()), wk->friendlist, &wk->SendList );
		wk->exchangeseq++;
		break;
	case EXCHANGE_SEQ_FRIENDLIST_END:
		if(wk->exchange_finish==3){
			wk->exchangeseq++;
		}
		break;
	case EXCHANGE_SEQ_PERAPVOICE:
		CommSendPerapVoice( SaveData_GetPerapVoice(wk->savedata) );
		wk->exchangeseq++;
		break;
	case EXCHANGE_SEQ_PERAPVOICE_END:
		if(wk->exchange_finish==4){
			wk->exchangeseq++;
			GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ,  VISIBLE_OFF);	//OBJ�ʂn�m

			// �A�C�R���f�[�^��ǂݍ���œ]��
			LoadPokeIcon( wk->MyPokeParty,     0, wk);
			LoadPokeIcon( wk->FriendPokeParty, 6, wk);

			{
				int i;
				for(i=0;i<2;i++){
					CLACT_SetDrawFlag( wk->clActWork[i], 1 );
				}
			}
		}
//		TimeWaitIconDel(wk->timeWaitWork);
		break;
	case EXCHANGE_SEQ_IN:
		ChangeBrightnessRequest( 8, 0, -16, PLANEMASK_BG1|PLANEMASK_BG2|PLANEMASK_BG3|PLANEMASK_OBJ, MASK_MAIN_DISPLAY );
		GF_BGL_VisibleSet( GF_BGL_FRAME1_M, VISIBLE_ON );
		GF_BGL_VisibleSet( GF_BGL_FRAME2_M, VISIBLE_ON );
		GF_BGL_VisibleSet( GF_BGL_FRAME3_M, VISIBLE_ON );
		GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ,  VISIBLE_ON);	//OBJ�ʂn�m
		
		wk->exchangeseq++;
		break;
	case EXCHANGE_SEQ_FADE1:
		if( IsFinishedBrightnessChg(MASK_MAIN_DISPLAY) ){
			POKEMON_PARAM *pp = PokeParty_GetMemberPointer(wk->MyPokeParty, 0);

			// ����ʗp�|�P�����O���t�B�b�N�]��
			wk->vblankreq = TransPokeGra_SubLcd(0,pp, wk->PokeGra[0], &wk->PokeGraSsa[0] );
			TransPokeStr_SubLcd(wk->TradeListWin,0,wk->MyPokeParty, 0, wk);
			wk->exchangeseq++;
		}
		break;
	case EXCHANGE_SEQ_FADE2:
		ChangeBrightnessRequest( 8, 0, -16, PLANEMASK_BG0|PLANEMASK_BG1|PLANEMASK_BG2|PLANEMASK_OBJ, MASK_SUB_DISPLAY );
		GF_BGL_VisibleSet( GF_BGL_FRAME0_S, VISIBLE_ON );
		GF_BGL_VisibleSet( GF_BGL_FRAME1_S, VISIBLE_ON );
		GF_BGL_VisibleSet( GF_BGL_FRAME2_S, VISIBLE_ON );
		GF_Disp_GXS_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);	//OBJ�ʂn�m

		wk->exchangeseq++;

		// ���ԃA�C�R���\��
		TimeIconDel( wk );

		break;
	case EXCHANGE_SEQ_FADE3:
		if( IsFinishedBrightnessChg(MASK_SUB_DISPLAY) ){

			BmpTalkWinClear( &wk->TradeListWin[BMP_M_MES3_WIN], WINDOW_TRANS_ON );

			// �|�P������I��ł�������
			GF_BGL_ScrFill(	wk->bgl, GF_BGL_FRAME0_M, 0, 0, 0, 32, 24,  0);
			TradeListWindowPrint(
				&wk->TradeListWin[BMP_M_MES1_WIN],
				mes_dstrade_02_01,FONT_TALK,
				wk->MsgManager,
				wk->PokeNameWordSet
			);

			OS_Printf("�|�P�p�[�e�B�[ = %d\n",PokeParty_GetPokeCount(wk->MyPokeParty));

			// �\�t�g���Z�b�g�\�ɂ���
			sys.DontSoftReset = 0;


			return TRADELIST_SEQ_MAIN;
		}
		break;
	}

	return TRADELIST_SEQ_POKEMON_EXCHANGE;
}


//------------------------------------------------------------------
/**
 * @brief   �Ă����|�P�����̕\���Ɏg�������W�߂�
 *
 * @param   pp		
 * @param   info		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void GetPokeInfo( POKEMON_PARAM *pp, POKE_INFO* info )
{
	int fastflag, item;

	// �������t���OON
	fastflag = PokeParaFastModeOn( pp );
	info->monsball   = PokeParaGet( pp, ID_PARA_get_ball,    NULL );
	info->exist      = PokeParaGet( pp, ID_PARA_monsno,      NULL );
	info->form       = PokeParaGet( pp, ID_PARA_form_no,     NULL );
	info->tamago     = PokeParaGet( pp, ID_PARA_tamago_flag, NULL );
	info->sex        = PokeParaGet( pp, ID_PARA_sex,         NULL );
	info->customball = PokeParaGet( pp, ID_PARA_cb_id,       NULL );
	item             = PokeParaGet( pp, ID_PARA_item,        NULL );

	// �������t���OOFF
	PokeParaFastModeOff( pp, fastflag );

	// ���]�t���O�擾
	if( info->exist!=0 ){
		info->reverse = PokePersonalParaGet( info->exist, ID_PER_reverse );
	}

	// ���[���`�F�b�N
	if(item!=0){
		info->item = ItemMailCheck( item )+1;	// ���[����������Q�Aitem��������P
	}
	

}
//------------------------------------------------------------------
/**
 * @brief   �E���̃p�l����`�悷��
 *
 * @param   wk		
 *
 * @retval  static		
 */
//------------------------------------------------------------------
static void SubLcd_RightPanelOn( TRADELIST_WORK *wk, int pos )
{
	POKEMON_PARAM *pp = PokeParty_GetMemberPointer(wk->FriendPokeParty, pos%6 );

	// 10x10�|�P�����摜�]��
	wk->vblankreq = TransPokeGra_SubLcd(1, pp,wk->PokeGra[pos/6], &wk->PokeGraSsa[pos/6] );

	TransPokeStr_SubLcd(wk->TradeListWin,1,wk->FriendPokeParty, pos%6, wk);
	// �����X�^�[�{�[���`�F���W
	CLACT_AnmChg( wk->SubLCDIconActWork[3], wk->pokeInfo[pos].monsball+CELL_MONSTER_BALL_NO-1 );


}


//------------------------------------------------------------------
/**
 * @brief    ����ʂ�]������
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void CursorSubLcd_Update(TRADELIST_WORK *wk)
{
	// �J�[�\�����f�����i�ړ����Ă��牺��ʂ̏��������ցj
		if(wk->cursor_pos[0]!=12){
			// �|�P�����摜�]��
			if(wk->cursor_pos[0]<6){
				POKEMON_PARAM *pp = PokeParty_GetMemberPointer(wk->MyPokeParty, wk->cursor_pos[0] );

				// 10x10�|�P�����摜�]��
				wk->vblankreq = TransPokeGra_SubLcd(0, pp, wk->PokeGra[wk->cursor_pos[0]/6], &wk->PokeGraSsa[wk->cursor_pos[0]/6] );
				TransPokeStr_SubLcd(wk->TradeListWin,0,wk->MyPokeParty,    wk->cursor_pos[0], wk);

				// �E����\��
				PokeStr_SubLcdOff(wk->TradeListWin, 1, wk);
				CLACT_SetDrawFlag(wk->SubLCDIconActWork[3], 0);	

			}else{
				SubLcd_RightPanelOn( wk, wk->cursor_pos[0] );
				// ������\��
				PokeStr_SubLcdOff(wk->TradeListWin, 0, wk);
				CLACT_SetDrawFlag(wk->SubLCDIconActWork[2], 0);
			}
		}
		

}



//------------------------------------------------------------------
/**
 * �������X�g���C�����[�v
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int TradeListMain( TRADELIST_WORK *wk )
{
	// �J�[�\���ړ�
	if(wk->func!=NULL){
		wk->inputmode = wk->func(wk);
	}
	switch(wk->inputmode){
	case MODE_NORMAL:
		break;
	case MODE_END_SELECT:
		return TRADELIST_SEQ_END;
		break;
	case MODE_TRADE_SELECT:
		break;
	case MODE_STATUS_SELECT:
		return TRADELIST_SEQ_STATUS_INFADE;
		break;
	}


	// �����̃J�[�\���ړ�(�J�[�\�����ړ������牺��ʂ̃|�P�����\����ύX����j
	if(ViewChange(&wk->CommWork[0], &wk->cursor_pos[0], wk->clActWork[0], wk->pokeInfo,0)){
		CursorSubLcd_Update( wk );
	}

	// ����̃J�[�\���ړ�
	ViewChange(&wk->CommWork[1], &wk->cursor_pos[1], wk->clActWork[1], wk->pokeInfo,1);
	CursorColTrans(&wk->CursorPal);


	// �J�[�\���ʒu���W�𑗐M����
	TradeListCommDiffSend( wk, CT_CURSOR_POS, wk->cursor_pos[0]);

	return TRADELIST_SEQ_MAIN;
}



//------------------------------------------------------------------
/**
 * @brief   �Z���A�N�^�[����̃V�X�e�����
 *
 * @param   wk		
 *
 * @retval  none
 */
//------------------------------------------------------------------
static void FreeClact( TRADELIST_WORK *wk )
{
	int i;
	// �Z���A�N�^�[���\�[�X���
	// �L�����]���}�l�[�W���[�j��
	CLACT_U_CharManagerDelete(wk->resObjTbl[MAIN_LCD][CLACT_U_CHAR_RES]);
	CLACT_U_CharManagerDelete(wk->resObjTbl[SUB_LCD][CLACT_U_CHAR_RES]);

	// �p���b�g�]���}�l�[�W���[�j��
	CLACT_U_PlttManagerDelete(wk->resObjTbl[MAIN_LCD][CLACT_U_PLTT_RES]);
	CLACT_U_PlttManagerDelete(wk->resObjTbl[SUB_LCD][CLACT_U_PLTT_RES]);
		
	// �L�����E�p���b�g�E�Z���E�Z���A�j���̃��\�[�X�}�l�[�W���[�j��
	for(i=0;i<CLACT_RESOURCE_NUM;i++){
		CLACT_U_ResManagerDelete(wk->resMan[i]);
	}
	// �Z���A�N�^�[�Z�b�g�j��
	CLACT_DestSet(wk->clactSet);

	//OAM�����_���[�j��
	REND_OAM_Delete();

	// �L�����}�l�[�W���[�A�p���b�g�}�l�[�W���[�폜
	DeleteCharManager();
	DeletePlttManager();

}

//------------------------------------------------------------------
/**
 * @brief   �|�P�����A�C�R���摜�̉��
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void PokeIconFree( TRADELIST_WORK *wk )
{
	int i;
	
	for(i=0;i<PokeParty_GetPokeCount(wk->MyPokeParty);i++){
		sys_FreeMemoryEz( wk->PokeIconBuf[i] );
	}
	for(i=0;i<PokeParty_GetPokeCount(wk->FriendPokeParty);i++){
		sys_FreeMemoryEz( wk->PokeIconBuf[i+6] );
	}


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
PROC_RESULT TradeListProc_End( PROC * proc, int * seq )
{
	TRADELIST_WORK  *wk          = PROC_GetWork( proc );
	TRADELIST_PARAM *param = PROC_GetParentWork(proc);

	int i;


	// �������邩���Ȃ����H
	param->result = wk->result;


	// �|�P�����A�C�R�����
	PokeIconFree( wk );

	// �������̕�������
	STRBUF_Delete(wk->MotimonoStr);

	sys_FreeMemoryEz(wk->FriendPokeParty);

	// �Z���A�N�^�[����̃V�X�e�����
	FreeClact( wk );

	// BMP�E�B���h�E�J��
	TradeListBmpExit(wk->TradeListWin);

	// BGL�폜
	BgExit( wk->bgl );

	// BGL���
	sys_FreeMemory( HEAPID_TRADELIST, wk->bgl );


	// ���b�Z�[�W�}�l�[�W���[�E���[�h�Z�b�g�}�l�[�W���[���
	MSGMAN_Delete( wk->MsgManager );
	WORDSET_Delete( wk->SubLcdWordSet );
	WORDSET_Delete( wk->WindowStrWordSet );
	WORDSET_Delete( wk->PokeNameWordSet );

	// STRBUF���
	STRBUF_Delete(wk->MyName);

	PROC_FreeWork( proc );				// ���[�N�J��

	sys_VBlankFuncChange( NULL, NULL );		// VBlank�Z�b�g

	sys_DeleteHeap( HEAPID_TRADELIST );

	// ���̊֐��Ăяo������2sync�����͒ʐM�G���[��ʂɔ�΂��Ȃ�

	return PROC_RES_FINISH;
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
	TRADELIST_WORK *wk = (TRADELIST_WORK*)work;

	// BGL����
	GF_BGL_VBlankFunc( wk->bgl );

	if(wk->vblankreq){
		int side = wk->vblankreq - 1;
		// OAM�pVRAM�ɓ]��
		GXS_LoadOBJ( wk->PokeGra[side], POKEGRA_VRAM_OFFSET + side*POKEGRA_VRAM_SIZE, POKEGRA_VRAM_SIZE);

		// �p���b�g�]��
		ArcUtil_PalSet( wk->PokeGraSsa[side].arc_no, wk->PokeGraSsa[side].index_pal, 
						PALTYPE_SUB_OBJ, 0x20*(2+side), 32, HEAPID_TRADELIST );
		
		wk->vblankreq = 0;
	}

	// �Z���A�N�^�[
	// Vram�]���}�l�[�W���[���s
	DoVramTransferManager();

	// �����_�����LOAM�}�l�[�W��Vram�]��
	REND_OAMTrans();	
	
	OS_SetIrqCheckFlag( OS_IE_V_BLANK );
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
static void VramBankSet(void)
{
	GF_BGL_DISPVRAM tbl = {
		GX_VRAM_BG_128_A,				// ���C��2D�G���W����BG
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
 * BG�ݒ�
 *
 * @param	ini		BGL�f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BgInit( GF_BGL_INI * ini )
{
	// BG SYSTEM
	{	
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D,
		};
		GF_BGL_InitBG( &BGsys_data );
	}

	// ----------���C�����-------------------
	// ���C����ʃE�C���h�EBG0
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME0_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME0_M );


	}

	// ���C����ʃ|�P��������������BG1
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x08000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME1_M );
	}

	// ���C����ʃp�l��BG2
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe000, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
			2, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME2_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME2_M );
	}

	// ���C����ʔw�iBG3
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe800, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
			3, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME3_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
	}

	// -----�T�u���-------------

	// �T�u��ʃe�L�X�gBG (CHAR)
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME0_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME0_S );
	}

	// �T�u��ʃJ�[�hBG (CHAR)
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
	}
	// �T�u��ʔw�iBG (CHAR)
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xd800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME2_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
	}

	GF_BGL_ClearCharSet( GF_BGL_FRAME0_M, 32, 0, HEAPID_TRADELIST );
	GF_BGL_ClearCharSet( GF_BGL_FRAME1_M, 32, 0, HEAPID_TRADELIST );
	GF_BGL_ClearCharSet( GF_BGL_FRAME0_S, 32, 0, HEAPID_TRADELIST );

	// BG�X�N���[�����W�X�^������
	{
		int i;
		for(i=0;i<4;i++){
			GF_BGL_ScrollSet( ini, GF_BGL_FRAME0_M+i, GF_BGL_SCROLL_X_SET, 0 );
			GF_BGL_ScrollSet( ini, GF_BGL_FRAME0_M+i, GF_BGL_SCROLL_Y_SET, 0 );
			GF_BGL_ScrollSet( ini, GF_BGL_FRAME0_S+i, GF_BGL_SCROLL_X_SET, 0 );
			GF_BGL_ScrollSet( ini, GF_BGL_FRAME0_S+i, GF_BGL_SCROLL_Y_SET, 0 );
		}
	}

	GF_BGL_VisibleSet( GF_BGL_FRAME0_M, VISIBLE_OFF );
	GF_BGL_VisibleSet( GF_BGL_FRAME1_M, VISIBLE_OFF );
	GF_BGL_VisibleSet( GF_BGL_FRAME2_M, VISIBLE_OFF );
	GF_BGL_VisibleSet( GF_BGL_FRAME3_M, VISIBLE_OFF );
	GF_BGL_VisibleSet( GF_BGL_FRAME0_S, VISIBLE_OFF );
	GF_BGL_VisibleSet( GF_BGL_FRAME1_S, VISIBLE_OFF );
	GF_BGL_VisibleSet( GF_BGL_FRAME2_S, VISIBLE_OFF );

	// ���ʂ̃n�[�h�E�F�A�E�C���h�E���nFF��
	GX_SetVisibleWnd( GX_WNDMASK_NONE  );


}


//------------------------------------------------------------------
/**
 * �|�P�����������X�g���[�N������
 *
 * @param   wk		NAMEIN_WORK*
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void InitWork(TRADELIST_WORK *wk, PROC * proc)
{
	TRADELIST_PARAM *param = PROC_GetParentWork(proc);
	wk->param         = param;
	

	wk->seq           = NAMEIN_MODE;

	wk->subseqflag    = 0;
	wk->yesnoseq      = 0;
	wk->MyPokeNum     = 6;
	wk->FriendPokeNum = 6;
	wk->cursor_pos[0] = 0;
	wk->cursor_pos[1] = 6;
	wk->inputmode     = MODE_NORMAL;

	wk->tradeseq      = 0;
	wk->exchangeseq   = 0;
	wk->func          = trade_seq_normal;
	wk->end_flag[0]   = 0;
	wk->end_flag[1]   = 0;
	wk->result		  = 0;
	wk->vblankreq     = 0;
	wk->posBackup     = -1;
	wk->commandBackup = -1;
	wk->savePreWait   = 0;

	wk->timeOutFlag = 0;
	wk->timeOutWait = 0;

	// �莝���|�P�����f�[�^�擾
	wk->MyPokeParty     = param->myparty;;
	wk->friendlist      = param->friendlist;
	wk->savedata        = param->savedata;

	// ����̃|�P�����f�[�^�p���[�N����
	wk->FriendPokeParty = sys_AllocMemory( HEAPID_TRADELIST, PokeParty_GetWorkSize());
	PokeParty_Init(wk->FriendPokeParty, 6);
	memset(wk->FriendPokeParty,0xff,PokeParty_GetWorkSize());
	
	wk->MyName = MyStatus_CreateNameString(param->mystatus, 	HEAPID_TRADELIST);
	
	// �u�������́v������m��
	wk->MotimonoStr = MSGMAN_AllocString( wk->MsgManager, mes_dstrade_05_05 );

	// �n���V�o�^
	Comm_WifiHistoryCheck( param->wifihistory );
	
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
static void BgExit( GF_BGL_INI * ini )
{

	//��b�E�C���h�E�p�o�b�t�@���
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME2_S);
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME1_S );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME0_S );

	GF_BGL_BGControlExit( ini, GF_BGL_FRAME3_M );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME2_M );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME1_M );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME0_M );

}


//------------------------------------------------------------------
/**
 * �]���Ȃ��ŃX�N���[���f�[�^��ǂݍ���
 *
 * @param   fileIdx		
 * @param   dataIdx		
 * @param   bgl		
 * @param   frm		
 * @param   offs		
 * @param   transSize		
 * @param   compressedFlag		
 * @param   heapID		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void ArcUtil_ScrnSetNoTrans(u32 fileIdx, u32 dataIdx, GF_BGL_INI* bgl, u32 frm, u32 offs, u32 transSize, BOOL compressedFlag, u32 heapID)
{
	void* arcData = ArcUtil_Load( fileIdx, dataIdx, compressedFlag, heapID, ALLOC_BOTTOM );

	if( arcData != NULL )
	{
		NNSG2dScreenData* scrnData;

		if( NNS_G2dGetUnpackedScreenData( arcData, &scrnData ) )
		{
			if( transSize == 0 )
			{
				transSize = scrnData->szByte;
			}

			if( GF_BGL_ScreenAdrsGet( bgl, frm ) != NULL )
			{
				GF_BGL_ScreenBufSet( bgl, frm, scrnData->rawData, transSize );
			}
		}
		sys_FreeMemoryEz( arcData );
	}
}

#define POKEPARTY_NUM	(  6 )

#define CARD_W			(  8 )
#define CARD_H			(  5 )

#define LEFT_CARD_SX	(  0 )
#define LEFT_CARD_SY	(  4 )
#define RIGHT_CARD_SX	( 16 )
#define RIGHT_CARD_SY	(  4 )

static const card_pos_table[][2]={
	{LEFT_CARD_SX,			LEFT_CARD_SY},
	{LEFT_CARD_SX+CARD_W,	LEFT_CARD_SY},
	{LEFT_CARD_SX,			LEFT_CARD_SY+CARD_H},
	{LEFT_CARD_SX+CARD_W,	LEFT_CARD_SY+CARD_H},
	{LEFT_CARD_SX,			LEFT_CARD_SY+CARD_H*2},
	{LEFT_CARD_SX+CARD_W,	LEFT_CARD_SY+CARD_H*2},

	{RIGHT_CARD_SX,			RIGHT_CARD_SY},
	{RIGHT_CARD_SX+CARD_W,	RIGHT_CARD_SY},
	{RIGHT_CARD_SX,			RIGHT_CARD_SY+CARD_H},
	{RIGHT_CARD_SX+CARD_W,	RIGHT_CARD_SY+CARD_H},
	{RIGHT_CARD_SX,			RIGHT_CARD_SY+CARD_H*2},
	{RIGHT_CARD_SX+CARD_W,	RIGHT_CARD_SY+CARD_H*2},
};

//------------------------------------------------------------------
/**
 * ���O�\�����J�[�h����
 *
 * @param   bgl		
 * @param   mynum		
 * @param   friendnum		
 *
 * @retval  void 			
 */
//------------------------------------------------------------------
static void TradeListMakeScreenSet(GF_BGL_INI *bgl, int mynum, int friendnum)
{
	int i;

#if 0
	// �|�P�����̐��ɂ��킹�ăJ�[�h�̐���ς���
	for(i=mynum;i<6;i++)
	{
		GF_BGL_ScrFill(	bgl, GF_BGL_FRAME2_M, 0, card_pos_table[i][0], card_pos_table[i][1], CARD_W, CARD_H,  0);
	}
	for(i=friendnum;i<6;i++)
	{
		GF_BGL_ScrFill(	bgl, GF_BGL_FRAME2_M, 0, card_pos_table[i+6][0], card_pos_table[i+6][1], CARD_W, CARD_H,  0);
	}
#endif

	// �X�N���[���]��
	GF_BGL_LoadScreen( bgl, GF_BGL_FRAME2_M, GF_BGL_ScreenAdrsGet( bgl, GF_BGL_FRAME2_M ), 32*24*2, 0 );

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
static void BgGraphicSet( TRADELIST_WORK * wk )
{
	GF_BGL_INI *bgl = wk->bgl;

	// �㉺��ʂa�f�p���b�g�]��
	ArcUtil_PalSet(    ARC_TRADELIST_GRA, NARC_TradeList_DsTradeList_nclr, PALTYPE_SUB_BG,  0, 16*9*2,  HEAPID_TRADELIST);
	ArcUtil_PalSet(    ARC_TRADELIST_GRA, NARC_TradeList_DsTradeList_nclr, PALTYPE_MAIN_BG, 0, 16*9*2,  HEAPID_TRADELIST);
	GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_M, 0 );
	GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_S, 0 );

	// ��b�t�H���g�p���b�g�]��
	TalkFontPaletteLoad( PALTYPE_MAIN_BG, TALK_FONT_PAL * 32, HEAPID_TRADELIST );

	// ����BG�L�����]��
	ArcUtil_BgCharSet( ARC_TRADELIST_GRA, NARC_TradeList_chara_m_lz_ncgr, bgl, GF_BGL_FRAME2_M, 0, 16*18*0x20, 1, HEAPID_TRADELIST);

	// ����BG2�X�N���[���ǂݍ��݁i�̂݁j
	ArcUtil_ScrnSetNoTrans(   ARC_TRADELIST_GRA, NARC_TradeList_main2_lz_nscr, bgl, GF_BGL_FRAME2_M, 0, 32*24*2, 1, HEAPID_TRADELIST);

	// ����BG3�X�N���[���]��
	ArcUtil_ScrnSet(   ARC_TRADELIST_GRA, NARC_TradeList_main3_lz_nscr, bgl, GF_BGL_FRAME3_M, 0, 32*24*2, 1, HEAPID_TRADELIST);
	
	// ���ʂɃt�H���g�p���b�g�]��
	TalkFontPaletteLoad(   PALTYPE_MAIN_BG , 2*32, HEAPID_TRADELIST );
	SystemFontPaletteLoad( PALTYPE_MAIN_BG,  3*32, HEAPID_TRADELIST );


	// �����BG�L�����]��
	ArcUtil_BgCharSet( ARC_TRADELIST_GRA, NARC_TradeList_chara_s_lz_ncgr, bgl, GF_BGL_FRAME1_S, 0, 16*4*0x20, 1, HEAPID_TRADELIST);

	// �����BG�X�N���[���]��
	ArcUtil_ScrnSet(   ARC_TRADELIST_GRA, NARC_TradeList_sub2_lz_nscr, bgl, GF_BGL_FRAME1_S, 0, 32*24*2, 1, HEAPID_TRADELIST);

	// �����BG�X�N���[���]��
	ArcUtil_ScrnSet(   ARC_TRADELIST_GRA, NARC_TradeList_sub3_lz_nscr, bgl, GF_BGL_FRAME2_S, 0, 32*24*2, 1, HEAPID_TRADELIST);

	// ����ʃt�H���g�p���b�g�]��
	TalkFontPaletteLoad(   PALTYPE_SUB_BG , 2*32, HEAPID_TRADELIST );
	SystemFontPaletteLoad( PALTYPE_SUB_BG,  3*32, HEAPID_TRADELIST );

	GF_BGL_ScrClear( bgl, GF_BGL_FRAME0_S );


}


//** CharManager PlttManager�p **//
#define TRADELIST_CHAR_CONT_NUM					(20)
#define TRADELIST_CHAR_VRAMTRANS_MAIN_SIZE		(2048)
#define TRADELIST_CHAR_VRAMTRANS_SUB_SIZE		(2048)
#define TRADELIST_PLTT_CONT_NUM					(20)

//-------------------------------------
//
//	�L�����N�^�}�l�[�W���[
//	�p���b�g�}�l�[�W���[�̏�����
//
//=====================================
static void char_pltt_manager_init(void)
{
	// �L�����N�^�}�l�[�W���[������
	{
		CHAR_MANAGER_MAKE cm = {
			TRADELIST_CHAR_CONT_NUM,
			TRADELIST_CHAR_VRAMTRANS_MAIN_SIZE,
			TRADELIST_CHAR_VRAMTRANS_SUB_SIZE,
			HEAPID_TRADELIST
		};
		InitCharManager(&cm);
	}
	// �p���b�g�}�l�[�W���[������
	InitPlttManager(TRADELIST_PLTT_CONT_NUM, HEAPID_TRADELIST);

	// �ǂݍ��݊J�n�ʒu��������
	CharLoadStartAll();
	PlttLoadStartAll();
}


//------------------------------------------------------------------
/**
 * ���[�_�[��ʗp�Z���A�N�^�[������
 *
 * @param   wk		���[�_�[�\���̂̃|�C���^
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void InitCellActor(TRADELIST_WORK *wk)
{
	int i;
	
	
	// OAM�}�l�[�W���[�̏�����
	NNS_G2dInitOamManagerModule();

	// ���LOAM�}�l�[�W���쐬
	// �����_���pOAM�}�l�[�W���쐬
	// �����ō쐬����OAM�}�l�[�W�����݂�Ȃŋ��L����
	REND_OAMInit( 
			0, 127,		// ���C�����OAM�Ǘ��̈�
			0, 32,		// ���C����ʃA�t�B���Ǘ��̈�
			0, 127,		// �T�u���OAM�Ǘ��̈�
			0, 32,		// �T�u��ʃA�t�B���Ǘ��̈�
			HEAPID_TRADELIST);
	
	
	
	// �Z���A�N�^�[������
	wk->clactSet = CLACT_U_SetEasyInit( TRADELIST_CACT_MAX, &wk->renddata, HEAPID_TRADELIST );
	
	//���\�[�X�}�l�[�W���[������
	for(i=0;i<CLACT_RESOURCE_NUM;i++){		//���\�[�X�}�l�[�W���[�쐬
		wk->resMan[i] = CLACT_U_ResManagerInit(2, i, HEAPID_TRADELIST);
	}


	//---------���ʗp-------------------
	
	//chara�ǂݍ���
	wk->resObjTbl[MAIN_LCD][CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(wk->resMan[CLACT_U_CHAR_RES], 
							ARC_TRADELIST_GRA, NARC_TradeList_obj_lz_ncgr, 1, 0, NNS_G2D_VRAM_TYPE_2DMAIN, HEAPID_TRADELIST);

	//pal�ǂݍ���
	wk->resObjTbl[MAIN_LCD][CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(wk->resMan[CLACT_U_PLTT_RES],
							ARC_TRADELIST_GRA, NARC_TradeList_DsTradeList_nclr, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 9, HEAPID_TRADELIST);

	//cell�ǂݍ���
	wk->resObjTbl[MAIN_LCD][CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELL_RES],
							ARC_TRADELIST_GRA, NARC_TradeList_obj_lz_ncer, 1, 0, CLACT_U_CELL_RES,HEAPID_TRADELIST);

	//�����֐���anim�ǂݍ���
	wk->resObjTbl[MAIN_LCD][CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELLANM_RES],
							ARC_TRADELIST_GRA, NARC_TradeList_obj_lz_nanr, 1, 0, CLACT_U_CELLANM_RES,HEAPID_TRADELIST);


	//---------����ʗp-------------------


	//chara�ǂݍ���
	wk->resObjTbl[SUB_LCD][CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(wk->resMan[CLACT_U_CHAR_RES], 
							ARC_TRADELIST_GRA, NARC_TradeList_obj_s_lz_ncgr, 1, 1, NNS_G2D_VRAM_TYPE_2DSUB, HEAPID_TRADELIST);

	//pal�ǂݍ���
	wk->resObjTbl[SUB_LCD][CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(wk->resMan[CLACT_U_PLTT_RES],
							ARC_TRADELIST_GRA, NARC_TradeList_DsTradeList_nclr, 0, 1, NNS_G2D_VRAM_TYPE_2DSUB, 10, HEAPID_TRADELIST);

	//cell�ǂݍ���
	wk->resObjTbl[SUB_LCD][CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELL_RES],
							ARC_TRADELIST_GRA, NARC_TradeList_obj_s_lz_ncer, 1, 1, CLACT_U_CELL_RES,HEAPID_TRADELIST);

	//�����֐���anim�ǂݍ���
	wk->resObjTbl[SUB_LCD][CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELLANM_RES],
							ARC_TRADELIST_GRA, NARC_TradeList_obj_s_lz_nanr, 1, 1, CLACT_U_CELLANM_RES,HEAPID_TRADELIST);

	// ���\�[�X�}�l�[�W���[����]��

	// Chara�]��
	CLACT_U_CharManagerSet( wk->resObjTbl[MAIN_LCD][CLACT_U_CHAR_RES] );
	CLACT_U_CharManagerSet( wk->resObjTbl[SUB_LCD][CLACT_U_CHAR_RES] );

	// �p���b�g�]��
	CLACT_U_PlttManagerSet( wk->resObjTbl[MAIN_LCD][CLACT_U_PLTT_RES] );
	CLACT_U_PlttManagerSet( wk->resObjTbl[SUB_LCD][CLACT_U_PLTT_RES] );

	// �|�P�����A�C�R���p�p���b�g����C�ɓǂݍ����VRAM�]������
	ArcUtil_PalSet( ARC_POKEICON, PokeIconPalArcIndexGet(), PALTYPE_MAIN_OBJ, POKEICON_PAL_OFFSET*0x20, 0x20*4, HEAPID_TRADELIST );


}

//------------------------------------------------------------------
/**
 * ����ʂ̃|�P�����摜��]������
 *
 * @param   side		�����E��(0-1)
 * @param   pokeno		�|�P�����̊J��NO
 * @param   char_work	�|�P�����摜��ǂݍ��ޗ̈�
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static int TransPokeGra_SubLcd(int side, POKEMON_PARAM *pp, u8 *char_work, SOFT_SPRITE_ARC *ssa)
{
	// �|�P�����̉摜��ǂݍ��ށi�������\�t�g�E�F�A�X�v���C�g�p�̃e�N�X�`����ԁj
	PokeGraArcDataGetPP( ssa, pp, PARA_FRONT);

	// �e�N�X�`����OAM�p�̕��тɕϊ�����
	{
		int rnd    = PokeParaGet( pp, ID_PARA_personal_rnd, NULL );
		int monsno = PokeParaGet( pp, ID_PARA_monsno, NULL );
		Ex_ChangesInto_OAM_from_PokeTex(ssa->arc_no, ssa->index_chr, HEAPID_TRADELIST, 0, 0, 10, 10, char_work, 
										rnd, 0, PARA_FRONT, monsno);
	}

	DC_FlushRange( char_work, 0x20*10*10 );	// �]���O�Ƀ���������
	
	return side+1;
	

}





//------------------------------------------------------------------
/**
 * @brief   �|�P�����̖��O��`��
 *
 * @param   win		
 * @param   party		
 * @param   pos		
 * @param   width		
 * @param   print_sw		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void PokeNamePrint( GF_BGL_BMPWIN *win, POKEPARTY *party, int pos, int width, int print_sw )
{
	STRBUF *name;
	
	name = STRBUF_Create(20,HEAPID_TRADELIST);
	PokeParaGet(PokeParty_GetMemberPointer(party, pos),ID_PARA_nickname_buf, name);

	// �|�P������
	GF_BGL_BmpWinDataFill( win, 0 );
	TradeListPrint(win, name, width, MSG_ALLPUT, print_sw,1);
	STRBUF_Delete(name);

}

//------------------------------------------------------------------
/**
 * @brief   �j�h�������E���p�̓��ʏ���
 *
 * @param   info	
 * @param   party	
 * @param   pos		
 * @param   sex		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int NidoranSpecialCheck( POKE_INFO *info, POKEPARTY *party, int pos, int sex )
{
	// �j�h���������j�h��������
	if(info->exist==MONSNO_NIDORAN_F || info->exist==MONSNO_NIDORAN_M){

		// �j�b�N�l�[���t���O�������Ă��Ȃ��ꍇ��
		POKEMON_PARAM *pp = PokeParty_GetMemberPointer( party, pos );
		int flag = PokeParaGet( pp, ID_PARA_nickname_flag,NULL );
		if(flag==0){
			// ���ʖ��������ɂ��ĉ���ʂɐ��ʃA�C�R�����o���Ȃ��悤�ɂ�����
			return PARA_UNK;
		}
	}
	
	return sex;
}


//------------------------------------------------------------------
/**
 * �T�u��ʂɕ�����`���OAM�\��ON���s��
 *
 * @param   win		
 * @param   side		
 * @param   party		
 * @param   pos		
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void TransPokeStr_SubLcd(GF_BGL_BMPWIN *win, int side, POKEPARTY *party, int pos, TRADELIST_WORK *wk)
{
	STRBUF *level, *item;
	u16 itemno,levelnum;
	int height;
	POKEMON_PARAM *pp;
	
	pp = PokeParty_GetMemberPointer(party, pos);
	
	// ���������擾
	height = PokeParaHeightGet( pp, PARA_FRONT );

//	OS_Printf("�����@%d\n",height);

	// ����ʃ|�P�����\��
	CLACT_SetDrawFlag(wk->SubLCDIconActWork[side], 1);
	Clact_SetPos( wk->SubLCDIconActWork[side],  sub_icon_pos[side][0], 
												sub_icon_pos[side][1]+height+SUB_SURFACE_Y_INTEGER  );

	// ���E���]�t���O�����Ĕ��]�����Ȃ��悤�ɂ���
	if(side==0){
		CLACT_SetFlip( wk->SubLCDIconActWork[side], wk->pokeInfo[pos].reverse );
	}

	// �����X�^�[�{�[���`�F���W�E�\��
	CLACT_AnmChg( wk->SubLCDIconActWork[2+side], wk->pokeInfo[pos].monsball+CELL_MONSTER_BALL_NO-1 );
	CLACT_SetDrawFlag(wk->SubLCDIconActWork[2+side], 1);


	PokeNamePrint(&win[BMP_S_MYPOKENAME_WIN+side], party, pos, SUB_POKENAME_W, 6);

	// ���ʃA�C�R���\��
	{
		
		int sex = wk->pokeInfo[side*6+pos].sex;
		sex = NidoranSpecialCheck( &wk->pokeInfo[side*6+pos], party, pos, sex );
		// �^�}�S�͕\�����Ȃ�
		if(wk->pokeInfo[side*6+pos].tamago){
			sex = PARA_UNK;
		}
		switch(sex){
		case PARA_UNK:
			// ���ʖ����Ȃ�A�C�R���\��OFF
			CLACT_SetDrawFlag(wk->SubLCDIconActWork[4+side], 0);
			break;
		// ���ʂɂ��킹�ĕ\��
		case PARA_MALE:
			CLACT_SetDrawFlag(wk->SubLCDIconActWork[4+side], 1);
			CLACT_AnmChg(wk->SubLCDIconActWork[4+side], CELL_SEX_ICON_NO+1 );
			break;
		case PARA_FEMALE:
			CLACT_SetDrawFlag(wk->SubLCDIconActWork[4+side], 1);
			CLACT_AnmChg(wk->SubLCDIconActWork[4+side], CELL_SEX_ICON_NO );
			break;
		}
	}

	// �^�}�S����Ȃ����
	if(!wk->pokeInfo[side*6+pos].tamago){

		// ���x���uLV.�v
		level = STRBUF_Create(10,HEAPID_TRADELIST);
		GF_BGL_BmpWinDataFill( &win[BMP_S_MYPOKELEVEL_WIN+side], 0 );
		MSGMAN_GetString( wk->MsgManager, mes_dstrade_05_03, level );
		TradeListPrint( &win[BMP_S_MYPOKELEVEL_WIN+side], level, SUB_POKENAME_W, MSG_NO_PUT, 6,0);
	
		// ���x������
		levelnum = PokeParaGet(PokeParty_GetMemberPointer(party, pos),ID_PARA_level,NULL);
		STRBUF_SetNumber( level, levelnum, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		TradeListPrint( &win[BMP_S_MYPOKELEVEL_WIN+side], level, SUB_POKENAME_W, MSG_ALLPUT, 24+6,0);
		STRBUF_Delete(level);
	}else{
		GF_BGL_BmpWinOff( &win[BMP_S_MYPOKELEVEL_WIN+side] );
	
	}

	// �u�������́v
	TradeListPrint(&win[BMP_S_MOTIMONO0_WIN+side], wk->MotimonoStr, SUB_MOTIMONOSTR_W, MSG_ALLPUT, 3,0);

	itemno = PokeParaGet(PokeParty_GetMemberPointer(party, pos),ID_PARA_item,NULL);
	GF_BGL_BmpWinDataFill( &win[BMP_S_MYITEM_WIN+side], 0 );

	// �A�C�e�����i�u�Ȃ��v�Ƃ���������͂܂��\���ł��Ȃ��Bitemname=0�́u�H�H�H�v����������j
	item = STRBUF_Create(20,HEAPID_TRADELIST);
	GetItemName( item, itemno, HEAPID_TRADELIST );
	TradeListPrint(&win[BMP_S_MYITEM_WIN+side], item, SUB_POKENAME_W, MSG_ALLPUT, 3,0);
	STRBUF_Delete(item);

}


//------------------------------------------------------------------
/**
 * @brief   ����ʃJ�[�h��\������
 *
 * @param   win		
 * @param   side		
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void PokeStr_SubLcdOff(GF_BGL_BMPWIN *win, int side, TRADELIST_WORK *wk)
{
	// ����ʃ|�P������\��
	CLACT_SetDrawFlag(wk->SubLCDIconActWork[side], 0);

	// �����X�^�[�{�[���`�F���W��\��
	CLACT_SetDrawFlag(wk->SubLCDIconActWork[2+side], 0);

	// ���ʃA�C�R��
	CLACT_SetDrawFlag(wk->SubLCDIconActWork[4+side], 0);

	// ���O�E���x���E�u�������́v�E�������́@��\��
	GF_BGL_BmpWinOff( &win[BMP_S_MYPOKENAME_WIN+side] );
	GF_BGL_BmpWinOff( &win[BMP_S_MYPOKELEVEL_WIN+side] );
	GF_BGL_BmpWinOff( &win[BMP_S_MOTIMONO0_WIN+side] );
	GF_BGL_BmpWinOff( &win[BMP_S_MYITEM_WIN+side] );

}



//------------------------------------------------------------------
/**
 * �Z���A�N�^�[�o�^
 *
 * @param   wk			NAMEIN_WORK*
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SetCellActor(TRADELIST_WORK *wk)
{
	// �Z���A�N�^�[�w�b�_�쐬
	CLACT_U_MakeHeader(&wk->clActHeader_m, 0, 0, 0, 0, CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
	0, 2,
	wk->resMan[CLACT_U_CHAR_RES],
	wk->resMan[CLACT_U_PLTT_RES],
	wk->resMan[CLACT_U_CELL_RES],
	wk->resMan[CLACT_U_CELLANM_RES],
	NULL,NULL);

	CLACT_U_MakeHeader(&wk->clActHeader_s, 1, 1, 1, 1, CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
	0, 0,
	wk->resMan[CLACT_U_CHAR_RES],
	wk->resMan[CLACT_U_PLTT_RES],
	wk->resMan[CLACT_U_CELL_RES],
	wk->resMan[CLACT_U_CELLANM_RES],
	NULL,NULL);

	{
		//�o�^���i�[
		CLACT_ADD add;
		int i;

		add.ClActSet	= wk->clactSet;
		add.ClActHeader	= &wk->clActHeader_m;

		add.mat.x		= FX32_CONST(32) ;
		add.mat.y		= FX32_CONST(96) ;		//��ʂ͏㉺�A�����Ă���iMAIN����ASUB�����j
		add.mat.z		= 0;
		add.sca.x		= FX32_ONE;
		add.sca.y		= FX32_ONE;
		add.sca.z		= FX32_ONE;
		add.rot			= 0;
		add.pri			= 0;
		add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
		add.heap		= HEAPID_TRADELIST;

		//�Z���A�N�^�[�\���J�n

		// ���ʗp�J�[�\��
		for(i=0;i<2;i++){
			add.mat.x = FX32_ONE*main_cursor_pos[i][0];
			add.mat.y = FX32_ONE*main_cursor_pos[i][1];
			wk->clActWork[i] = CLACT_Add(&add);
			CLACT_SetAnmFlag(wk->clActWork[i],1);
			CursorPosChange(wk->cursor_pos[i],wk->clActWork[i], i);
			CLACT_DrawPriorityChg( wk->clActWork[i], 100 );		
			CLACT_SetDrawFlag( wk->clActWork[i], 0 );

		}

		// �|�P�����A�C�R��
		for(i=0;i<TRADELIST_POKE_MAX;i++){
			add.mat.x = FX32_ONE*(main_cursor_pos[i][0]+16);
			add.mat.y = FX32_ONE*(main_cursor_pos[i][1]-6);
			wk->PokeIconActWork[i] = CLACT_Add(&add);
			CLACT_SetAnmFlag(wk->PokeIconActWork[i],1);
			CLACT_AnmChg( wk->PokeIconActWork[i], 5+i );
//			CLACT_BGPriorityChg( wk->PokeIconActWork[i], 1 );	// �v���C�I���e�B���J�[�\�����͏��
			CLACT_DrawPriorityChg(wk->PokeIconActWork[i], 5);	// ���ꂼ��̃A�N�^�[�̃v���C�I���e�B�ݒ�
			CLACT_SetDrawFlag( wk->PokeIconActWork[i], 0 );
		}

		// �|�P�����̃A�C�e��
		for(i=0;i<TRADELIST_POKE_MAX;i++){
			add.mat.x = FX32_ONE*(main_cursor_pos[i][0]+16+20);
			add.mat.y = FX32_ONE*(main_cursor_pos[i][1]+16);
			add.pri			= 0;
			wk->PokeItemActWork[i] = CLACT_Add(&add);
			CLACT_DrawPriorityChg(wk->PokeItemActWork[i], 3);	// ���ꂼ��̃A�N�^�[�̃v���C�I���e�B�ݒ�
			CLACT_SetDrawFlag( wk->PokeItemActWork[i], 0 );
		}

		// �|�P�����̃J�X�^���{�[��
		for(i=0;i<TRADELIST_POKE_MAX;i++){
			add.mat.x = FX32_ONE*(main_cursor_pos[i][0]+16+20+9);
			add.mat.y = FX32_ONE*(main_cursor_pos[i][1]+16);
			add.pri			= 0;
			wk->PokeCBallActWork[i] = CLACT_Add(&add);
			CLACT_DrawPriorityChg(wk->PokeCBallActWork[i], 3);	// ���ꂼ��̃A�N�^�[�̃v���C�I���e�B�ݒ�
			CLACT_SetDrawFlag( wk->PokeCBallActWork[i], 0 );
		}

		// �u�������܂����H�v�̖��
		add.mat.x = FX32_ONE*( 128-4*8 );
		add.mat.y = FX32_ONE*(     8*8+2 );
		wk->ExchangeArrow = CLACT_Add(&add);
		CLACT_SetAnmFlag( wk->ExchangeArrow,1);
		CLACT_AnmChg( wk->ExchangeArrow, 20 );
		CLACT_SetDrawFlag( wk->ExchangeArrow, 0 );


		// ����ʗp(�|�P�����Q�́E���Q�E���ʃA�C�R���j
		for(i=0;i<6;i++){
			add.ClActHeader	= &wk->clActHeader_s;
			add.mat.x = FX32_ONE*sub_icon_pos[i][0];
			add.mat.y = FX32_ONE*(sub_icon_pos[i][1]) + SUB_SURFACE_Y;
			add.DrawArea	= NNS_G2D_VRAM_TYPE_2DSUB;
			wk->SubLCDIconActWork[i] = CLACT_Add(&add);
			CLACT_SetDrawFlag(wk->SubLCDIconActWork[i], 0);
			CLACT_SetAnmFlag(wk->SubLCDIconActWork[i],0);
			CLACT_AnmChg( wk->SubLCDIconActWork[i], sub_icon_pos[i][2] );
		}
		
	}	
	
}







#ifdef PM_DEBUG
//------------------------------------------------------------------
/**
 * �f�o�b�O�\���p��OBJ��BG�𓮂���
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void DebugOBJPOSGet(TRADELIST_WORK *wk)
{
		if( sys.cont & PAD_KEY_UP){
			VecFx32 tmpVex;
			wk->framenum[wk->frame][1]--;
			tmpVex.x = FX32_ONE*wk->framenum[wk->frame][0];
			tmpVex.y = FX32_ONE*wk->framenum[wk->frame][1];
			CLACT_SetMatrix(wk->clActWork[wk->frame], &tmpVex);
			OS_Printf("frame %d x=%d, y=%d\n",wk->frame, wk->framenum[wk->frame][0],wk->framenum[wk->frame][1]);
		}
		if( sys.cont & PAD_KEY_DOWN){
			VecFx32 tmpVex;
			wk->framenum[wk->frame][1]++;
			tmpVex.x = FX32_ONE*wk->framenum[wk->frame][0];
			tmpVex.y = FX32_ONE*wk->framenum[wk->frame][1];
			CLACT_SetMatrix(wk->clActWork[wk->frame], &tmpVex);
			OS_Printf("frame %d x=%d, y=%d\n",wk->frame, wk->framenum[wk->frame][0],wk->framenum[wk->frame][1]);
			
		}
		if( sys.cont & PAD_KEY_LEFT){
			VecFx32 tmpVex;
			wk->framenum[wk->frame][0]--;
			tmpVex.x = FX32_ONE*wk->framenum[wk->frame][0];
			tmpVex.y = FX32_ONE*wk->framenum[wk->frame][1];
			CLACT_SetMatrix(wk->clActWork[wk->frame], &tmpVex);
			OS_Printf("frame %d x=%d, y=%d\n",wk->frame, wk->framenum[wk->frame][0],wk->framenum[wk->frame][1]);
			
		}
		if( sys.cont & PAD_KEY_RIGHT){
			VecFx32 tmpVex;
			wk->framenum[wk->frame][0]++;
			tmpVex.x = FX32_ONE*wk->framenum[wk->frame][0];
			tmpVex.y = FX32_ONE*wk->framenum[wk->frame][1];
			CLACT_SetMatrix(wk->clActWork[wk->frame], &tmpVex);
			OS_Printf("frame %d x=%d, y=%d\n",wk->frame, wk->framenum[wk->frame][0],wk->framenum[wk->frame][1]);
		}

}

#endif

#define MOVE_UP 	1
#define MOVE_DOWN 	2
#define MOVE_LEFT 	3
#define MOVE_RIGHT 	4

static const arrowtbl[][2]={{0,0},{0,-1},{0,1},{-1,0},{1,0}};

static int AroundWork(int w, int min, int max)
{
	if(w>=max){
		w = min;
	}
	if(w<min){
		w = max-1;
	}
	return w;
}


//------------------------------------------------------------------
/**
 * �J�[�\���ړ�����
 *
 * @param   wk		NAMEIN_WORK*
 *
 * @retval  none	
 */
//------------------------------------------------------------------
static void ControlCursor(u32 *CommWork)
{
	int move  = 0;
	int arrow = 0;

	// �L�[���͂ɑ΂��Ĉړ�����S�����̂����̈������
	if( sys.repeat & PAD_KEY_UP){
		arrow = MOVE_UP;
		move++;
	}
	if( sys.repeat & PAD_KEY_DOWN){
		arrow = MOVE_DOWN;
		move++;
	}
	if( sys.repeat & PAD_KEY_LEFT){
		arrow = MOVE_LEFT;
		move++;
	}
	if( sys.repeat & PAD_KEY_RIGHT){
		arrow = MOVE_RIGHT;
		move++;
	}

	// �ړ�������������ύX
	if(move){
		*CommWork = arrow;
	}

}



// ����ʗp�{�^���ʒu��`
#define SUB_BUTTON1_POSX			( 3*8  )
#define SUB_BUTTON1_POSY			( 7*8  )
#define SUB_BUTTON2_POSX			( 19*8 )
#define SUB_BUTTON2_POSY			( 7*8  )

#define SUB_BUTTON_W			( 8*10 )
#define SUB_BUTTON_H			( 8*10 )

static const RECT_HIT_TBL sub_button_hittbl[]={
	{SUB_BUTTON1_POSY, SUB_BUTTON1_POSY+SUB_BUTTON_H, SUB_BUTTON1_POSX, SUB_BUTTON1_POSX+SUB_BUTTON_W},
//	{SUB_BUTTON2_POSY, SUB_BUTTON2_POSY+SUB_BUTTON_H, SUB_BUTTON2_POSX, SUB_BUTTON2_POSX+SUB_BUTTON_W},
	{RECT_HIT_END,0,0,0},		// �I���f�[�^
};



//------------------------------------------------------------------
/**
 * �^�b�`�p�l���ŉ������{�^�����ւ���
 *
 * @param   wk		NAMEIN_WORK�̃|�C���^
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void TouchFunc(TRADELIST_WORK *wk)
{
	u16 monsno;
	int button=-1,i;

	// �����̑��ɃJ�[�\��������Ȃ�
	if( wk->cursor_pos[0]>=6){
		return;
	}

	// �^�b�`�p�l�����͏���
	button=GF_TP_RectHitTrg( sub_button_hittbl );

	// ����ʂŎ����̃|�P�������^�b�`����
	if( button != RECT_HIT_NONE ){

		// �^�}�S�͖���
		if(wk->pokeInfo[wk->cursor_pos[0]].tamago){
			return;
		}

		// �������i�y���b�v�{�C�X�Ή��j
		monsno = wk->pokeInfo[wk->cursor_pos[0]].exist;
		//�؃��b�v���`�F�b�N
		if( monsno == MONSNO_PERAPPU ){

			//�����̃y���b�v�f�[�^�Œ�ɂ��Ă���̂Ō�ŕύX����I
			//Snd_PerapVoicePlay( CommGetCurrentID(), PM_MALE, PV_VOL_DEFAULT, 0 );
			Snd_PerapVoicePlay( SaveData_GetPerapVoice(wk->savedata), 
								PM_MALE, PV_VOL_DEFAULT, 0 );
		}else{
			Snd_PMVoicePlay( monsno );
		}
		
		// �|�P�������W�����v����
		CLACT_SetAnmFlag(wk->SubLCDIconActWork[button],1);
		CLACT_AnmChg( wk->SubLCDIconActWork[button], 4+button );
		OS_Printf("�W�����v�I\n");
	}


}


//------------------------------------------------------------------
/**
 * �J�[�\���̃p���b�g�ύX�i�_�Łj
 *
 * @param   CursorCol	sin�ɓn���p�����[�^�i360�܂Łj
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void CursorColTrans(u16 *CursorCol)
{
	fx32  sin;
	GXRgb tmp;
	int   r,g,b;

	*CursorCol+=20;
	if(*CursorCol>360){
		*CursorCol = 0;
	}

	sin = Sin360R(*CursorCol);
	g   = 15 +( sin * 10 ) / FX32_ONE;
	tmp = GX_RGB(29,g,0);


	GX_LoadOBJPltt((u16*)&tmp, (16+13)*2, 2);
}




//--------------------------------------------------------------------------
/**
 * ���ق̎��̈ړ���͑��݂��Ă��邩���ō�6�܂ŒT��
 *
 * @param   pos		���݂̈ʒu�ԍ�
 * @param   arrow	�ړ�����
 *
 * @retval  u8		�ړ�����
 */
//--------------------------------------------------------------------------
static int NextCursorSearch(int pos, int arrow, POKE_INFO *info)
{
	int i,w;
	w = 0;
	for(i=0;i<6;i++){
		if(info[movepostbl[pos][arrow][i]].exist!=0){
			w = movepostbl[pos][arrow][i];
			break;
		}
	}
	return w;
}


static const CursorAnmTable[][3]={
	{ 0, 1, 2},
	{17,18,19},
};
//--------------------------------------------------------------------------
/**
 * ���وړ�����
 *
 * @param   pos		�J�[�\���ʒu���i�[���Ă��郏�[�N�̃|�C���^
 * @param   arrow	�ړ�����
 *
 * @retval  none		
 *
 *
 */
//--------------------------------------------------------------------------
static void CursorPosChange(int pos, CLACT_WORK_PTR CursorAct,int side)
{
	VecFx32 tmpVex;
	GF_ASSERT(pos<13);

	tmpVex.x = FX32_ONE*main_cursor_pos[pos][0];
	tmpVex.y = FX32_ONE*main_cursor_pos[pos][1];

	if(pos==CURSOR_END_POS){
		CLACT_SetMatrix(CursorAct, &tmpVex);
		CLACT_AnmChg( CursorAct, CursorAnmTable[side][2] );	// �����p�J�[�\���ɃA�N�^�[�ύX
	}else{
		CLACT_SetMatrix(CursorAct, &tmpVex);
		if(pos<6){
			CLACT_AnmChg( CursorAct, CursorAnmTable[side][0] );	// ���p�ɃA�N�^�[�ύX
		}else{
			CLACT_AnmChg( CursorAct, CursorAnmTable[side][1] );	// �E�p�ɃA�N�^�[�ύX
		}
	}

}


//------------------------------------------------------------------
/**
 * �J�[�\�����ړ������ꍇ�ɍ��W�E�`��̕ύX���s��
 *
 * @param   Command		
 * @param   pos		
 * @param   CursorAct		
 * @param   existtbl		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int ViewChange(u32 *Command, int *pos, CLACT_WORK_PTR CursorAct, POKE_INFO *info, int side)
{
	int arrow  = *Command - 1;
	int w      = 0;
	int result = 0;
	
	if(side==0){
		if(*Command){
			w = NextCursorSearch(*pos,arrow,info);
			CursorPosChange(w,CursorAct,side);
			if(*pos!=w){					//�ړ����Ă����SE�炷
				Snd_SePlay(NAMEIN_MOVE_SE);
				*pos = w;					//���W�X�V
				result = 1;
			}
		}
		*Command = 0;	//�R�}���h�N���A
	}else{
		CursorPosChange(*pos,CursorAct,side);
	}

	return result;
}


//------------------------------------------------------------------
/**
 * �������M�f�[�^�𑗂�i��ɃJ�[�\���̈ʒu�𑗐M����j
 *
 * @param   netID		
 * @param   pos		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
void TradeListCommSend(int netID, int command, int pos)
{
	
	u8 data = pos;

	CommSendData(command,&data,1);
}


//==============================================================================
/**
 * @brief   ���M�f�[�^���O��̑��M�f�[�^�ƈႤ�Ƃ��������M����
 *
 * @param   wk		
 * @param   command		
 * @param   pos		
 *
 * @retval  none		
 */
//==============================================================================
void TradeListCommDiffSend( TRADELIST_WORK *wk, int command, int pos)
{
	if(pos != wk->posBackup || command != wk->commandBackup){
		TradeListCommSend( CommGetCurrentID(), command, pos );
		wk->posBackup     = pos;
		wk->commandBackup = command;

		OS_Printf("Id:%d command=%d pos=%d�𑗐M\n", CommGetCurrentID(), command, pos);
	}
}


//------------------------------------------------------------------
/**
 * 
 *
 * @param   party		
 * @param   no		
 *
 * @retval  void *		
 */
//------------------------------------------------------------------
static void *GetPartyAdrs(POKEPARTY *party, int no)
{
	u32 adrs = (u32)party;
	
	return (void*)(adrs+no*POKEPARTY_SEND_ONCE_SIZE);
}


//==============================================================================
/**
 * �|�P�����f�[�^�𑗐M����i�ʐM�̐e�q�Ŋ֐���ւ���j
 *
 * @param   netID		
 * @param   party		
 * @param   no		
 *
 * @retval  none		
 */
//==============================================================================
void TradeListCommSendPokeData(int netID, POKEPARTY *party, int no)
{
	if(CommIsConnect(netID)){			// �f�o�b�O�ň�l�p�𓮂�����������Ȃ��̂ŔO�̂���
		u8 data = no;
		CommSendHugeData(CT_POKEDATA,GetPartyAdrs(party,no),POKEPARTY_SEND_ONCE_SIZE);
	}
}

//==============================================================================
/**
 * @brief   ���{����񑗐M
 *
 * @param   sv		
 * @param   no		
 *
 * @retval  none		
 */
//==============================================================================
static void TradeListCommSpRibbonDate(  SAVEDATA *sv )
{
	u8 *p = SaveData_GetSpRibbon( sv );
	int i;
	
	CommSendData( CT_SP_RIBBON_INFO, p, HAIFU_RIBBON_MAX);

}

//------------------------------------------------------------------
/**
 * $brief   ���肠���O���[�v�f�[�^�̑��M
 *
 * @param   mystatus		
 * @param   friendlist		
 * @param   sendbuf		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void CommSendFriendList( MYSTATUS *mystatus, FRIEND_LIST *friendlist, FRIEND_LIST *sendbuf )
{
	int i;

	// ���M�f�[�^�̍쐬
	PM_strcpy( sendbuf->name, MyStatus_GetMyName( mystatus ));	// ���O
	sendbuf->id       = MyStatus_GetID(mystatus);				// ID
	sendbuf->region   = MyStatus_GetRegionCode(mystatus);		// ���[�W����
	sendbuf->rom_code = MyStatus_GetRomCode(mystatus);			// ROM
	sendbuf->sex      = MyStatus_GetMySex(mystatus);			// ����
	
	for(i=0;i<FRIENDLIST_FRIEND_MAX;i++){						// �����̒m�荇����ID��
		sendbuf->group_id[i]      = friendlist[i].id;			// �m�荇���̒m�荇���Ƃ��Ă͓n�����߂ɐ��`
		sendbuf->group_romcode[i] = friendlist[i].rom_code;
		sendbuf->group_region[i]  = friendlist[i].region;
		sendbuf->group_sex[i]     = friendlist[i].sex;
	}


	// ���M
	CommSendHugeData( CT_FRINEDLIST, sendbuf, sizeof(FRIEND_LIST) );
	
}

//------------------------------------------------------------------
/**
 * @brief   �y���b�v�{�C�X���M
 *
 * @param   pv		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void CommSendPerapVoice( PERAPVOICE *pv )
{
	CommSendHugeData( CT_PERAPVOICE, pv, PERAPVOICE_LENGTH );
}

//------------------------------------------------------------------
/**
 * �ʏ�ړ�
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_normal(TRADELIST_WORK *wk)
{
	ControlCursor(&wk->CommWork[0]);

	if(sys.trg & PAD_BUTTON_A){
		if(wk->CommWork[0]==0){
			if(wk->cursor_pos[0]==CURSOR_END_POS){
				wk->func = trade_seq_endyesno;
			}else if(wk->cursor_pos[0]<6){
				wk->func = trade_seq_mypoke;
			}else if(wk->cursor_pos[0]>=6 && wk->cursor_pos[0]<CURSOR_END_POS){
				wk->func = trade_seq_friendpoke;
			}
		}
	}
	return MODE_NORMAL;
}

// �X�e�[�^�X��ʂŕ\������t���O�̗�i�r�b�g�e�[�u���ɂ���΂����̂Ɂc�j
static const u8 StatusPageTable[]={
	PST_PAGE_INFO,			// �u�|�P�������傤�ق��v
	PST_PAGE_MEMO,			// �u�g���[�i�[�����v
	PST_PAGE_PARAM,			// �u�|�P�����̂���傭�v
	PST_PAGE_CONDITION,		// �u�R���f�B�V�����v
	PST_PAGE_B_SKILL,		// �u���������킴�v
	PST_PAGE_C_SKILL,		// �u�R���e�X�g�킴�v
	PST_PAGE_RIBBON,		// �u���˂񃊃{���v
	PST_PAGE_RET,			// �u���ǂ�v
	PST_PAGE_MAX

};


//------------------------------------------------------------------
/**
 * @brief   �X�e�[�^�X���Ă΂ꂽ�̂őS�Ĕj�����ăX�e�[�^�X�Ăяo��
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static void poke_status_setup( TRADELIST_WORK *wk, int side )
{

	if(side==0){
		// �����̂Ă���
		wk->statusParam.ppd        = wk->MyPokeParty;
		wk->statusParam.max        = PokeParty_GetPokeCount(wk->param->myparty);
//		wk->statusParam.perap      = (PERAPVOICE*)wk->perap_buf[CommGetCurrentID()];
		wk->statusParam.perap      = NULL;
		PokeStatus_PlayerSet( &wk->statusParam, CommInfoGetMyStatus(CommGetCurrentID()) );

	}else{
		// ����̂Ă����i�y���b�v�{�C�X���Z�b�g����j
		wk->statusParam.ppd        = wk->FriendPokeParty;
		wk->statusParam.max        = PokeParty_GetPokeCount(wk->FriendPokeParty);
		wk->statusParam.perap      = (PERAPVOICE*)wk->perap_buf[CommGetCurrentID()^1];
		PokeStatus_PlayerSet( &wk->statusParam, CommInfoGetMyStatus(CommGetCurrentID()^1) );
	}
	wk->statusParam.ppt        = PST_PP_TYPE_POKEPARTY;
	wk->statusParam.pos        = wk->cursor_pos[0]%6;
	wk->statusParam.mode       = PST_MODE_NO_WAZACHG;	// �Z����ւ��֎~�ɂ���
	wk->statusParam.waza       = 0;
	wk->statusParam.ev_contest = PokeStatus_ContestFlagGet(wk->param->savedata);
	wk->statusParam.zukan_mode = wk->param->zukanmode;
	wk->statusParam.cfg        = wk->param->config;
	wk->statusParam.ribbon     = SaveData_GetSpRibbon(wk->param->savedata);
	PokeStatus_PageSet( &wk->statusParam, StatusPageTable );
	
	wk->subproc = PROC_Create( &PokeStatusProcData, &wk->statusParam, HEAPID_TRADELIST );
	
	wk->status_side            = side;
}
//------------------------------------------------------------------
/**
 * �I���x�d�r�m�n
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_endyesno(TRADELIST_WORK *wk )
{
	GF_BGL_ScrFill(	wk->bgl, GF_BGL_FRAME0_M, 0, 0, 0, 32, 24,  0);
	TradeListWindowPrint(
		&wk->TradeListWin[BMP_M_MES3_WIN],
		mes_dstrade_04_04,FONT_TALK,
		wk->MsgManager,
		wk->PokeNameWordSet
	);
	wk->func = trade_seq_endyesno_wait;

	return MODE_NORMAL;
	
}

//------------------------------------------------------------------
/**
 * �I���x�d�r�m�n�҂�
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_endyesno_wait(TRADELIST_WORK *wk)
{
	switch(TradeListYesNoFunc(wk->bgl, &wk->YesNoMenu, &wk->yesnoseq)){
	case 0:
		GF_BGL_ScrFill(	wk->bgl, GF_BGL_FRAME0_M, 0, 0, 0, 32, 24,  0);
		TradeListWindowPrint(
			&wk->TradeListWin[BMP_M_MES3_WIN],
			mes_dstrade_04_07,FONT_TALK,
			wk->MsgManager,
			wk->PokeNameWordSet
		);
		// ��߂鎖������
		TradeListCommDiffSend( wk, CT_TRADE_DECIDE, DECIDE_COMMAND_END);
		wk->func   = trade_seq_end;
		wk->result = TRADELIST_END_FINISH;
		break;
	case BMPMENU_CANCEL:
		GF_BGL_ScrFill(	wk->bgl, GF_BGL_FRAME0_M, 0, 0, 0, 32, 24,  0);
		TradeListWindowPrint(
			&wk->TradeListWin[BMP_M_MES1_WIN],
			mes_dstrade_02_01,FONT_TALK,
			wk->MsgManager,
			wk->PokeNameWordSet
		);
		wk->func = trade_seq_normal;
		break;
	default:
		break;
	}

	return MODE_NORMAL;
}



//------------------------------------------------------------------
/**
 * @brief   �L�����Z������
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_return(TRADELIST_WORK *wk)
{
	GF_BGL_ScrFill(	wk->bgl, GF_BGL_FRAME0_M, 0, 0, 0, 32, 24,  0);
	TradeListWindowPrint(
		&wk->TradeListWin[BMP_M_MES3_WIN],
		wk->fail_reason,FONT_TALK,
		wk->MsgManager,
		wk->PokeNameWordSet
	);
	wk->func = trade_seq_return_wait;
	
	return MODE_NORMAL;
}

//------------------------------------------------------------------
/**
 * @brief   �L�����Z����̃{�^���҂�
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_return_wait(TRADELIST_WORK *wk)
{
	if(sys.trg & PAD_BUTTON_A){
		GF_BGL_ScrFill(	wk->bgl, GF_BGL_FRAME0_M, 0, 0, 0, 32, 24,  0);
		TradeListWindowPrint(
			&wk->TradeListWin[BMP_M_MES1_WIN],
			mes_dstrade_02_01,FONT_TALK,
			wk->MsgManager,
			wk->PokeNameWordSet
		);
		wk->func=trade_seq_normal;
		trade_icon_reappear( wk );
	}

	return MODE_NORMAL;
}



//------------------��������Ƃ������蒠

#define _FRIENDNOTE_END_TIMING   (19)    // �Ƃ������蒠���͊�������

// �蒠�o�^�̃��b�Z�[�W�̕\��
static void _friendMessagePrint(TRADELIST_WORK* wk, int msgNo)
{
    TradeListWindowPrint(
        &wk->TradeListWin[BMP_M_MES3_WIN],
        msgNo,
        FONT_TALK,
        wk->friendMsgManager,
        wk->friendWordSet
        );
}


//------------------------------------------------------------------
/**
 * �폜�͂�߂Ƃ��HYESNO
 * @param   wk		
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_friend_endyesno( TRADELIST_WORK* wk )
{
    int i;
    switch(TradeListYesNoFunc(wk->bgl, &wk->YesNoMenu, &wk->yesnoseq)){
	case 0:
		wk->func = trade_seq_friend_regist_init;
		break;
	case BMPMENU_CANCEL:
        _friendMessagePrint(wk,msg_wifi_note_add_02);
        wk->func = trade_seq_friend_regist_del_yesno;
		break;
	default:
        break;
	}
	return MODE_NORMAL;
}



//------------------------------------------------------------------
/**
 * �폜���j���[�\��
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------

static int trade_seq_friend_regist_erase_yesno( TRADELIST_WORK* wk )
{
    MYSTATUS* pMyStatus;
    int i;
    switch(TradeListYesNoFunc(wk->bgl, &wk->YesNoMenu, &wk->yesnoseq)){
	case 0:
        // ����+�ǉ�
        WifiList_ResetData(wk->pWifiList, wk->erasePos);
        dwc_friendWrite(wk->savedata, wk->addFriendNo,WIFILIST_FRIEND_MAX-1,HEAPID_TRADELIST, FALSE);
		wk->func = trade_seq_friend_regist_init;
		break;
	case BMPMENU_CANCEL:
        pMyStatus = CommInfoGetMyStatus(wk->addFriendNo);
        WORDSET_RegisterPlayerName(wk->friendWordSet, 0, pMyStatus);
        _friendMessagePrint(wk,msg_wifi_note_add_03);
        wk->func = trade_seq_friend_endyesno;
		break;
	default:
        break;
	}
	return MODE_NORMAL;
}

//------------------------------------------------------------------
/**
 * �폜���j���[�\��
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------

static int trade_seq_friend_regist_delmenu_wait( TRADELIST_WORK* wk )
{
    int ret;
    MYSTATUS* pMyStatus;

    ret = BmpListMain(wk->lw);
    switch(ret){
    case BMPLIST_NULL:
        return MODE_NORMAL;
    case BMPLIST_CANCEL:
		Snd_SePlay( SEQ_SE_DP_SELECT );
        pMyStatus = CommInfoGetMyStatus(wk->addFriendNo);
        WORDSET_RegisterPlayerName(wk->friendWordSet, 0, pMyStatus);
        _friendMessagePrint(wk,msg_wifi_note_add_03);
        wk->func = trade_seq_friend_endyesno;
        break;
    default:
		Snd_SePlay( SEQ_SE_DP_SELECT );
        wk->erasePos = ret;
        {
            MYSTATUS* pMy = MyStatus_AllocWork(HEAPID_TRADELIST);
            MyStatus_SetMyName(pMy,WifiList_GetFriendNamePtr(wk->pWifiList,ret));
            WORDSET_RegisterPlayerName(wk->friendWordSet, 0, pMy);
            sys_FreeMemoryEz(pMy);
        }
        _friendMessagePrint(wk,msg_wifi_note_add_04);
        wk->func = trade_seq_friend_regist_erase_yesno;
        break;
    }

    BmpMenuWinClear(&wk->listWin, WINDOW_TRANS_ON );
    GF_BGL_BmpWinDel(&wk->listWin);
    BmpListExit(wk->lw, NULL, NULL);
    BMP_MENULIST_Delete( wk->menulist );
	return MODE_NORMAL;
}

//------------------------------------------------------------------
/**
 * �폜���j���[�\��
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------

static int trade_seq_friend_regist_delmenu_init( TRADELIST_WORK* wk )
{
    BMPLIST_HEADER list_h;
    int count = WifiList_GetFriendDataNum(wk->pWifiList);
    int line = 5;

    //BMP�E�B���h�E����
    wk->menulist = BMP_MENULIST_Create( count+1, HEAPID_TRADELIST );
	{
		MSGDATA_MANAGER* msgman;
        STRBUF* pExpStrBuf = STRBUF_Create(100,HEAPID_TRADELIST);
		int i=0;

        for(i=0; i < WIFILIST_FRIEND_MAX ; i++){
            if(WifiList_IsFriendData( wk->pWifiList, i )){
                STRBUF_SetStringCode(pExpStrBuf, WifiList_GetFriendNamePtr(wk->pWifiList, i));
                BMP_MENULIST_AddString( wk->menulist, pExpStrBuf, i);
            }
		}
        BMP_MENULIST_AddArchiveString( wk->menulist, wk->friendMsgManager,
                                       msg_wifi_note_12, BMPLIST_CANCEL);
        STRBUF_Delete(pExpStrBuf);
    }
    wk->lw = TradeListMenuInit(wk->menulist, count, &wk->listWin, wk->bgl);
    
    wk->func = trade_seq_friend_regist_delmenu_wait;
	return MODE_NORMAL;
}

//------------------------------------------------------------------
/**
 * �Ƃ������蒠�폜�m�F
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_friend_regist_del_yesno(TRADELIST_WORK* wk)
{
    MYSTATUS* pMyStatus;
    int i;
    switch(TradeListYesNoFunc(wk->bgl, &wk->YesNoMenu, &wk->yesnoseq)){
	case 0:
		wk->func = trade_seq_friend_regist_delmenu_init;
		break;
	case BMPMENU_CANCEL:
        pMyStatus = CommInfoGetMyStatus(wk->addFriendNo);
        WORDSET_RegisterPlayerName(wk->friendWordSet, 0, pMyStatus);
        _friendMessagePrint(wk,msg_wifi_note_add_03);
        wk->func = trade_seq_friend_endyesno;
		break;
	default:
		break;
	}
	return MODE_NORMAL;
}

//------------------------------------------------------------------
/**
 * �Ƃ������蒠�o�^�I��
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_friend_regist_yesno(TRADELIST_WORK* wk)
{
    int i;

    switch(TradeListYesNoFunc(wk->bgl, &wk->YesNoMenu, &wk->yesnoseq)){
	case 0:
		wk->func = trade_seq_friend_regist_init;
        // �o�^
        for(i = 0; i < WIFILIST_FRIEND_MAX;i++){
            if( !WifiList_IsFriendData( wk->pWifiList, i ) ){
                dwc_friendWrite(wk->savedata, wk->addFriendNo,i,HEAPID_TRADELIST, FALSE);
                break;
            }
        }
        if(i == WIFILIST_FRIEND_MAX){
            // �������߂Ȃ��ꍇ
            _friendMessagePrint(wk,msg_wifi_note_add_02);
            wk->func = trade_seq_friend_regist_del_yesno;
            return FALSE;
        }
		break;
	case BMPMENU_CANCEL:
        wk->func = trade_seq_friend_regist_init;
		break;
	default:
		break;
	}
	return MODE_NORMAL;
}

//------------------------------------------------------------------
/**
 * �Ƃ������蒠�I�������҂�
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------

static int trade_seq_friend_regist_timing(TRADELIST_WORK* wk)
{
    if(CommIsTimingSync(_FRIENDNOTE_END_TIMING)){
		return MODE_END_SELECT;
    }
	return MODE_NORMAL;
}


//------------------------------------------------------------------
/**
 * �Ƃ������蒠�o�^�J�n
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_friend_regist_init(TRADELIST_WORK* wk)
{
    int i;
    MYSTATUS* pMyStatus;

    wk->addFriendNo = -1;
    for(i = 0; i < CommGetConnectNum(); i++){
        if(wk->friendNetID[i] == DWCFRIEND_NODATA){
            wk->addFriendNo = i;
            wk->friendNetID[i] = DWCFRIEND_INLIST;
            break;
        }
    }
    if(wk->addFriendNo == -1){  // �o�^����
        MSGMAN_Delete( wk->friendMsgManager );
        WORDSET_Delete( wk->friendWordSet );
        CommTimingSyncStart( _FRIENDNOTE_END_TIMING );
		TradeListWindowPrint(
			&wk->TradeListWin[BMP_M_MES3_WIN],
			mes_dstrade_04_07,FONT_TALK,
			wk->MsgManager,
			wk->PokeNameWordSet
		);

        wk->func = trade_seq_friend_regist_timing;
        return MODE_NORMAL;
    }
	//�蒠�������Ă�����
	if( MyItem_CheckItem( SaveData_GetMyItem(wk->savedata),
							ITEM_TOMODATITETYOU,1,HEAPID_TRADELIST) == TRUE ){
        pMyStatus = CommInfoGetMyStatus(wk->addFriendNo);
        WORDSET_RegisterPlayerName(wk->friendWordSet, 0, pMyStatus);
        _friendMessagePrint(wk,msg_wifi_note_add_01);
        wk->func = trade_seq_friend_regist_yesno;
        return MODE_NORMAL;
    }
    // �����ĂȂ��Ȃ�AUTO
    {
        WIFI_LIST* pList = SaveData_GetWifiListData(wk->savedata);
        for(i = 0; i < WIFILIST_FRIEND_MAX;i++){
            if( !WifiList_IsFriendData( pList, i ) ){
                dwc_friendWrite(wk->savedata, wk->addFriendNo,
                                i, HEAPID_TRADELIST, FALSE);
                break;
            }
        }
    }
    wk->func = trade_seq_friend_regist_init;
    return MODE_NORMAL;
}

//------------------------------------------------------------------
/**
 * �Ƃ������蒠�o�^����    k.ohno
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_friend_regist(TRADELIST_WORK* wk)
{
    if(FALSE == dwc_friendAutoInputCheck(wk->savedata, wk->friendNetID, HEAPID_TRADELIST)){
        OHNO_PRINT("����̓o�^�͖���\n");
        CommTimingSyncStart( _FRIENDNOTE_END_TIMING );

		TradeListWindowPrint(
			&wk->TradeListWin[BMP_M_MES3_WIN],
			mes_dstrade_04_07,FONT_TALK,
			wk->MsgManager,
			wk->PokeNameWordSet
		);

        wk->func = trade_seq_friend_regist_timing;
        return MODE_NORMAL;  // ����̓o�^�͖���
    }
    wk->friendWordSet    = WORDSET_Create( HEAPID_TRADELIST );
    wk->friendMsgManager = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_wifi_note_dat, HEAPID_TRADELIST );
    wk->pWifiList = SaveData_GetWifiListData(wk->savedata);

    wk->func = trade_seq_friend_regist_init;
	return MODE_NORMAL;
}
//------------------�����܂łƂ������蒠

//------------------------------------------------------------------
/**
 * �I��
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_end(TRADELIST_WORK *wk)
{
	if(wk->end_flag[0]!=0 && wk->end_flag[1]!=0){
		if(wk->end_flag[0]==1 && wk->end_flag[1]==1){
            wk->func = trade_seq_friend_regist;
		}else{
			wk->func = trade_seq_return;
		}
		wk->end_flag[0] = 0;
		wk->end_flag[1] = 0;
		wk->fail_reason = mes_dstrade_04_08;	// �����̓L�����Z������܂����B
	}
	return MODE_NORMAL;
}


//------------------------------------------------------------------
/**
 * �����̃|�P������I��
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_mypoke(TRADELIST_WORK *wk )
{
	BMPMENU_HEADER temp;

	temp.font  = FONT_SYSTEM;
	temp.x_max = 1;
	temp.y_max = 3;
	temp.line_spc = 0;
	temp.c_disp_f = 0;
	temp.loop_f   = 0;
	
	WORDSET_RegisterPokeNickName(wk->WindowStrWordSet, 0, 
		PPPPointerGet(PokeParty_GetMemberPointer(wk->MyPokeParty, wk->cursor_pos[0])));
	
	GF_BGL_ScrFill(	wk->bgl, GF_BGL_FRAME0_M, 0, 0, 0, 32, 24,  0);
	TradeListWindowPrint(
		&wk->TradeListWin[BMP_M_MES2_WIN],
		mes_dstrade_02_02,FONT_TALK,
		wk->MsgManager,
		wk->WindowStrWordSet
	);
	
	wk->BmpMenuList = BMP_MENULIST_Create( 3, HEAPID_TRADELIST );
	BMP_MENULIST_AddArchiveString( wk->BmpMenuList, wk->MsgManager, mes_dstrade_03_01, 0 );		// �u�悳���݂�v
	BMP_MENULIST_AddArchiveString( wk->BmpMenuList, wk->MsgManager, mes_dstrade_03_02, 1 );		// �u�������񂷂�v
	BMP_MENULIST_AddArchiveString( wk->BmpMenuList, wk->MsgManager, mes_dstrade_03_03, 2 );
	
	temp.menu = wk->BmpMenuList;
	temp.win  = &wk->TradeListWin[BMP_M_SELECT1_WIN];

	TradeListWinWrite( &wk->TradeListWin[BMP_M_SELECT1_WIN] );
	wk->BmpMenuWork = BmpMenuAddEx( &temp, 8, 0, 0, HEAPID_TRADELIST, PAD_BUTTON_B );
	

	wk->func = trade_seq_mypoke_menu;
	
	return MODE_NORMAL;
}

#ifdef DEBUG_PAD_ON
	#define SELECT_STATUS	( 1 )
	#define SELECT_TRADE	( 0 )
	#define SELECT_MODORU	( 2 )
#else
	#define SELECT_STATUS	( 0 )
	#define SELECT_TRADE	( 1 )
	#define SELECT_MODORU	( 2 )
#endif

//------------------------------------------------------------------
/**
 * $brief   �����̃|�P�����̎��̑I��
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_mypoke_menu(TRADELIST_WORK *wk )
{
	switch(BmpMenuMain( wk->BmpMenuWork )){
	case SELECT_STATUS:		// �悳���݂�
		GF_BGL_ScrFill(	wk->bgl, GF_BGL_FRAME0_M, 0, 0, 0, 32, 24,  0);
		TradeListWindowPrint(
			&wk->TradeListWin[BMP_M_MES1_WIN],
			mes_dstrade_02_01,FONT_TALK,
			wk->MsgManager,
			wk->PokeNameWordSet
		);
		BmpMenuExit( wk->BmpMenuWork, NULL );
		BMP_MENULIST_Delete( wk->BmpMenuList );
		wk->func = trade_seq_normal;
		return MODE_STATUS_SELECT;
		break;
	case SELECT_TRADE:		// �������񂷂�
		GF_BGL_ScrFill(	wk->bgl, GF_BGL_FRAME0_M, 0, 0, 0, 32, 24,  0);
		TradeListWindowPrint(
			&wk->TradeListWin[BMP_M_MES3_WIN],
			mes_dstrade_04_01,FONT_TALK,
			wk->MsgManager,
			wk->PokeNameWordSet
		);
		BmpMenuExit( wk->BmpMenuWork, NULL );
		BMP_MENULIST_Delete( wk->BmpMenuList );
		wk->func = trade_seq_decide;
		break;
	case SELECT_MODORU: case BMPMENU_CANCEL:	// �L�����Z��
		GF_BGL_ScrFill(	wk->bgl, GF_BGL_FRAME0_M, 0, 0, 0, 32, 24,  0);
		TradeListWindowPrint(
			&wk->TradeListWin[BMP_M_MES1_WIN],
			mes_dstrade_02_01,FONT_TALK,
			wk->MsgManager,
			wk->PokeNameWordSet
		);
		BmpMenuExit( wk->BmpMenuWork, NULL );
		BMP_MENULIST_Delete( wk->BmpMenuList );
		wk->func = trade_seq_normal;
		break;
	}
	return MODE_NORMAL;

}



//------------------------------------------------------------------
/**
 * $brief   �����|�P��������
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_decide(TRADELIST_WORK *wk )
{
	GF_BGL_ScrFill(	wk->bgl, GF_BGL_FRAME0_M, 0, 0, 0, 32, 24,  0);
	TradeListWindowPrint(
		&wk->TradeListWin[BMP_M_MES3_WIN],
		mes_dstrade_04_01,FONT_TALK,
		wk->MsgManager,
		wk->PokeNameWordSet
	);

	// ��������|�P���������肵�����Ƃ�ʒm
	TradeListCommDiffSend( wk, CT_TRADE_DECIDE, DECIDE_COMMAND_NEXT);
	
	wk->func = trade_seq_decide_wait;
	
	return MODE_NORMAL;
}

//------------------------------------------------------------------
/**
 * $brief   ����҂�
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_decide_wait(TRADELIST_WORK *wk )
{
	if(wk->end_flag[0]!=0 && wk->end_flag[1]!=0){
		if(wk->end_flag[0]==DECIDE_COMMAND_NEXT && wk->end_flag[1]==DECIDE_COMMAND_NEXT){
			wk->func = trade_seq_icon_move;
		}else{
			wk->func = trade_seq_return;
		}
		wk->fail_reason = mes_dstrade_04_03;	// �����̓L�����Z������܂����B
		wk->end_flag[0] = 0;
		wk->end_flag[1] = 0;


	}

	return MODE_NORMAL;
}


//------------------------------------------------------------------
/**
 * @brief   �������邱�Ƃɂ����|�P�����A�C�R���������Ɉړ�����
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_icon_move( TRADELIST_WORK *wk )
{
	int i;

	// �I�������|�P�����ȊO�͉B��
	for(i=0;i<6;i++){
		if(i!=wk->cursor_pos[0]){
			CLACT_SetDrawFlag(wk->PokeIconActWork[i],0);
			if(wk->pokeInfo[i].item){
				CLACT_SetDrawFlag(wk->PokeItemActWork[i],0);
			}
			if(wk->pokeInfo[i].customball){
				CLACT_SetDrawFlag(wk->PokeCBallActWork[i],0);
			}
		}
		GF_BGL_BmpWinOffVReq(&wk->TradeListWin[BMP_M_MYPOKENAME0_WIN+i]);
		if(i!=(wk->cursor_pos[1]-6)){
			CLACT_SetDrawFlag(wk->PokeIconActWork[i+6],0);
			if(wk->pokeInfo[i+6].item){
				CLACT_SetDrawFlag(wk->PokeItemActWork[i+6],0);
			}
			if(wk->pokeInfo[i+6].customball){
				CLACT_SetDrawFlag(wk->PokeCBallActWork[i+6],0);
			}
		}
		GF_BGL_BmpWinOffVReq(&wk->TradeListWin[BMP_M_FRIENDPOKENAME0_WIN+i]);
	}
	
	// �J�[�\�����B��
	CLACT_SetDrawFlag(wk->clActWork[0],0);
	CLACT_SetDrawFlag(wk->clActWork[1],0);

	// �ړ������ݒ�
	AnimePosSet(wk->myanimpos, main_cursor_pos[wk->cursor_pos[0]][0]+POKEICON_DIFFX, 
							   main_cursor_pos[wk->cursor_pos[0]][1]+POKEICON_DIFFY,
							   6*8, 6*8);
	AnimePosSet(wk->f_animpos, main_cursor_pos[wk->cursor_pos[1]][0]+POKEICON_DIFFX, 
							   main_cursor_pos[wk->cursor_pos[1]][1]+POKEICON_DIFFY,
							   22*8, 6*8);

	wk->animcount = 0;
	wk->func      = trade_seq_icon_move_wait;

	return MODE_NORMAL;
}

//------------------------------------------------------------------
/**
 * @brief   �ړ��A�j���p�n�_�E�I�_�w��
 *
 * @param   animpos[]		
 * @param   sx		
 * @param   sy		
 * @param   ex		
 * @param   ey		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void AnimePosSet(VecFx32 animpos[], int sx, int sy, int ex, int ey)
{
	animpos[0].x = FX32_ONE*sx;
	animpos[0].y = FX32_ONE*sy;
	animpos[1].x = FX32_ONE*ex;
	animpos[1].y = FX32_ONE*ey;
	
}

#define ICON_MOVE_MAX	(20)

//------------------------------------------------------------------
/**
 * @brief   �A�C�R���ړ�
 *
 * @param   icon		
 * @param   item		
 * @param   count		
 * @param   pos[]		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void PokeIconPosSet( CLACT_WORK_PTR icon, CLACT_WORK_PTR item, CLACT_WORK_PTR cball, int count, VecFx32 pos[], POKE_INFO *info )
{
	VecFx32 pokeVex,itemVex,cballVex;

	// �|�P�����A�C�R�����W
	pokeVex.x = pos[0].x + ((pos[1].x-pos[0].x)/ICON_MOVE_MAX)*count;
	pokeVex.y = pos[0].y + ((pos[1].y-pos[0].y)/ICON_MOVE_MAX)*count;

	CLACT_SetMatrix(icon, &pokeVex);

	// �A�C�e�����W
	if(info->item){
		itemVex.x = pokeVex.x+20*FX32_ONE;
		itemVex.y = pokeVex.y+(16+6)*FX32_ONE;
		CLACT_SetMatrix(item, &itemVex);
	}

	if(info->customball){
		cballVex.x = pokeVex.x+(20+8)*FX32_ONE;
		cballVex.y = pokeVex.y+(16+6)*FX32_ONE;
		CLACT_SetMatrix(cball, &cballVex);
	}
}

//------------------------------------------------------------------
/**
 * @brief   �A�C�R���ړ��I���҂�
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_icon_move_wait( TRADELIST_WORK *wk )
{
	wk->animcount++;

	// �A�C�R���ړ��A�j��
	PokeIconPosSet( wk->PokeIconActWork[wk->cursor_pos[0]],
					wk->PokeItemActWork[wk->cursor_pos[0]],
					wk->PokeCBallActWork[wk->cursor_pos[0]],
					wk->animcount, wk->myanimpos, &wk->pokeInfo[wk->cursor_pos[0]] );
	PokeIconPosSet( wk->PokeIconActWork[wk->cursor_pos[1]],
					wk->PokeItemActWork[wk->cursor_pos[1]],
					wk->PokeCBallActWork[wk->cursor_pos[1]],
					wk->animcount, wk->f_animpos, &wk->pokeInfo[wk->cursor_pos[1]] );
	if(wk->animcount==ICON_MOVE_MAX+1){
		// �����ɂQ�̖̂��O��\��
		PokeNamePrint(&wk->TradeListWin[BMP_M_EX_MYPOKENAME_WIN], 
						wk->MyPokeParty, wk->cursor_pos[0], TRADELIST_POKENAME_W, CENTER_PRINT);
		PokeNamePrint(&wk->TradeListWin[BMP_M_EX_F_POKENAME_WIN], 
						wk->FriendPokeParty, wk->cursor_pos[1]-6, TRADELIST_POKENAME_W, CENTER_PRINT);

		// ����ʉE�p�l����\������
		SubLcd_RightPanelOn(wk, wk->cursor_pos[1]);
		wk->func = trade_seq_trade_yesno;
		CLACT_SetDrawFlag( wk->ExchangeArrow, 1 );

	}	

	return MODE_NORMAL;
}

//------------------------------------------------------------------
/**
 * @brief   ���̈ʒu�ɖ߂��ĕ\�����߂�
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static void trade_icon_reappear( TRADELIST_WORK *wk )
{
	int i;
	VecFx32 tmpVex;

	// �����ɕ\�������|�P�����̖��O���B��
	GF_BGL_BmpWinOffVReq(&wk->TradeListWin[BMP_M_EX_MYPOKENAME_WIN]);
	GF_BGL_BmpWinOffVReq(&wk->TradeListWin[BMP_M_EX_F_POKENAME_WIN]);

	// �B�����|�P������S�Ė߂�
	for(i=0;i<TRADELIST_POKE_MAX;i++){
		if(wk->pokeInfo[i].exist!=0){

			Clact_SetPos( wk->PokeIconActWork[i],
							main_cursor_pos[i][0] + POKEICON_DIFFX,
							main_cursor_pos[i][1] + POKEICON_DIFFY );


			CLACT_SetDrawFlag(wk->PokeIconActWork[i],1);

			if(wk->pokeInfo[i].item){
				Clact_SetPos(wk->PokeItemActWork[i],
								main_cursor_pos[i][0] + POKEITEM_DIFFX,
								main_cursor_pos[i][1] + POKEITEM_DIFFY );

				CLACT_SetDrawFlag(wk->PokeItemActWork[i],1);
			}

			if(wk->pokeInfo[i].customball){
				Clact_SetPos( wk->PokeCBallActWork[i], 
								main_cursor_pos[i][0] + POKECBALL_DIFFX, 
								main_cursor_pos[i][1] + POKEITEM_DIFFY );
				CLACT_SetDrawFlag(wk->PokeCBallActWork[i],1);
			}

			GF_BGL_BmpWinOnVReq(&wk->TradeListWin[BMP_M_MYPOKENAME0_WIN+i]);
		}
	}
	
	// �J�[�\���\������
	CLACT_SetDrawFlag(wk->clActWork[0],1);
	CLACT_SetDrawFlag(wk->clActWork[1],1);

	// ����ʉE����\��
	PokeStr_SubLcdOff(wk->TradeListWin, 1, wk);
	CLACT_SetDrawFlag(wk->SubLCDIconActWork[3], 0);	

	// �������B��
	CLACT_SetDrawFlag( wk->ExchangeArrow, 0 );


}
//------------------------------------------------------------------
/**
 * $brief   ���݂��̃|�P�����Ō������邩�����₷��
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_trade_yesno(TRADELIST_WORK *wk )
{
	
	GF_BGL_ScrFill(	wk->bgl, GF_BGL_FRAME0_M, 0, 0, 0, 32, 24,  0);
	WORDSET_RegisterPokeNickName(wk->WindowStrWordSet, 0, 
		PPPPointerGet(PokeParty_GetMemberPointer(wk->MyPokeParty,     wk->cursor_pos[0])));
	WORDSET_RegisterPokeNickName(wk->WindowStrWordSet, 1, 
		PPPPointerGet(PokeParty_GetMemberPointer(wk->FriendPokeParty, wk->cursor_pos[1]-6)));

	TradeListWindowPrint(
		&wk->TradeListWin[BMP_M_MES3_WIN],
		mes_dstrade_04_02,FONT_TALK,
		wk->MsgManager,
		wk->WindowStrWordSet
	);
	
	
	wk->func = trade_seq_trade_yesno_wait;
	return MODE_NORMAL;
}

//------------------------------------------------------------------
/**
 * $brief   �u�������܂����H�v�͂��E������
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_trade_yesno_wait(TRADELIST_WORK *wk)
{
	switch(TradeListYesNoFunc(wk->bgl, &wk->YesNoMenu, &wk->yesnoseq)){
	case 0:
		// ��������
		if(wk->pokeInfo[wk->cursor_pos[0]].customball==0){
			// �Ă����������Ȃ�Ȃ��H
			if(TradeTemochiCheck( wk )){
				GF_BGL_ScrFill(	wk->bgl, GF_BGL_FRAME0_M, 0, 0, 0, 32, 24,  0);
				TradeListWindowPrint(
					&wk->TradeListWin[BMP_M_MES3_WIN],
					mes_dstrade_04_01,FONT_TALK,
					wk->MsgManager,
					wk->PokeNameWordSet
				);
				wk->func = trade_seq_trade_yesno_result;
				TradeListCommDiffSend( wk, CT_TRADE_DECIDE, DECIDE_COMMAND_YES);
				wk->result = TRADELIST_END_DEMO;
			}else{
				// �Ă������Ȃ��Ȃ邩��������Ă͂����Ȃ�
				wk->func = trade_seq_trade_yesno_result;
				TradeListCommDiffSend( wk, CT_TRADE_DECIDE, DECIDE_COMMAND_NO);
			}
		}else{
			// �J�X�^���{�[�������Ă���Ȃ�
			wk->func = trade_seq_customball_yesno;
		}
		break;
	case BMPMENU_CANCEL:
		// ��߂鎖������
		GF_BGL_ScrFill(	wk->bgl, GF_BGL_FRAME0_M, 0, 0, 0, 32, 24,  0);
		TradeListWindowPrint(
			&wk->TradeListWin[BMP_M_MES3_WIN],
			mes_dstrade_04_01,FONT_TALK,
			wk->MsgManager,
			wk->PokeNameWordSet
		);
		wk->func = trade_seq_trade_yesno_result;
		TradeListCommDiffSend( wk, CT_TRADE_DECIDE, DECIDE_COMMAND_NO);
		break;
	default:
		break;
	}

	return MODE_NORMAL;
}



//------------------------------------------------------------------
/**
 * $brief   �J�X�^���{�[�������Ă��鎞�͂͂���鎖�𕷂�
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_customball_yesno(TRADELIST_WORK *wk )
{
	
	GF_BGL_ScrFill(	wk->bgl, GF_BGL_FRAME0_M, 0, 0, 0, 32, 24,  0);

	// �{�[���J�X�^�}�C�Y���O��܂�����낵���ł����H
	TradeListWindowPrint(
		&wk->TradeListWin[BMP_M_MES3_WIN],
		mes_dstrade_04_15,FONT_TALK,
		wk->MsgManager,
		wk->WindowStrWordSet
	);
	
	
	wk->func = trade_seq_customball_yesno_wait;
	return MODE_NORMAL;
}

//------------------------------------------------------------------
/**
 * $brief   �u�J�X�^���{�[�����O��܂�����낵���ł����H�v�͂��E������
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_customball_yesno_wait(TRADELIST_WORK *wk)
{
	switch(TradeListYesNoFunc(wk->bgl, &wk->YesNoMenu, &wk->yesnoseq)){
	case 0:
		GF_BGL_ScrFill(	wk->bgl, GF_BGL_FRAME0_M, 0, 0, 0, 32, 24,  0);
		TradeListWindowPrint(
			&wk->TradeListWin[BMP_M_MES3_WIN],
			mes_dstrade_04_01,FONT_TALK,
			wk->MsgManager,
			wk->PokeNameWordSet
		);
		wk->func = trade_seq_trade_yesno_result;
		// ��������
		TradeListCommDiffSend( wk, CT_TRADE_DECIDE, DECIDE_COMMAND_YES);
		wk->result = TRADELIST_END_DEMO;
		break;
	case BMPMENU_CANCEL:
		GF_BGL_ScrFill(	wk->bgl, GF_BGL_FRAME0_M, 0, 0, 0, 32, 24,  0);
		TradeListWindowPrint(
			&wk->TradeListWin[BMP_M_MES3_WIN],
			mes_dstrade_04_01,FONT_TALK,
			wk->MsgManager,
			wk->PokeNameWordSet
		);
		wk->func = trade_seq_trade_yesno_result;
		// ��߂鎖������
		TradeListCommDiffSend( wk, CT_TRADE_DECIDE, DECIDE_COMMAND_NO);
		break;
	default:
		break;
	}

	return MODE_NORMAL;
}


//------------------------------------------------------------------
/**
 * $brief   �������܂����H�̌���҂�
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_trade_yesno_result( TRADELIST_WORK *wk )
{
	if(wk->end_flag[0]!=0 && wk->end_flag[1]!=0){
		if(wk->end_flag[0]==DECIDE_COMMAND_YES && wk->end_flag[1]==DECIDE_COMMAND_YES){
            wk->tradeNum++;
			wk->func = trade_seq_go_next;
		}else{
			wk->func = trade_seq_return;
		}
		wk->end_flag[0] = 0;
		wk->end_flag[1] = 0;
		if(TradeTemochiCheck(wk)){
			wk->fail_reason = mes_dstrade_04_03;	// �����̓L�����Z������܂����B
		}else{
			wk->fail_reason = mes_dstrade_04_13;	// �Ă������Ȃ��Ȃ��Ă��܂�
		}

	}

	return MODE_NORMAL;
	
}


//------------------------------------------------------------------
/**
 * $brief   �|�P��������
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static  int trade_seq_go_next( TRADELIST_WORK *wk )
{

    CommInfoSetTradeResult(wk->savedata, 1); // �����񐔂̋L�^ k.ohno
	// �|�P�����f�[�^����ւ�
	PokemonDataExchange(wk->MyPokeParty, wk->FriendPokeParty, wk->cursor_pos[0], wk->cursor_pos[1]-6, wk->param);

	wk->func = trade_seq_return;
	return MODE_END_SELECT;

}


//#ifdef PM_DEBUG	
//	// �Z�[�u�e�X�g�p�ɌĂяo��
//	wk->func = trade_seq_save_text;
//	return MODE_NORMAL;
//#else
//	// ��������������
//	wk->func = trade_seq_return;
//	return MODE_END_SELECT;
//#endif


static int trade_seq_save_text( TRADELIST_WORK *wk )
{


	// �Ƃ�������҂��Ă��܂��B
	TradeListWindowPrint(
			&wk->TradeListWin[BMP_M_MES3_WIN],
			mes_dstrade_04_01,FONT_TALK,
			wk->MsgManager,
			wk->PokeNameWordSet
		);

	wk->func = trade_seq_save_func;
	wk->saveseq = 0;
	
	return MODE_NORMAL;
}

int CommSaveSequence( SAVEDATA *savedata, int *seq, int *wait );

static int trade_seq_save_func( TRADELIST_WORK *wk )
{
	
//	SaveData_Save(wk->savedata);
//	CommTimingSyncStart( 5 );

	if(CommSaveSequence(wk->savedata, &wk->saveseq, &wk->savewait)){
		wk->func = trade_seq_save_wait;
	}

	return MODE_NORMAL;

}


static int trade_seq_save_wait( TRADELIST_WORK *wk )
{
//	if(CommIsTimingSync(5)){
	
		wk->func = trade_seq_return;
		return MODE_END_SELECT;
//	}
//	return MODE_NORMAL;
	
}


//==============================================================================
/**
 * $brief   �ʐM���Z�[�u�V�[�P���X
 *			
 *
 * @param   savedata	�Z�[�u�f�[�^�ւ̃|�C���^
 * @param   seq			�V�[�P���X�Ǘ����[�N�i���Ȃ炸0�ɏ��������Ă���Ăюn�߂Ă��������j
 * @param   wait		�E�F�C�g�Ǘ����[�N
 *
 * @retval  int			0:�I�����ĂȂ�	1���Ԃ��Ă���܂ŌĂё����Ă�������
 */
//==============================================================================
int CommSaveSequence( SAVEDATA *savedata, int *seq, int *wait )
{	
	switch(*seq){
	case 0:
		// �Z�[�u�J�n����
		CommTimingSyncStart( 252 );
		(*seq)++;
		break;
	case 1:
		// �e�@�̏������z���E�F�C�g�ɗ��p����
		if(CommIsTimingSync(252)){
//			*wait = CommInfoGetMacAddress( 0 )[3] % 90;
			MYSTATUS *mystatus = CommInfoGetMyStatus(0);
			*wait = MyStatus_GetGold(mystatus) % 90;
			(*seq)++;
			OS_TPrintf("�Z�[�u�V�[�P���X�F�P��ړ���");
		}
		break;

	case 2:
		// �E�F�C�g��0�ɂȂ�����Z�[�u�J�n
		if(*wait==0){
//			SaveData_Save(savedata);
			(*seq)++;
		}
		(*wait)--;
		break;
	case 3:
		// �Z�[�u�I����ɓ���
		CommTimingSyncStart( 253 );
		(*seq)++;
		break;
	case 4:
		// ����������I��
		if(CommIsTimingSync(253)){
			OS_TPrintf("�Z�[�u�V�[�P���X�F�Q��ړ���");
			(*seq)=0;
			return 1;
		}
		break;
	}
	return 0;
}
//------------------------------------------------------------------
/**
 * ����̃|�P������I�񂾁����j���[
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_friendpoke(TRADELIST_WORK *wk )
{

	BMPMENU_HEADER temp;

	temp.font  = FONT_SYSTEM;
	temp.x_max = 1;
	temp.y_max = 2;
	temp.line_spc = 0;
	temp.c_disp_f = 0;
	temp.loop_f   = 0;
	
	WORDSET_RegisterPokeNickName(wk->WindowStrWordSet, 0, 
		PPPPointerGet(PokeParty_GetMemberPointer(wk->FriendPokeParty, wk->cursor_pos[0]-6)));
	
	GF_BGL_ScrFill(	wk->bgl, GF_BGL_FRAME0_M, 0, 0, 0, 32, 24,  0);
	TradeListWindowPrint(
		&wk->TradeListWin[BMP_M_MES2_WIN],
		mes_dstrade_02_02,FONT_TALK,
		wk->MsgManager,
		wk->WindowStrWordSet
	);
	
	wk->BmpMenuList = BMP_MENULIST_Create( 2, HEAPID_TRADELIST );
	BMP_MENULIST_AddArchiveString( wk->BmpMenuList, wk->MsgManager, mes_dstrade_03_01, 0 );
	BMP_MENULIST_AddArchiveString( wk->BmpMenuList, wk->MsgManager, mes_dstrade_03_03, 1 );
	
	temp.menu = wk->BmpMenuList;
	temp.win  = &wk->TradeListWin[BMP_M_SELECT2_WIN];

	TradeListWinWrite( &wk->TradeListWin[BMP_M_SELECT2_WIN] );
	wk->BmpMenuWork = BmpMenuAddEx( &temp, 8, 0, 0, HEAPID_TRADELIST, PAD_BUTTON_B );
	

	wk->func = trade_seq_friend_menu;

	return MODE_NORMAL;
	
}

//------------------------------------------------------------------
/**
 * $brief   ����̃|�P������I�����Ă���Ƃ��̃��j���[�҂�
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int trade_seq_friend_menu(TRADELIST_WORK *wk )
{
	switch(BmpMenuMain( wk->BmpMenuWork )){
	// �悳���݂�
	case 0:
		GF_BGL_ScrFill(	wk->bgl, GF_BGL_FRAME0_M, 0, 0, 0, 32, 24,  0);
		TradeListWindowPrint(
			&wk->TradeListWin[BMP_M_MES1_WIN],
			mes_dstrade_02_01,FONT_TALK,
			wk->MsgManager,
			wk->PokeNameWordSet
		);
		wk->func = trade_seq_normal;
		BmpMenuExit( wk->BmpMenuWork, NULL );
		BMP_MENULIST_Delete( wk->BmpMenuList );
		return MODE_STATUS_SELECT;
		break;

	// ���ǂ�
	case 1:case BMPMENU_CANCEL:
		GF_BGL_ScrFill(	wk->bgl, GF_BGL_FRAME0_M, 0, 0, 0, 32, 24,  0);
		TradeListWindowPrint(
			&wk->TradeListWin[BMP_M_MES1_WIN],
			mes_dstrade_02_01,FONT_TALK,
			wk->MsgManager,
			wk->PokeNameWordSet
		);
		BmpMenuExit( wk->BmpMenuWork, NULL );
		BMP_MENULIST_Delete( wk->BmpMenuList );
		wk->func = trade_seq_normal;
		break;
	}
	return MODE_NORMAL;

}



//------------------------------------------------------------------
/**
 * $brief   �|�P�����f�[�^�������[�`��
 *
 * @param   my		
 * @param   your		
 * @param   mysel		
 * @param   yoursel		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void PokemonDataExchange(POKEPARTY *my, POKEPARTY *your, int mysel, int yoursel, TRADELIST_PARAM *param)
{
	POKEMON_PARAM *pp,*pp2;
	
	pp  = PokemonParam_AllocWork(HEAPID_TRADELIST);
	pp2 = PokemonParam_AllocWork(HEAPID_TRADELIST);
	
	//��U�R�s�[
	PokeCopyPPtoPP(PokeParty_GetMemberPointer(  my,   mysel), pp  );
	PokeCopyPPtoPP(PokeParty_GetMemberPointer(your, yoursel), pp2 );

	// �����f���p�Ƀp�����[�^�n��
	PokeCopyPPtoPP( pp  ,param->result_sendPoke);		// �o���|�P����
	PokeCopyPPtoPP( pp2 ,param->result_recvPoke);		// ���炤�|�P����
	MyStatus_Copy(  CommInfoGetMyStatus(CommGetCurrentID()^1),  param->result_partner );	// ����̏��
	param->exchangepos = mysel;


	// ���܂��Ŗ�����΁A�Ȃ��x�ݒ�i�V�O�Ɂj
	if(PokeParaGet(pp2, ID_PARA_tamago_flag, NULL)==0){
		u8 natsuki = FIRST_NATUKIDO;
		PokeParaPut( pp2, ID_PARA_friend, &natsuki );

	}

	// �g���[�i�[������񖄂ߍ���
	TrainerMemoSetPP( pp2,	CommInfoGetMyStatus(CommGetCurrentID()),TRMEMO_ONTRADE_PLACESET, 0, HEAPID_WORLD);

	// �������󂯎��|�P�����̃J�X�^���{�[�������N���A
	PokePara_CustomBallDataInit( pp2 );

	// �Ă�������y���b�v�����Ȃ��Ȃ����琺�f�[�^����������(���̃^�C�~���O���Ƒ��肩��y���b�v��������Ă�����������j
	if(PokeParty_PokemonCheck( my, MONSNO_PERAPPU )==0){
		PERAPVOICE *pv = SaveData_GetPerapVoice( param->savedata );
		PERAPVOICE_ClearExistFlag( pv );
	}

	// �}�ӓ��̓o�^����
	SaveData_GetPokeRegister( param->savedata, pp2 );

	// ��������|�P������ǉ�
	PokeCopyPPtoPP( pp2, PokeParty_GetMemberPointer(  my,   mysel) );
	PokeCopyPPtoPP(  pp, PokeParty_GetMemberPointer(your, yoursel) );

	// �`���m�[�g�p�f�[�^�쐬
	SetFnoteData( param->fnote, pp2 );

	// ���R�[�h�f�[�^����
	RECORD_Inc( param->record, RECID_COMM_TRADE );


	sys_FreeMemoryEz(pp);
	sys_FreeMemoryEz(pp2);
}


//------------------------------------------------------------------
/**
 * @brief   �`���m�[�g�p�̃f�[�^����������
 *
 * @param   fnote		
 * @param   pp		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SetFnoteData( FNOTE_DATA *fnote, POKEMON_PARAM *pp )
{
	void *FnoteWork;
	MYSTATUS *friend = CommInfoGetMyStatus(CommGetCurrentID()^1);
	STRCODE  MonsName[MONS_NAME_SIZE+EOM_SIZE];

	PokeParaGet(pp, ID_PARA_nickname, MonsName);

	FnoteWork = FNOTE_SioUnionChangeDataMake( (STRCODE*)MyStatus_GetMyName(friend), 
												MyStatus_GetMySex(friend), 
												MonsName, 
												PokeSexGet(pp), 
												HEAPID_TRADELIST );

	FNOTE_DataSave( fnote, FnoteWork, FNOTE_TYPE_SIO );


}

//------------------------------------------------------------------
/**
 * $brief   ����ʂ̔w�i�����X�N���[��������
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SubLCD_ScrollFunc( TRADELIST_WORK *wk )
{
	wk->sub_bg2_scroll += 2;
	GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME2_S, GF_BGL_SCROLL_X_SET, wk->sub_bg2_scroll );
	GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME3_M, GF_BGL_SCROLL_X_SET, wk->sub_bg2_scroll );
}

//------------------------------------------------------------------
/**
 * @brief   �Z���A�N�^�[�ɐ���XY�ō��W��n��
 *
 * @param   clact		
 * @param   x		
 * @param   y		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void Clact_SetPos( CLACT_WORK_PTR clact, int x, int y )
{
	VecFx32 tmpVex;

	tmpVex.x = FX32_ONE*x;
	tmpVex.y = FX32_ONE*y;

	CLACT_SetMatrix( clact, &tmpVex);
	
}


//------------------------------------------------------------------
/**
 * @brief   ���ԃA�C�R���ǉ�
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void TimeIconAdd( TRADELIST_WORK *tlw )
{
	tlw->timeWaitWork = TimeWaitIconAdd( &tlw->TradeListWin[BMP_M_MES3_WIN], TALKWIN_FRAME_OFFSET );
}

//------------------------------------------------------------------
/**
 * @brief   ���ԃA�C�R�������iNULL�`�F�b�N����j
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void TimeIconDel( TRADELIST_WORK *tlw )
{
	if(tlw->timeWaitWork!=NULL){
		TimeWaitIconDel(tlw->timeWaitWork);
		tlw->timeWaitWork = NULL;
	}
}


//------------------------------------------------------------------
/**
 * @brief   ���̃|�P��������������ƂĂ��������Ȃ��Ȃ�Ȃ����H
 *
 * @param   wk		
 *
 * @retval  int		1:���v	0:�_��
 */
//------------------------------------------------------------------
static int TradeTemochiCheck( TRADELIST_WORK *wk )
{
	int i;
	int tamagoNum = 0;
	int pokeNum   = PokeParty_GetPokeCount(wk->MyPokeParty);

	// ���I�����Ă���|�P�����ȊO�Ń^�}�S�͂������邩
	for(i=0;i<pokeNum;i++){
		if(i!=wk->cursor_pos[0]){
			tamagoNum += wk->pokeInfo[i].tamago;
		}
	}
	
	// �^�}�S�̐��ƂĂ����̐�-1�Ȃ�����_��
	if(tamagoNum==(pokeNum-1)){
		return 0;
	}
	
	return 1;
}


//------------------------------------------------------------------
/**
 * @brief   �^�C���A�E�g�����J�n
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void TimeoutStart( TRADELIST_WORK *wk )
{
	wk->timeOutFlag = 1;
	wk->timeOutWait = 0;
}


//------------------------------------------------------------------
/**
 * @brief   �^�C���A�E�g����
 *
 * @param   wk		
 *
 * @retval  none
 */
//------------------------------------------------------------------
static void TimeoutErrorCheck( TRADELIST_WORK *wk )
{
	// �^�C���A�E�g�t���O���n�m��
	if(wk->timeOutFlag){
		wk->timeOutWait++;

		// �^�C���A�E�g���Ԃ��߂�����i�����ł͂Q���j
		if(wk->timeOutWait > TIMEOUT_LIMIT){
			// �ʐM�G���[�ݒ�
			CommStateSetError(COMM_ERROR_RESET_OTHER);
			OS_Printf("Timeout...\n");
		}
	}

}

