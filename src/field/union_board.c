
//===========================================================================
/**
 *
 *@file		union_board.c
 *@brief	���j�I�����[���f���\�������i�T�u��ʁj
 *@author	Akito Mori
 *@data		2006.02.03
 *
 */
//===========================================================================

#ifdef PM_DEBUG
//#define UNIONBOARD_DEBUG
#endif

#include "common.h"
#include "gflib/touchpanel.h"


#include "system/lib_pack.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/pm_overlay.h"

#include "system/clact_util.h"
#include "system/render_oam.h"
#include "system/pm_str.h"
#include "gflib/strbuf_family.h"

#include "system/bmp_menu.h"
#include "system/window.h"
#include "system/fontproc.h"
#include "system/pms_word.h"
#include "system/wordset.h"
#include "system/msgdata.h"
#include "system/msgdata_util.h"

#include "savedata/friendlist.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_union.h"

#include "fld_bmp.h"
#include "fieldmap.h"
#include "fieldsys.h"
#include "talk_msg.h"

#include "communication/communication.h"
#include "underground/ug_manager.h"
#include "comm_player.h"
#include "unionroom.naix"
#include "union_board.h"

#include "comm_union.h"
#include "comm_union_view.h"
#include "comm_union_view_def.h"
#include "comm_union_beacon.h"


FS_EXTERN_OVERLAY(unionroom_board);


struct _STRBUF {
	u16  size;			///< �z��T�C�Y
	u16  strlen;		///< �����񒷁iEOM���܂܂Ȃ��j
	u32  magicNumber;	///< ����ɏ������ς݂ł��邱�Ƃ��`�F�b�N���邽�߂̃i���o�[

	STRCODE  buffer[1];	///< �z��{��
};

//========================================================================================
// �萔�錾
//========================================================================================

#define UNION_BOARD_RESOURCE_ID	( 999 ) // ����ʂ̃��\�[�X�h�c���Փ˂��Ȃ��悤�ɂ��邽�߂�1000�Ƃ���


// CellActor�ɏ��������郊�\�[�X�}�l�[�W���̐��i���}���`�Z���E�}���`�Z���A�j���͎g�p���Ȃ��j
#define CELL_ANIME_RESOURCE_NUM		(4)

// ���j�I���{�[�h�ɕ\������OBJ�̐�
#define UNION_BOARD_OBJ_PARTS_NUM	(3)	

// �Y�z���[�_�[�̃^�X�N�̗D�揇�ʁi�ʐM���͉��ɂ���K�v�Ƃ�����Ǝv���̂Łj
#define UNION_BOARD_TCB_PRIORITY	(4)

// ����ʂɕ\������ȈՉ�b�̐�
#define UNION_BOARD_CARD_NUM		( 3 )

#define UNION_BOARD_CLACT_MAX			( 10 )

#define MESSAGE_NONE		( 0 )
#define MESSAGE_WAIT		( 1 )
#define MESSAGE_END			( 2 )


#define _EVWIN_MSG_BUF_SIZE		(50*2)			//���b�Z�[�W�o�b�t�@�T�C�Y

// -----�Y�z���[�_�[�����̃V�[�P���X��`---------
enum{
	UNIONBOARD_INIT_BG = 0,
	UNIONBOARD_INIT_ACTOR,
	UNIONBOARD_MAIN,
	UNIONBOARD_END,
};



//========================================================================================
// �\���̐錾
//========================================================================================
typedef struct{
	u16 max;
	u16 old_max;
	u16 now;
	u16 barflag;
}UNION_SCROLL;

typedef struct{
	GF_BGL_BMPWIN	bName;							// ���O�`��r�b�g�}�b�v
	GF_BGL_BMPWIN	bMessage;						// �ȈՉ�b�`��r�b�g�}�b�v
	GF_BGL_BMPWIN	bFriend;						// ���肠�����m�r�b�g�}�b�v
	int				sex;							// �\��t����J�[�h�̔w�i
	int				push;							// �������܂���
}UNION_BOARD_BMP;

struct UNION_BOARD_WORK{
	int           			mode;									//�V�[�P���X�J��

	COMM_UNIONROOM_VIEW 	*cuv;
	COMM_UNIONROOM_WORK     *union_work;
	FIELDSYS_WORK 			*fsys;									// �t�B�[���h��������p���V�X�e���|�C���^
	MYSTATUS				*mystatus;
	GF_BGL_INI    			*bgl;									// �t�B�[���h��������p���a�f�V�X�e���|�C���^
	

	WORDSET					*WordSet;								// ���b�Z�[�W�W�J�p���[�N�}�l�[�W���[
	MSGDATA_MANAGER 		*MsgManager;							// ���b�Z�[�W�f�[�^�}�l�[�W���[

	u16			  	 		*Bg1ScrenData;							// BG1���������p�X�N���[���f�[�^����
	NNSG2dScreenData 		*BoardScreen;							// BG1���������p�X�N���[���f�[�^�A�h���X

	CLACT_SET_PTR 			clactSet;								// �Z���A�N�^�[�Z�b�g
	CLACT_U_EASYRENDER_DATA	renddata;								// �ȈՃ����_�[�f�[�^
	CLACT_U_RES_MANAGER_PTR	resMan[CELL_ANIME_RESOURCE_NUM];		// ���\�[�X�}�l�[�W��
	CLACT_U_RES_OBJ_PTR 	resObjTbl[CELL_ANIME_RESOURCE_NUM];		// ���\�[�X�I�u�W�F�e�[�u��
	CLACT_HEADER			clActHeader;							// �Z���A�N�^�[�w�b�_�[

	CLACT_WORK_PTR			clActWork[COMM_MACHINE_MAX];			// �Z���A�N�^�[���[�N�|�C���^�z��(��l���j
	int						MesIndex;								// ���b�Z�[�W�C���f�b�N�X
	int						TalkMode;
	int						Wait;
	int						lastHitTrg;

	UNION_BOARD_BMP			UnionBmp[3];
	UNION_CHAT_RINGBUF		*UnionChatRingBuf;

	UNION_SCROLL			Scroll;
	int						old_scrollpoint;
	int						old_winanime;

	BOOL					BgTransReq;

	TCB_PTR					tcb;	
};


#ifdef PM_DEBUG
static UNION_BOARD_WORK *debug_ubw;
#endif

//========================================================================================
// �v���g�^�C�v�錾
//========================================================================================
static void InitWork( UNION_BOARD_WORK *ubw );
static void destBG(GF_BGL_INI* bgl);
static void initBG( GF_BGL_INI *bgl );
static void InitCellActor(UNION_BOARD_WORK *ubw);
static void SetCellActor( UNION_BOARD_WORK *ubw );

static void BmpWinInit( GF_BGL_INI *bgl, UNION_BOARD_BMP *UnionBmp);
static void BmpWinDelete( UNION_BOARD_BMP *UnionBmp );

extern void FieldMsgPrintInitSub(void);
extern void FldTalkBmpAddSub( GF_BGL_INI * ini, GF_BGL_BMPWIN * win );


static void UnionChatInit( UNION_CHAT *chat);
static void UnionChatAllocInit( UNION_CHAT_RINGBUF *chatbuf);
static void UnionChatFree(UNION_CHAT *chat);
static void UnionChatAllFree( UNION_CHAT_RINGBUF *chatbuf);

static void BoardWriteFunc( UNION_BOARD_WORK *ubw );
static void UnionChat_Print( UNION_BOARD_WORK *ubw, int no,  UNION_CHAT *mes);
static void TouchPanelFunc( UNION_BOARD_WORK *ubw );
static void ScrollControl( UNION_BOARD_WORK *ubw );
static void SetScrollBar_PosY( CLACT_WORK_PTR act, int y );
static void GetUnionChat( UNION_BOARD_WORK *ubw );
static void AddUnionChatPmsData( UNION_BOARD_WORK *ubw, u32 id, PMS_DATA *pms, MYSTATUS *mystatus );
static int UnionChatRegisterCheck(UNION_BOARD_WORK *ubw, PMS_DATA *pms, int id);
static int AddUnionChatRingBufPos( UNION_CHAT_RINGBUF *chatbuf, int pos );
static int GetUnionBoardPrintPoint( int start, int now );
static int  TouchTrgFunc( UNION_BOARD_WORK *ubw );
static int  TouchContFunc( UNION_BOARD_WORK *ubw );



static void UnionBoardReWriteOn( UNION_BOARD_WORK *ubw);
static void UnionBoard_AddChatSub( UNION_BOARD_WORK *ubw, MYSTATUS *status, PMS_DATA *pms, u32 id );
static STRBUF *FriendLinkStringGet(FRIEND_LIST *friendlist, u32 id, WORDSET *wordset, MSGDATA_MANAGER *msgdata, MYSTATUS *my);
static void ChatButtonAnimation( GF_BGL_INI *bgl, NNSG2dScreenData *Screen, UNION_BOARD_BMP *Board, int button, int num, int *old);



//------------------------------------------------------------------
/**
 * �Y�z���[�_�[���C���i�^�X�N�֐��j
 *
 * @param   tcb		�^�X�N�|�C���^
 * @param   wk		���[�N�|�C���^(UG_RADAR_WORK�Ƃ��ăL���X�g���Ďg���j
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void UnionRoom_BoardFunc(TCB_PTR tcb, void *wk)
{
	UNION_BOARD_WORK *ubw = wk;
	GF_BGL_INI       *bgl = ubw->bgl;
	int i;

	// ���j�I�����[�������l�������ł����ƃ��j�I���p�̃��[�N�����ł��Ă��܂��̂ŗ\�h��
	if(ubw->fsys->union_view==NULL){
		return;
	}

	switch(ubw->mode){
	case UNIONBOARD_INIT_BG:
		// BG�������EVRAM�]��
		OS_Printf("start unionboard = %ld\n",sys_GetHeapFreeSize(HEAPID_FIELD));
		OS_Printf("underground  work= %ld\n",sizeof(UNION_BOARD_WORK));

		initBG( bgl );

		// ���[�_�[�p�z�񏉊���
		InitWork( ubw );
//		UnionChatAllocInit( &ubw->UnionChatRingBuf );

#ifdef PM_DEBUG
		debug_ubw = ubw;

#endif
	
		ubw->mode++;
		break;
	case UNIONBOARD_INIT_ACTOR:

		InitCellActor(ubw);
		SetCellActor(ubw);
		FontProc_LoadBitData(FONT_TALK, HEAPID_FIELD);


		BmpWinInit( ubw->bgl, ubw->UnionBmp );

		GF_Disp_GXS_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);	//OBJ�ʂn�m
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_ON );
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_ON );
		UnionBoardReWriteOn( ubw );
		ubw->mode++;
		break;
	// ���C���V�[�P���X
	case UNIONBOARD_MAIN:
		GetUnionChat( ubw );
		ScrollControl( ubw );
		TouchPanelFunc( ubw );

#ifdef UNIONBOARD_DEBUG
		if(sys.trg&PAD_BUTTON_Y){
			int r;
			for(i=0;i<ubw->UnionChatRingBuf->num;i++){
				OS_TPrintf("----chat no %d\n",i);
				OS_TPrintf("name ");
				for(r=0;r<6;r++){
					OS_TPrintf("%02x ",ubw->UnionChatRingBuf->mes[i].name->buffer[r]);
				}
				OS_TPrintf("\nmessage ");
				for(r=0;r<6;r++){
					OS_TPrintf("%02x ",ubw->UnionChatRingBuf->mes[i].message->buffer[r]);
				}
				OS_TPrintf("\nfriend ");
				if(ubw->UnionChatRingBuf->mes[i].friend!=NULL){
					for(r=0;r<6;r++){
						OS_TPrintf("%02x ",ubw->UnionChatRingBuf->mes[i].friend->buffer[r]);
					}
				}else{
					OS_TPrintf("\n");
				}
				
				OS_TPrintf("\nid = %08x, sex = %d \n", ubw->UnionChatRingBuf->mes[i].id, ubw->UnionChatRingBuf->mes[i].sex);

				OS_TPrintf("PmsData ");
				OS_TPrintf("type %d, id %d, word0 %d, word1 %d\n", 
								ubw->UnionChatRingBuf->mes[i].PmsData.sentence_type,
								ubw->UnionChatRingBuf->mes[i].PmsData.sentence_id,
								ubw->UnionChatRingBuf->mes[i].PmsData.word[0],
								ubw->UnionChatRingBuf->mes[i].PmsData.word[1]
				);
			}
		}
		if(sys.trg & PAD_BUTTON_L){
			OS_TPrintf(" HEAPID_BASE_SYSTEM = %x\n",sys_GetHeapFreeSize( HEAPID_BASE_SYSTEM ));	
			OS_TPrintf(" HEAPID_BASE_APP = %x\n",   sys_GetHeapFreeSize( HEAPID_WORLD ));	
			OS_TPrintf(" HEAPID_WORLD = %x\n",   sys_GetHeapFreeSize( HEAPID_WORLD ));	
			OS_TPrintf(" HEAPID_UNIONBoARD = %x\n",   sys_GetHeapFreeSize( HEAPID_UNIONBOARD ));	
		}
		
		if(sys.trg & PAD_BUTTON_DEBUG){
			WMBssDesc         *beacon;
			_GF_BSS_DATA_INFO *gfinfo;
			int i;
			
			OS_TPrintf("now beacon =\n");
			for(i=0;i<10;i++){
				beacon = CommMPGetWMBssDesc(i);	
				if(beacon!=NULL){		// �r�[�R�������Ȃ�������X���[
					gfinfo = (_GF_BSS_DATA_INFO*)&beacon->gameInfo.userGameInfo;
					OS_TPrintf( "%08x,  ", gfinfo->pokeID);
				}
			}
			OS_TPrintf("\n");
			Debug_FriendListAllPrint( SaveData_GetFriendList(ubw->fsys->savedata) );
		}

		if(sys.trg & PAD_BUTTON_SELECT){
			PMS_DATA pmsdata;
			PMSDAT_SetDebugRandom( &pmsdata );
			Union_SetMyPmsData( ubw->union_work, &pmsdata );		// ���j�I�����[�N�ŕۑ����Ă�������ʂɕ\��������
		}

#endif
		BoardWriteFunc( ubw );

		CLACT_Draw( ubw->clactSet );									// �Z���A�N�^�[�풓�֐�
		break;

	case UNIONBOARD_END:
		break;

	}
}

// ���O�\���a�l�o��`
#define NAME_BMPWIN_W			(  8 )
#define NAME_BMPWIN_H			(  2 )

#define NAME_BMPWIN_POSX		(  1 )
#define NAME0_BMPWIN_POSY		(  1 )

// �ȈՉ�b�\���a�l�o��`
#define MESSAGE_BMPWIN_W		( 27 )
#define MESSAGE_BMPWIN_H		(  5 )

#define MESSAGE_BMPWIN_POSX		(  2 )
#define MESSAGE0_BMPWIN_POSY	(  3 )

// ���肠�����m�a�l�o��`
#define FRIEND_BMPWIN_W		( 15 )
#define FRIEND_BMPWIN_H		(  2 )

#define FRIEND_BMPWIN_POSX		( 12 )
#define FRIEND_BMPWIN_POSY		(  1 )




#define UNION_BOARD_BGCHAR_OFFSET	( 32*5 )
#define UNION_NAME_BMP_SIZE         ( NAME_BMPWIN_W*NAME_BMPWIN_H )
#define UNION_CHAT_BMP_SIZE  	    ( MESSAGE_BMPWIN_W * MESSAGE_BMPWIN_H )
#define UNION_FRIEND_BMP_SIZE   	( FRIEND_BMPWIN_W  * FRIEND_BMPWIN_H )

#define UNION_BOARD_NAMECHAR_OFFSET   ( UNION_BOARD_BGCHAR_OFFSET + UNION_NAME_BMP_SIZE*3 )
#define UNION_BOARD_FRIENDCHAR_OFFSET ( UNION_BOARD_NAMECHAR_OFFSET + UNION_CHAT_BMP_SIZE*3 )

//------------------------------------------------------------------
/**
 * ���j�I���{�[�h���[�N������
 *
 * @param   pos[][POS_XZ]			
 * @param   view[][POS_XZ_TIME]		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void InitWork( UNION_BOARD_WORK *ubw )
{
	int i;
	ubw->BgTransReq = FALSE;

	ubw->Scroll.max     = 0;
	ubw->Scroll.old_max = 0;
	ubw->Scroll.now     = 0;
	ubw->Scroll.barflag = 0;


	// ������}�l�[�W���[������
	ubw->WordSet    = WORDSET_Create( HEAPID_FIELD );
	ubw->MsgManager = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_union_dat, HEAPID_FIELD );


	// ���H�pBG1�f�[�^�ǂݍ���
	ubw->Bg1ScrenData = ArcUtil_ScrnDataGet(ARC_UNIONROOM_GRA, NARC_unionroom_unionbg1_lz_nscr, 1, &(ubw->BoardScreen), HEAPID_FIELD);
	OS_Printf( "bg1srcreen data adrs = %08x\n",ubw->BoardScreen);


}


//------------------------------------------------------------------
/**
 * $brief   BMPWIN�m��
 *
 * @param   bgl		
 * @param   UnionBmp		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void BmpWinInit( GF_BGL_INI *bgl, UNION_BOARD_BMP *UnionBmp)
{
	// ����ʃ{�^���pBMP�m��
	int i;

	for(i=0;i<UNION_BOARD_CARD_NUM;i++){
		// ���O
		GF_BGL_BmpWinAdd(bgl, &UnionBmp[i].bName, GF_BGL_FRAME0_S+i,	
			NAME_BMPWIN_POSX, 
			NAME0_BMPWIN_POSY+i*8, 
			NAME_BMPWIN_W, 
			NAME_BMPWIN_H, 
			FLD_MESFONT_PAL,  UNION_BOARD_BGCHAR_OFFSET + i * UNION_NAME_BMP_SIZE);
		GF_BGL_BmpWinDataFill( &UnionBmp[i].bName, 0x0000 );

		GF_BGL_BmpWinOn( &UnionBmp[i].bName );

		// �ȈՉ�b
		GF_BGL_BmpWinAdd(bgl, &UnionBmp[i].bMessage, GF_BGL_FRAME0_S+i,	
			MESSAGE_BMPWIN_POSX, 
			MESSAGE0_BMPWIN_POSY+i*8, 
			MESSAGE_BMPWIN_W, 
			MESSAGE_BMPWIN_H, 
			FLD_MESFONT_PAL,  UNION_BOARD_NAMECHAR_OFFSET + i * UNION_CHAT_BMP_SIZE);
		GF_BGL_BmpWinDataFill( &UnionBmp[i].bMessage, 0x0000 );
		GF_BGL_BmpWinOn( &UnionBmp[i].bMessage );

		// ���肠����b
		GF_BGL_BmpWinAdd(bgl, &UnionBmp[i].bFriend, GF_BGL_FRAME0_S+i,	
			FRIEND_BMPWIN_POSX, 
			FRIEND_BMPWIN_POSY+i*8, 
			FRIEND_BMPWIN_W, 
			FRIEND_BMPWIN_H, 
			FLD_MESFONT_PAL,  UNION_BOARD_FRIENDCHAR_OFFSET + i * UNION_FRIEND_BMP_SIZE);
		GF_BGL_BmpWinDataFill( &UnionBmp[i].bFriend, 0x0000 );
		GF_BGL_BmpWinOn( &UnionBmp[i].bFriend );
		
	}

	OS_Printf(" CHAT_BOARD BMP End = %d\n ",UNION_BOARD_FRIENDCHAR_OFFSET + i * UNION_FRIEND_BMP_SIZE);
	OS_Printf("heap remain = %d\n",sys_GetHeapFreeSize( HEAPID_FIELD ));

}

//------------------------------------------------------------------
/**
 * $brief   BMPWIN���
 *
 * @param   UnionBmp		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void BmpWinDelete( UNION_BOARD_BMP *UnionBmp )
{
	int i;
	for(i=0;i<UNION_BOARD_CARD_NUM;i++){
		GF_BGL_BmpWinDel( &UnionBmp[i].bMessage );
		GF_BGL_BmpWinDel( &UnionBmp[i].bName );
		GF_BGL_BmpWinDel( &UnionBmp[i].bFriend );
	}
}


//==============================================================================
/**
 * �Y�z���[�_�[�������֐��i�^�X�N�o�^�j
 *
 * @param   fsys		FIELDSYS_WORK�̃|�C���^
 *
 * @retval  none		
 */
//==============================================================================
UNION_BOARD_WORK *UnionRoom_BoardInit( FIELDSYS_WORK *fsys )
{
	UNION_BOARD_WORK *ubw;
	TCB_PTR       tcb;

	//�Y�z���[�_�[�^�X�N��ǉ�
	tcb           = PMDS_taskAdd(UnionRoom_BoardFunc, sizeof(UNION_BOARD_WORK), UNION_BOARD_TCB_PRIORITY, HEAPID_FIELD);
	ubw           = TCB_GetWork(tcb);
	ubw->fsys     = fsys;
	ubw->bgl      = fsys->bgl;
	ubw->cuv      = fsys->union_view;
	ubw->union_work = fsys->union_work;
	ubw->mystatus = SaveData_GetMyStatus(fsys->savedata);
	ubw->mode     = 0;
	ubw->tcb      = tcb;

	
	ubw->UnionChatRingBuf = fsys->union_view->unionBoardChat;
//	ubw->UnionChatRingBuf = UnionBoard_ChatAllocInit( HEAPID_FIELD );
	

	return ubw;
}

//==============================================================================
/**
 * ���[�_�[��ʏI����ʒm
 *
 * @param   fsys		FieldSys�̃|�C���^
 *
 * @retval  none		
 */
//==============================================================================
void UnionRoom_BoardEnd(UNION_BOARD_WORK *ubw)
{
	// ���[�_�[�̃V�[�P���X��`���I���ɕύX
	if(ubw->mode==UNIONBOARD_MAIN){
		GF_BGL_INI       *bgl = ubw->bgl;
		int i;

		ubw->mode = UNIONBOARD_END;

		FontProc_UnloadBitData( FONT_TALK );

		// �L�����]���}�l�[�W���[�j��
		CLACT_U_CharManagerDelete(ubw->resObjTbl[CLACT_U_CHAR_RES]);

		// �p���b�g�]���}�l�[�W���[�j��
		CLACT_U_PlttManagerDelete(ubw->resObjTbl[CLACT_U_PLTT_RES]);
		
		// �L�����E�p���b�g�E�Z���E�Z���A�j���̃��\�[�X�}�l�[�W���[�j��
		for(i=0;i<CELL_ANIME_RESOURCE_NUM;i++){
			CLACT_U_ResManagerDelete(ubw->resMan[i]);
		}
		// �Z���A�N�^�[�Z�b�g�j��
		CLACT_DestSet(ubw->clactSet);

		// ������}�l�[�W���[�j��
		MSGMAN_Delete(  ubw->MsgManager );
		WORDSET_Delete( ubw->WordSet );

		//BmpWin���
		BmpWinDelete( ubw->UnionBmp );				

		destBG(bgl);											// BG0,BG1�p�o�b�t�@���

//		UnionChatAllFree( ubw->UnionChatRingBuf);
//		UnionBoard_ChatDataDelete( ubw->UnionChatRingBuf );
		sys_FreeMemoryEz( ubw->Bg1ScrenData );

		PMDS_taskDel( ubw->tcb );

	}else{
		GF_ASSERT("���[�_�[���������I���Ȃ������ɏI���Ăяo������܂���");
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief �n����ʂɓ˓�����܂ł̃T�u��ʂa�f�̃V�X�e����j��
 *
 *@param	bgl		BGL�V�X�e���\���̂̃|�C���^
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void destBG(GF_BGL_INI* bgl)
{
	GF_BGL_BGControlExit(bgl, GF_BGL_FRAME0_S);
	GF_BGL_BGControlExit(bgl, GF_BGL_FRAME1_S);
	GF_BGL_BGControlExit(bgl, GF_BGL_FRAME2_S);
	GF_BGL_BGControlExit(bgl, GF_BGL_FRAME3_S);
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	BG�R���g���[���ݒ�
 *
 *@param	bgl	BGL�V�X�e���̃|�C���^
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void initBG( GF_BGL_INI* bgl )
{
	// ���܂ł̔j��
	destBG(bgl);

	// �T�u��BG�ݒ�
	// BG0�ʁi�e�L�X�g0�j
	{
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x6000, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( bgl, GF_BGL_FRAME0_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( bgl, GF_BGL_FRAME0_S );
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );
	}
	// BG1�ʁi�e�L�X�g1�j
	{
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x6800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			2, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( bgl, GF_BGL_FRAME1_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( bgl, GF_BGL_FRAME1_S );
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
	}

	// BG2�ʁi�e�L�X�g1�j
	{
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x7000, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			2, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( bgl, GF_BGL_FRAME2_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( bgl, GF_BGL_FRAME2_S );
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );
	}

	// BG3�ʁi�w�i�j
	{
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x7800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			2, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( bgl, GF_BGL_FRAME3_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_OFF );
	}

	// �p���b�g�]��
	ArcUtil_PalSet(    ARC_UNIONROOM_GRA, NARC_unionroom_unionbg_nclr, PALTYPE_SUB_BG, 0, 0x20*3,  HEAPID_FIELD);

	// �L�����]��(�]���L�����̎w�肪BGCHAR_OFFSET�ɂȂ��Ă���̂́ABG��VRAM����]�����Ă��邩��j
	ArcUtil_BgCharSet( ARC_UNIONROOM_GRA, NARC_unionroom_unionbg_lz_ncgr, bgl, GF_BGL_FRAME3_S, 0, UNION_BOARD_BGCHAR_OFFSET*0x20, 1, HEAPID_FIELD);

	// �X�N���[���]��
	ArcUtil_ScrnSet(   ARC_UNIONROOM_GRA, NARC_unionroom_unionbg1_base_lz_nscr, bgl, GF_BGL_FRAME3_S, 0, 32*24*2, 1, HEAPID_FIELD);

	FieldMsgPrintInit(PALTYPE_SUB_BG, MSG_PRINT_NO_INIT);				// �T�u���VRAM�Ƀt�H���g�ƃp���b�g��]��

}



//------------------------------------------------------------------
/**
 * ���[�_�[��ʗp�Z���A�N�^�[������
 *
 * @param   ubw		���[�_�[�\���̂̃|�C���^
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void InitCellActor(UNION_BOARD_WORK *ubw)
{
	int i;
	// �Z���A�N�^�[������
	ubw->clactSet = CLACT_U_SetEasyInit( UNION_BOARD_CLACT_MAX, &ubw->renddata, HEAPID_FIELD );
	
	//���\�[�X�}�l�[�W���[������
	for(i=0;i<CELL_ANIME_RESOURCE_NUM;i++){		//���\�[�X�}�l�[�W���[�쐬
		ubw->resMan[i] = CLACT_U_ResManagerInit(1, i, HEAPID_FIELD);
	}

	
	//chara�ǂݍ���
	ubw->resObjTbl[CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(ubw->resMan[CLACT_U_CHAR_RES], 
			ARC_UNIONROOM_GRA, NARC_unionroom_unionobj_lz_ncgr, 1, UNION_BOARD_RESOURCE_ID, NNS_G2D_VRAM_TYPE_2DSUB, HEAPID_FIELD);

	//pal�ǂݍ���
	ubw->resObjTbl[CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(ubw->resMan[CLACT_U_PLTT_RES],
			ARC_UNIONROOM_GRA, NARC_unionroom_unionobj_nclr, 0, UNION_BOARD_RESOURCE_ID, NNS_G2D_VRAM_TYPE_2DSUB, 1, HEAPID_FIELD);

	//cell�ǂݍ���
	ubw->resObjTbl[CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(ubw->resMan[CLACT_U_CELL_RES],
			ARC_UNIONROOM_GRA, NARC_unionroom_unionobj_lz_ncer, 1, UNION_BOARD_RESOURCE_ID, CLACT_U_CELL_RES,HEAPID_FIELD);

	//�����֐���anim�ǂݍ���
	ubw->resObjTbl[CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(ubw->resMan[CLACT_U_CELLANM_RES],
			ARC_UNIONROOM_GRA, NARC_unionroom_unionobj_lz_nanr, 1, UNION_BOARD_RESOURCE_ID, CLACT_U_CELLANM_RES,HEAPID_FIELD);

	// Chara�]��
	CLACT_U_CharManagerSetAreaCont( ubw->resObjTbl[CLACT_U_CHAR_RES] );

	// �p���b�g�]��
	CLACT_U_PlttManagerSetCleanArea( ubw->resObjTbl[CLACT_U_PLTT_RES] );

}

#define UNION_ARROW_X			(256-24)
#define UNION_ARROW_UP_Y		(     0)
#define UNION_ARROW_DOWN_Y		(192-8*4)
#define UNION_ARROW_SCROLL_Y	(192/2)

static const int obj_parts_table_y[]={
		UNION_ARROW_UP_Y	,
		UNION_ARROW_DOWN_Y	,
		UNION_ARROW_SCROLL_Y,
};


//------------------------------------------------------------------
/**
 * $brief   �Z���A�N�^�[�z�u
 *
 * @param   ubw		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SetCellActor( UNION_BOARD_WORK *ubw )
{
	int i;
		// �Z���A�N�^�[�w�b�_�쐬
		CLACT_U_MakeHeader(&ubw->clActHeader, 
							UNION_BOARD_RESOURCE_ID,
							UNION_BOARD_RESOURCE_ID,
							UNION_BOARD_RESOURCE_ID,
							UNION_BOARD_RESOURCE_ID,
							CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
							0, 0,
							ubw->resMan[CLACT_U_CHAR_RES],
							ubw->resMan[CLACT_U_PLTT_RES],
							ubw->resMan[CLACT_U_CELL_RES],
							ubw->resMan[CLACT_U_CELLANM_RES],
							NULL,NULL);

		{
			//�o�^���i�[
			CLACT_ADD add;

			add.ClActSet	= ubw->clactSet;
			add.ClActHeader	= &ubw->clActHeader;

			add.mat.z		= 0;
			add.sca.x		= FX32_ONE;
			add.sca.y		= FX32_ONE;
			add.sca.z		= FX32_ONE;
			add.rot			= 0;
			add.pri			= 0;
			add.DrawArea	= NNS_G2D_VRAM_TYPE_2DSUB;
			add.heap		= HEAPID_FIELD;

			//�Z���A�N�^�[�\���J�n

			// �㉺���X�N���[���o�[�o�^
			for(i=0;i<UNION_BOARD_OBJ_PARTS_NUM;i++){
				add.mat.x		= FX32_CONST( UNION_ARROW_X ) ;
				add.mat.y		= FX32_CONST( obj_parts_table_y[i] ) + SUB_SURFACE_Y;		//��ʂ͏㉺�A�����Ă���iMAIN����ASUB�����j
				ubw->clActWork[i] = CLACT_Add(&add);
				CLACT_SetAnmFlag(ubw->clActWork[i],1);
				CLACT_AnmChg( ubw->clActWork[i], i );	//�e�X�̎p��
			}
//			CLACT_SetDrawFlag(ubw->clActWork[2], 0);	//�X�N���[���o�[�͔�\����
			
		}	

}





//------------------------------------------------------------------
/**
 * $brief   �����O�o�b�t�@���ŎQ�Ɠ_�̑����Z���s��
 *
 * @param   chatbuf		
 * @param   pos		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int AddUnionChatRingBufPos( UNION_CHAT_RINGBUF *chatbuf, int pos )
{
	pos++;
	if(pos==UNION_CHAT_MAX){
		pos = 0;
	}

	return pos;
}

//------------------------------------------------------------------
/**
 * $brief   �����O�o�b�t�@���l�������`���b�g�\���J�n�ʒu�擾
 *
 * @param   start		
 * @param   now		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int GetUnionBoardPrintPoint( int start, int now )
{
	int result = start+now;
	if(result>=UNION_CHAT_MAX){
		result -= UNION_CHAT_MAX;
	}
	return result;
}
//------------------------------------------------------------------
/**
 * $brief   ���O���ȈՉ�b��`��
 *
 * @param   ubw		
 * @param   no		
 * @param   mes		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void UnionChat_Print( UNION_BOARD_WORK *ubw, int no, UNION_CHAT *mes)
{

	// �J�[�h�p�ɐ��ʂ�ۑ�
	ubw->UnionBmp[no].sex = mes->sex;

	OS_Printf("�J�[�h�`��\n");

	// �X�N���[�����H�]��(���ʂɑΉ����Đ��ԂɂȂ�j
	GF_BGL_ScrWriteExpand(	ubw->bgl, GF_BGL_FRAME3_S, 0, no*8, 32, 8,
			ubw->BoardScreen->rawData, 0, 24*ubw->UnionBmp[no].sex, 32, 48 );

	// BMP�p�o�b�t�@�N���A
	GF_BGL_BmpWinDataFill( &ubw->UnionBmp[no].bName,    0x0000 );
	GF_BGL_BmpWinDataFill( &ubw->UnionBmp[no].bMessage, 0x0000 );
	GF_BGL_BmpWinDataFill( &ubw->UnionBmp[no].bFriend,  0x0000 );
	
	// ������`��
	GF_STR_PrintColor( &ubw->UnionBmp[no].bName,    FONT_TALK, mes->name,    0, 2, MSG_NO_PUT, GF_PRINTCOLOR_MAKE(1,2,0),NULL );
	GF_STR_PrintColor( &ubw->UnionBmp[no].bMessage, FONT_TALK, mes->message, 0, 6, MSG_NO_PUT, GF_PRINTCOLOR_MAKE(1,2,0),NULL );

	// VRAM��vBlank���ɓ]��
	GF_BGL_BmpWinOnVReq( &ubw->UnionBmp[no].bName    );
	GF_BGL_BmpWinOnVReq( &ubw->UnionBmp[no].bMessage );

	if(mes->friend){
		GF_STR_PrintColor( &ubw->UnionBmp[no].bFriend, FONT_TALK, mes->friend, 0, 2, MSG_NO_PUT, GF_PRINTCOLOR_MAKE(1,2,0),NULL );
	}
	GF_BGL_BmpWinOnVReq( &ubw->UnionBmp[no].bFriend );
}

//------------------------------------------------------------------
/**
 * $brief   ���j�I���{�[�h�`��풓�֐�
 *
 * @param   ubw		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void BoardWriteFunc( UNION_BOARD_WORK *ubw )
{
	int i,r;
	int pos = GetUnionBoardPrintPoint( ubw->UnionChatRingBuf->start, ubw->Scroll.now );
	int max = ubw->UnionChatRingBuf->num;
	
	if(max>3){
		max = 3;
	}

	// �X�N���[���o�[�̈ʒu�������Ă����ꍇ�͍ĕ`��
	if(ubw->Scroll.now!=ubw->old_scrollpoint){
		UnionBoardReWriteOn( ubw );
		ubw->old_scrollpoint = ubw->Scroll.now;
	}

	// �ȈՉ�b�`��
	if(ubw->BgTransReq==TRUE){
//		OS_Printf( "pos=%d, bufnum=%d bufstart=%d now=%d",pos, ubw->UnionChatRingBuf.num, ubw->UnionChatRingBuf.start, ubw->Scroll.now);

		
		// �ȈՉ�b�`��
		for(i=0;i<max;i++){
			UnionChat_Print(ubw, i, &ubw->UnionChatRingBuf->mes[pos]);
			pos = AddUnionChatRingBufPos(ubw->UnionChatRingBuf,pos);
		}
		DC_FlushRange((void*)GF_BGL_ScreenAdrsGet( ubw->bgl, GF_BGL_FRAME3_S ), 32*24*2);
		GF_BGL_LoadScreen(	ubw->bgl, GF_BGL_FRAME3_S, GF_BGL_ScreenAdrsGet( ubw->bgl, GF_BGL_FRAME3_S ), 32*24*2, 0 );

		ubw->BgTransReq = FALSE;

	}

}

// ����ʗp�{�^���ʒu��`
#define SUB_BUTTON1_POSX		( 256-24   )
#define SUB_BUTTON1_POSY		( 0        )
#define SUB_BUTTON2_POSX		( 256-24   )
#define SUB_BUTTON2_POSY		( 192-8*4  )
#define SUB_BUTTON_W			( 8*2 )
#define SUB_BUTTON_H			( 8*4 )
#define SUB_SCROLLBAR_POSX		( 256-24   )
#define SUB_SCROLLBAR_POSY		( 8*4+16  )
#define SUB_SCROLLBAR_W			( 24  )
#define SUB_SCROLLBAR_H			( 192-8*8-16*2  )

#define SUB_CHAT_POSX			(  0 )
#define SUB_CHAT1_POSY			(  0 )
#define SUB_CHAT2_POSY			( 8*8)
#define SUB_CHAT3_POSY			(16*8)
#define SUB_CHAT_W				(29*8)
#define SUB_CHAT_H				( 8*8)


static const RECT_HIT_TBL sub_button_hittbl[]={
	{SUB_BUTTON1_POSY, SUB_BUTTON1_POSY+SUB_BUTTON_H, SUB_BUTTON1_POSX, SUB_BUTTON1_POSX+SUB_BUTTON_W},
	{SUB_BUTTON2_POSY, SUB_BUTTON1_POSY+SUB_BUTTON_H, SUB_BUTTON2_POSX, SUB_BUTTON1_POSX+SUB_BUTTON_W},
	{SUB_CHAT1_POSY, SUB_CHAT1_POSY+SUB_CHAT_H, SUB_CHAT_POSX, SUB_CHAT_POSX+SUB_CHAT_W},
	{SUB_CHAT2_POSY, SUB_CHAT2_POSY+SUB_CHAT_H, SUB_CHAT_POSX, SUB_CHAT_POSX+SUB_CHAT_W},
	{SUB_CHAT3_POSY, SUB_CHAT3_POSY+SUB_CHAT_H, SUB_CHAT_POSX, SUB_CHAT_POSX+SUB_CHAT_W},
	{SUB_SCROLLBAR_POSY, SUB_SCROLLBAR_POSY+SUB_SCROLLBAR_H, SUB_SCROLLBAR_POSX, SUB_SCROLLBAR_POSX+SUB_SCROLLBAR_W},
	{RECT_HIT_END,0,0,0},		// �I���f�[�^
};

static const RECT_HIT_TBL sub_scroll_hittbl[]={
	{SUB_SCROLLBAR_POSY, SUB_SCROLLBAR_POSY+SUB_SCROLLBAR_H, SUB_SCROLLBAR_POSX, SUB_SCROLLBAR_POSX+SUB_SCROLLBAR_W},
	{SUB_CHAT1_POSY, SUB_CHAT1_POSY+SUB_CHAT_H, SUB_CHAT_POSX, SUB_CHAT_POSX+SUB_CHAT_W},
	{SUB_CHAT2_POSY, SUB_CHAT2_POSY+SUB_CHAT_H, SUB_CHAT_POSX, SUB_CHAT_POSX+SUB_CHAT_W},
	{SUB_CHAT3_POSY, SUB_CHAT3_POSY+SUB_CHAT_H, SUB_CHAT_POSX, SUB_CHAT_POSX+SUB_CHAT_W},
	{RECT_HIT_END,0,0,0},		// �I���f�[�^
};

//------------------------------------------------------------------
/**
 * $brief   �X�N���[���o�[�̍��W��ݒ肷��
 *
 * @param   act		�A�N�^�[�̃|�C���^
 * @param   y		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SetScrollBar_PosY( CLACT_WORK_PTR act, int y )
{
	VecFx32 mat;

	mat.x = FX32_CONST( SUB_SCROLLBAR_POSX );
	mat.y = FX32_CONST( y ) + SUB_SURFACE_Y;
	mat.z = 0;
	CLACT_SetMatrix( act, &mat);

}

//------------------------------------------------------------------
/**
 * $brief   �X�N���[���o�[����̏���
 *
 * @param   ubw		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void ScrollControl( UNION_BOARD_WORK *ubw )
{

	ubw->Scroll.max = ubw->UnionChatRingBuf->num;

	// ���ڐ����S�ȏ�ɂȂ�����X�N���[���o�[��\������(���鎖�͂Ȃ����낤���ǁj
	if(ubw->Scroll.max > 3 && ubw->Scroll.old_max<=3){
		ubw->Scroll.barflag = 1;
		ubw->Scroll.now            = 0;
	}
	CLACT_SetDrawFlag(ubw->clActWork[2], ubw->Scroll.barflag);	//�X�N���[���o�[�\������
	
	if( ubw->Scroll.barflag ){
		if(!GF_TP_GetCont()){
			int haba,y;
			y    = SUB_SCROLLBAR_POSY + (ubw->Scroll.now * SUB_SCROLLBAR_H) / (ubw->Scroll.max-3);
			SetScrollBar_PosY( ubw->clActWork[2],y );
//			OS_Printf("y=%d, haba=%d, now=%d max=%d\n",y,haba,ubw->Scroll.now, ubw->Scroll.max);
		}
	}
	ubw->Scroll.old_max = ubw->Scroll.max;
}	

//------------------------------------------------------------------
/**
 * @brief   �^�b�`�p�l���̃g���K�[����
 *
 * @param   ubw		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int TouchTrgFunc( UNION_BOARD_WORK *ubw )
{
	int button,i,listpos;
	WMBssDesc         *beacon;
	_GF_BSS_DATA_INFO *gfinfo;

	button=GF_TP_RectHitTrg( sub_button_hittbl );
	if( button != RECT_HIT_NONE ){
		switch(button){
		// ����i��ɃE�C���h�E���P�X�N���[���j
		case 0:
			CLACT_AnmChg( ubw->clActWork[button], button+4 );	//�e�X�̎p��
			if(ubw->Scroll.now!=0){
				Snd_SePlay(SEQ_SE_DP_BUTTON3);
				ubw->Scroll.now--;
			}
			break;
		// �����i���ɃE�C���h�E���P�X�N���[���j
		case 1:
			CLACT_AnmChg( ubw->clActWork[button], button+4 );	//�e�X�̎p��
			if(ubw->Scroll.now<ubw->Scroll.max-3){
				Snd_SePlay(SEQ_SE_DP_BUTTON3);
				ubw->Scroll.now++;
			}
			break;
		// �X�N���[���o�[
		case 5:
			break;

		// ���ʃ����o�[�T�[�`�����i�E�C���h�E��G��Ə�ŐԂ��g�j
		// �ȈՉ�b�E�C���h�E��������
//		case 2:	case 3:	case 4:
		default:
			if(ubw->UnionChatRingBuf->num >= (button-1)){	// �󂯎���Ă����b�����{�^�����傫���Ƃ��͖�������

				listpos = GetUnionBoardPrintPoint( ubw->UnionChatRingBuf->start, ubw->Scroll.now )+button-2;

				// �r�[�R����ID����v���āA�����ɒn�ʂɗ����Ă���Ȃ�΃G�t�F�N�gON
			
				// �P�O�l���̐e�@�r�[�R������������
				for(i=0;i<10;i++){
					beacon = CommMPGetWMBssDesc(i);	
					if(beacon!=NULL){		// �r�[�R�������Ȃ�������X���[
						gfinfo = (_GF_BSS_DATA_INFO*)&beacon->gameInfo.userGameInfo;
						// �r�[�R����ID����v���āA�����ɒn�ʂɗ����Ă���Ȃ�΃G�t�F�N�gON
//						OS_Printf("appear=%d, pokeID=%d, RingBufID=%d\n",ubw->cuv->objwork[i].appear,gfinfo->pokeID,ubw->UnionChatRingBuf.mes[listpos].id);
						if((ubw->cuv->objwork[i].appear==OBJ_OK) && (gfinfo->pokeID == ubw->UnionChatRingBuf->mes[listpos].id)){
							Snd_SePlay(SEQ_SE_DP_BUTTON3);
							ubw->cuv->objwork[i].effect = 1;
							break;
						}
					}
				}
				// �����̃`���b�g�H
				{
					MYSTATUS *my = CommMPGetMyStatus();
					
					if(ubw->UnionChatRingBuf->mes[listpos].id == MyStatus_GetID(my)){
						Snd_SePlay(SEQ_SE_DP_BUTTON3);
						ubw->cuv->objwork[UNION_EFFECT_HERO_NO].effect = 1;
					}
				
				}

			}
			break;
		}
		ubw->lastHitTrg = button-2;
	}

	return button;
}

//------------------------------------------------------------------
/**
 * @brief   �^�b�`�p�l�����h���b�O����Ƃ��̏���
 *
 * @param   ubw		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int TouchContFunc( UNION_BOARD_WORK *ubw )
{
	int button;

	// �X���C�h�o�[����
	button=GF_TP_RectHitCont( sub_scroll_hittbl );
	if( button != RECT_HIT_NONE ){
		u32 x, y;
		switch(button){
		case 0:

			// �^�b�`���Ă�����W�ɃX���C�h�o�[�����W�ݒ�
			GF_TP_GetPointCont( &x, &y );
			SetScrollBar_PosY( ubw->clActWork[2],y );
		
			// ��ԋ߂����b�Z�[�W�������ʒu�̃A�^�����擾���Ă���
			if(ubw->Scroll.max>3){
				int haba,i;

				haba = SUB_SCROLLBAR_H / (ubw->Scroll.max-2);
				for(i=0;i<ubw->Scroll.max-2;i++){
					if( (y >= SUB_SCROLLBAR_POSY+haba*i) && (y < SUB_SCROLLBAR_POSY+haba*(i+1))){
						ubw->Scroll.now =i;
						break;
					}
				}
			}
			break;
		// �ȈՉ�b�E�C���h�E
//		case 1: case 2: case 3:
		default:
			if(ubw->UnionChatRingBuf->num>=button){	// �󂯎���Ă����b�����{�^�����傫���Ƃ��͖�������

				// �����ĂȂ������܂��͓����{�^�������������Ă���Ȃ甽������
				if(ubw->lastHitTrg==(button-1)){	
					if(ubw->UnionBmp[button-1].push<2*2+1){
						ubw->UnionBmp[button-1].push++;
					}
				}
			}
			break;
		}
	}

	return button;
}


//------------------------------------------------------------------
/**
 * @brief   �k�q�{�^���Ń`���b�g�E�C���h�E�𓮂��������ł���
 *
 * @param   ubw		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void LR_ButtonFunc( UNION_BOARD_WORK *ubw )
{
	if(sys.trg & PAD_BUTTON_L){
		// ����i���ɃE�C���h�E���P�X�N���[���j�Ɠ����@�\
		CLACT_AnmChg( ubw->clActWork[0], 0+4 );
		if(ubw->Scroll.now!=0){
			ubw->Scroll.now--;
			Snd_SePlay(SEQ_SE_DP_BUTTON3);
		}
	}else if(sys.trg & PAD_BUTTON_R){
		// �����i���ɃE�C���h�E���P�X�N���[���j�Ɠ����@�\
		CLACT_AnmChg( ubw->clActWork[1], 1+4 );
		if(ubw->Scroll.now<ubw->Scroll.max-3){
			ubw->Scroll.now++;
			Snd_SePlay(SEQ_SE_DP_BUTTON3);
		}
	}

}
//------------------------------------------------------------------
/**
 * $brief   �^�b�`�p�l������
 *
 * @param   ubw		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void TouchPanelFunc( UNION_BOARD_WORK *ubw )
{
	int button=RECT_HIT_NONE;

	// �C�x���g���łȂ���΃^�b�`�p�l���ɔ�������
	if(!FieldEvent_Check(ubw->fsys)){
		int check;
		check  = TouchTrgFunc( ubw );
		button = TouchContFunc( ubw );

		// �^�b�`�p�l���ɂ܂������G���Ă��Ȃ��Ȃ�k�q�{�^���̏������Ăяo��
		if(check==RECT_HIT_NONE && button == RECT_HIT_NONE){
			LR_ButtonFunc(ubw);
		}
	}
	

	// �ȈՉ�b�E�C���h�E�{�^���̃A�j�������i�����ꂽ��ւ��ށE�����Ɩ߂�j
	ChatButtonAnimation( ubw->bgl, ubw->BoardScreen, ubw->UnionBmp, button-1, ubw->UnionChatRingBuf->num, &ubw->old_winanime);
}


static const bg_src_anime_offset[]={0,3,5};

//------------------------------------------------------------------
/**
 * @brief   �ȈՉ�b�E�C���h�E�A�j������
 *
 * @param   bgl		
 * @param   Screen		
 * @param   Board		
 * @param   button		
 * @param   num		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void ChatButtonAnimation( GF_BGL_INI *bgl, NNSG2dScreenData *Screen, UNION_BOARD_BMP *Board, int button, int num, int *old)
{
	int i,tmp=0;
	if(num>3){
		num = 3;
	}
	
	for(i=0;i<num;i++){
		if(button!=i){
			if(Board[i].push!=0){
				Board[i].push--;
			}
		}
		tmp += Board[i].push;
//		OS_Printf("button %d = %d   ", i, Board[i].push);
	}
//	OS_Printf("\n");

	// �S���O��������]���̕K�v�͂Ȃ�(�S���O���������̃t���[�����]������j
	if(tmp==0 && *old==0){
		*old = tmp;
		return;
	}
	// �O��̃t���[���̃o�b�N�A�b�v
	*old = tmp;

	for(i=0;i<num;i++){
		int page = Board[i].push/2;

		// �X�N���[�����H�]��
		GF_BGL_ScrWriteExpand( bgl, GF_BGL_FRAME3_S, 0, i*8, 32, 8,
			Screen->rawData, 0, 24*Board[i].sex+8*page, 32, 48 );
		GF_BGL_ScrollSet( bgl, GF_BGL_FRAME0_S+i, GF_BGL_SCROLL_Y_SET, bg_src_anime_offset[page] );

	}
	DC_FlushRange((void*)GF_BGL_ScreenAdrsGet( bgl, GF_BGL_FRAME3_S ), 32*24*2);

	GF_BGL_LoadScreen(	bgl, GF_BGL_FRAME3_S, GF_BGL_ScreenAdrsGet( bgl, GF_BGL_FRAME3_S ), 32*24*2, 0 );


//	OS_Printf("�]�����Ă�\n");

}

//------------------------------------------------------------------
/**
 * $brief   ���肠���Ȃ�u�������̂Ƃ������v�Ƃ�����������Z�b�g
 *
 * @param   fr		
 * @param   id		
 * @param   wordset		
 * @param   msgdata		
 *
 * @retval  STRBUF *		
 */
//------------------------------------------------------------------
static STRBUF *FriendLinkStringGet(FRIEND_LIST *friendlist, u32 id, WORDSET *wordset, MSGDATA_MANAGER *msgdata, MYSTATUS *my)
{
	STRBUF *string = NULL;
	STRBUF *name;
	int ret = 0;

	// ���肠�����A���肠���̂��肠��������
	if(id != MyStatus_GetID(my)){
		ret = FriendList_IdFullCheck( friendlist, id );
	}
	
	if(ret>0){
		if(ret==DIRECT_FRIEND){
			// �����̂��肠���������玩���̖��O��
			WORDSET_RegisterPlayerName( wordset, 0, my );
		}else if(ret>=INDIRECT_FRIEND){
			// �F�B�̒m�荇���������炻�̗F�B�̖��O��
			int index = ret-INDIRECT_FRIEND;
			name = STRBUF_Create(10,HEAPID_UNIONBOARD);
			STRBUF_SetStringCode( name, FriendList_GetName(friendlist, index));
			WORDSET_RegisterWord( wordset, 0, name, 0, 0, FriendList_GetGroupListRegion( friendlist, index ) );
			STRBUF_Delete(name);
		}
		// �u�������̂Ƃ������v
		string = MSGDAT_UTIL_AllocExpandString( wordset, msgdata, msg_union_friend_name01, HEAPID_UNIONBOARD );
	}
	return string;
}


//------------------------------------------------------------------
/**
 * $brief   UnionChat�\���̂ɐV�����f�[�^��o�^����
 *
 * @param   union_mes		
 * @param   id		
 * @param   pms		
 * @param   mystatus		
 * @param   no		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void AddUnionChatPmsData( UNION_BOARD_WORK *ubw,	u32 id, PMS_DATA *pms, MYSTATUS *mystatus )
{
	UNION_CHAT_RINGBUF *chatbuf = ubw->UnionChatRingBuf;
	FRIEND_LIST *friendlist 	= ubw->cuv->friendlist;
	int *pos;

	OS_Printf("�������ݑO chat->num %d, chat->start %d\n", chatbuf->num, chatbuf->start);

	// �`���b�g�����O�o�b�t�@�̍ő吔�܂ł��Ă���ꍇ�̓X�^�[�g�ʒu�����炵�Ă����i�����O�o�b�t�@�����j
	if(chatbuf->num==UNION_CHAT_MAX){	// MAX=30��
		pos = &chatbuf->start;
	}else{
		pos = &chatbuf->num;
	}
	
	// ���ɊȈՉ�b�̕�����o�b�t�@���m�ۂ��Ă���ꍇ�͉������
	if(chatbuf->mes[*pos].message!=NULL){
		STRBUF_Delete(chatbuf->mes[*pos].message);
	}
	// ���ɂ��肠�����m�̕�����o�b�t�@���m�ۂ��Ă���ꍇ�͉������
	if(chatbuf->mes[*pos].friend!=NULL){
		STRBUF_Delete(chatbuf->mes[*pos].friend);
	}
	
	// ���O�EID�E�ȈՉ�b�E�ȈՉ�b������̓o�^
	STRBUF_SetStringCode( chatbuf->mes[*pos].name, MyStatus_GetMyName(mystatus));
	chatbuf->mes[*pos].PmsData = *pms;
	chatbuf->mes[*pos].id      = id;
	chatbuf->mes[*pos].sex     = MyStatus_GetMySex(mystatus);
	chatbuf->mes[*pos].message = PMSDAT_ToString( pms, HEAPID_UNIONBOARD );
	chatbuf->mes[*pos].friend  = FriendLinkStringGet(friendlist, id, ubw->WordSet, ubw->MsgManager, ubw->mystatus);
	
	// ���̓o�^�ʒu�ɂ��炷
	(*pos)++;

	// �X�^�[�g�ʒu���ő�܂ł����ꍇ�͍ŏ��ɖ߂�
	if(chatbuf->start==UNION_CHAT_MAX){
		chatbuf->start = 0;
	}

	OS_Printf("�������݌� chat->num %d, chat->start %d\n", chatbuf->num, chatbuf->start);

}


//------------------------------------------------------------------
/**
 * $brief   �`���b�g�f�[�^���o�^���邩�ǂ����`�F�b�N
 *
 * @param   ubw		
 * @param   pms		
 * @param   id		
 *
 * @retval  int		0�͓o�^�ς� 1�Ȃ�o�^����ĂȂ��V�����o�[ 
 */
//------------------------------------------------------------------
static int UnionChatRegisterCheck(UNION_BOARD_WORK *ubw, PMS_DATA *pms, int id)
{
	int r,index;


	// �ȈՉ�b�͗L���ȓ��e���H
	if(!PMSDAT_IsEnabled(pms)){
		return 0;
	}

	// ���ɕ\���ς݂̓��e���`�F�b�N
	for(r=0;r<ubw->UnionChatRingBuf->num;r++){
		if( id==ubw->UnionChatRingBuf->mes[r].id ){
			if(PMSDAT_Compare( pms, &ubw->UnionChatRingBuf->mes[r].PmsData)){
				break;
			}
		}
	}

	// ���ɓo�^�ς݂��H( �o�^���O�̎��͐�Γo�^)
	if(r!=ubw->UnionChatRingBuf->num && ubw->UnionChatRingBuf->num!=0){
		return 0;
	}

	if( id==ubw->UnionChatRingBuf->mes[r].id ){
		OS_Printf("ID��������̂œo�^ %08x , %08x\n", id,ubw->UnionChatRingBuf->mes[r].id);
	}else if(PMSDAT_Compare( pms, &ubw->UnionChatRingBuf->mes[r].PmsData)){
		OS_Printf("�ȈՉ�b��������̂œo�^ %08x , %08x\n", id,ubw->UnionChatRingBuf->mes[r].id);
	}

	return 1;
	
}



//------------------------------------------------------------------
/**
 * $brief   �V�K�ȈՉ�b�o�^�i���l�E���������Ή��j
 *
 * @param   ubw		
 * @param   mystatus		
 * @param   pms		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void UnionBoard_AddChatSub( UNION_BOARD_WORK *ubw, MYSTATUS *status, PMS_DATA *pms, u32 id )
{
	int flag=0;

	// �X�N���[���o�[�̈�ԉ��Ɉʒu���Ă��邩
	if(ubw->Scroll.now==ubw->Scroll.max-3){
		flag = 1;
	}
	OS_Printf("scroll.now=%d scroll_max = %d\n", ubw->Scroll.now, ubw->Scroll.max);

	// �`���b�g���o�b�t�@�ƈ�v���Ȃ������̂œo�^
	AddUnionChatPmsData( ubw, id, pms, status );

	// �X�N���[���o�[����ԉ��ɂ��鎞�͉��ɂ��Â���悤�Ɂ{�P����
	if(ubw->Scroll.barflag){
		if(flag){
			ubw->Scroll.now = ubw->UnionChatRingBuf->num-3;
		}
		OS_Printf("scrol.now=%d, chat->num=%d, chat->start=%d\n", ubw->Scroll.now,ubw->UnionChatRingBuf->num,ubw->UnionChatRingBuf->start);
	}
	UnionBoardReWriteOn( ubw );

}


static _GF_BSS_DATA_INFO* d_gfinfo;
static PMS_DATA* d_pms;

//------------------------------------------------------------------
/**
 * $brief   �r�[�R���f�[�^����V�����`���b�g�f�[�^���擾����
 *
 * @param   ubw		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void GetUnionChat( UNION_BOARD_WORK *ubw )
{
//	GetWMBssDesc_toPmsData(ubw->UnionChat);
	int i,r;
	WMBssDesc 			*beacon;
	_GF_BSS_DATA_INFO   *gfinfo;
	PMS_DATA			*pms;
	MYSTATUS			*status;
	PMS_DATA			debugpms;

	// �b���|�����̓`���b�g�X�V�����Ȃ�
	if(FieldEvent_Check(ubw->fsys)){
		return;
	}

	status = MyStatus_AllocWork(HEAPID_FIELD);
	
	for(i=0;i<16;i++){
		beacon = CommMPGetWMBssDesc(i);
		
		// �r�[�R�������݂��Ă��遁���j�I�����[���̐l������
		if(beacon!=NULL){

			gfinfo = (_GF_BSS_DATA_INFO*)&beacon->gameInfo.userGameInfo;
			pms    = (PMS_DATA*)&gfinfo->pmsData;
			d_gfinfo = (_GF_BSS_DATA_INFO*)&beacon->gameInfo.userGameInfo;
			d_pms    = (PMS_DATA*)&gfinfo->pmsData;
			MyStatus_Copy((MYSTATUS*)gfinfo->myStatusBuff, status);

			// �`���b�g�f�[�^�͓o�^�ς݁H
			if(UnionChatRegisterCheck(ubw, pms, gfinfo->pokeID)){
				// ��v���Ȃ������̂œo�^
				UnionBoard_AddChatSub( ubw, status, pms, gfinfo->pokeID );	// �ȈՉ�b�o�^
			}
		}
	}

	// �����̃f�[�^���f�ڃ��N�G�X�g���󂯂Ă��Ȃ����H
	if((pms=Union_GetMyPmsData( ubw->union_work ))!=NULL){
		u32 id = MyStatus_GetID( ubw->mystatus );
		UnionBoard_AddChatSub( ubw, ubw->mystatus, pms, id  );	// �ȈՉ�b�o�^
	}
	
	sys_FreeMemoryEz(status);
}


//------------------------------------------------------------------
/**
 * $brief   BMP�ʂ̍ĕ`�惊�N�G�X�g���s
 *
 * @param   ubw		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void UnionBoardReWriteOn( UNION_BOARD_WORK *ubw)
{
	ubw->BgTransReq = TRUE;

}
