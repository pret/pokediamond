//==============================================================================
/**
 * @file	pm_overlay.h
 * @brief	�I�[�o�[���C����̃w�b�_
 * @author	matsuda
 * @date	2005.06.20(��)
 */
//==============================================================================
#ifndef __PM_OVERLAY_H__
#define __PM_OVERLAY_H__


//==============================================================================
//	�萔��`
//==============================================================================

/*------------------------------------
�����֐��Ɣ񓯊��֐��̓���̈Ⴂ�͔񓯊��֐��͕ʃX���b�h�œǂݍ��݂��s���Ƃ����_�ł��B
���̋����̈Ⴂ����A���荞�݋֎~��Ԃ�A�g�p����X�^�b�N���قȂ�Ƃ�������������܂��B
---------------------------------------*/

///�I�[�o�[���C���s���̃��[�h�^�C�v
enum{
	OVERLAY_LOAD_SYNCHRONIZE = 0,	///<�S�Ă𓯊��I�Ɏ��s
	OVERLAY_LOAD_SYNCHRONIZE_2,		///<�����I�Ɏ��ƂŎ��s (�����I)
	OVERLAY_LOAD_NOT_SYNCHRONIZE,	///<�S�Ă����ƂŎ��s (�񓯊��I)
};

///�I�[�o�[���C�̓W�J�������G���A
enum{
	OVERLAY_AREA_MAIN = 0,			///<���C��������
	OVERLAY_AREA_ITCM,				///<����TCM
	OVERLAY_AREA_DTCM,				///<�f�[�^TCM
};


//==============================================================================
//	�O���֐��錾
//==============================================================================
extern void Overlay_SystemWorkInit(void);
extern void Overlay_Init(void);
extern void Overlay_UnloadID(const FSOverlayID id);
extern void Overlay_UnloadMain(void);
extern void Overlay_UnloadItcm(void);
extern void Overlay_UnloadDtcm(void);
extern void Overlay_UnloadSameArea(const FSOverlayID id);
extern void Overlay_UnloadAll(void);
extern int Overlay_MemoryAreaGet(const FSOverlayID id);
extern BOOL Overlay_Load(const FSOverlayID id, int load_type);
extern BOOL Overlay_Call(const FSOverlayID id, int load_type, void(*func)(void *), void * work);



#endif	//__PM_OVERLAY_H__


