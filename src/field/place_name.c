//============================================================================================
/**
 * @file	place_name.c	
 * @bfief	�n���\��
 * @author	Nozomu Saito
 * @date	01.03.29
 *
 */
//============================================================================================
#include "common.h"
#include "place_name.h"
#include "zonedata.h"
#include "system/bmp_menu.h"
#include "fieldsys.h"
#include "fieldmap.h"
#include "system/fontproc.h"
#include "system/pm_str.h"
#include "fld_bmp.h"
#include "system/msgdata.h"
#include "msgdata/msg.naix"				//NARC_msg_??_dat
#include "msgdata/msg_place_name.h"

#include "fieldmap_work.h"

#define PAL_ONE_SIZE	( 32 )		// �ʏ�p���b�g 16x2
#define ONE_CHAR_SIZE	(8)
#define PLACE_NAME_FRAME	(GF_BGL_FRAME3_M)

#define PLACE_NAME_OFS_MIN	(0)
#define PLACE_NAME_OFS_MAX	(38)
#define PLANE_NAME_SCROLL_SPEED	(4)
#define PLACE_NAME_HOLD_TIME	(60)

//�������艺�̒�`�̓p���b�g�A�L�����f�[�^�Ɉˑ����܂�
#define PLACE_NAME_PAL_WHITE	(0x0f)

#define PLACE_NAME_CHAR_LU		(1)
#define PLACE_NAME_CHAR_UP		(2)
#define PLACE_NAME_CHAR_RU		(3)
#define PLACE_NAME_CHAR_LD		(4)
#define PLACE_NAME_CHAR_DOWN	(5)
#define PLACE_NAME_CHAR_RD		(6)
#define PLACE_NAME_CHAR_LEFT	(7)
#define PLACE_NAME_CHAR_RIGHT	(8)
#define PLACE_NAME_CHAR_CENTER	(9)

//���Ӑ}�I�ȋ�
#define WIN_WHITE_SPACE			(8)

//���f�U�C����A�t���[���̏����Ă���L�����ŕ����̂�����X�y�[�X�i�h�b�g�j
#define WIN_CAN_USE_SPACE				(4)
//���f�U�C����A�t���[���̏����Ă���L�����̕����̂����Ȃ��X�y�[�X�i�h�b�g�j
#define WIN_DEAD_SPACE			(ONE_CHAR_SIZE-WIN_CAN_USE_SPACE)	
#define WRITE_NAME_POS_Y	(4)

typedef enum {
	NAME_STATE_NONE = 0,
	NAME_STATE_DOWN,
	NAME_STATE_UP,
	NAME_STATE_DOWN_HOLD
} PLACE_NAME_STATE;

typedef struct PLACE_NAME_CONT_tag
{
	BOOL			Moving;				//�^�X�N�͉ғ������H
	u8				State;				//�\�����
	TCB_PTR			Task;				//�^�X�N�|�C���^
	int				Offset;				//�X�N���[���l
	u16				WaitCount;
	BOOL			IsNext;
	int				NameID;
	GF_BGL_INI		*WinIni;
	GF_BGL_BMPWIN	Win;
	u8				WriteOffs;
	NNSG2dCharacterData *CharDat;
	void * CharBuff;
	MSGDATA_MANAGER* MsgDataManager;
	STRBUF			*NameBuff; 
}PLACE_NAME_CONT;

static void SetPlaceNameGraphic(PNC_PTR outPlaceNameCont);
static void SetPlaceNameWinGraphic( PNC_PTR outPlaceNameCont,
									u8 frmnum,
									u16 cgx,
									u8 pal,
									u8 win_num );
static void CleanPlaceNameCont(PNC_PTR outPlaceNameCont);
static void SetUpPlaceNameCont(PNC_PTR, GF_BGL_INI *bgl);
static void PlaceNameTask(TCB_PTR tcb,void *work);
static void SetupPlaceNameWin(PNC_PTR outPlaceNameCont, const int inLen);
static void SetUPState(PNC_PTR outPlaceNameCont);
static void WritePlaceName(PNC_PTR ioPlaceNameCont,const STRBUF* inName);
static u32 GetPlaceName(MSGDATA_MANAGER* manager, const int inNameID, STRBUF *outName);

//------------------------------------------------------------------
/**
 * @brief	�p���b�g�Z�b�g
 * @param	buf		�o�b�t�@		
 * @param	siz		�T�C�Y
 * @param	ofs		�I�t�Z�b�g
 * @return	none
 */
//------------------------------------------------------------------
static void SetPlaceNameWinPalette( void * buf, u16 siz, u16 ofs )
{
	DC_FlushRange( (void *)buf, siz * PAL_ONE_SIZE );
	GX_LoadBGPltt( (const void *)buf, ofs * PAL_ONE_SIZE, siz * PAL_ONE_SIZE );
}

//------------------------------------------------------------------
/**
 * @brief	�O���t�B�b�N�Z�b�g
 * @param	outPlaceNameCont	�n���\���̂ւ̃|�C���^		
 * @return	none
 */
//------------------------------------------------------------------
static void SetPlaceNameGraphic(PNC_PTR outPlaceNameCont)
{
	GF_BGL_BmpWinAdd(
			outPlaceNameCont->WinIni, &outPlaceNameCont->Win,
			FLD_MBGFRM_FONT,  FLD_PLACE_WIN_PX,  FLD_PLACE_WIN_PY,
			FLD_PLACE_WIN_SX, FLD_PLACE_WIN_SY, PLACE_WIN_PAL, FLD_PLACE_WIN_CGX );
	SetPlaceNameWinGraphic( outPlaceNameCont,
							FLD_MBGFRM_FONT,
							PLACE_WIN_CGX_NUM,
							PLACE_WIN_PAL,
							0 );
}

//------------------------------------------------------------------
/**
 * @brief	�E�B���h�E�O���t�B�b�N�Z�b�g
 * @param	ioPlaceNameCont	�n���\���̂ւ̃|�C���^
 * @param	frmnum			�t���[���i���o�[
 * @param	cgx				�L����
 * @param	pal				�p���b�g
 * @param	win_num			�E�B���h�E�i���o�[
 * @return	none
 */
//------------------------------------------------------------------
static void SetPlaceNameWinGraphic( PNC_PTR ioPlaceNameCont,
									u8 frmnum,
									u16 cgx,
									u8 pal,
									u8 win_num )
{
	void * buf;
	u32	size;
	NNSG2dPaletteData * pal_dat;

	ioPlaceNameCont->CharDat = GF_BGL_NTRCHR_CharGet(	&ioPlaceNameCont->CharBuff,
														HEAPID_FIELD,
														"/data/dp_areawindow.NCGR" );
	GF_BGL_LoadCharacter(	ioPlaceNameCont->WinIni,
							frmnum,
							ioPlaceNameCont->CharDat->pRawData,
							ioPlaceNameCont->CharDat->szByte,
							cgx );
	pal_dat = GF_BGL_NTRCHR_PalLoad(&buf,HEAPID_FIELD, "/data/dp_areawindow.NCLR");
	
	SetPlaceNameWinPalette( pal_dat->pRawData, 1, pal );
	sys_FreeMemoryEz( buf );
}

//------------------------------------------------------------------
/**
 * @brief	�E�B���h�E�Z�b�g�A�b�v
 * @param	ioPlaceNameCont	�n���\���̂ւ̃|�C���^
 * @param	len				�����񒷂�
 * @return	none
 */
//------------------------------------------------------------------
static void SetupPlaceNameWin(PNC_PTR ioPlaceNameCont, const int inLen)
{
	int bmp_len;	//�t���[�����[�������܂܂Ȃ��A�K�v��BMP�h�b�g�T�C�Y
	int char_w;		//�L�����T�C�Y
	int plus_ofs;	//�t���[�����[�̕����������Ȃ��I�t�Z�b�g�l����̃I�t�Z�b�g

	int total_dot;
	int rest_dot;
	int plus;
	u8 plus_char;
	u8 i;			//�ėp�J�E���^

	total_dot = (inLen+ONE_CHAR_SIZE)/ONE_CHAR_SIZE*ONE_CHAR_SIZE;
	rest_dot = total_dot-inLen;
	plus = rest_dot/2;
 
	if ( WIN_WHITE_SPACE <= (WIN_CAN_USE_SPACE+plus) ){
		plus_char = 0;
	}else{
		int temp;
		temp = WIN_WHITE_SPACE - (WIN_CAN_USE_SPACE+plus);	//�󔒂����̂ɑ���Ȃ��Б��̃h�b�g��
		temp*=2;											//�󔒂����̂ɑ���Ȃ��h�b�g�����v
		plus_char = (temp+(ONE_CHAR_SIZE-1))/ONE_CHAR_SIZE;	//�K�v�L����
	}

	bmp_len = inLen;
	if (bmp_len <=0 ){
		char_w = 0;
		plus_ofs = 0;
	}else{
		char_w = (bmp_len+ONE_CHAR_SIZE)/ONE_CHAR_SIZE;	//�t���[���������������K�v�L������
		char_w += plus_char;
		//�����Z�I�t�Z�b�g���i�������������Ƃ��ł���h�b�g��-�n�������h�b�g���j/2
		plus_ofs = ( ((char_w*ONE_CHAR_SIZE)+(WIN_CAN_USE_SPACE*2) ) - inLen ) / 2;
	}
	
	ioPlaceNameCont->WriteOffs = WIN_DEAD_SPACE+plus_ofs;
	///OS_Printf("name =%d,%d,%d,%d\n",total_dot,inLen,char_w,plus_ofs);

	//�N���[������
	{
		GF_BGL_BmpWinDataFill( &ioPlaceNameCont->Win, 0 );	//�a�l�o�E�B���h�E���N���A
		
		//�a�l�o�E�B���h�E���쐬
		{
			//����t���[��
			GF_BGL_BmpWinPrint(
					&ioPlaceNameCont->Win, ioPlaceNameCont->CharDat->pRawData,
					PLACE_NAME_CHAR_LU*ONE_CHAR_SIZE, 0, ONE_CHAR_SIZE, ONE_CHAR_SIZE,
					0, 0, ONE_CHAR_SIZE, ONE_CHAR_SIZE );
			//�E��t���[��
			GF_BGL_BmpWinPrint(
					&ioPlaceNameCont->Win, ioPlaceNameCont->CharDat->pRawData,
					PLACE_NAME_CHAR_RU*ONE_CHAR_SIZE, 0, ONE_CHAR_SIZE, ONE_CHAR_SIZE,
					(char_w+1)*ONE_CHAR_SIZE, 0, ONE_CHAR_SIZE, ONE_CHAR_SIZE );
			//���t���[��
			GF_BGL_BmpWinPrint(
					&ioPlaceNameCont->Win, ioPlaceNameCont->CharDat->pRawData,
					PLACE_NAME_CHAR_LEFT*ONE_CHAR_SIZE, 0, ONE_CHAR_SIZE, ONE_CHAR_SIZE,
					0, ONE_CHAR_SIZE, ONE_CHAR_SIZE, ONE_CHAR_SIZE );
			//�E�t���[��
			GF_BGL_BmpWinPrint(
					&ioPlaceNameCont->Win, ioPlaceNameCont->CharDat->pRawData,
					PLACE_NAME_CHAR_RIGHT*ONE_CHAR_SIZE, 0, ONE_CHAR_SIZE, ONE_CHAR_SIZE,
					(char_w+1)*ONE_CHAR_SIZE, ONE_CHAR_SIZE, ONE_CHAR_SIZE, ONE_CHAR_SIZE );
			//�����t���[��
			GF_BGL_BmpWinPrint(
					&ioPlaceNameCont->Win, ioPlaceNameCont->CharDat->pRawData,
					PLACE_NAME_CHAR_LD*ONE_CHAR_SIZE, 0, ONE_CHAR_SIZE, ONE_CHAR_SIZE,
					0, ONE_CHAR_SIZE*2, ONE_CHAR_SIZE, ONE_CHAR_SIZE );
			//�E���t���[��
			GF_BGL_BmpWinPrint(
					&ioPlaceNameCont->Win, ioPlaceNameCont->CharDat->pRawData,
					PLACE_NAME_CHAR_RD*ONE_CHAR_SIZE, 0, ONE_CHAR_SIZE, ONE_CHAR_SIZE,
					(char_w+1)*ONE_CHAR_SIZE, ONE_CHAR_SIZE*2, ONE_CHAR_SIZE, ONE_CHAR_SIZE );
			for(i=0;i<char_w;i++){
				//��t���[��
				GF_BGL_BmpWinPrint(
					&ioPlaceNameCont->Win, ioPlaceNameCont->CharDat->pRawData,
					PLACE_NAME_CHAR_UP*ONE_CHAR_SIZE, 0, ONE_CHAR_SIZE, ONE_CHAR_SIZE,
					ONE_CHAR_SIZE*(1+i), 0, ONE_CHAR_SIZE, ONE_CHAR_SIZE );
				//�E�B���h�E��
				GF_BGL_BmpWinPrint(
					&ioPlaceNameCont->Win, ioPlaceNameCont->CharDat->pRawData,
					PLACE_NAME_CHAR_CENTER*ONE_CHAR_SIZE, 0, ONE_CHAR_SIZE, ONE_CHAR_SIZE,
					ONE_CHAR_SIZE*(1+i), ONE_CHAR_SIZE, ONE_CHAR_SIZE, ONE_CHAR_SIZE );
				//���t���[��
				GF_BGL_BmpWinPrint(
					&ioPlaceNameCont->Win, ioPlaceNameCont->CharDat->pRawData,
					PLACE_NAME_CHAR_DOWN*ONE_CHAR_SIZE, 0, ONE_CHAR_SIZE, ONE_CHAR_SIZE,
					ONE_CHAR_SIZE*(1+i), ONE_CHAR_SIZE*2, ONE_CHAR_SIZE, ONE_CHAR_SIZE );
			}
			GF_BGL_BmpWinOn( &ioPlaceNameCont->Win );
		}
	}
}

//------------------------------------------------------------------
/**
 * @brief	�\���̃N���[��
 * @param	outPlaceNameCont	�n���\���̂ւ̃|�C���^
 * @return	none
 */
//------------------------------------------------------------------
static void CleanPlaceNameCont(PNC_PTR outPlaceNameCont)
{
	outPlaceNameCont->Moving = FALSE;
	outPlaceNameCont->State = NAME_STATE_NONE;
	outPlaceNameCont->Task = NULL;
	outPlaceNameCont->Offset = 0;
	outPlaceNameCont->WaitCount = 0;
	outPlaceNameCont->IsNext = FALSE;
	outPlaceNameCont->NameID = 0;
	outPlaceNameCont->WinIni = NULL;
}

//------------------------------------------------------------------
/**
 * @brief	�\���̃Z�b�g�A�b�v
 * @param	outPlaceNameCont	�n���\���̂ւ̃|�C���^
 * @param	bgl	BGL
 * @return	none
 */
//------------------------------------------------------------------
static void SetUpPlaceNameCont(PNC_PTR outPlaceNameCont, GF_BGL_INI *bgl)
{
	CleanPlaceNameCont(outPlaceNameCont);
	outPlaceNameCont->WinIni = bgl;
}

//------------------------------------------------------------------
/**
 * @brief	�n���\���^�X�N
 * @param	tcb			�^�X�N�|�C���^
 * @param	work		���[�N
 * @return	none
 */
//------------------------------------------------------------------
static void PlaceNameTask(TCB_PTR tcb,void *work)
{
	STRCODE name[BUFLEN_PLACE_NAME];
	u32 len;
	PLACE_NAME_CONT *place_name = (PLACE_NAME_CONT *)(work);
	switch(place_name->State){
	case NAME_STATE_DOWN:			//�~����
		place_name->Offset-=PLANE_NAME_SCROLL_SPEED;

		if (place_name->Offset < PLACE_NAME_OFS_MIN){
			place_name->Offset = PLACE_NAME_OFS_MIN;
		}
		
		GF_BGL_ScrollSet( place_name->WinIni, PLACE_NAME_FRAME, GF_BGL_SCROLL_Y_SET, place_name->Offset );
		if (place_name->Offset == PLACE_NAME_OFS_MIN){
			
			place_name->WaitCount = 0;
			place_name->State = NAME_STATE_DOWN_HOLD;
		}
		break;
	case NAME_STATE_DOWN_HOLD:		//�~����㏸�҂�
		place_name->WaitCount++;
		if (place_name->WaitCount>=PLACE_NAME_HOLD_TIME){
			place_name->WaitCount = 0;
			place_name->State = NAME_STATE_UP;
		}
		break;
	case NAME_STATE_UP:				//�㏸��
		place_name->Offset+=PLANE_NAME_SCROLL_SPEED;
		if (place_name->Offset > PLACE_NAME_OFS_MAX){
			place_name->Offset = PLACE_NAME_OFS_MAX;
		}
		GF_BGL_ScrollSet( place_name->WinIni, PLACE_NAME_FRAME, GF_BGL_SCROLL_Y_SET, place_name->Offset );
		if (place_name->Offset == PLACE_NAME_OFS_MAX){
			if (place_name->IsNext){
				place_name->IsNext = FALSE;

				//���O�Z�b�g
				len = PNC_GetPlaceName(place_name->MsgDataManager, place_name->NameID, place_name->NameBuff);
				
				SetupPlaceNameWin(place_name,len);
				
				WritePlaceName(place_name,place_name->NameBuff);
				place_name->State = NAME_STATE_DOWN;
			}else{
				StopPlaceName(place_name);	//<<�����Ń^�X�N������Ă�
				return;
			}
		}
		break;
	case NAME_STATE_NONE:
	default:
		//�A�T�[�V����
		break;
	}
}

//------------------------------------------------------------------
/**
 * @brief	�n���̃��C�g
 * @param	ioPlaceNameCont	�n���\���̂ւ̃|�C���^
 * @param	inName			�n��
 * @return	none
 */
//------------------------------------------------------------------
static void WritePlaceName(PNC_PTR ioPlaceNameCont, const STRBUF *inName)
{	
	GF_PRINTCOLOR col;
	col = GF_PRINTCOLOR_MAKE(1,2,0);
	GF_STR_PrintColor(	&ioPlaceNameCont->Win,
						FONT_SYSTEM,
						inName,
						ioPlaceNameCont->WriteOffs, WRITE_NAME_POS_Y,
						MSG_ALLPUT,
						col,
						NULL );
}

//------------------------------------------------------------------
/**
 * @brief	�n���\���󋵂̃Z�b�g
 * @param	outPlaceNameCont	�n���\���̂ւ̃|�C���^
 * @return	none
 */
//------------------------------------------------------------------
static void SetUPState(PNC_PTR outPlaceNameCont)
{
	outPlaceNameCont->State = NAME_STATE_UP;
	outPlaceNameCont->WaitCount = 0;
}

//------------------------------------------------------------------
/**
 * @brief	�������A���P�[�V����
 * @param	bgl	BGL
 * @return	none
 */
//------------------------------------------------------------------
PNC_PTR	AllocPlaceNameCont(GF_BGL_INI *bgl)
{
	PLACE_NAME_CONT *place_name_cont;
	place_name_cont = sys_AllocMemory( HEAPID_FIELD, sizeof(PLACE_NAME_CONT) );
	place_name_cont->NameBuff = STRBUF_Create( BUFLEN_PLACE_NAME, HEAPID_FIELD );
	SetUpPlaceNameCont(place_name_cont,bgl);
	SetPlaceNameGraphic(place_name_cont);
	place_name_cont->MsgDataManager = MSGMAN_Create(	MSGMAN_TYPE_DIRECT,
														ARC_MSG,
														NARC_msg_place_name_dat,
														HEAPID_FIELD );
	return place_name_cont;
}

//------------------------------------------------------------------
/**
 * @brief	�������t���[
 * @param	outPlaceNameCont	�n���\���̂ւ̃|�C���^
 * @return	none
 */
//------------------------------------------------------------------
void FreePlaceNameCont(PNC_PTR outPlaceNameCont)
{
	MSGMAN_Delete( outPlaceNameCont->MsgDataManager );
	GF_BGL_BmpWinDel( &outPlaceNameCont->Win );
	STRBUF_Delete( outPlaceNameCont->NameBuff );
	sys_FreeMemoryEz(outPlaceNameCont->CharBuff);
	sys_FreeMemoryEz( outPlaceNameCont );
	outPlaceNameCont = NULL;
}

//------------------------------------------------------------------
/**
 * @brief	�n���\�����N�G�X�g
 * @param	ioPlaceNameCont	�n���\���̂ւ̃|�C���^
 * @param	inZoneID	�n��ID
 * @return	none
 */
//------------------------------------------------------------------
void PlaceNameRequest(PNC_PTR ioPlaceNameCont,const int inPlaceID)
{
	STRCODE name[BUFLEN_PLACE_NAME];
	u32 len;	
	ioPlaceNameCont->NameID = inPlaceID;//ZoneData_GetPlaceNameID(inZoneID);
	if (ioPlaceNameCont->Moving == FALSE){	//�ғ����Ă��Ȃ�
		ioPlaceNameCont->Moving = TRUE;	//�ғ����ɂ���
		//�a�f�I�t�Z�b�g������
		GF_BGL_ScrollSet( ioPlaceNameCont->WinIni, PLACE_NAME_FRAME, GF_BGL_SCROLL_Y_SET, PLACE_NAME_OFS_MAX );
		//�J�E���^0�Z�b�g
		ioPlaceNameCont->Offset = PLACE_NAME_OFS_MAX;
		//�^�X�N�쐬
		ioPlaceNameCont->Task = TCB_Add(PlaceNameTask, ioPlaceNameCont, 0);
		//�X�e�[�g�Z�b�g
		ioPlaceNameCont->State = NAME_STATE_DOWN;
		//���O�Z�b�g
		len = PNC_GetPlaceName(ioPlaceNameCont->MsgDataManager, ioPlaceNameCont->NameID, ioPlaceNameCont->NameBuff);
		SetupPlaceNameWin(ioPlaceNameCont,len);
		WritePlaceName(ioPlaceNameCont,ioPlaceNameCont->NameBuff);
	}else{									//���łɉғ����Ă���
		//�ғ��󋵂�����
		switch(ioPlaceNameCont->State){
		case NAME_STATE_DOWN:			//�~����
		case NAME_STATE_DOWN_HOLD:		//�~����㏸�҂�
			//�X�e�[�g���㏸�ɕύX���A���̒n�����Z�b�g����
			SetUPState(ioPlaceNameCont);
			ioPlaceNameCont->IsNext = TRUE;
			break;
		case NAME_STATE_UP:				//�㏸��
			//�X�e�[�g�͂��̂܂܁A���̒n�����Z�b�g����
			ioPlaceNameCont->IsNext = TRUE;
			break;
		case NAME_STATE_NONE:
		default:
			//�A�T�[�V����
			GF_ASSERT(0);
			break;
		}
	}	
}

//------------------------------------------------------------------
/**
 * @brief	�n���\�����~
 * @param	ioPlaceNameCont	�n���\���̂ւ̃|�C���^
 * @return	none
 */
//------------------------------------------------------------------
void StopPlaceName(PNC_PTR ioPlaceNameCont)
{
	if (ioPlaceNameCont->Task!=NULL){
		//�^�X�N�폜
		TCB_Delete(ioPlaceNameCont->Task);
	}
	GF_BGL_BmpWinOff( &ioPlaceNameCont->Win );
	//GF_BGL_BmpWinDel( &ioPlaceNameCont->Win );

	//�a�f�I�t�Z�b�g���A
	GF_BGL_ScrollSet( ioPlaceNameCont->WinIni, PLACE_NAME_FRAME, GF_BGL_SCROLL_Y_SET, 0 );

	{
		GF_BGL_INI *bgl = ioPlaceNameCont->WinIni;	//�ޔ�
		//�\���̍ăZ�b�g�A�b�v
		SetUpPlaceNameCont(ioPlaceNameCont,bgl);
	}
}

//------------------------------------------------------------------
/**
 * @brief	�t�B�[���h�V�X�e���|�C���^�ɂ��n���\�����N�G�X�g(�����̒��́A���N�G�X�g����)
 * @param	ioPlaceNameCont	�n���\���̂ւ̃|�C���^
 * @param	inZoneID	�n��ID
 * @return	none
 */
//------------------------------------------------------------------
void PlaceNameRequestByFsys(FIELDSYS_WORK * fsys)
{
	int place_id;
	if ( !ZoneData_IsRoom(fsys->location->zone_id) ){
		place_id = ZoneData_GetPlaceNameID(fsys->location->zone_id);
		PlaceNameRequest(fsys->fldmap->place_name_cont, place_id); //�n���\��
	}
}
