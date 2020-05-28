//============================================================================================
/**
 * @file	poketch_a04.h
 * @bfief	�|�P�b�`�i�A�v��No04:�A�i���O���v�j �@�����w�b�_
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_A04_H_
#define _POKETCH_A04_H_


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
typedef	struct _POKETCH_A04_VIEWWORK  VIEWWORK;

//====================================================
// �֐��v���g�^�C�v
//====================================================
extern BOOL Poketch_A04_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl );
extern void Poketch_A04_SetViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A04_WaitViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A04_WaitViewCommandAll(VIEWWORK* wk);
extern void Poketch_A04_DeleteViewWork(VIEWWORK* wk);

#endif
