/**
 *	@file	poru_3d.h
 *	@brief	�|���g�f�� 3D�w�b�_
 *	@author	Miyuki Iwasawa
 *	@date	06.03.28
 */

#ifndef __H_PORU_3D_H__
#define __H_PORU_3D_H__

#undef	GLOBAL
#ifdef	PORU_DEMO_3D_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif

typedef struct _PORUDEMO_POKE{
	POKEMON_PARAM*	pp;	///<�ۂ���
	u16	monsno;		///<�|�P����No
	u8	seikaku;	///<�|�P�����̐��i
	u8	sex;		///<�|�P�����̐���
	u8	flip;		///<�t���b�v�t���O
	u8	favolite;	///<�D������
	STRBUF*	name;	///<�|�P�����̃j�b�N�l�[��
}PORUDEMO_POKE;

typedef struct _PORU3D_WORK{
	GF_CAMERA_PTR	camera;
	void*			ssm;

	SOFT_SPRITE_ARC	ssa;	///<�\�t�g�E�F�A�X�v���C�g
	SOFT_SPRITE	* ss;
}PORU3D_WORK;

#define POKEA_INI_PX	(128)	///<�f���|�P�����������WX
#define POKEA_INI_PY	(96)	///<�f���|�P�����������WY

/**
 *	@brief	3D�֘A������
 */
GLOBAL void PoruDemo_3DInit(PORU3D_WORK* wk,PORUDEMO_POKE* poke,int heapID);
GLOBAL void PoruDemo_3DMain(PORU3D_WORK* wk);
GLOBAL void PoruDemo_3DRelease(PORU3D_WORK* wk);


#endif	//__H_PORU_3D_H__
