#ifndef _TRCARD_SYS_H_
#define _TRCARD_SYS_H_

#include "common.h"
#include "system/bmp_menu.h"
#include "system/window.h"
#include "application/trainer_card.h"
#include "trcard_obj.h"
#include "trcard_snd.h"

#define TRC_SCREEN_WIDTH	(32)
#define TR_CARD_WIN_MAX	(11)

#define TR_CARD_BADGE_LV_MAX	(4)		//�o�b�W�̍ő僌�x��
#define TR_BADGE_NUM_MAX	(8)

//�p���b�g�g�p���X�g
enum{
	TR_FONT_PAL = 15,
};

typedef struct TR_SCRUCH_SND_tag
{
	s8 OldDirX;
	s8 OldDirY;
	s8 DirX;
	s8 DirY;
	u8 Snd;
}TR_SCRUCH_SND;

typedef struct TR_CARD_WORK_tag
{
	GF_BGL_INI * bgl;						// BGL�f�[�^

	GF_BGL_BMPWIN	win[TR_CARD_WIN_MAX];			// BMP�E�B���h�E�f�[�^�i�ʏ�j
	TR_CARD_DATA *TrCardData;
	u8 TrSignData[SIGN_SIZE_X*SIGN_SIZE_Y*64];	//�]������̂łS�o�C�g���E�̈ʒu�ɒu������
	void *TrArcData;							//�g���[�i�[�O���t�B�b�N�A�[�J�C�u�f�[�^
	NNSG2dCharacterData* TrCharData;			//�g���[�i�[�L�����f�[�^�|�C���^
	BOOL is_back;
	BOOL brushOK;
	
	fx32 CardScaleX;
	fx32 CardScaleY;
	fx32 CoverScaleY;

	int touch;
	BOOL rc_cover;
	int BeforeX;
	int BeforeY;
	TR_CARD_OBJ_WORK ObjWork;
	int RevSpeed;
	int Scroll;
	BOOL ButtonPushFlg;
	SND_BADGE_WORK SndBadgeWork;
	void *TrScrnArcData;
	NNSG2dScreenData* ScrnData;
	TR_SCRUCH_SND ScruchSnd;
	
	STRBUF	*PlayTimeBuf;		//�v���C���ԗp������o�b�t�@
	STRBUF	*SecBuf;			//�v���C���ԃR�����p������o�b�t�@

	u8 ScruchCounter[TR_BADGE_NUM_MAX];
	
	u8 IsOpen;
	u8 Counter;
	u8 sub_seq;
	u8 ButtonAnmCount;
	u8 AnmNum;
	u8 AnimeType;
	u8 SecCount;				//�b�\���̂��߂̃J�E���^
	u8 Dummy;
	
}TR_CARD_WORK;

#endif //_TRCARD_SYS_H_


