/* WIFI�p�f�o�b�N��`
 *	tomoya takahashi
 */

#ifdef PM_DEBUG


#ifndef	_DEUBG_WIFI_H__
#define _DEUBG_WIFI_H__

//-------------------------------------
// ���̃t���O�𗧂Ă邱�Ƃɂ��
//�@WIFI�ΐ�AUTOӰ��
//	L+X��L+Y��2�@���N��������Ɠ���
//=====================================
//#define	_WIFI_DEBUG_TUUSHIN

#ifdef _WIFI_DEBUG_TUUSHIN
#define _WIFI_DEBUG_NONE	(0)
#define _WIFI_DEBUG_MODE_X	(1)
#define _WIFI_DEBUG_MODE_Y	(2)
// WIFI�f�o�b�N���[�N
typedef struct{
	u32 DEBUG_WIFI_MODE : 8;		//�N��Ӱ��
	u32 DEBUG_WIFI_SEQ : 8;			//�t�B�[���h�ł̓����V�[�P���X
	u32 DEBUG_WIFI_MOVE_WAIT : 12;	//�����҂�
	u32 DEBUG_WIFI_BATTLE : 1;		//�ΐ풆�t���O
	u32 DEBUG_WIFI_A_REQ : 1;		//A�A�Ń��N�G�X�g
	u32 DEBUG_WIFI_B_REQ : 1;		//B�A�Ń��N�G�X�g
	u32 DEBUG_WIFI_TOUCH_REQ : 1;	//�h������h�^�b�`���N�G�X�g
} WIFI_DEBUG_BATTLE_WK;
#endif	// _WIFI_DEBUG_TUUSHIN


#endif	// _DEUBG_WIFI_H__


#endif	// PM_DEBUG
