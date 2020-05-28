//============================================================================================
/**
 * @file	fnote_main.h
 * @brief	�`���m�[�g�@�\�����C������
 * @author	Hiroyuki Nakamura
 * @date	2006.03.06
 */
//============================================================================================
#ifndef FNOTE_MAIN_H
#define FNOTE_MAIN_H
#undef GLOBAL
#ifdef FNOTE_MAIN_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif


//============================================================================================
//	�萔��`
//============================================================================================

enum {
	WIN_TIME1 = 0,		// ���t�P
	WIN_STR1,			// ���P
	WIN_TIME2,			// ���t�Q
	WIN_STR2,			// ���Q
	WIN_MAX
};


typedef struct {
	GF_BGL_INI * bgl;				// BGL�f�[�^

	GF_BGL_BMPWIN	win[WIN_MAX];	// BMP�E�B���h�E�f�[�^

	FNOTE_DATA * dat;
	MYSTATUS * myst;
	SAVEDATA * sv;				// ���C�o�����擾�̂��߁E�E�E

	MSGDATA_MANAGER * mman;		// ���b�Z�[�W�f�[�^�}�l�[�W��
	WORDSET * wset;				// �P��Z�b�g
	STRBUF * msg_buf;			// �e���|�������b�Z�[�W�o�b�t�@

//	TCB_PTR		vtask;


	u16	chr_scrn[32*32];		// �w�iBG�ۑ��ꏊ
	u16	bmp_scrn[32*32];		// BMP��BG�ۑ��ꏊ

//	BOOL	wipe_flg;

	s8	page;					// ���݂̃y�[�W
	s8	page_chg_mv;			// �y�[�W�؂�ւ�����
	s8	page_chg_seq;			// �y�[�W�؂�ւ��V�[�P���X
	s8	page_chg_cnt;			// �y�[�W�؂�ւ��J�E���^
	s8	page_write_flg;			// �y�[�W�������݃t���O

	u8	now_chr_frm;
	u8	now_bmp_frm;
	u8	new_chr_frm;
	u8	new_bmp_frm;

}FNOTE_WORK;



//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================




#undef GLOBAL
#endif	/* FNOTE_MAIN_H */
