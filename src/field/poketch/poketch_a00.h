//============================================================================================
/**
 * @file	poketch_a00.h
 * @bfief	�|�P�b�`�i�A�v��No00:�f�W�^�����v�j �@�����w�b�_
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_A00_H_
#define _POKETCH_A00_H_


//====================================================
// �`��R�}���h
//====================================================
enum {
	CMD_INIT,
	CMD_TIME_UPDATE,
	CMD_BACKLIGHT_UPDATE,
	CMD_QUIT,
};

//====================================================
// �`��p�����[�^
//====================================================
typedef struct {
	RTCTime   time;
	u32       backlight;
}VIEWPARAM;

//====================================================
// �`��p�����[�^
//====================================================
typedef	struct _POKETCH_A00_VIEWWORK  VIEWWORK;

//====================================================
// �֐��v���g�^�C�v
//====================================================
extern BOOL Poketch_A00_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl );
extern void Poketch_A00_SetViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A00_WaitViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A00_WaitViewCommandAll(VIEWWORK* wk);
extern void Poketch_A00_DeleteViewWork(VIEWWORK* wk);

#endif
