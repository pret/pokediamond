
//===========================================================================
/**
 *
 *@file		ug_radar.c
 *@brief	�Y�z���[�_�[�����i�T�u��ʁj
 *@author	Akito Mori
 *@data		2005.09.23
 *
 */
//===========================================================================

#include "common.h"
#include "system/lib_pack.h"
#include "system/brightness.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "gflib/strbuf.h"
#include "gflib/strbuf_family.h"

#include "system/clact_util.h"
#include "system/render_oam.h"
#include "system/pm_str.h"

#include "system/bmp_menu.h"
#include "system/window.h"
#include "system/fontproc.h"
#include "fld_bmp.h"
#include "fieldmap.h"
#include "fieldsys.h"
#include "talk_msg.h"

#include "communication/communication.h"
#include "underground/ug_manager.h"
#include "underground/ug_trap.naix"
#include "comm_player.h"
#include "underg_radar.naix"
#include "ug_radar.h"

//========================================================================================
// �萔�錾
//========================================================================================

#define UG_RADAR_RESOURCE_ID	(   1000 ) 	// ����ʂ̃��\�[�X�h�c���Փ˂��Ȃ��悤�ɂ��邽�߂�1000�Ƃ���
#define UG_TALK_SPLIT_WORD_MAX	( 20*2*2 )	// ���s�������Ă��郍�O��b�̍ő啶����
#define UG_MESSAGE_LINE_NUM     (      2 )  // ��b�E�C���h�E�͂Q�s�����Ȃ���

// pos�Eview�z��̓Y������`
#define POS_XZ 		(2)
#define POS_XZ_TIME (3)
#define POS_XZ_INFO	(4)
#define POS_X  		(0)
#define POS_Z  		(1)
#define POS_TIME  	(2)
#define POS_INFO	(2)
#define POS_OLDINFO (3)


// �Y�B���[�_�[�ő�OBJ�o�^��
#define UG_RADAR_CLACT_MAX ( COMM_MACHINE_MAX + TRAP_NUM_SINGLE_MAX + 1) //32+1�̂͂�


// ���[�_�[�\���ʒu�w��p��`
#define RADAR_MIN_X		(7*8+4)
#define RADAR_MIN_Y		(    8+1)
#define RADAR_MAX_X		(RADAR_MIN_X+8*17+2)
#define RADAR_MAX_Y		(RADAR_MIN_Y+8*16)

// �}�b�v���u���b�N�f�[�^�̉E���ɂȂ����炵���̂ŋ����p�f�[�^

// +--------------+
// |              |
// | +------------+
// | |            |
// | |   ����     |
// | |            |
// | |            |
// +-+------------+
#define MAP_START_OFFSET_X	( 32 )
#define MAP_START_OFFSET_Y	( 64 )

// �O���b�h���l�ő��`
#define RADAR_GRID_MAX_X (32*14)
#define RADAR_GRID_MAX_Z (32*13)


// CellActor�ɏ��������郊�\�[�X�}�l�[�W���̐��i���}���`�Z���E�}���`�Z���A�j���͎g�p���Ȃ��j
#define CELL_ANIME_RESOURCE_NUM	(4)

// �Y�z���[�_�[�̃^�X�N�̗D�揇�ʁi�ʐM���͉��ɂ���K�v�Ƃ�����Ǝv���̂Łj
#define UNDER_GROUND_RADAR_TCB_PRIORITY		(4)


#define MESSAGE_NONE		( 0 )
#define MESSAGE_WAIT		( 1 )
#define MESSAGE_END			( 2 )

#define RADAR_TALK_WAIT 	( 8 )

#define UG_MES_FIFO_MAX		( 32 )

#define _EVWIN_MSG_BUF_SIZE		(50*2)			//���b�Z�[�W�o�b�t�@�T�C�Y

// -----�Y�z���[�_�[�����̃V�[�P���X��`---------
enum{
	UG_INIT_BG = 0,
	UG_INIT_ACTOR,
	UG_START_FADE,
	UG_LCD_ON,
	UG_WAIT_FADE,
	UG_MAIN,
	UG_END_READY,
	UG_END,
	UG_END_FADE,
};

typedef struct{
    STRBUF* TalkBuf[UG_MES_FIFO_MAX];
    STRBUF* tempBuf;
	STRBUF* splitbuf[UG_MESSAGE_LINE_NUM];
	int top;
	int bottom;
	STRCODE codework[UG_TALK_SPLIT_WORD_MAX];
}UG_MESSAGE_FIFO;



//========================================================================================
// �\���̐錾
//========================================================================================
struct UG_RADAR_WORK{
	int           mode;												// ���[�_�[�J��
	int           pos[COMM_MACHINE_MAX][POS_XZ];					// �S�����̍��W
	int           view[COMM_MACHINE_MAX][POS_XZ_TIME];				// �\���p�̍��W�{��������(2�b)
	int		      trappos[TRAP_NUM_SINGLE_MAX+1][POS_XZ_INFO];		// 
	

	FIELDSYS_WORK *fsys;											// �t�B�[���h��������p���V�X�e���|�C���^
	GF_BGL_INI    *bgl;												// �t�B�[���h��������p���a�f�V�X�e���|�C���^

	CLACT_SET_PTR clactSet;											// �Z���A�N�^�[�Z�b�g
	CLACT_U_EASYRENDER_DATA	renddata;								// �ȈՃ����_�[�f�[�^
	CLACT_U_RES_MANAGER_PTR	resMan[CELL_ANIME_RESOURCE_NUM];		// ���\�[�X�}�l�[�W��
	CLACT_U_RES_OBJ_PTR 	resObjTbl[CELL_ANIME_RESOURCE_NUM];		// ���\�[�X�I�u�W�F�e�[�u��
	CLACT_HEADER			clActHeader;							// �Z���A�N�^�[�w�b�_�[

	CLACT_WORK_PTR			clActWork[COMM_MACHINE_MAX];			// �Z���A�N�^�[���[�N�|�C���^�z��(��l���j
	CLACT_WORK_PTR			TrapActWork[TRAP_NUM_SINGLE_MAX+1];		// �Z���A�N�^�[���[�N�|�C���^�z��i㩁j
	GF_BGL_BMPWIN 			talkWin;								// ���[�_�[��ʃ��b�Z�[�W�E�C���h�E
	int						MesIndex;								// ���b�Z�[�W�C���f�b�N�X
	int						TalkMode;
	int						Wait;
	UG_MESSAGE_FIFO			UgMesFifo;
//    u16                   talkBuff[32][50*GLOBAL_MSGLEN];			

	
};

int debugpos[COMM_MACHINE_MAX][POS_XZ];


//========================================================================================
// �v���g�^�C�v�錾
//========================================================================================
static void initBG(GF_BGL_INI *bgl,GF_BGL_BMPWIN *talkWin);
static void InitCellActor(UG_RADAR_WORK *urw);
static void HeroPosGet(const PLAYER_STATE_PTR jiki,int pos[][POS_XZ], int view[][POS_XZ_TIME]);
static void InitWork(int pos[][POS_XZ], int view[][POS_XZ_TIME]);
static void HeroRadarPosSet(int view[][POS_XZ_TIME], CLACT_WORK_PTR clActWork[]);
static void initBG(GF_BGL_INI* bgl, GF_BGL_BMPWIN *talkWin);
static void destBG(GF_BGL_INI* bgl);


extern void FieldMsgPrintInitSub(void);
extern void FldTalkBmpAddSub( GF_BGL_INI * ini, GF_BGL_BMPWIN * win );

static void RadarActionMessageFunc(GF_BGL_INI *bgl, GF_BGL_BMPWIN *talkWin, int *MesIndex, int *talkmode, int *wait, UG_MESSAGE_FIFO *MesFifo);


static void     MessageFifoInit(UG_MESSAGE_FIFO *fifo);
static void     MessageFifoFinalize(UG_MESSAGE_FIFO *fifo);
static int      MessageFifoIn(UG_MESSAGE_FIFO *fifo, STRBUF *src);
static STRBUF*  MessageFifoOut(UG_MESSAGE_FIFO *fifo);
static int      MessageFifoCheck(UG_MESSAGE_FIFO *fifo);
static void HeroTrapActSet( int pos[][POS_XZ_INFO],  CLACT_WORK_PTR TrapActWork[]);
static void HeroTrapPosGet( int pos[][POS_XZ_INFO] );

static UG_RADAR_WORK *debug_ug_radar;

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
static void UnderGround_RadarFunc(TCB_PTR tcb, void *wk)
{
	UG_RADAR_WORK *urw = wk;
	GF_BGL_INI    *bgl = urw->bgl;
	int i;

	debug_ug_radar = urw;
	switch(urw->mode){
	case UG_INIT_BG:
		// BG�������EVRAM�]��
		OS_Printf("start underground = %ld\n",sys_GetHeapFreeSize(HEAPID_FIELD));
		OS_Printf("underground  work= %ld\n",sizeof(UG_RADAR_WORK));

		initBG(bgl,&urw->talkWin);

		// ���[�_�[�p�z�񏉊���
		InitWork(urw->pos,urw->view);
		MessageFifoInit(&urw->UgMesFifo);
		urw->mode++;
		break;
	case UG_INIT_ACTOR:

		InitCellActor(urw);

		// �Z���A�N�^�[�w�b�_�쐬
		CLACT_U_MakeHeader(&urw->clActHeader, 
							UG_RADAR_RESOURCE_ID,
							UG_RADAR_RESOURCE_ID,
							UG_RADAR_RESOURCE_ID,
							UG_RADAR_RESOURCE_ID,
							CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
							0, 0,
							urw->resMan[CLACT_U_CHAR_RES],
							urw->resMan[CLACT_U_PLTT_RES],
							urw->resMan[CLACT_U_CELL_RES],
							urw->resMan[CLACT_U_CELLANM_RES],
							NULL,NULL);

		{
			//�o�^���i�[
			CLACT_ADD add;

			add.ClActSet	= urw->clactSet;
			add.ClActHeader	= &urw->clActHeader;

			add.mat.x		= FX32_CONST(32) ;
			add.mat.y		= FX32_CONST(96) + SUB_SURFACE_Y;		//��ʂ͏㉺�A�����Ă���iMAIN����ASUB�����j
			add.mat.z		= 0;
			add.sca.x		= FX32_ONE;
			add.sca.y		= FX32_ONE;
			add.sca.z		= FX32_ONE;
			add.rot			= 0;
			add.pri			= 0;
			add.DrawArea	= NNS_G2D_VRAM_TYPE_2DSUB;
			add.heap		= HEAPID_FIELD;

			//�Z���A�N�^�[�\���J�n

			// ��l���o�^
			for(i=0;i<COMM_MACHINE_MAX;i++){
				urw->clActWork[i] = CLACT_Add(&add);
				CLACT_SetAnmFlag(urw->clActWork[i],1);
				CLACT_SetDrawFlag(urw->clActWork[i], 0);	//��\����
				if(i==0){			//��U�����͂O�Ƃ������Ƃɂ���
					CLACT_AnmChg( urw->clActWork[i], 1 );		//�F��
				}
			}
			
			// 㩓o�^
			for(i=0;i<TRAP_NUM_SINGLE_MAX+1;i++){
				urw->TrapActWork[i] = CLACT_Add(&add);
				CLACT_SetAnmFlag(urw->TrapActWork[i],1);
				CLACT_SetDrawFlag(urw->TrapActWork[i], 0);	//��\����
				CLACT_AnmChg( urw->TrapActWork[i], 2 );		//㩃A�j���Ƀ`�F���W
			}
			
		}	
		


		GF_Disp_GXS_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);	//OBJ�ʂn�m
		
		urw->mode++;
		break;
	case UG_START_FADE:
		// �P�x�t�F�[�h�J�n
//		ChangeBrightnessRequest(30,BRIGHTNESS_NORMAL,BRIGHTNESS_BLACK,
//			PLANEMASK_BG0|PLANEMASK_BG3|PLANEMASK_OBJ,MASK_SUB_DISPLAY);
		urw->mode++;
		break;
	case UG_LCD_ON:
		// �T�u��ʕ\���n�m
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_ON );
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
		GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_S, 0 );
		urw->mode++;
		break;
	case UG_WAIT_FADE:
//		if(IsFinishedBrightnessChg(MASK_SUB_DISPLAY)){		//�t�F�[�h�I���҂�
			urw->mode++;
//		}
		break;
		
	// ���C���V�[�P���X
	case UG_MAIN:
		HeroPosGet(urw->fsys->player,urw->pos,urw->view);				// �ʐM�֐������l���̈ʒu���擾����
		HeroRadarPosSet(urw->view, urw->clActWork);						// ���[�_�[�p�̍��W�ɕϊ����ēo�^����
		HeroTrapPosGet( urw->trappos);									// �����Őݒu����㩂̈ʒu���擾����
		HeroTrapActSet( urw->trappos, urw->TrapActWork);
		

		RadarActionMessageFunc(urw->bgl,
                               &urw->talkWin,&urw->MesIndex,
                               &urw->TalkMode,&urw->Wait,&urw->UgMesFifo);	// �s�����e�����b�Z�[�W�ɔ��f

		CLACT_Draw( urw->clactSet );									// �Z���A�N�^�[�풓�֐�
		break;

	// �I���V�[�P���X
	case UG_END_READY:
		if(FldTalkMsgEndCheck( urw->MesIndex )){					//���b�Z�[�W�\���I����҂��Ȃ��Ƃӂ��Ƃ�
			urw->mode++;
		}
		break;

	case UG_END:
		// �L�����]���}�l�[�W���[�j��
		CLACT_U_CharManagerDelete(urw->resObjTbl[CLACT_U_CHAR_RES]);

		// �p���b�g�]���}�l�[�W���[�j��
		CLACT_U_PlttManagerDelete(urw->resObjTbl[CLACT_U_PLTT_RES]);
		
		// �L�����E�p���b�g�E�Z���E�Z���A�j���̃��\�[�X�}�l�[�W���[�j��
		for(i=0;i<CELL_ANIME_RESOURCE_NUM;i++){
			CLACT_U_ResManagerDelete(urw->resMan[i]);
		}
		// �Z���A�N�^�[�Z�b�g�j��
		CLACT_DestSet(urw->clactSet);

		BmpTalkWinClear( &urw->talkWin, WINDOW_TRANS_ON );
		GF_BGL_BmpWinDel( &urw->talkWin );						//BmpWin���

		GF_BGL_BGControlExit(bgl, GF_BGL_FRAME3_S);				//��b�E�C���h�E�p�o�b�t�@���
		destBG(bgl);											// BG0,BG1�p�o�b�t�@���
        MessageFifoFinalize(&urw->UgMesFifo);

		// �P�x�t�F�[�h�J�n
//		ChangeBrightnessRequest(30,BRIGHTNESS_BLACK,BRIGHTNESS_NORMAL,PLANEMASK_BG0,MASK_SUB_DISPLAY);
		urw->mode++;
		break;

	case UG_END_FADE:
//		if(IsFinishedBrightnessChg(MASK_SUB_DISPLAY)){
			urw->fsys->UnderGroundRadar = NULL;
			PMDS_taskDel(tcb);	//�^�X�N�폜
			OS_Printf("end underground = %ld\n",sys_GetHeapFreeSize(HEAPID_FIELD));
//		}


		break;
		

	}

}

//------------------------------------------------------------------
/**
 * ���[�_�[�\���p���W������
 *
 * @param   pos[][POS_XZ]			
 * @param   view[][POS_XZ_TIME]		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void InitWork(int pos[][POS_XZ], int view[][POS_XZ_TIME])
{
	int i;
	for(i=0;i<COMM_MACHINE_MAX;i++){
		pos[i][POS_X]     = 0;
		pos[i][POS_Z]     = 0;
		view[i][POS_X]    = 0;
		view[i][POS_Z]    = 0;
		view[i][POS_TIME] = 0;
		
		debugpos[i][POS_X]   = gf_rand()%500+50;
		debugpos[i][POS_Z]   = gf_rand()%500+50;

	}
}

#if 0
int debugposmovex(int no, int flag)
{
	debugpos[no][flag] += gf_rand()%4 -2;

	return debugpos[no][flag];
}

#endif
//------------------------------------------------------------------
/**
 * ���݂̎�l���̍��W���擾����i�ʐM�֐����炩�A�t�B�[���h�֐����炩�͔��f�j
 *
 * @param   jiki					fieldsys��player�\���̂̃|�C���^
 * @param   pos[][POS_XZ]			��l���̍��W
 * @param   view[][POS_XZ_TIME]		���[�_�[�\���p�̍��W�z��̃|�C���^
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void HeroPosGet(const PLAYER_STATE_PTR jiki,int pos[][POS_XZ], int view[][POS_XZ_TIME])
{
	int i;
	
	//�ʐM�֐������l���̈ʒu���擾
	for(i=0;i<COMM_MACHINE_MAX;i++){
		pos[i][POS_X] = CommPlayerGetPosX(i);
		pos[i][POS_Z] = CommPlayerGetPosZ(i);
	}

	//�ʐM���Ă��Ȃ��Ƃ��̓t�B�[���h��̍��W���擾

	if(CommIsInitialize()){
		if(CommIsConnect(CommGetCurrentID())==0){
			pos[0][POS_X] = Player_NowGPosXGet( jiki );	
			pos[0][POS_Z] = Player_NowGPosZGet( jiki );
		}else{
            // ���������Ȃ�悤�Ɉʒu������
            int gx = pos[0][POS_X];
            int gz = pos[0][POS_Z];
			pos[0][POS_X] = pos[CommGetCurrentID()][POS_X];
			pos[0][POS_Z] = pos[CommGetCurrentID()][POS_Z];
			pos[CommGetCurrentID()][POS_X] = gx;
			pos[CommGetCurrentID()][POS_Z] = gz;
		}
	}
	//�擾�l��\�����W�Ɋi�[����
	for(i=0;i<COMM_MACHINE_MAX;i++){
        if(!UgSecretBaseIsSecretBasePlace(pos[i][POS_X],pos[i][POS_Z])){
            view[i][POS_X]    = pos[i][POS_X] - MAP_START_OFFSET_X;
			view[i][POS_Z]    = pos[i][POS_Z] - MAP_START_OFFSET_Y;
			view[i][POS_TIME] = 60; //RADAR_LIFE_TIME;
//			OS_Printf("comm= %d, X= %ld,Y= %ld\n",CommIsConnect(CommGetCurrentID()),pos[i][POS_X],pos[i][POS_Z]);
		}else{
			if(view[i][POS_TIME]!=0){
				if(view[i][POS_X]>=0){		//��x�������Ă���
					view[i][POS_TIME]--;
				}
			}
		}
	}
}


//------------------------------------------------------------------
/**
 * ���[�_�[�p�̍��W�ɕϊ����ēo�^����(�\���E��\���̐�����s���j
 *
 * @param   view[][POS_XZ_TIME]		�\���p���W�i�[�z��
 * @param   clActWork[]				�Z���A�N�^�[���[�N�̃|�C���^�z��
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void HeroRadarPosSet(int view[][POS_XZ_TIME], CLACT_WORK_PTR clActWork[])
{
	int i;

	for(i=0;i<COMM_MACHINE_MAX;i++){
		if(view[i][POS_TIME]!=0){
			VecFx32 pos;

			pos.x = (RADAR_MIN_X + ((RADAR_MAX_X-RADAR_MIN_X)*view[i][POS_X])/RADAR_GRID_MAX_X)*FX32_ONE;
			pos.y = (RADAR_MIN_Y + ((RADAR_MAX_Y-RADAR_MIN_Y)*view[i][POS_Z])/RADAR_GRID_MAX_Z)*FX32_ONE+ SUB_SURFACE_Y;
			pos.z = FX32_ONE;
			CLACT_SetMatrix(clActWork[i], &pos);
			CLACT_SetDrawFlag(clActWork[i], 1);	//���݂��Ă���Ȃ�\����

		}else{
			CLACT_SetDrawFlag(clActWork[i], 0);	//�O�ȊO�͔�\����
		}
	}
}


//------------------------------------------------------------------
/**
 * ������㩂̃O���b�h�ʒu���擾�i�����̂Ȃ̂ŒʐM�͊֌W�Ȃ��j
 *     ���点�������̂�Ԃ��悤�ɓ����֐��ύX���܂���  k.ohno 06.03.22
 * @param   pos[][POS_XZ]		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void HeroTrapPosGet( int pos[][POS_XZ_INFO] )
{
	int i, x, z,info;
	for(i=0;i<TRAP_NUM_SINGLE_MAX+1;i++){

		x    = UgMgrGetDispPointX(i);
    	z    = UgMgrGetDispPointZ(i);
		info = UgMgrGetDispPointInfo(i);

        if(!UgSecretBaseIsSecretBasePlace(x, z)){
            pos[i][POS_X] = x - MAP_START_OFFSET_X;
            pos[i][POS_Z] = z - MAP_START_OFFSET_Y;
			pos[i][POS_INFO] = info;
        }
        else{
            pos[i][POS_X] = 0;
            pos[i][POS_Z] = 0;
			pos[i][POS_INFO] = 0;
        }
	}
}



//------------------------------------------------------------------
/**
 * ������㩂̕\��
 *
 * @param   pos[][POS_XZ]		
 *
 * @retval  staitc void		
 */
//------------------------------------------------------------------
static void HeroTrapActSet( int pos[][POS_XZ_INFO],  CLACT_WORK_PTR TrapActWork[])
{
	int i;
	for(i=0;i<TRAP_NUM_SINGLE_MAX+1;i++){
		if(pos[i][POS_X]!=0 ){
			VecFx32 vec;
			vec.x = (RADAR_MIN_X + ((RADAR_MAX_X-RADAR_MIN_X)*pos[i][POS_X])/RADAR_GRID_MAX_X)*FX32_ONE;
			vec.y = (RADAR_MIN_Y + ((RADAR_MAX_Y-RADAR_MIN_Y)*pos[i][POS_Z])/RADAR_GRID_MAX_Z)*FX32_ONE +SUB_SURFACE_Y;
			vec.z = FX32_ONE;
			CLACT_SetMatrix(TrapActWork[i], &vec);

			// �O��ƕ\����񂪕ς���Ă���ꍇ�͌����ڕύX
			if(pos[i][POS_INFO]!=pos[i][POS_OLDINFO]){
				if(pos[i][POS_INFO]!=RADAR_TYPE_NONE){
					CLACT_AnmChg( TrapActWork[i], pos[i][POS_INFO] );
					CLACT_SetDrawFlag(TrapActWork[i], 1);
				}else{
					CLACT_SetDrawFlag(TrapActWork[i], 0);	//�O�ȊO�͔�\����
				}
			}
		}else{
			CLACT_SetDrawFlag(TrapActWork[i], 0);	//�O�ȊO�͔�\����
		}

		// �\�������X�V
        pos[i][POS_OLDINFO] = pos[i][POS_INFO];

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
UG_RADAR_WORK *UnderGround_RadarInit( FIELDSYS_WORK *fsys )
{
	UG_RADAR_WORK *urw;
	TCB_PTR       tcb;

	//�Y�z���[�_�[�^�X�N��ǉ�
	tcb = PMDS_taskAdd(UnderGround_RadarFunc, sizeof(UG_RADAR_WORK), UNDER_GROUND_RADAR_TCB_PRIORITY, HEAPID_FIELD);
	urw = TCB_GetWork(tcb);
	urw->fsys = fsys;
	urw->bgl  = fsys->bgl;

	return urw;
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
void UnderGround_RadarEnd(UG_RADAR_WORK *urw)
{
	// ���[�_�[�̃V�[�P���X��`���I���ɕύX
	if(urw->mode==UG_MAIN){
		urw->mode = UG_END_READY;
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
static void initBG(GF_BGL_INI* bgl, GF_BGL_BMPWIN *talkWin)
{
	// ���܂ł̔j��
	destBG(bgl);

	// �T�u��BG�O�C�P,3�̃R���g���[����ݒ�
	{
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x7000, GX_BG_CHARBASE_0x04000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( bgl, GF_BGL_FRAME0_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );
	}
	{
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x7800, GX_BG_CHARBASE_0x04000, GX_BG_EXTPLTT_01,
			2, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( bgl, GF_BGL_FRAME1_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
	}
	{
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x6800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( bgl, GF_BGL_FRAME3_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_OFF );
		GF_BGL_ScrClear( bgl, GF_BGL_FRAME3_S );
	}


	// �p���b�g�]��
	ArcUtil_PalSet(    ARC_UG_RADAR_GRA, NARC_underg_radar_ug_radar_NCLR, PALTYPE_SUB_BG, 0, 0x20*2,  HEAPID_FIELD);



	// �L�����]��( 32*9*0x20�܂ł͂�����j
	ArcUtil_BgCharSet( ARC_UG_RADAR_GRA, NARC_underg_radar_ug_radar_NCGR, bgl, GF_BGL_FRAME0_S, 0, 32*5*0x20, 0, HEAPID_FIELD);
																					

	// �X�N���[���]��
	ArcUtil_ScrnSet(   ARC_UG_RADAR_GRA, NARC_underg_radar_ug_radar_NSCR, bgl, GF_BGL_FRAME0_S, 0, 32*24*2, 0, HEAPID_FIELD);

	FieldMsgPrintInit( PALTYPE_SUB_BG, MSG_PRINT_NO_INIT );				// �T�u���VRAM�Ƀt�H���g�ƃp���b�g��]��

	
	GF_BGL_ClearCharSet( FLD_SBGFRM_FONT, 32, 0, HEAPID_FIELD );
    FldTalkBmpAdd( bgl, talkWin, FLD_SBGFRM_FONT);	// �T�u��ʃ��b�Z�[�W�E�C���h�E�m��
	GF_BGL_BmpWinDataFill( talkWin, 0 );

	ArcUtil_PalSet(ARC_UG_TRAP_GRA, NARC_ug_trap_ug_menu_NCLR, PALTYPE_SUB_BG, FLD_MESFRAME_PAL*0x20, 4*0x20,  HEAPID_FIELD);

//    FldTalkWinPut( talkWin );			// �T�u��ʃ��b�Z�[�W�E�C���h�E�\���J�n
//    _pInfo->msgIndex = FldTalkMsgStart(&_pInfo->talkWin, pMsg, 1);

}



//------------------------------------------------------------------
/**
 * ���[�_�[��ʗp�Z���A�N�^�[������
 *
 * @param   urw		���[�_�[�\���̂̃|�C���^
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void InitCellActor(UG_RADAR_WORK *urw)
{
	int i;
	// �Z���A�N�^�[������
	urw->clactSet = CLACT_U_SetEasyInit( UG_RADAR_CLACT_MAX, &urw->renddata, HEAPID_FIELD );
	
	//���\�[�X�}�l�[�W���[������
	for(i=0;i<CELL_ANIME_RESOURCE_NUM;i++){		//���\�[�X�}�l�[�W���[�쐬
		urw->resMan[i] = CLACT_U_ResManagerInit( 1, i, HEAPID_FIELD );
	}

	
	//chara�ǂݍ���
	urw->resObjTbl[CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(urw->resMan[CLACT_U_CHAR_RES], 
			ARC_UG_RADAR_GRA, NARC_underg_radar_ug_radar_obj_NCGR, 0, UG_RADAR_RESOURCE_ID, NNS_G2D_VRAM_TYPE_2DSUB, HEAPID_FIELD);

	//pal�ǂݍ���
	urw->resObjTbl[CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(urw->resMan[CLACT_U_PLTT_RES],
			ARC_UG_RADAR_GRA, NARC_underg_radar_ug_radar_obj_NCLR, 0, UG_RADAR_RESOURCE_ID, NNS_G2D_VRAM_TYPE_2DSUB, 2, HEAPID_FIELD);

	//cell�ǂݍ���
	urw->resObjTbl[CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(urw->resMan[CLACT_U_CELL_RES],
			ARC_UG_RADAR_GRA, NARC_underg_radar_ug_radar_obj_NCER, 0, UG_RADAR_RESOURCE_ID, CLACT_U_CELL_RES,HEAPID_FIELD);

	//�����֐���anim�ǂݍ���
	urw->resObjTbl[CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(urw->resMan[CLACT_U_CELLANM_RES],
			ARC_UG_RADAR_GRA, NARC_underg_radar_ug_radar_obj_NANR, 0, UG_RADAR_RESOURCE_ID, CLACT_U_CELLANM_RES,HEAPID_FIELD);

	// Chara�]��
	CLACT_U_CharManagerSetAreaCont( urw->resObjTbl[CLACT_U_CHAR_RES] );

	// �p���b�g�]��
	CLACT_U_PlttManagerSetCleanArea( urw->resObjTbl[CLACT_U_PLTT_RES] );

}




//------------------------------------------------------------------
/**
 * �Y�B���[�_�[��b�E�C���h�E��ʐ���
 *
 * @param  bgl 		GF_BGL_INI*
 * @param  talkWin	GF_BGL_BMPWIN*
 * @param  MesIndex	�����\���҂��t���O
 * @param  talkmode �����\����ԁi����Ȃ��A�\���҂��A�X�N���[�����j
 * @param  wait		�����\�����Ŏg�p����E�F�C�g�J�E���^
 * @param  MesFifo	�ʐM��l���s�����OFIFO
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void RadarActionMessageFunc(
	GF_BGL_INI *bgl, 
	GF_BGL_BMPWIN *talkWin, 
	int *MesIndex, 
	int *talkmode, 
	int *wait,  
	UG_MESSAGE_FIFO *MesFifo)
{
    STRBUF* strbuf;
    
    while(CommUnderGetActionMessage(MesFifo->tempBuf)){  // ���̏󋵂������o��FIFO�ɋl�߂�
		MessageFifoIn(MesFifo,MesFifo->tempBuf);
    }

	switch(*talkmode){
	// ���͕\���J�n
	case MESSAGE_NONE:
		if((strbuf=MessageFifoOut(MesFifo))!=NULL){
			*MesIndex = GF_STR_PrintSimple(
				talkWin, FONT_TALK, strbuf, 0, 2+16, 1,	NULL );
	        *talkmode = MESSAGE_WAIT;
		}
        break;
	// �\���I���҂�
	case MESSAGE_WAIT:
		if(FldTalkMsgEndCheck( *MesIndex )){
			*talkmode = MESSAGE_END;
			*wait = 0;
		}
		break;

	// �X�N���[��
	case MESSAGE_END:
		if(MessageFifoCheck(MesFifo)==0){
			GF_BGL_BmpWinShift( talkWin, GF_BGL_BMPWIN_SHIFT_U, 2,  0x00);
			GF_BGL_BmpWinOn( talkWin );
			if(++(*wait) > RADAR_TALK_WAIT){
				*wait = 0;
//				BmpTalkWinClear( talkWin, WINDOW_TRANS_OFF );
				*talkmode = MESSAGE_NONE;
			}
		}
		break;
	}
}


//------------------------------------------------------------------
/**
 * ���b�Z�[�WFIFO������
 *
 * @param   fifo	UG_MESSAGE_FIFO�\���̂̃|�C���^
 *
 * @retval  none	
 */
//------------------------------------------------------------------
static void MessageFifoInit(UG_MESSAGE_FIFO *fifo)
{
	int i;
	for(i=0;i<UG_MES_FIFO_MAX;i++){
        fifo->TalkBuf[i] = STRBUF_Create( _EVWIN_MSG_BUF_SIZE, HEAPID_FIELD );
    }
	fifo->top    = 0;
	fifo->bottom = 0;
    fifo->tempBuf = STRBUF_Create( _EVWIN_MSG_BUF_SIZE, HEAPID_FIELD );
	for(i=0;i<UG_MESSAGE_LINE_NUM;i++){
		fifo->splitbuf[i] = STRBUF_Create( UG_TALK_SPLIT_WORD_MAX, HEAPID_FIELD );
	}
}

//------------------------------------------------------------------
/**
 * ���b�Z�[�WFIFO�I��
 *
 * @param   fifo	UG_MESSAGE_FIFO�\���̂̃|�C���^
 *
 * @retval  none	
 */
//------------------------------------------------------------------
static void MessageFifoFinalize(UG_MESSAGE_FIFO *fifo)
{
	int i;
	for(i=0;i<UG_MES_FIFO_MAX;i++){
        STRBUF_Delete(fifo->TalkBuf[i]);
    }
    STRBUF_Delete(fifo->tempBuf);
	for(i=0;i<UG_MESSAGE_LINE_NUM;i++){
		STRBUF_Delete( fifo->splitbuf[i] );
	}

}

//------------------------------------------------------------------
/**
 * $brief   ���s���݂̔z��Ȃ番�����ĂP�s���ɂ킯��
 *
 * @param   fifo	
 * @param   src		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int UgMessageCheck( UG_MESSAGE_FIFO* fifo, STRBUF *src )
{
	int i,num,pos;
	// STRCODE�ɖ߂�
	STRBUF_GetStringCode( src, fifo->codework, UG_TALK_SPLIT_WORD_MAX );

	// ���s�R�[�h�����邩�T��
	num = 0;
	i   = 0;
	while(fifo->codework[i]!=EOM_){
		if(fifo->codework[i]==CR_){
			num++;
			pos = i;
		}
		i++;
	}
	GF_ASSERT(num<2 && "�Y�B���[�_�[���b�Z�[�W�ɉ��s���Q�����Ă���");

	// ���s�R�[�h�͂Ȃ�����
	if(num==0){
		// ���ʂɃR�s�[���ďI��
		STRBUF_Copy(fifo->splitbuf[0],src);
		return 1;
	}else{
	// ���s�R�[�h���������ꍇ�͂Q��STRBUF�ɕ����ĕۑ�����
		fifo->codework[pos] = EOM_;
		STRBUF_SetStringCode( fifo->splitbuf[0], fifo->codework );
		STRBUF_SetStringCode( fifo->splitbuf[1], &fifo->codework[pos+1] );
	}

	return 2;
}
//------------------------------------------------------------------
/**
 * ���b�Z�[�WFIFO�ɒǉ�
 *
 * @param   fifo	UG_MESSAGE_FIFO�\���̂̃|�C���^
 * @param   src		�R�s�[���̕�����
 *
 * @retval  int		�i�[������1,���Ȃ�������0
 */
//------------------------------------------------------------------
static int MessageFifoIn(UG_MESSAGE_FIFO *fifo, STRBUF *src)
{
	int top,i,linenum;

	// �Q�s�ɂ܂�������STRBUF���`�F�b�N
	linenum = UgMessageCheck( fifo, src );

	// FIFO�o�^�O�`�F�b�N
	top = fifo->top;
	for(i=0;i<linenum;i++){
		if(++top==UG_MES_FIFO_MAX){
			top = 0;
		}
		if(top==fifo->bottom){			// bottom�ɒǂ����Ă��Ȃ����`�F�b�N
			return 0;					// �o�^����Ƃ������Ă��܂��ꍇ�͏I��
		}
	}

	// �o�^�ł���
	for(i=0;i<linenum;i++){
   		STRBUF_Copy(fifo->TalkBuf[fifo->top],fifo->splitbuf[i]);
		fifo->top++;
		if(fifo->top==UG_MES_FIFO_MAX){
			fifo->top = 0;
		}
	}
	return 1;
}

//------------------------------------------------------------------
/**
 * ���b�Z�[�WFIFO������o��
 *
 * @param   fifo		UG_MESSAGE_FIFO�\���̂̃|�C���^
 *
 * @retval  STRCODE*	���o����������̃|�C���^
 */
//------------------------------------------------------------------
static STRBUF* MessageFifoOut(UG_MESSAGE_FIFO *fifo)
{
	int result;
	if(fifo->top!=fifo->bottom){	// FIFO�������������Ă��Ȃ����`�F�b�N
		result = fifo->bottom;
		if(++fifo->bottom==UG_MES_FIFO_MAX){
			fifo->bottom = 0;
		}

		return fifo->TalkBuf[result];
	}
	return NULL;
}

//------------------------------------------------------------------
/**
 * FIFO�������������Ă��邩�`�F�b�N
 *
 * @param   fifo	UG_MESSAGE_FIFO�\���̂̃|�C���^
 *
 * @retval  int		�����������Ă�����1,�������0
 */
//------------------------------------------------------------------
static int MessageFifoCheck(UG_MESSAGE_FIFO *fifo)
{
	if(fifo->top!=fifo->bottom){	// FIFO�������������Ă��Ȃ����`�F�b�N
		return 0;
	}
	return 1;
}