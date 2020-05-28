//==============================================================================
/**
 * @file	temoti_gauge.h
 * @brief	�莝���Q�[�W�̃w�b�_
 * @author	matsuda
 * @date	2006.06.14(��)
 */
//==============================================================================
#ifndef __TEMOTI_GAUGE_H__
#define __TEMOTI_GAUGE_H__


//==============================================================================
//	�萔��`
//==============================================================================
///�莝���Q�[�W�������ɏo��ő吔
#define TEMOTIGAUGE_MAX			(2)		//���@���{�G��

typedef enum{
	TEMOTI_MINE,	///<���@���莝���Q�[�W
	TEMOTI_ENEMY,	///<�G���莝���Q�[�W
}TEMOTI_SIDE;

///���ޏꓮ��w��
typedef enum{
	ARROW_OUT_TYPE_SCROLL,		///<�X�N���[�����Ȃ��������
	ARROW_OUT_TYPE_SPOT,		///<���̏�ŏ�����
}ARROW_OUT_TYPE;

///�{�[���o�ꓮ��w��
typedef enum{
	BALL_IN_TYPE_ENCOUNT,		///<�G���J�E���g���̃{�[���C��
	BALL_IN_TYPE_CHANGE,		///<����ւ����̃{�[���C��
}BALL_IN_TYPE;

///�{�[���ޏꓮ��w��
typedef enum{
	BALL_OUT_TYPE_ENCOUNT,		///<�G���J�E���g���̃{�[���A�E�g
	BALL_OUT_TYPE_CHANGE,		///<����ւ����̃{�[���A�E�g
}BALL_OUT_TYPE;

///�{�[���o��ʒu�w��
typedef enum{
	BALL_POS_HIGH,				///<��i�ɕ\��
	BALL_POS_MIDDLE,			///<���f�ɕ\��
	BALL_POS_LOW,				///<���i�ɕ\��
}BALL_POS_TYPE;


//==============================================================================
//	�^��`
//==============================================================================
///TEMOTIGAUGE_WORK�̕s��`�|�C���^
typedef struct _TEMOTIGAUGE_WORK * TEMOTIGAUGE_PTR;


//==============================================================================
//	�O���֐��錾
//==============================================================================
extern void TEMOTI_ResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, PALETTE_FADE_PTR pfd);
extern void TEMOTI_ResourceFree(CATS_RES_PTR crp);
extern TEMOTIGAUGE_PTR TEMOTI_InEffectSet(u8 status[], TEMOTI_SIDE side, BALL_IN_TYPE ball_in_type,
	BALL_POS_TYPE pos_type, CATS_SYS_PTR csp, CATS_RES_PTR crp);
extern void TEMOTI_OutEffectSet(TEMOTIGAUGE_PTR tg, 
	ARROW_OUT_TYPE arrow_out_type, BALL_OUT_TYPE ball_out_type);
extern BOOL TEMOTI_InEffectEndCheck(TEMOTIGAUGE_PTR tg);
extern BOOL TEMOTI_OutEffectEndCheck(TEMOTIGAUGE_PTR tg);
extern void TEMOTI_EffectFree(TEMOTIGAUGE_PTR tg);


#endif	__TEMOTI_GAUGE_H__

