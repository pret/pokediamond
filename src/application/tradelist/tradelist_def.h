//============================================================================================
/**
 * @file	tradelist_def.h
 * @bfief	�|�P�����������X�g��ʗp�w�b�_
 * @author	Akito Mori
 * @date	05.12.08
 */
//============================================================================================

#ifndef __TRADELIST_DEF_H__
#define __TRADELIST_DEF_H__

#include "savedata/wifilist.h"
#include "savedata/sp_ribbon.h"
#include "system/bmp_list.h"
#include "savedata/perapvoice.h"
#include "application/tradelist.h"
#include "application/p_status.h"
//---------------------------------------------------------------
//--BMPWIN�p��`-------------------------------------------------
//---------------------------------------------------------------

#define TRADELIST_WIN_OFFSET	( 1 )		// BGVRAM�̃X�^�[�g���炱���܂ł̓E�C���h�E�g�p�ɋ󂯂Ă���



// ��̉�ʂ̃g���[�i�[��
#define TRADELIST_MYNAME_X			(  2  )
#define TRADELIST_FRIENDNAME_X		(  20 )
#define TRADELIST_NAME_Y			(   1 )
#define TRADELIST_NAME_W			(  10 )
#define TRADELIST_NAME_H			(   2 )
#define MAIN_MYNAMEBMP_OFFSET   	( TRADELIST_WIN_OFFSET )
#define MAIN_FRIENDNAMEBMP_OFFSET	( MAIN_MYNAMEBMP_OFFSET + ( TRADELIST_NAME_W * TRADELIST_NAME_H))

//��̉�ʂ́u�����v
#define TRADELIST_ENDSTR_X		(  26 )
#define TRADELIST_ENDSTR_Y		(  21 )
#define TRADELIST_ENDSTR_W		(   5 )
#define TRADELIST_ENDSTR_H		(   2 )
#define MAIN_ENDSTRBMP_OFFSET   ( MAIN_FRIENDNAMEBMP_OFFSET + ( TRADELIST_NAME_W * TRADELIST_NAME_H))


// �|�P�����̖��O(12���j
#define TRADELIST_POKENAME_X	(  0 )
#define TRADELIST_POKENAME_Y	(  7 )
#define TRADELIST_POKENAME_W	(  8 )
#define TRADELIST_POKENAME_H	(  2 )
#define TRADELIST_POKENAME_OFSX	(  8 )
#define TRADELIST_POKENAME_OFSY	(  5 )
#define MAIN_POKENAME_OFFSET	( MAIN_ENDSTRBMP_OFFSET    + (TRADELIST_ENDSTR_W*TRADELIST_ENDSTR_H))

#define TRADE_EX_MYPOKENAME_X 	(  4 )
#define TRADE_EX_MYPOKENAME_Y	( 10 )
#define TRADE_EX_F_POKENAME_X 	( 20 )
#define TRADE_EX_F_POKENAME_Y   ( 10 )



// ��̉�ʂ̃��b�Z�[�W�E�C���h�E�P�i�P��Łj
#define TRADELIST_TALKWIN1_X	(   2 )
#define TRADELIST_TALKWIN1_Y	(  21 )
#define TRADELIST_TALKWIN1_W	(  20 )
#define TRADELIST_TALKWIN1_H	(   2 )
#define MAIN_TALKWIN1_OFFSET    (   1 )

// ��̉�ʂ̃��b�Z�[�W�E�C���h�E2�i2��ŁE�Z���j
#define TRADELIST_TALKWIN2_X	(   2 )
#define TRADELIST_TALKWIN2_Y	(  19 )
#define TRADELIST_TALKWIN2_W	(  14 )
#define TRADELIST_TALKWIN2_H	(   4 )
#define MAIN_TALKWIN2_OFFSET    ( TRADELIST_TALKWIN1_W * TRADELIST_TALKWIN1_H )

// ��̉�ʂ̃��b�Z�[�W�E�C���h�E3�i2��ŁE�����j
#define TRADELIST_TALKWIN3_X	(   2 )
#define TRADELIST_TALKWIN3_Y	(  19 )
#define TRADELIST_TALKWIN3_W	(  27 )
#define TRADELIST_TALKWIN3_H	(   4 )
#define MAIN_TALKWIN3_OFFSET    ( TRADELIST_TALKWIN2_W * TRADELIST_TALKWIN2_H )

// ��̉�ʂ̑I���E�C���h�E1( �R��Łj
#define TRADELIST_SELECT1_X		(  20 )
#define TRADELIST_SELECT1_Y		(  17 )
#define TRADELIST_SELECT1_W		(  11 )
#define TRADELIST_SELECT1_H		(   6 )
#define MAIN_SELECT1_OFFSET     ( MAIN_TALKWIN3_OFFSET + (TRADELIST_TALKWIN3_W*TRADELIST_TALKWIN3_H ))

// ��̉�ʂ̑I���E�C���h�E2( 2��Łj
#define TRADELIST_SELECT2_X		(  20 )
#define TRADELIST_SELECT2_Y		(  19 )
#define TRADELIST_SELECT2_W		(  11 )
#define TRADELIST_SELECT2_H		(   4 )
#define MAIN_SELECT2_OFFSET   	( MAIN_SELECT1_OFFSET + (TRADELIST_SELECT1_W*TRADELIST_SELECT1_H))


// ��̉�ʂ̂͂��E�������E�C���h�E
#define MAIN_YESNO_OFFSET	  	( MAIN_SELECT2_OFFSET + (TRADELIST_SELECT2_W*TRADELIST_SELECT2_H))


// ���̉�ʂ̃|�P�����̖��O
#define SUB_MYPOKENAME_X		(  4 )
#define SUB_FRIENDPOKENAME_X	(  4+16 )
#define SUB_POKENAME_Y			(  1 )
#define SUB_POKENAME_W			(  9 )
#define SUB_POKENAME_H			(  2 )
#define SUB_MYPOKEBMP_OFFSET 		( 1 )
#define SUB_FRIENDPOKEBMP_OFFSET	( SUB_MYPOKEBMP_OFFSET + ( SUB_POKENAME_W * SUB_POKENAME_H))


// ���̉�ʂ̃��x���\��
#define SUB_MYPOKELEVEL_X		(  4 )
#define SUB_FRIENDPOKELEVEL_X	(  4+16 )
#define SUB_POKELEVEL_Y			(  3 )
#define SUB_POKELEVEL_W			(  8 )
#define SUB_POKELEVEL_H			(  2 )
#define SUB_MYPOKELVBMP_OFFSET 		( SUB_FRIENDPOKEBMP_OFFSET + ( SUB_POKENAME_W * SUB_POKENAME_H))
#define SUB_FRIENDPOKELVBMP_OFFSET	( SUB_MYPOKELVBMP_OFFSET   + ( SUB_POKELEVEL_W * SUB_POKELEVEL_H))

// ���̉�ʂ̕�����u�������́v
#define SUB_MOTIMONOSTR_L_X		(  2 )
#define SUB_MOTIMONOSTR_R_X		(  2+16 )
#define SUB_MOTIMONOSTR_Y		( 19 )
#define SUB_MOTIMONOSTR_W		(  7 )
#define SUB_MOTIMONOSTR_H		(  2 )
#define SUB_MYMOTIMONOSTRBMP_OFFSET 	( SUB_FRIENDPOKELVBMP_OFFSET  + ( SUB_POKELEVEL_W * SUB_POKELEVEL_H))
#define SUB_FRIENDMOTIMONOSTRBMP_OFFSET	( SUB_MYMOTIMONOSTRBMP_OFFSET + ( SUB_MOTIMONOSTR_W * SUB_MOTIMONOSTR_H))

// ���̉�ʂ̃A�C�e����
#define SUB_MYITEM_X			(  2 )
#define SUB_FRIENDITEM_X		(  2+16 )
#define SUB_ITEM_Y				( 21 )
#define SUB_ITEM_W				( 12 )
#define SUB_ITEM_H				(  2 )
#define SUB_MYITEMBMP_OFFSET 		( SUB_FRIENDMOTIMONOSTRBMP_OFFSET + ( SUB_MOTIMONOSTR_W * SUB_MOTIMONOSTR_H))
#define SUB_FRIENDITEMBMP_OFFSET	( SUB_MYITEMBMP_OFFSET + ( SUB_ITEM_W * SUB_ITEM_H))



// ���ʗp��b�E�C���h�E�g�E���j���[�g�̃L�����]�����`
#define MENUWIN_FRAME_OFFSET	(512 - MENU_WIN_CGX_SIZ)
#define TALKWIN_FRAME_OFFSET	(512 - (MENU_WIN_CGX_SIZ+TALK_WIN_CGX_SIZ) )

//-----------------------------------------
// ������\���p��`
//-----------------------------------------
enum{
	LEFT_PRINT   = 0,
	CENTER_PRINT,
};


#define INPUT_SCREEN_MAX	( 5)	
#define INPUT_WORD_W		(17)
#define INPUT_WORD_H		( 5)
#define INPUT_WORD_WH		(INPUT_WORD_W*INPUT_WORD_H)
#define INPUT_WORD_MAX		(32)	//�����͖���

// CellActor�ɏ��������郊�\�[�X�}�l�[�W���̎�ނ̐��i���}���`�Z���E�}���`�Z���A�j���͎g�p���Ȃ��j
#define CLACT_RESOURCE_NUM		(  4 )
#define NAMEIN_OAM_NUM			( 14 )
#define NAMELINE_OAM_NUM		( 10 )

// �J�[�\����CLACT_WORK�i���o�[
#define CLACT_CURSOR_NUM		(  8 )

// �����p�l���̓]����
#define WORDPANEL_TRANS_SIZE	( 32*13*2 )

// �����p�l���̈ʒu��`
#define WORDPANEL_POS_REGX		(  -11 )
#define WORDPANEL_POS_REGY		(  -80 )
#define HIDDENPANEL_POS_REGX	(  234 )
#define DOWNPANEL_POS_REGY		( -196 )

#define WORDPANEL_IN_SPEED		( 24 )
#define WORDPANEL_OUT_SPEED		( 10 )

// ���͍ςݕ����̉���OBJ
#define NAMELINE_POS_X			( 10*8   )
#define NAMELINE_POS_Y			(  6*8+5 )

// �p�\�R���E���@�E�|�P�����A�C�R��OBJ�ʒu
#define NAMEIN_MYICON_X			( 24 )
#define NAMEIN_MYICON_Y			( 16 )

// �|�P�����̐��ʃA�C�R���̈ʒu
#define NAMEIN_SEXICON_Y		( NAMELINE_POS_Y - 12)

// ���O���͏��ʒu��`�i���Ȃ��̂Ȃ܂��́H�j
#define NAME_INFO_POSX			(  8 )
#define NAME_INFO_POSY			(  2 )
#define NAME_INFO_POSW			( 18 )
#define NAME_INFO_POSH			(  2 )
#define NAMEINFO_WIN_SIZE		( NAME_INFO_POSW*NAME_INFO_POSH )


// ���O���͌��ʕ\���ʒu��`
#define NAME_RESULT_POSX		( 10   )
#define NAME_RESULT_POSY		(  5   )
#define NAME_RESULT_POSW		( 9*2  )
#define NAME_RESULT_POSH		(  2   )


#define TALK_FONT_PAL			( 13   )

// �����p�l���̑J�ڗp
enum{
	NAMEIN_MODE_REQ  = 0, 
	NAMEIN_MODE_SET,
	NAMEIN_MODE_ANIM,
	NAMEIN_MODE_ANIM_WAIT,
	NAMEIN_MODE,
};

// �@�\�{�^����`
enum{
	NAMEIN_MODE_HIRA = 0,
	NAMEIN_MODE_KANA,
	NAMEIN_MODE_ALPHA,
	NAMEIN_MODE_KIGOU,
};

// �㉺��ʎw���`
#define BOTH_LCD	( 2 )
#define MAIN_LCD	( GF_BGL_MAIN_DISP )	// �v�͂O��
#define SUB_LCD		( GF_BGL_SUB_DISP )		// �P�Ȃ�ł����B


// �\�������|�P�����̍ő吔
#define TRADELIST_POKE_MAX	( 12 )

// �u�����v�������J�[�\���̈ʒu�ԍ�
#define CURSOR_END_POS		( 12 )


// BMPWIN�w��
enum{

	// ---���C�����--
	BMP_M_MYNAME_WIN=0,			// �����̖��O
	BMP_M_FRIENDNAME_WIN,		// ����̖��O
	BMP_M_TRADEMES_WIN,			// ��b�E�C���h�E
	BMP_M_TRADECENTER_WIN1,		// �����E�C���h�E
	BMP_M_SELECT_WIN,			// �I���E�C���h�E
	BMP_M_YESNO_WIN,			// �x�d�r�m�n�E�C���h�E
	BMP_M_ENDSTR_WIN,			// �u�����v
	BMP_M_MYPOKENAME0_WIN,		// �����̎莝���|�P�����̖��O
	BMP_M_MYPOKENAME1_WIN,
	BMP_M_MYPOKENAME2_WIN,
	BMP_M_MYPOKENAME3_WIN,
	BMP_M_MYPOKENAME4_WIN,
	BMP_M_MYPOKENAME5_WIN,
	BMP_M_FRIENDPOKENAME0_WIN,	// ����̎莝���|�P�����̖��O
	BMP_M_FRIENDPOKENAME1_WIN,
	BMP_M_FRIENDPOKENAME2_WIN,
	BMP_M_FRIENDPOKENAME3_WIN,
	BMP_M_FRIENDPOKENAME4_WIN,
	BMP_M_FRIENDPOKENAME5_WIN,

	BMP_M_EX_MYPOKENAME_WIN,
	BMP_M_EX_F_POKENAME_WIN,

	BMP_M_MES1_WIN,				// 1�s�ŕ\��������b�E�C���h�E
	BMP_M_MES2_WIN,				// 2�s�����A�E���ɂ̓��j���[���\�������Ƃ���܂ł����Ȃ��E�C���h�E
	BMP_M_MES3_WIN,				// �t���łQ�s��b�\������E�C���h�E
	BMP_M_SELECT1_WIN,			// �u�悤�����݂�v�u�������񂷂�v�u��߂�v�E�C���h�E
	BMP_M_SELECT2_WIN,			// �u�悤�����݂�v�u��߂�v�E�C���h�E

	// ---�T�u���--
	BMP_S_MYPOKENAME_WIN,		// �����̃|�P�����̖��O+���ʃA�C�R��
	BMP_S_FRIENDPOKENAME_WIN,
	BMP_S_MYPOKELEVEL_WIN,		// �|�P�����̃��x��
	BMP_S_FRIENDPOKELEVEL_WIN,
	BMP_S_MOTIMONO0_WIN,		// �u�������́v
	BMP_S_MOTIMONO1_WIN,
	BMP_S_MYITEM_WIN,			// �A�C�e����
	BMP_S_FRIENDITEM_WIN,
	BMP_TRADELIST_MAX,
};

// �@�\�{�^���p��`
#define FUNCBUTTON_NUM	( 7 ) 		// �@�\�{�^���̐�
#define START_WORDPANEL ( 0 )		// �ŏ��̕������̓p�l���̔ԍ��i�O���Ђ炪�ȁj

// CT_DECIDE�p�R�}���h
#define DECIDE_COMMAND_END		1
#define DECIDE_COMMAND_NEXT		2
#define DECIDE_COMMAND_YES		3
#define DECIDE_COMMAND_NO		4




//============================================================================================
//	�\���̒�`
//============================================================================================

// �J�[�\���p�\����
typedef struct {
	int x;			// ���݈ʒu
	int y;			//
	int oldx;		// 1STEP�O�̈ʒu
	int oldy;		//
	int lastxarrow;	// �Ō�̈ړ�����

	int on;			// �\��ON�EOFF
}TRADELIST_CURSOR;

// �Ă����|�P�����\���p�\����
typedef struct{
	u16  exist;		// �����X�^�[�ԍ�
	u16  item;		// �����A�C�e��
	u8   monsball;	// �ߊl�{�[��
	u8   tamago;	// �^�}�S�t���O
	u8   form;		// �t�H�����f�[�^
	u16  sex;		// ����
	u16  reverse;   // ���]�t���O
	int  customball;	// �{�[���J�X�^�}�C�Y
}POKE_INFO;

struct TRADELIST_WORK{

	FIELDSYS_WORK		*fsys;
	SAVEDATA			*savedata;
	TRADELIST_PARAM		*param;

	PSTATUS_DATA	 	statusParam;						// �X�^�[�^�X�Ăяo���p�p�����[�^
	int					status_side;						// �����̑���̂ǂ����̃X�e�[�^�X���Ă񂾂�(0:1)
	PROC				*subproc;							// �X�^�[�^�X�Ăяo���p�T�u�v���Z�X�f�[�^

	int					subseqflag;
	int					tradeseq;
	int					exchangeseq;
	int					exchange_work;
	int					exchange_finish;
	int					exchange_friend_count;
	int					result;								// �������ʂ́H�itradelist.h�̒�`������j

	int					end_flag[2];
	int					fail_reason;
	BOOL				wipe_end;

	TRADELIST_CURSOR 	Cursor;								// �J�[�\�����@X�EY�E�ߋ�X�E�\��ON
	int				cursor_pos[2];
	u16				CursorPal;
	u16 			wordmap[INPUT_WORD_H][INPUT_WORD_W];	// �����Ճ}�b�v
	u16 			nowmap;									// ���݂̕����}�b�v
	u16				nowinput;								// ���݂̃J�[�\���ʒu
	int				inputmode;
	u16				subtouchword[3];						// �R�̉��{�^���ɔz�u����Ă��镶���R�[�h
	u32				CommWork[2];
	u32				CommSeq[2][3];

	int				MyPokeNum;								// �����̎莝���|�P�����̐�
	int				FriendPokeNum;							// ����̎莝���|�P�����̐�

	GF_BGL_INI		*bgl;

	WORDSET			*PokeNameWordSet;								// ���b�Z�[�W�W�J�p���[�N�}�l�[�W���[
	WORDSET			*WindowStrWordSet;								// ���b�Z�[�W�W�J�p���[�N�}�l�[�W���[
	WORDSET			*SubLcdWordSet;								// ���b�Z�[�W�W�J�p���[�N�}�l�[�W���[
	MSGDATA_MANAGER *MsgManager;							// ���b�Z�[�W�f�[�^�}�l�[�W���[
//	STRBUF			*TitleStr;								// ���O���̓^�C�g��
	STRBUF			*WindowPrintStr;						// �|�P�����������ł���������
	STRBUF			*MyName;
	STRBUF			*MotimonoStr;							// �u�������́v������


	CLACT_SET_PTR 			clactSet;								// �Z���A�N�^�[�Z�b�g
	CLACT_U_EASYRENDER_DATA	renddata;								// �ȈՃ����_�[�f�[�^
	CLACT_U_RES_MANAGER_PTR	resMan[CLACT_RESOURCE_NUM];				// ���\�[�X�}�l�[�W��
	CLACT_U_RES_OBJ_PTR 	resObjTbl[BOTH_LCD][CLACT_RESOURCE_NUM];// ���\�[�X�I�u�W�F�e�[�u��
	CLACT_HEADER			clActHeader_m;							// �Z���A�N�^�[�w�b�_�[
	CLACT_HEADER			clActHeader_s;							// �Z���A�N�^�[�w�b�_�[
	CLACT_WORK_PTR			clActWork[NAMEIN_OAM_NUM];				// �Z���A�N�^�[���[�N�|�C���^�z��
	CLACT_WORK_PTR			PokeIconActWork[TRADELIST_POKE_MAX];
	CLACT_WORK_PTR			PokeItemActWork[TRADELIST_POKE_MAX];
	CLACT_WORK_PTR			PokeCBallActWork[TRADELIST_POKE_MAX];
	CLACT_WORK_PTR			SubLCDIconActWork[6];
	CLACT_WORK_PTR			ExchangeArrow;							// �������܂����H�̎��ɕ\��

	TCB_PTR					FuncButtonTask[FUNCBUTTON_NUM];

	GF_BGL_BMPWIN 			TradeListWin[BMP_TRADELIST_MAX];		// ������ʗpBMP�E�C���h�E
	BMPMENU_WORK 			*YesNoMenu;
	BMPMENU_DATA			*BmpMenuList;
	BMPMENU_WORK 			*BmpMenuWork;

	int						yesnoseq;
	

	int						seq;									// ���݂̕������͏�ԁi����OK/�A�j�����j�Ȃ�
	int						mode;									// ���ݍőO�ʂ̕����p�l��

	int						front;									// ��O�ɗ��Ă���BG��
	VecFx32					panelpos[2];							// �ړ�����2��BG�ʗp���W���[�N(�Œ菭���ł͎g���Ă��Ȃ��j

	int						word;									
//	int						existtbl[13];							///< ���ۂ��߹�݂����邩�ǂ������׸�
//	int						item[TRADELIST_POKE_MAX];				///< �����Ă���A�C�e��
//	int						monsball[TRADELIST_POKE_MAX];			///< ���܂��������X�^�[�{�[��
//	int						monssex[TRADELIST_POKE_MAX];			///< �|�P�����̐���
//	int						tamagotbl[TRADELIST_POKE_MAX];			///< �^�}�S���ǂ���
	POKE_INFO				pokeInfo[TRADELIST_POKE_MAX+1];			///< �J�[�\���ʒu�ɑΉ������|�P�����̏�� (�u�����v�v���܂܂�Ă���j

	int						old_subbutton;							// �O��̉���ʃ{�^�����
	int						subbutton_mode;
	int						subbutton_work;

	int						funcbutton[FUNCBUTTON_NUM];				// �{�^��������ԃt���O

	void*					BgCharaBuf;
	NNSG2dCharacterData*	BgCharaDat;

	void*					PokeIconBuf[TRADELIST_POKE_MAX];		// �|�P�����A�C�R���f�[�^
	NNSG2dCharacterData*	PokeIconCharaDat[TRADELIST_POKE_MAX];					

	u8						PokeGra[2][0x20*10*10];					// �|�P�����O���t�B�b�N�f�[�^
	SOFT_SPRITE_ARC 		PokeGraSsa[2];							// �|�P�����O���t�B�N�f�[�^�A�[�J�C�u���
	int						vblankreq;
	
	u8						ObjTransWork[32*4*2];					//

	int 					(*func)(TRADELIST_WORK *wk);

	POKEPARTY				*MyPokeParty;
	POKEPARTY				*FriendPokeParty;
	PERAPVOICE				*perap;

	FRIEND_LIST				*friendlist;
	FRIEND_LIST				SendList;

	int						saveseq;
	int						savewait;
	int						sub_bg2_scroll;							// BG3�X�N���[���p�̕ϐ�
	int						animcount;
	int						savePreWait;
	VecFx32					myanimpos[2];
	VecFx32					f_animpos[2];
	

	u8						recv_buf[2][POKEPARTY_SEND_ONCE_SIZE];
	u8						perap_buf[2][PERAPVOICE_DATA_LENGTH];

    // �F�B�o�^�p
    int friendNetID[WIFILIST_FRIEND_MAX]; //�t�����h�o�^����netID
    int addFriendNo;  // ���ݓo�^���̐l
    int erasePos;  //�����\��̐l
    WORDSET			*friendWordSet;			
    MSGDATA_MANAGER *friendMsgManager;			
    BMPLIST_DATA*   menulist;
    BMPLIST_WORK* lw;		// BMP���j���[���[�N
	GF_BGL_BMPWIN			listWin;	// �폜���X�g�E�C���h�E
    WIFI_LIST* pWifiList;
	int tradeNum;
  
	int	commSaveSeq;		// �ʐM�Z�[�u�p���[�N

	int posBackup;			// �ʐM�R�}���h�̃R�}���h�̃o�b�N�A�b�v�f�[�^
	int commandBackup;		// �ʐM�R�}���h�̈ʒu�f�[�^�̃o�b�N�A�b�v�f�[�^

	void *timeWaitWork;		// ���ԃA�C�R���p�^�X�N���[�N

	int	 timeOutFlag;		// �^�C���A�E�g�������s�����t���O
	int  timeOutWait;		// �^�C���A�E�g�J�E���^

#ifdef PM_DEBUG
	int 					frame;									//
	int						framenum[9][2];							//
#endif
};



//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================
extern void TradeListCommSendPokeData(int netID, POKEPARTY *party, int no);
extern void TradeListCommSend(int netID, int command, int pos);
extern void TradeListCommDiffSend( TRADELIST_WORK *wk, int command, int pos);

#endif
