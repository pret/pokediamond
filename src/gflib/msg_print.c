//=============================================================================================
/**
 * @file	msg_print.c
 * @brief	�r�b�g�}�b�v������\���p�V�X�e��
 * @author	tetsu
 * @date	2003.03.17
 *
 * @data	2004.11.04 AGB -> NDS
 * @author	Hiroyuki Nakamura
 */
//=============================================================================================
#include <nitro.h>
#include "gflib/assert.h"
#include "system.h"
#include "bg_system.h"
#include "tcb.h"

#define	__MSG_PRINT_H_GLOBAL
#include "msg_print.h"

#include "system\fontproc.h"
#include "system/arc_util.h"
#include "system/font_arc.h"

#include "system/clact_util.h"
#include "system/render_oam.h"
#include "gflib/display.h"
#include "gflib/char_manager.h"
#include "gflib/pltt_manager.h"


typedef struct {
	CLACT_SET_PTR	cas;
	CLACT_U_EASYRENDER_DATA	renddata;	// �ȈՃ����_�[�f�[�^
	CLACT_HEADER_TBL_PTR	clh;		// �w�b�_�[
	CLACT_U_RES_MANAGER_PTR	resMan[4];	// ���\�[�X�}�l�[�W��
	CLACT_U_RES_OBJ_TBL * resObjTbl[2];	// ���\�[�X�I�u�W�F�e�[�u��
	int resObjNum[4];					// ���ꂼ��̃��\�[�X�I�u�W�F��
	CLACT_WORK_PTR	cwp;
}TRG_CURSOR;



//==================================================================
//	�ϐ� �� �֐��錾
//==================================================================
static PRINT_RESULT	MSG_PrintDataSet( GF_BGL_INI * ini, MSG_DATA_HEADER * mdh_p );
static PRINT_RESULT GF_MSG_PrintDataSet( MSG_DATA_HEADER * mdh_p );
static void GF_MSG_PrintMain( TCB_PTR tcb, void *work );
static u8 SetNewPrintTask(TCB_FUNC func, void* work, u32 task_pri);
static void DeletePrintTask( u8 index );


static void DispIconInit( MSG_DATA_HEADER* mdh );
static void DispIconExit( MSG_DATA_HEADER* mdh );
static u8*  DispIconCreate(void);


static const MSG_FONT_HEADER*	font_header = NULL;

static u8				msg_main_pause = 0;
//static MSG_DATA_HEADER	mdh_buf = {0};



//---------------------------------------------------------------------------------------------
/**
 *	�����\���V�X�e���������֐�
 *
 * @param	�t�H���g�֐��Q�w�b�_
 *
 * @retval	�Ȃ�
 */
//---------------------------------------------------------------------------------------------
void MSG_PrintSysInit( const MSG_FONT_HEADER * header )
{
	font_header = header;
}







//==============================================================================================
//
// �����o�̓^�X�N���Ǘ����邽�߂̎d�g��
//
//==============================================================================================


enum {
	PRINTTASK_MAX = 8	// �����o�̓^�X�N��o�^�ł��鑍��
};
static TCB_PTR			PrintTaskTable[PRINTTASK_MAX] = {0};


//------------------------------------------------------------------
/**
 * �V���������\���^�X�N���Z�b�g����
 *
 * @retval  u8		�Z�b�g�����^�X�N�̃C���f�b�N�X�l
 */
//------------------------------------------------------------------
static u8 SetNewPrintTask(TCB_FUNC func, void* work, u32 task_pri)
{
	int i;

	for( i=0; i<PRINTTASK_MAX; i++ ){
		if( PrintTaskTable[i] == NULL )
		{
			PrintTaskTable[i] = PrintTCB_Add(func, work, task_pri);
			if( PrintTaskTable[i] == NULL )
			{
				i = PRINTTASK_MAX;
			}
			break;
		}
	}
	return i;
}

//------------------------------------------------------------------
/**
 * �����\���^�X�N���~�E�폜����
 *
 * @param   index		�^�X�N�C���f�b�N�X�l
 *
 */
//------------------------------------------------------------------
static void DeletePrintTask( u8 index )
{
	GF_ASSERT(index < PRINTTASK_MAX);
	GF_ASSERT(PrintTaskTable[index]!=NULL);

	if( index < PRINTTASK_MAX && PrintTaskTable[index] != NULL )
	{
//		void *work = TCB_GetWork(PrintTaskTable[index]);
		MSG_DATA_HEADER * work = TCB_GetWork(PrintTaskTable[index]);
		if(work)
		{
			DispIconExit( work );
			sys_FreeMemoryEz(work);
		}
		TCB_Delete(PrintTaskTable[index]);
		PrintTaskTable[index] = NULL;
	}
}

//------------------------------------------------------------------
/**
 * �w��C���f�b�N�X�̕����\���^�X�N���I�����Ă��邩�`�F�b�N
 *
 * @param   index		�C���f�b�N�X�l
 *
 * @retval  BOOL		TRUE�ŏI�����Ă���^FALSE�œ��쒆
 */
//------------------------------------------------------------------
static BOOL CheckPrintTaskWorking( u8 index )
{
	return PrintTaskTable[index] != NULL;
}

//-------------------------------------------------------------------------------------
/**
 *	�����\���������֐�
 *
 * @param	�Ȃ�
 *
 * @retval	�Ȃ�
 */
//-------------------------------------------------------------------------------------
void MSG_PrintInit(void)
{
	int i;

	for(i=0; i<PRINTTASK_MAX; i++)
	{
		PrintTaskTable[i] = NULL;
	}
}
//---------------------------------------------------------------------------------------------
/*
 * �����\���I���`�F�b�N�֐�
 *
 * @param	msg_index	���b�Z�[�W�C���f�b�N�X
 *
 * @retval	0	�I��
 * @retval	1	������
 */
//---------------------------------------------------------------------------------------------
u8 GF_MSG_PrintEndCheck( u8 msg_index )
{
	return CheckPrintTaskWorking(msg_index);
}

//------------------------------------------------------------------
/**
 * �����\���̃^�X�N��������~����
 *
 * @param   msg_index		���b�Z�[�W�C���f�b�N�X
 *
 */
//------------------------------------------------------------------
void GF_STR_PrintForceStop( u8 msg_index )
{
	DeletePrintTask( msg_index );
}



#include "gflib/strbuf_family.h"


//------------------------------------------------------------------------------
/**
 * BitmapWindow �̓���CGX�̈�ɕ�����`�悷��i�ȈՔŁj
 *
 * @param   win			[out] BitmapWindow
 * @param   fontID		�t�H���g�h�c
 * @param   msg			[in]  �`�敶���񂪊i�[����Ă��镶���o�b�t�@
 * @param   xofs		�`��J�n�_�w���W�i�h�b�g�P�ʁj
 * @param   yofs		�`��J�n�_�x���W�i�h�b�g�P�ʁj
 * @param   wait		�P�����`�悲�Ƃ̃E�F�C�g�t���[�����i���j
 * @param   callback	�P�����`�悲�Ƃ̃R�[���o�b�N�֐��A�h���X�i�s�v�Ȃ�NULL�j
 *
 * @retval  u8			��������镶���`�惋�[�`���̃C���f�b�N�X
 *
 * �� wait �� MSG_NO_PUT ���w�肵���ꍇ�A�L�����̈�ɑ΂���`��݂̂����s�����
 *            MSG_ALLPUT ���w�肵���ꍇ�A�L�����̈�`��{BitmapWindow�X�N���[���쐬�{������VRam�]�����s����
 *            ����ȊO�̒l���w�肵���ꍇ�A
 *
 */
//------------------------------------------------------------------------------
u8 GF_STR_PrintSimple( GF_BGL_BMPWIN* win, u32 fontID, const STRBUF* msg, u32 xofs, u32 yofs, u32 wait, pStrPrintCallBack call_back )
{
	MSG_PRINT_HEADER	mph;

	mph.strbuf		= msg;
	mph.bmpwin		= win;
	mph.fnt_index	= fontID;		//�g�p�t�H���gINDEX
	mph.start_x		= xofs;			//�E�C���h�E���\���J�nX�I�t�Z�b�g
	mph.start_y		= yofs;			//�E�C���h�E���\���J�nY�I�t�Z�b�g
	mph.write_x		= xofs;			//�E�C���h�E���`��X�I�t�Z�b�g
	mph.write_y		= yofs;			//�E�C���h�E���`��Y�I�t�Z�b�g
	mph.space_x		= font_header[fontID].space_x;	//�����ԊuX
	mph.space_y		= font_header[fontID].space_y;	//�����ԊuY
	mph.style		= font_header[fontID].style;		//�t�H���g�X�^�C��
	mph.f_col		= font_header[fontID].f_col;		//�����F�i���o�[
	mph.b_col		= font_header[fontID].b_col;		//�w�i�F�i���o�[
	mph.s_col		= font_header[fontID].s_col;		//�e�F�@�i���o�[
	mph.dot_tbl		= 0;			//�g��p�h�b�g�e�[�u��
	mph.dot_wy		= 0;			//�g�厞��Y���W�̕`��␳�l

	return GF_STR_Print( &mph, wait, call_back );
}

//------------------------------------------------------------------------------
/**
 * BitmapWindow �̓���CGX�̈�ɕ�����`�悷��i�J���[�w��Łj
 *
 * @param   win			[out] BitmapWindow
 * @param   fontID		�t�H���g�h�c
 * @param   msg			[in]  �`�敶���񂪊i�[����Ă��镶���o�b�t�@
 * @param   xofs		�`��J�n�_�w���W�i�h�b�g�P�ʁj
 * @param   yofs		�`��J�n�_�x���W�i�h�b�g�P�ʁj
 * @param   wait		�P�����`�悲�Ƃ̃E�F�C�g�t���[�����i���j
 * @param   col			�`��Ɏg���F�ԍ��iGF_PRINTCOLOR_MAKE�}�N�����g�p���邱�Ɓj
 * @param   callback	�P�����`�悲�Ƃ̃R�[���o�b�N�֐��A�h���X�i�s�v�Ȃ�NULL�j
 *
 * @retval  u8			��������镶���`�惋�[�`���̃C���f�b�N�X
 *
 * �� wait �� MSG_NO_PUT ���w�肵���ꍇ�A�L�����̈�ɑ΂���`��݂̂����s�����
 *            MSG_ALLPUT ���w�肵���ꍇ�A�L�����̈�`��{BitmapWindow�X�N���[���쐬�{������VRam�]�����s����
 *            ����ȊO�̒l���w�肵���ꍇ�A
 *
 */
//------------------------------------------------------------------------------
u8 GF_STR_PrintColor(
		GF_BGL_BMPWIN * win, u32 fontID, const STRBUF* msg, u32 xofs, u32 yofs, u32 wait,
		GF_PRINTCOLOR col, pStrPrintCallBack call_back )
{
	MSG_PRINT_HEADER	mph;

	mph.strbuf		= msg;
	mph.bmpwin		= win;
	mph.fnt_index	= fontID;		//�g�p�t�H���gINDEX
	mph.start_x		= xofs;			//�E�C���h�E���\���J�nX�I�t�Z�b�g
	mph.start_y		= yofs;			//�E�C���h�E���\���J�nY�I�t�Z�b�g
	mph.write_x		= xofs;			//�E�C���h�E���`��X�I�t�Z�b�g
	mph.write_y		= yofs;			//�E�C���h�E���`��Y�I�t�Z�b�g
	mph.space_x		= font_header[fontID].space_x;	//�����ԊuX
	mph.space_y		= font_header[fontID].space_y;	//�����ԊuY
	mph.style		= font_header[fontID].style;		//�t�H���g�X�^�C��
	mph.f_col		= GF_PRINTCOLOR_GET_LETTER(col);
	mph.s_col		= GF_PRINTCOLOR_GET_SHADOW(col);
	mph.b_col		= GF_PRINTCOLOR_GET_GROUND(col);
	mph.dot_tbl		= 0;			//�g��p�h�b�g�e�[�u��
	mph.dot_wy		= 0;			//�g�厞��Y���W�̕`��␳�l

	return GF_STR_Print( &mph, wait, call_back );
}

//------------------------------------------------------------------------------
/**
 * BitmapWindow �̓���CGX�̈�ɕ�����`�悷��i�J���[�����ԁE�s�Ԏw��Łj
 *
 * @param   win			[out] BitmapWindow
 * @param   fontID		�t�H���g�h�c
 * @param   msg			[in]  �`�敶���񂪊i�[����Ă��镶���o�b�t�@
 * @param   xofs		�`��J�n�_�w���W�i�h�b�g�P�ʁj
 * @param   yofs		�`��J�n�_�x���W�i�h�b�g�P�ʁj
 * @param   wait		�P�����`�悲�Ƃ̃E�F�C�g�t���[�����i���j
 * @param   col			�`��Ɏg���F�ԍ��iGF_PRINTCOLOR_MAKE�}�N�����g�p���邱�Ɓj
 * @param   xspc		�������Ƃ̊Ԋu�i�h�b�g�P�ʁj
 * @param   yspc		�s���Ƃ̊Ԋu�i�h�b�g�P�ʁj
 * @param   callback	�P�����`�悲�Ƃ̃R�[���o�b�N�֐��A�h���X�i�s�v�Ȃ�NULL�j
 *
 * @retval  u8			��������镶���`�惋�[�`���̃C���f�b�N�X
 *
 * �� wait �� MSG_NO_PUT ���w�肵���ꍇ�A�L�����̈�ɑ΂���`��݂̂����s�����
 *            MSG_ALLPUT ���w�肵���ꍇ�A�L�����̈�`��{BitmapWindow�X�N���[���쐬�{������VRam�]�����s����
 *            ����ȊO�̒l���w�肵���ꍇ�A
 *
 */
//------------------------------------------------------------------------------
u8 GF_STR_PrintExpand(
		GF_BGL_BMPWIN * win, u32 fontID, const STRBUF* msg, u32 xofs, u32 yofs, u32 wait,
		GF_PRINTCOLOR col, u32 xspc, u32 yspc, pStrPrintCallBack  call_back )
{
	MSG_PRINT_HEADER	mph;

	mph.strbuf		= msg;
	mph.bmpwin		= win;
	mph.fnt_index	= fontID;	//�g�p�t�H���gINDEX
	mph.start_x		= xofs;		//�E�C���h�E���\���J�nX�I�t�Z�b�g
	mph.start_y		= yofs;		//�E�C���h�E���\���J�nY�I�t�Z�b�g
	mph.write_x		= xofs;		//�E�C���h�E���`��X�I�t�Z�b�g
	mph.write_y		= yofs;		//�E�C���h�E���`��Y�I�t�Z�b�g
	mph.space_x		= xspc;		//�����ԊuX
	mph.space_y		= yspc;		//�����ԊuY
	mph.style		= font_header[fontID].style;		//�t�H���g�X�^�C��
	mph.f_col		= GF_PRINTCOLOR_GET_LETTER(col);
	mph.s_col		= GF_PRINTCOLOR_GET_SHADOW(col);
	mph.b_col		= GF_PRINTCOLOR_GET_GROUND(col);
	mph.dot_tbl		= 0;			//�g��p�h�b�g�e�[�u��
	mph.dot_wy		= 0;			//�g�厞��Y���W�̕`��␳�l

	return GF_STR_Print( &mph, wait, call_back );

}

//------------------------------------------------------------------
/**
 * BitmapWindow �̓���CGX�̈�ɕ�����`�悷��
 *
 * @param   mph_p			
 * @param   wait			
 * @param   call_back		
 *
 * @retval  u8			��������镶���`�惋�[�`���̃C���f�b�N�X
 */
//------------------------------------------------------------------
u8 GF_STR_Print( const MSG_PRINT_HEADER* mph_p, u32 wait, pStrPrintCallBack call_back )
{
	MSG_DATA_HEADER * mdh_p;
	int i;

	if(font_header == NULL){
		return 0xff;		//�t�H���g�f�[�^�擾�v���O�������ݒ肳��Ă��Ȃ�
	}

	mdh_p = sys_AllocMemory( HEAPID_BASE_SYSTEM, sizeof(MSG_DATA_HEADER) );

	//�\���f�[�^�ݒ�
	mdh_p->sw				= 1;
	mdh_p->seq				= 0;
	mdh_p->wait				= wait;
	mdh_p->waitwork			= 0;
	mdh_p->scrwork			= 0;
	mdh_p->callback_cont_flag = 0;
	for( i=0; i<MDH_WORKSIZE; i++){
		mdh_p->userwork[i]	= 0;
	}
	mdh_p->mph				= *mph_p;
	mdh_p->mph.msg = STRBUF_GetStringCodePointer(mdh_p->mph.strbuf);
	mdh_p->call_back		= call_back;
	msg_main_pause = 0;

	DispIconInit( mdh_p );

	// �P�������ƂɃE�F�C�g�����������`��i�^�X�N�����j
	if((wait != MSG_NO_PUT)&&(wait != MSG_ALLPUT))
	{
		mdh_p->wait--;			//wait�l�␳(0�`)
		mdh_p->wait_flg = 1;
		mdh_p->msg_index = SetNewPrintTask(GF_MSG_PrintMain, mdh_p, 1);
		return mdh_p->msg_index;
	}
	// �ꊇ�`��
	else
	{
		u32 error_check;

		mdh_p->wait= 0;
		mdh_p->wait_flg = 0;
		error_check = 0;	//�Ƃ肠�����C�x�ߒ��x��
		FntDataColorSet(mph_p->f_col, mph_p->b_col, mph_p->s_col);

		while(error_check < 1024){
			//�����`��(�ꊇ)
			if(GF_MSG_PrintDataSet( mdh_p ) == PRINT_RESULT_END){
				break;
			}
			error_check++;
		}

		if(wait != MSG_NO_PUT){
			//�f�B�X�v���C�]��(�L�����N�^�ꊇ)
			GF_BGL_BmpWinOn( mdh_p->mph.bmpwin );
		}

		DispIconExit( mdh_p );
		sys_FreeMemoryEz( mdh_p );
		return PRINTTASK_MAX;
	}
}






//---------------------------------------------------------------------------------------------
/**
 *	�����\�����C���֐�
 *
 * @param	�Ȃ�
 *
 * @retval	�Ȃ�
 */
//---------------------------------------------------------------------------------------------
static void GF_MSG_PrintMain( TCB_PTR tcb, void *work )
{
	MSG_DATA_HEADER * mdh_p;
	PRINT_RESULT	result;

	if(msg_main_pause){	return; }		// ���C�����f

	mdh_p = (MSG_DATA_HEADER *)work;

	if( mdh_p->callback_cont_flag == FALSE )
	{

		mdh_p->callback_arg = 0;
		FntDataColorSet(mdh_p->mph.f_col, mdh_p->mph.b_col, mdh_p->mph.s_col);

		//�t�H���g�f�[�^�擾
		result = GF_MSG_PrintDataSet( mdh_p );

		//�t�H���g�f�[�^�擾�֐��Ԃ�l�ɂ�鏈������
		switch( result ){
		case PRINT_RESULT_WRITE:
			GF_BGL_BmpWinOn( mdh_p->mph.bmpwin );

		case PRINT_RESULT_COMMAND:
			//�����`�悲�Ƃ̃R�[���o�b�N�֐��Ăяo��
			if(mdh_p->call_back != NULL){
				mdh_p->callback_cont_flag = (mdh_p->call_back)( &(mdh_p->mph), mdh_p->callback_arg );
			}
			break;

		case PRINT_RESULT_END:
			DeletePrintTask( mdh_p->msg_index );
			break;
		}
	}
	else
	{
		mdh_p->callback_cont_flag = (mdh_p->call_back)( &(mdh_p->mph), mdh_p->callback_arg );
	}
}

//---------------------------------------------------------------------------------------------
/*
 *	�����f�[�^�擾
 */
//---------------------------------------------------------------------------------------------
static PRINT_RESULT GF_MSG_PrintDataSet( MSG_DATA_HEADER * mdh_p )
{
	PRINT_RESULT  res;

	//�e��t�H���g�V�X�e���v���O�����̌Ăяo��(�R�[�h����)
	do{
		res = FontDataPrint( mdh_p->mph.fnt_index, mdh_p );

	}while(res == PRINT_RESULT_LOOP);

	return res;
}





















//---------------------------------------------------------------------------------------------
/*
 *	FntDataSet8x8_2bit ���ĂԑO�ɁA�F�ԍ����Z�b�g���Ă����i�������̂��߁j
 *
 * @param	col_f	�����F�ԍ�
 * @param	col_b	�w�i�F�ԍ�
 * @param	col_s	�e�F�ԍ�
 */
//---------------------------------------------------------------------------------------------
#define DOTTBL_USE

#ifdef DOTTBL_USE
static u16 DotTbl[256];
#else
static u16 Col_b4, Col_b8, Col_b12;
static u16 Col_f4, Col_f8, Col_f12;
static u16 Col_s4, Col_s8, Col_s12;
#endif
static u16 Col_b, Col_f, Col_s;

void FntDataColorSet(u8 col_f, u8 col_b, u8 col_s)
{
#ifdef DOTTBL_USE
	int d1,d2,d3,d4,n;
	u32 col[4];

	col[0] = 0;
	col[1] = col_f;
	col[2] = col_s;
	col[3] = col_b;

	Col_b = col_b;
	Col_f = col_f;
	Col_s = col_s;

	n = 0;
	for(d1=0; d1<4; d1++){
		for(d2=0; d2<4; d2++){
			for(d3=0; d3<4; d3++){
				for(d4=0; d4<4; d4++){
					DotTbl[n++] =	(col[d4]<<12) | 
									(col[d3]<<8) |
									(col[d2]<<4) |
									(col[d1]);
				}
			}
		}
	}

#else
	Col_b = col_b;
	Col_f = col_f;
	Col_s = col_s;

	Col_b4 = col_b << 4;
	Col_b8 = col_b << 8;
	Col_b12 = col_b << 12;

	Col_f4 = col_f << 4;
	Col_f8 = col_f << 8;
	Col_f12 = col_f << 12;

	Col_s4 = col_s << 4;
	Col_s8 = col_s << 8;
	Col_s12 = col_s << 12;
#endif
}

void FntDataColorBackUp(u8* col_f, u8* col_b, u8* col_s)
{
	*col_b = Col_b; 
	*col_f = Col_f;
	*col_s = Col_s;
}

void FntDataColorRecover(u8* col_f, u8* col_b, u8* col_s)
{
	FntDataColorSet(*col_f,*col_b,*col_s);
}

//---------------------------------------------------------------------------------------------
/*
 *	�����f�[�^�ݒ�
 *
 * @param	radrs		�ǂݍ��݃f�[�^�J�n�A�h���X
 * @param	wadrs		�������݃f�[�^�o�b�t�@�A�h���X
 *
 * @retval	x_size		�����w�T�C�Y(�����l�ߗp)
 */
//---------------------------------------------------------------------------------------------
#include "gflib\apptimer.h"
void FntDataSet8x8_2bit(u32 radrs,u32 wadrs)
{
	u32 dat;
	u16 *src;
	u16 *dst;

	src = (u16*)radrs;
	dst = (u16*)wadrs;


	dat = (u32)(*src) >> 8;
	*dst++ = DotTbl[ dat ];
	dat = (u32)((*src++) << 24) >> 24;
	*dst++ = DotTbl[ dat ];

	dat = (u32)(*src) >> 8;
	*dst++ = DotTbl[ dat ];
	dat = (u32)((*src++) << 24) >> 24;
	*dst++ = DotTbl[ dat ];

	dat = (u32)(*src) >> 8;
	*dst++ = DotTbl[ dat ];
	dat = (u32)((*src++) << 24) >> 24;
	*dst++ = DotTbl[ dat ];

	dat = (u32)(*src) >> 8;
	*dst++ = DotTbl[ dat ];
	dat = (u32)((*src++) << 24) >> 24;
	*dst++ = DotTbl[ dat ];

	dat = (u32)(*src) >> 8;
	*dst++ = DotTbl[ dat ];
	dat = (u32)((*src++) << 24) >> 24;
	*dst++ = DotTbl[ dat ];

	dat = (u32)(*src) >> 8;
	*dst++ = DotTbl[ dat ];
	dat = (u32)((*src++) << 24) >> 24;
	*dst++ = DotTbl[ dat ];

	dat = (u32)(*src) >> 8;
	*dst++ = DotTbl[ dat ];
	dat = (u32)((*src++) << 24) >> 24;
	*dst++ = DotTbl[ dat ];

	dat = (u32)(*src) >> 8;
	*dst++ = DotTbl[ dat ];
	dat = (u32)((*src) << 24) >> 24;
	*dst = DotTbl[ dat ];

}
//---------------------------------------------------------------------------------------------
/*
 *	FntDataColorSet �Őݒ肵���F�ԍ����擾
 *
 * @param	mode	���[�h�ienum COLOR_GET_MODE : msg_print.h�j
 *
 * @retval	�F�ԍ�
 */
//---------------------------------------------------------------------------------------------
u8 FntDataColorGet(u8 mode)
{
	switch(mode){
	case  COLOR_F: return Col_f;
	case  COLOR_B: return Col_b;
	case  COLOR_S: return Col_s;
	}
	return 0;
}











static void DispIconInit(MSG_DATA_HEADER* mdh)
{
	mdh->disp_icon = NULL;
}

static u8 * DispIconCreate(void)
{
	NNSG2dCharacterData * dat;
	void * arc;
	u8 * icon;

	icon = sys_AllocMemory( HEAPID_BASE_SYSTEM, 3*4 * 4 * 0x20 );
	arc  = ArcUtil_CharDataGet( ARC_FONT, NARC_font_dis_change_ncgr, 0, &dat, HEAPID_BASE_SYSTEM );
	MI_CpuCopy32( dat->pRawData, icon, 3*4 * 4 * 0x20 );
	sys_FreeMemoryEz( arc );

	return icon;
}

void GF_MSG_PrintDispIcon( MSG_DATA_HEADER * mdh, u16 px, u16 py, u16 pat )
{
	GF_BGL_BMPWIN * win = mdh->mph.bmpwin;
	u8 * iconcgx;

	if(mdh->disp_icon == NULL)
	{
		mdh->disp_icon = DispIconCreate();
	}

	iconcgx = mdh->disp_icon;
	iconcgx = &iconcgx[pat*12*0x20];

	px = ( GF_BGL_BmpWinGet_SizeX( win ) - 3 ) * 8;
	py = 0;
	GF_BGL_BmpWinPrint( win, iconcgx, 0, 0, 24, 32, px, py, 24, 32 );
}

static void DispIconExit( MSG_DATA_HEADER* mdh )
{
	if( mdh->disp_icon )
	{
		sys_FreeMemoryEz( mdh->disp_icon );
		mdh->disp_icon = NULL;
	}
}
