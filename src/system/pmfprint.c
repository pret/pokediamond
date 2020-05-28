//=============================================================================================
/**
 * @file	pmfprint.c
 * @brief	�����\���֐�
 * @author	tetsu
 * @date	2003.04.08
 *
 * @data	2004.11.04 AGB -> NDS
 * @author	Hiroyuki Nakamura
 */
//=============================================================================================
#include "common.h"
#include "fntsys.h"

#define __PMFPRINT_H_GLOBAL__
#include	"system/pmfprint.h"

#include	"system/snd_tool.h"
#include	"system\fontproc.h"
#include "../field/fld_bmp.h"




#define	CURSOR_WAIT_TIME		(8)

#define WRITE_SKIP_CURSOR_W		( 8)
#define WRITE_SKIP_CURSOR_H		(16)


extern void	BmpPrintMsg(MSG_DATA_HEADER* mdh_p);


#include "skip_cur.dat"			//����J�[�\���f�[�^

static MSG_PRINT_MODE msg_print_flag;


#define	AFF_FONT_POS_CHG		// �g��t�H���g�̈ʒu�ύX�i�R�����g�A�E�g�ŏ㑵���j

#ifdef	AFF_FONT_POS_CHG
//#define	AFF_FONT_CENTER		// �g��t�H���g�𒆑����ŕ\���i�R�����g�A�E�g�ŉ������j
#endif




//=============================================================================================
#define	PRINTSEQ_WRITE			(0)
#define	PRINTSEQ_TRGWAIT		(1)
#define	PRINTSEQ_TRGWAIT_CLEAR	(2)
#define	PRINTSEQ_TRGWAIT_SCROLL	(3)
#define	PRINTSEQ_SCROLL			(4)
#define	PRINTSEQ_SE_WAIT		(5)
#define	PRINTSEQ_FORCEWAIT		(6)

#define	SCR_SPEED_FAST		(4)
#define	SCR_SPEED_NORMAL	(2)
#define	SCR_SPEED_SLOW		(1)
static	const u8 scr_speed_value[] = {
	SCR_SPEED_SLOW,
	SCR_SPEED_NORMAL,
	SCR_SPEED_FAST,
};

//---------------------------------------------------------------------------------------------
/*
 *	�����f�[�^�擾
 *
 * @param	ini			BGL�f�[�^
 * @param	mdh_p		���b�Z�[�W�f�[�^�\���̃|�C���^
 *
 * @retval	w_flag		�����擾�p�����[�^
 *
 */
//---------------------------------------------------------------------------------------------
PRINT_RESULT PokeFontPrint( MSG_DATA_HEADER * mdh_p )
{
	const MSG_FONT_DATA* font_bmp;
	MSG_PRINT_USER*	mpu_p;
	int msg_speed, scr_sp;
	u16	fcode;

//	mdh_p->mph->bmpwin->ini

	mpu_p = (MSG_PRINT_USER *)&(mdh_p->userwork[0]);

	switch(mdh_p->seq){

	case PRINTSEQ_WRITE:		//�ʏ폈��

		//�������ςȂ��̏ꍇ�̔���(�ŏ��̃g���K�[�����o����Ă���ΗL��)
		if( ( (sys.cont & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL)) && (mpu_p->skip_f) ) ||
			( (sys.tp_cont) && (msg_print_flag.tp_f) ) ){
			mdh_p->waitwork = 0;
			if( mdh_p->wait != MSG_ALLPUT ){
				msg_print_flag.btl_skip_f = 1;
			}
		}
		if((mdh_p->waitwork)&&(mdh_p->wait)){
			(mdh_p->waitwork)--;

			if(msg_print_flag.skip_f){//�X�L�b�v�@�\���L���̏ꍇ�̏���
				//�ŏ��̃g���K�[�����o
				if( ( sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL) ) ||
					( (sys.tp_trg) && (msg_print_flag.tp_f) ) ){
					mpu_p->skip_f = 1;
					mdh_p->waitwork = 0;
				}
			}
			return PRINT_RESULT_COMMAND;
		}

/*		���ǁA�X�L�b�v�t���O�𗧂Ă�ƃ{�^���ő�����̂ŁA�E�F�C�g�̓v�����g���x�Ɉˑ�
		if(msg_print_flag.auto_f){
			mdh_p->waitwork = AUTO_MSGWAIT;		//�I�[�g���̓E�F�C�g���
		}else{
			mdh_p->waitwork = mdh_p->wait;
		}
*/
		mdh_p->waitwork = mdh_p->wait;


		//�t�H���g�f�[�^�擾
		fcode = *(u16*)(mdh_p->mph.msg);
		mdh_p->mph.msg++; 

		switch(fcode){

		/* �I���R�[�h */
		case EOM_:	
			return PRINT_RESULT_END;

		/* ���s�R�[�h */
		case CR_:	
			mdh_p->mph.write_x = mdh_p->mph.start_x;
			mdh_p->mph.write_y +=( FontHeaderGet( mdh_p->mph.fnt_index, FONT_HEADER_SIZE_Y ) + mdh_p->mph.space_y ); 
			return PRINT_RESULT_LOOP;

		/* �w��INDEX�o�b�t�@�̃��b�Z�[�W�W�J	*/
		case I_MSG_:	
			//���쐬(DATA = 1byte)
			mdh_p->mph.msg++; 
			return PRINT_RESULT_LOOP;


		/* �t�H���g����R�}���h */
		case _CTRL_TAG:
			// �^�O�R�[�h�o���ʒu�܂Ń|�C���^��߂�
			mdh_p->mph.msg--;

			fcode = STRCODE_GetTagType( mdh_p->mph.msg );

			switch( fcode ){
			case NC_FONT_COL_:				// �t�H���g����R�[�h
				{
					u16	 param = STRCODE_GetTagParam( mdh_p->mph.msg, 0 );

					mdh_p->mph.f_col = 1 + (param*2);
					mdh_p->mph.s_col = 1 + (param*2) + 1;
					FntDataColorSet(mdh_p->mph.f_col, mdh_p->mph.b_col, mdh_p->mph.s_col);
				}
				break;

			case NC_NOTE_ICON:		// �����ɒ��ڃA�C�R���������L�q����
				{
					u16	 param = STRCODE_GetTagParam( mdh_p->mph.msg, 0 );
					GF_MSG_PrintDispIcon( mdh_p, mdh_p->mph.write_x, mdh_p->mph.write_y, param );
				}
				if( mdh_p->wait_flg != 0 ){
					GF_BGL_BmpWinOn( mdh_p->mph.bmpwin );
				}
				break;

			case NC_FORCE_WAIT:
				{
					mdh_p->waitwork = STRCODE_GetTagParam( mdh_p->mph.msg, 0 );
					mdh_p->mph.msg = STRCODE_SkipTag( mdh_p->mph.msg );
					mdh_p->seq = PRINTSEQ_FORCEWAIT;
					return PRINT_RESULT_COMMAND;
				}
				break;

			case NC_CALLBACK_ARG:
				mdh_p->callback_arg = STRCODE_GetTagParam( mdh_p->mph.msg, 0 );
				mdh_p->mph.msg = STRCODE_SkipTag( mdh_p->mph.msg );
				return PRINT_RESULT_COMMAND;

			case NC_WRITEPOS_CHANGE_X:
				mdh_p->mph.write_x = STRCODE_GetTagParam( mdh_p->mph.msg, 0 );
				break;

			case NC_WRITEPOS_CHANGE_Y:
				mdh_p->mph.write_y = STRCODE_GetTagParam( mdh_p->mph.msg, 0 );
				break;

			case NC_FONT_SIZE_:
				{
					u16 param = STRCODE_GetTagParam( mdh_p->mph.msg, 0 );

					switch( param ) {
					case NC_FAFF_100_:		// �T�C�Y�F100��
						mdh_p->mph.dot_tbl = 0;
						mdh_p->mph.dot_wy = 0;
						break;
					case NC_FAFF_200_:		// �T�C�Y�F200��
						mdh_p->mph.dot_tbl = 0xfffc;
						mdh_p->mph.dot_wy = 0;
						break;
					}
				}
				break;

			case NC_MOVE_:				// ���쐧��R�[�h
				{
					u16	 c_move = STRCODE_GetTagParam( mdh_p->mph.msg, 0 );

					switch( c_move ){
					case NC_MV_CLEAR_:		// �L�[�҂��N���A
						mdh_p->seq	= PRINTSEQ_TRGWAIT_CLEAR;
						PokeFontTriggerCursorAnimeInit(mdh_p);
						mdh_p->mph.msg = STRCODE_SkipTag( mdh_p->mph.msg );
						return PRINT_RESULT_COMMAND;
					case NC_MV_SCROLL_:		// �L�[�҂��X�N���[��
						mdh_p->seq	= PRINTSEQ_TRGWAIT_SCROLL;
						PokeFontTriggerCursorAnimeInit(mdh_p);
						mdh_p->mph.msg = STRCODE_SkipTag( mdh_p->mph.msg );
						return PRINT_RESULT_COMMAND;
					}
				}
				break;
			}

			mdh_p->mph.msg = STRCODE_SkipTag( mdh_p->mph.msg );
			return PRINT_RESULT_LOOP;

		/* "��"		�g���K�[�҂���MSG�G���A�N���A(�{�`��J�n���Z�b�g) */
		case NORMAL_WAIT_:
			mdh_p->seq	= PRINTSEQ_TRGWAIT_CLEAR;
			PokeFontTriggerCursorAnimeInit(mdh_p);
			return PRINT_RESULT_COMMAND;
	
		/* "��"		�g���K�[�҂�����s�X�N���[��(�{���s) */
		case SCROLL_WAIT_:
			mdh_p->seq	= PRINTSEQ_TRGWAIT_SCROLL;
			PokeFontTriggerCursorAnimeInit(mdh_p);
			return PRINT_RESULT_COMMAND;

		}
		font_bmp = FontDataGet( mpu_p->fmode, fcode );

		//�e��t�H���g�`��
		GF_BGL_BmpWinPrintMsgWide(
			mdh_p->mph.bmpwin, font_bmp->data,
			font_bmp->size_x, font_bmp->size_y,
			mdh_p->mph.write_x,mdh_p->mph.write_y, mdh_p->mph.dot_tbl );

		//���̕����̕`��ʒu��ݒ�
		mdh_p->mph.write_x += (font_bmp->size_x + mdh_p->mph.space_x);
		return PRINT_RESULT_WRITE;

	case PRINTSEQ_TRGWAIT:		//�g���K�[�҂�
		if(PokeFontTriggerWait2(mdh_p)){
			PokeFontTriggerCursorAnimeExit2(mdh_p);
			mdh_p->seq	= PRINTSEQ_WRITE;
		}
		return PRINT_RESULT_COMMAND;

	case PRINTSEQ_TRGWAIT_CLEAR:		//�g���K�[�҂���MSG�G���A�N���A
		if(PokeFontTriggerWait(mdh_p)){
			//�G���A�N���A
			PokeFontTriggerCursorAnimeExit2(mdh_p);	//���œ����ɃN���A
			GF_BGL_BmpWinDataFill( mdh_p->mph.bmpwin, mdh_p->mph.b_col );
			mdh_p->mph.write_x = mdh_p->mph.start_x;
			mdh_p->mph.write_y = mdh_p->mph.start_y;
			mdh_p->seq	= PRINTSEQ_WRITE;
		}
		return PRINT_RESULT_COMMAND;

	case PRINTSEQ_TRGWAIT_SCROLL:		//�g���K�[�҂����X�N���[��
		if(PokeFontTriggerWait( mdh_p )){
			PokeFontTriggerCursorAnimeExit2(mdh_p);
			//�X�N���[�����ݒ�(Y�̍����� + �\����)
			mdh_p->scrwork	=( FontHeaderGet( mdh_p->mph.fnt_index, FONT_HEADER_SIZE_Y ) + mdh_p->mph.space_y ); 
			mdh_p->mph.write_x = mdh_p->mph.start_x;
			mdh_p->seq	= PRINTSEQ_SCROLL;
		}
		return PRINT_RESULT_COMMAND;

	case PRINTSEQ_SCROLL:				//�X�N���[������
		if( mdh_p->scrwork )
		{
			scr_sp = scr_speed_value[2];

			if(mdh_p->scrwork < scr_sp)
			{
				GF_BGL_BmpWinShift(
					mdh_p->mph.bmpwin, GF_BGL_BMPWIN_SHIFT_U,
					mdh_p->scrwork, (mdh_p->mph.b_col<<4)|mdh_p->mph.b_col );
				mdh_p->scrwork = 0;
			}
			else
			{
				GF_BGL_BmpWinShift(
					mdh_p->mph.bmpwin, GF_BGL_BMPWIN_SHIFT_U,
					scr_sp, (mdh_p->mph.b_col<<4)|mdh_p->mph.b_col );
				mdh_p->scrwork -= scr_sp;
			}

			GF_BGL_BmpWinOn( mdh_p->mph.bmpwin );

		}
		else
		{
			mdh_p->seq	= PRINTSEQ_WRITE;
		}
		return PRINT_RESULT_COMMAND;

	case PRINTSEQ_SE_WAIT:			//SE�E�F�C�g
		mdh_p->seq	= PRINTSEQ_WRITE;
		return PRINT_RESULT_COMMAND;

	case PRINTSEQ_FORCEWAIT:		//�����E�F�C�g
		if( mdh_p->waitwork )
		{
			mdh_p->waitwork--;
		}
		else
		{
			mdh_p->seq	= PRINTSEQ_WRITE;
		}
		return PRINT_RESULT_COMMAND;
	}
	return PRINT_RESULT_END;
}

//=============================================================================================
/**
 *		�g���K�[�҂��J�[�\���\��
 */
//=============================================================================================
static u16 TrgCursorCgxPos = 0;

void PokeFontTrgCursorCgxSet( u16 cgx )
{
	TrgCursorCgxPos = cgx;
}

void		PokeFontTriggerCursorAnimeInit(MSG_DATA_HEADER* mdh_p)
{
	MSG_PRINT_USER*	mpu_p;

	mpu_p = (MSG_PRINT_USER*)&(mdh_p->userwork[0]);

	if(msg_print_flag.auto_f){
		mpu_p->rep_wait = 0;	//�I�[�g���E�F�C�g���[�N������
	}else{
		mpu_p->cur_anm  = 0;
		mpu_p->cur_wait = 0;
	}
}

static const u8 CursorAnmData[] = {0,1,2,1,};

void PokeFontTriggerCursorAnime2( MSG_DATA_HEADER * mdh_p )
{
	MSG_PRINT_USER * mpu_p;
	void * cgx;

	mpu_p = (MSG_PRINT_USER *)&(mdh_p->userwork[0]);

	if(msg_print_flag.auto_f){
		return;
	}
	if(mpu_p->cur_wait){
		mpu_p->cur_wait--;
		return;
	}

	{
		u16	cgx;
		u8	frm, px, py, sx;

		frm = GF_BGL_BmpWinGet_Frame( mdh_p->mph.bmpwin );
		px  = GF_BGL_BmpWinGet_PosX( mdh_p->mph.bmpwin );
		py  = GF_BGL_BmpWinGet_PosY( mdh_p->mph.bmpwin );
		sx  = GF_BGL_BmpWinGet_SizeX( mdh_p->mph.bmpwin );
		cgx = TrgCursorCgxPos;

		GF_BGL_ScrFill(
			mdh_p->mph.bmpwin->ini, frm, cgx+18+(CursorAnmData[mpu_p->cur_anm]*4),
			px+sx+1, py+2, 1, 1, GF_BGL_SCRWRT_PALNL );
		GF_BGL_ScrFill(
			mdh_p->mph.bmpwin->ini, frm, cgx+19+(CursorAnmData[mpu_p->cur_anm]*4),
			px+sx+2, py+2, 1, 1, GF_BGL_SCRWRT_PALNL );
		GF_BGL_ScrFill(
			mdh_p->mph.bmpwin->ini, frm, cgx+20+(CursorAnmData[mpu_p->cur_anm]*4),
			px+sx+1, py+3, 1, 1, GF_BGL_SCRWRT_PALNL );
		GF_BGL_ScrFill(
			mdh_p->mph.bmpwin->ini, frm, cgx+21+(CursorAnmData[mpu_p->cur_anm]*4),
			px+sx+2, py+3, 1, 1, GF_BGL_SCRWRT_PALNL );
		GF_BGL_LoadScreenReq( mdh_p->mph.bmpwin->ini, frm );

		mpu_p->cur_wait = CURSOR_WAIT_TIME;
		mpu_p->cur_anm++;
	}
}

void PokeFontTriggerCursorAnimeExit2( MSG_DATA_HEADER* mdh_p )
{
	u16	cgx;
	u8	frm, px, py, sx;

	frm = GF_BGL_BmpWinGet_Frame( mdh_p->mph.bmpwin );
	px  = GF_BGL_BmpWinGet_PosX( mdh_p->mph.bmpwin );
	py  = GF_BGL_BmpWinGet_PosY( mdh_p->mph.bmpwin );
	sx  = GF_BGL_BmpWinGet_SizeX( mdh_p->mph.bmpwin );
	cgx = TrgCursorCgxPos;

	GF_BGL_ScrFill(
		mdh_p->mph.bmpwin->ini, frm, cgx+10, px+sx+1, py+2, 1, 2, GF_BGL_SCRWRT_PALNL );
	GF_BGL_ScrFill(
		mdh_p->mph.bmpwin->ini, frm, cgx+11, px+sx+2, py+2, 1, 2, GF_BGL_SCRWRT_PALNL );

	GF_BGL_LoadScreenReq( mdh_p->mph.bmpwin->ini, frm );
}















//=============================================================================================
/**
 *		�g���K�[�҂��֐�(0:wait��,1:����)
 */
//=============================================================================================
static BOOL PokeFontTriggerWaitCheck( MSG_DATA_HEADER * mdh_p )
{
	if( ( sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL) ) ||
		( (sys.tp_trg) && (msg_print_flag.tp_f) ) ){
		Snd_SePlay( SE_MSG_SKIP );
		msg_print_flag.btl_wait_f = 1;
		return TRUE;
	}
	return FALSE;
}

BOOL PokeFontTriggerWaitReplayCheck(MSG_DATA_HEADER* mdh_p)
{
	MSG_PRINT_USER*	mpu_p;
	u16	wait_len;

	mpu_p = (MSG_PRINT_USER*)&(mdh_p->userwork[0]);

	wait_len = AUTO_MSGTRGWAIT;

	if(mpu_p->rep_wait == wait_len){	//���v���C���E�F�C�g���
		return TRUE;
	}
	mpu_p->rep_wait++;

	if( msg_print_flag.auto_f_skip ){
		return PokeFontTriggerWaitCheck( mdh_p );
	}

	return FALSE;
}


BOOL PokeFontTriggerWait( MSG_DATA_HEADER* mdh_p )
{
	BOOL flg = FALSE;

	if(msg_print_flag.auto_f){
		//�I�[�g����E�F�C�g�`�F�b�N
		flg = PokeFontTriggerWaitReplayCheck(mdh_p);
	}else{
		PokeFontTriggerCursorAnime2(mdh_p);
		flg = PokeFontTriggerWaitCheck( mdh_p );
	}
	return flg;
}

BOOL PokeFontTriggerWait2(MSG_DATA_HEADER* mdh_p)
{
	u8	flg = FALSE;

	if(msg_print_flag.auto_f){
		//�I�[�g����E�F�C�g�`�F�b�N
		flg = PokeFontTriggerWaitReplayCheck(mdh_p);
	}else{
		flg = PokeFontTriggerWaitCheck( mdh_p );
	}
	return flg;
}









//=============================================================================================
//	�`�搧��
//=============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �X�L�b�v�ݒ�
 *
 * @param	flg		�t���O
 *
 * @return	none
 *
 *	flg = MSG_SKIP_OFF : �X�L�b�v����
 *	flg = MSG_SKIP_ON  : �X�L�b�v�L��
 */
//--------------------------------------------------------------------------------------------
void MsgPrintSkipFlagSet( int flg )
{
	msg_print_flag.skip_f = flg;
}

//--------------------------------------------------------------------------------------------
/**
 * ��������ݒ�
 *
 * @param	flg		�t���O
 *
 * @return	none
 *
 *	flg = MSG_AUTO_OFF     : �������薳��
 *	flg = MSG_AUTO_ON      : ��������L��
 *	flg = MSG_AOTO_SKIP_ON : ��������L��/�{�^���X�L�b�v�L��
 */
//--------------------------------------------------------------------------------------------
void MsgPrintAutoFlagSet( int flg )
{
	msg_print_flag.auto_f      = (flg&1);
	msg_print_flag.auto_f_skip = ((flg>>1)&1);
}

//--------------------------------------------------------------------------------------------
/**
 * �^�b�`�p�l������ݒ�
 *
 * @param	flg		�t���O
 *
 * @return	none
 *
 *	flg = MSG_TP_OFF : �^�b�`�p�l������
 *	flg = MSG_TP_ON  : �^�b�`�p�l���L��
 */
//--------------------------------------------------------------------------------------------
void MsgPrintTouchPanelFlagSet( int flg )
{
	msg_print_flag.tp_f = flg;
}


//--------------------------------------------------------------------------------------------
/**
 * �퓬�p�F�X�L�b�v����
 *
 * @param	none
 *
 * @retval	"1 = ���蒆"
 * @retval	"0 = ����ȊO"
 */
//--------------------------------------------------------------------------------------------
u8 MsgPrintBattleSkipPushFlagGet(void)
{
	return msg_print_flag.btl_skip_f;
}

void MsgPrintBattleSkipPushFlagClear(void)
{
	msg_print_flag.btl_skip_f = 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �퓬�p�F���𑗂�����
 *
 * @param	none
 *
 * @retval	"1 = ���蒆"
 * @retval	"0 = ����ȊO"
 */
//--------------------------------------------------------------------------------------------
u8 MsgPrintBattleWaitPushFlagGet(void)
{
	return msg_print_flag.btl_wait_f;
}
void MsgPrintBattleWaitPushFlagClear(void)
{
	msg_print_flag.btl_wait_f = 0;
}
