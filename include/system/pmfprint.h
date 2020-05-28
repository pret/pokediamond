//=========================================================================
//	
//	pmfprint.h
//
//=========================================================================
#ifndef _PMFPRINT_H_
#define _PMFPRINT_H_


#undef GLOBAL
#ifdef __PMFPRINT_H_GLOBAL__
#define GLOBAL /*	*/
#else
#define GLOBAL extern
#endif

#undef GLOBAL_WORK
#ifdef __PMFRINT_H_GLOBAL__
#define GLOBAL_WORK //
#else
#define GLOBAL_WORK extern
#endif

//=========================================================================
//	��`
//=========================================================================
#define	MSG_SKIP_OFF	(0)
#define	MSG_SKIP_ON		(1)

#define	CURSOR_FIELD	(0)
#define	CURSOR_BATTLE	(1)

#define	MSG_AUTO_OFF		(0)
#define	MSG_AUTO_ON			(1)
#define	MSG_AUTO_SKIP_ON	(3)

#define	MSG_TP_OFF		(0)
#define	MSG_TP_ON		(1)

#define MSGSPEED_FIX_OFF	(0)
#define MSGSPEED_FIX_ON		(1)

//���b�Z�[�W�\���E�F�C�g��`
#define AUTO_MSGWAIT	(3)		//(1)
#define AUTO_MSGTRGWAIT	(100)	//(96)	//(49)	//(120)

///�\��������ݒ�\����
typedef struct {
u8		fmode:4;	//�����̑傫��
u8		skip_f:1;	//�X�L�b�v����t���O
u8		dummy:3;

u8		cur_wait:5;	//�g���K�[�҂��J�[�\���E�F�C�g���[�N
u8		cur_anm:2;	//�g���K�[�҂��J�[�\���A�j�����[�N
u8		modechg_f:1;//�����傫���ύX�t���O

u8		rep_wait:8;	//���v���C���E�F�C�g���[�N
}MSG_PRINT_USER;

///�\���ݒ�
typedef struct {
u8		skip_f:1;		//�X�L�b�v����t���O
u8		cursor_type:1;	//�J�[�\���p�^�[��
u8		auto_f:1;		//�J�[�\����������
u8		speed_fix:1;	//���b�Z�[�W���x��� add by matsuda 2004.03.09(��)
u8		tp_f:1;			//�^�b�`�p�l������
u8		auto_f_skip:1;	//�J�[�\���������蒆�̃L�[���蔻��t���O

u8		btl_skip_f:1;	//�퓬�p�F�X�L�b�v����
u8		btl_wait_f:1;	//�퓬�p�F���𑗂�����

}MSG_PRINT_MODE;



GLOBAL_WORK MSG_PRINT_MODE msg_print_flag;



GLOBAL void PokeFontTrgCursorCgxSet( u16 cgx );

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
GLOBAL void MsgPrintSkipFlagSet( int flg );

//--------------------------------------------------------------------------------------------
/**
 * ��������ݒ�
 *
 * @param	flg		�t���O
 *
 * @return	none
 *
 *	flg = MSG_AUTO_OFF : �������薳��
 *	flg = MSG_AUTO_ON  : ��������L��
 */
//--------------------------------------------------------------------------------------------
GLOBAL void MsgPrintAutoFlagSet( int flg );

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
GLOBAL void MsgPrintTouchPanelFlagSet( int flg );




GLOBAL u8 MsgPrintBattleSkipPushFlagGet(void);
GLOBAL void MsgPrintBattleSkipPushFlagClear(void);
GLOBAL u8 MsgPrintBattleWaitPushFlagGet(void);
GLOBAL void MsgPrintBattleWaitPushFlagClear(void);


//=============================================================================================
/**
 *		�g���K�[�҂��J�[�\���\��
 */
//=============================================================================================
GLOBAL void	PokeFontTriggerCursorAnimeInit(MSG_DATA_HEADER* mdh_p);

GLOBAL void	PokeFontTriggerCursorAnime2( MSG_DATA_HEADER* mdh_p);
GLOBAL void PokeFontTriggerCursorAnimeExit2( MSG_DATA_HEADER* mdh_p );

GLOBAL BOOL PokeFontTriggerWaitReplayCheck(MSG_DATA_HEADER* mdh_p);

GLOBAL BOOL PokeFontTriggerWait( MSG_DATA_HEADER* mdh_p );

GLOBAL BOOL PokeFontTriggerWait2(MSG_DATA_HEADER* mdh_p);

//=============================================================================================
/**
 *		�g���K�[�҂��J�[�\���\��(�O������)
 *		u8 win_index			:�\���r�b�g�}�b�v�h�m�c�d�w
 *		u16 x,u16 y,			:�\���r�b�g�}�b�v�����W
 *		u8 b_col,				:�\���r�b�g�}�b�v�w�i�F
 *		u8 mode,				:�O�F�J�[�\������A�P�F�J�[�\������
 *		u8* wait,u8* anime		:�֐��g�p���[�N�|�C���^�i�������݉w��j
 */
//=============================================================================================
enum{
	MSG_TRG_CURSOR_PUT = 0,
	MSG_TRG_CURSOR_CLS,
};
GLOBAL void	MsgTriggerCursorAnime(u8 win_index,u16 x,u16 y,u8 b_col,u8 mode,u8* wait,u8* anime);










//--------------------------------------------------------------------------------------
/**
 * ������̕`��ɕK�v�ȕ��i�h�b�g���j���v�Z
 *
 * @param   fnt_index		�t�H���g�C���f�b�N�X
 * @param   str				������
 * @param   spc				�������Ƃ̊Ԋu�i== SPACE_DEFAULT���w��Ńf�t�H���g�l�j
 *
 * @retval  u32			�`��ɕK�v�ȕ��i�h�b�g�j
 *
 * I_MSG_, S_MSG_, C_FCHG_ �ɑΉ��B
 * CR_���܂ޕ����s�̏ꍇ�A�ł��傫���s�̕���Ԃ��B
 *
 */
//--------------------------------------------------------------------------------------
#define SPACE_DEFAULT  (-1)
GLOBAL u32 PokeStrWidthGet(u8 fnt_index, const u8* str, s16 spc);

//--------------------------------------------------------------
/**
 * @brief   �����f�[�^�擾(���퓬�E�C���h�E�n�a�i�p)������R�[�h�͖���
 *
 * @param	buf			�t�H���g�f�[�^�i�[�o�b�t�@�|�C���^
 * @param	fnt_index	�t�H���g�w��R�[�h
 * @param	msg			���b�Z�[�W�f�[�^�|�C���^
 */
//--------------------------------------------------------------
GLOBAL u16 PokeFontPrintFontData(void* buf,u8 fnt_index,const void* msg);



//------------------------------------------------------------------
/**
 *	����BITMAP�f�[�^�擾
 *
 * @param	ini			BGL�f�[�^
 * @param	mdh_p		���b�Z�[�W�f�[�^�\���̃|�C���^
 *
 * @retval	w_flag		�����擾�p�����[�^
 */
//------------------------------------------------------------------
GLOBAL PRINT_RESULT PokeFontPrint( MSG_DATA_HEADER * mdh_p );

#undef GLOBAL


#endif
