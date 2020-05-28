#ifndef __TRCARD_CGX_DEF_H__
#define __TRCARD_CGX_DEF_H__

#define TR_BG_BASE		(1)
//�g���[�i�[�摜�T�C�Y	(�j����l���̃L������32x3�����A���j�I���g���[�i�[�T�C�Y�ɍ��킹��)
#define TR_BG_SIZE		(10*11/*32*3*/)	

//�T�C��
#define SIGN_CGX	(TR_BG_BASE)
#define SIGN_PX	(4)
#define SIGN_PY	(14)
#define SIGN_SX	(24)
#define SIGN_SY	(8)
#define SIGN_BYTE_SIZE	(SIGN_SX*SIGN_SY*64)
#define TR_SIGN_SIZE	(SIGN_SX*SIGN_SY)	//�T�C���T�C�Y

#endif	//__TRCARD_CGX_DEF_H__
