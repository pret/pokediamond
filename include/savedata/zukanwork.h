//============================================================================================
/**
 * @file	zukanwork.h
 * @brief	������ԃf�[�^�A�N�Z�X�p�w�b�_
 * @author	tamada GAME FREAK inc.
 * @date	2005.12.15
 */
//============================================================================================
#ifndef __ZUKANWORK_H__
#define __ZUKANWORK_H__

#include "savedata/savedata_def.h"	//SAVEDATA�Q�Ƃ̂���

#include "poketool/poke_tool.h"
#include "poketool/monsno.h"

//============================================================================================
//============================================================================================
enum{
	ZUKAN_WORK_RANDOM_PACHI = 0,		// �p�b�`�[��������

	// �|�P�������ʎ擾�p
	ZUKAN_WORK_SEX_FIRST = 0,
	ZUKAN_WORK_SEX_SECOND,

	// ZukanWork_GetPokeSexFlag�n�֐��̃G���[�R�[�h
	ZUKAN_WORK_GET_SEX_ERR	= 0xffffffff,	

	
	// �S���}�Ӎő�
	ZUKAN_WORK_ZENKOKU_MONSMAX		= MONSNO_END,
	
	// �ݵ��޶ݍő吔
	// ���͑S���Ɠ����@��X�́@monsno.h�ɃV���I�E�̍ő吔��`���o����
	ZUKAN_WORK_SHINOU_MONSMAX	= SINOU_MAX,

	// �[���R�N�}�ӊ����ɕK�v�ȃ|�P�����̐�
	ZUKAN_WORK_ZENKOKU_COMP_NOPOKE_NUM = 11,	// �s�K�v�ȃ|�P������
	ZUKAN_WORK_ZENKOKU_COMP_NUM	= ZUKAN_WORK_ZENKOKU_MONSMAX - ZUKAN_WORK_ZENKOKU_COMP_NOPOKE_NUM,

	// �V���I�E�}�ӊ����ɕK�v�ȃ|�P�����̐�
	ZUKAN_WORK_SHINOU_COMP_NOPOKE_NUM = 1,	// �s�K�v�ȃ|�P������
	ZUKAN_WORK_SHINOU_COMP_NUM	= ZUKAN_WORK_SHINOU_MONSMAX - ZUKAN_WORK_SHINOU_COMP_NOPOKE_NUM,
		


	// �V�[�E�V�@�V�[�h���S�̌`��
	ZUKAN_WORK_UMIUSHI_FORM_NUM = 2,	//(������ς��������ł̓Z�[�u�̈�̕����⃏�[�N�T�C�Y�͕ς��Ȃ��̂ŁA�`�󐔂��ς�����Ƃ��͓������ύX���邱��)

	// �~�m���b�`�@�~�m���X�@�`��
	ZUKAN_WORK_MINOMUSHI_FORM_NUM = 3,	//(������ς��������ł̓Z�[�u�̈�̕����⃏�[�N�T�C�Y�͕ς��Ȃ��̂ŁA�`�󐔂��ς�����Ƃ��͓������ύX���邱��)

	// �f�I�L�V�X�̌`��
	ZUKAN_WORK_DEOKISISU_FORM_NUM = 4,
	ZUKAN_WORK_DEOKISISU_FORM_SAVEDATA_CUTNUM = 2,	// �f�I�L�V�X�Z�[�u�̈�́A�}篁@�ߊl�����t���O�̂���1byte���ÂɊ���U���Ă��܂��B�e1byte�ɃZ�[�u�ł���`��̐��ł�
	POKEZUKAN_DEOKISISU_INIT = 0xf,	// ���������i�[����Ă���l
};

//----------------------------------------------------------
//----------------------------------------------------------
typedef struct _ZUKAN_WORK ZUKAN_WORK;

//----------------------------------------------------------
//	�Z�[�u�f�[�^�V�X�e�����ˑ�����֐�
//----------------------------------------------------------
extern int ZukanWork_GetWorkSize(void);
extern ZUKAN_WORK * ZukanWork_AllocWork(u32 heapID);


//----------------------------------------------------------
//----------------------------------------------------------
extern void ZukanWork_Init(ZUKAN_WORK * zw);

extern u16 ZukanWork_GetPokeGetCount(const ZUKAN_WORK * zw);
extern u16 ZukanWork_GetPokeSeeCount(const ZUKAN_WORK * zw);

extern u16 ZukanWork_GetShinouPokeGetCount(const ZUKAN_WORK * zw);
extern u16 ZukanWork_GetShinouPokeSeeCount(const ZUKAN_WORK * zw);

// �[���R�N�}�ӎ����Ă���Ƃ��[���S���p�̊e������Ԃ�
// �ݵ��޶݂��������Ă��Ȃ��Ƃ��[���V���I�E�}�ӗp�̊e������Ԃ�
extern u16 ZukanWork_GetZukanPokeGetCount(const ZUKAN_WORK * zw);
extern u16 ZukanWork_GetZukanPokeSeeCount(const ZUKAN_WORK * zw);


// �[���R�N�}�Ӂ@�ݵ��}��
// �����ɕK�v�ȃ|�P���������ŃJ�E���g�����l���擾
extern u16 ZukanWork_GetZenkokuGetCompCount(const ZUKAN_WORK * zw);
extern u16 ZukanWork_GetShinouSeeCompCount(const ZUKAN_WORK * zw);

extern BOOL ZukanWork_CheckZenkokuComp(const ZUKAN_WORK * zw);
extern BOOL ZukanWork_CheckShinouComp(const ZUKAN_WORK * zw);

extern BOOL ZukanWork_GetPokeGetFlag(const ZUKAN_WORK * zw, u16 monsno);
extern BOOL ZukanWork_GetPokeSeeFlag(const ZUKAN_WORK * zw, u16 monsno);
extern u32 ZukanWork_GetPokeSexFlag(const ZUKAN_WORK * zw, u16 monsno, int first_second );
extern u32 ZukanWork_GetPokeAnoonForm(const ZUKAN_WORK * zw, int count);
extern u32 ZukanWork_GetPokeAnoonSeeNum(const ZUKAN_WORK * zw);
extern u32 ZukanWork_GetPokeSiiusiForm(const ZUKAN_WORK * zw, int count);
extern u32 ZukanWork_GetPokeSiiusiSeeNum(const ZUKAN_WORK * zw);
extern u32 ZukanWork_GetPokeSiidorugoForm(const ZUKAN_WORK * zw, int count);
extern u32 ZukanWork_GetPokeSiidorugoSeeNum(const ZUKAN_WORK * zw);
extern u32 ZukanWork_GetPokeMinomuttiForm(const ZUKAN_WORK * zw, int count);
extern u32 ZukanWork_GetPokeMinomuttiSeeNum(const ZUKAN_WORK * zw);
extern u32 ZukanWork_GetPokeMinomesuForm(const ZUKAN_WORK * zw, int count);
extern u32 ZukanWork_GetPokeMinomesuSeeNum(const ZUKAN_WORK * zw);
extern u32 ZukanWork_GetPokeRandomFlag(const ZUKAN_WORK * zw, u8 random_poke);
extern u32 ZukanWork_GetPokeDeokisisuForm(const ZUKAN_WORK * zw, int count);
extern u32 ZukanWork_GetPokeDeokisisuFormSeeNum(const ZUKAN_WORK * zw);
extern u32 ZukanWork_GetPokeForm( const ZUKAN_WORK* zw, int monsno, int count );

extern void ZukanWork_SetPokeSee(ZUKAN_WORK * zw, POKEMON_PARAM * pp);
extern void ZukanWork_SetPokeGet(ZUKAN_WORK * zw, POKEMON_PARAM * pp);

extern BOOL ZukanWork_GetZukanGetFlag(const ZUKAN_WORK * zw);
extern void ZukanWork_SetZukanGetFlag(ZUKAN_WORK * zw);

extern BOOL ZukanWork_GetZenkokuZukanFlag(const ZUKAN_WORK * zw);
extern void ZukanWork_SetZenkokuZukanFlag(ZUKAN_WORK * zw);

extern BOOL ZukanWork_GetGraphicVersionUpFlag(const ZUKAN_WORK * zw);
extern void ZukanWork_SetGraphicVersionUpFlag(ZUKAN_WORK * zw);

extern BOOL ZukanWork_GetTextVersionUpFlag(const ZUKAN_WORK * zw, u16 monsno, u32 country_code);

extern void ZukanWork_SetTextVersionUpMasterFlag( ZUKAN_WORK * zw );
extern BOOL ZukanWork_GetTextVersionUpMasterFlag(const ZUKAN_WORK * zw);

extern void ZukanWork_Copy(const ZUKAN_WORK * from, ZUKAN_WORK * to);

//----------------------------------------------------------
//	�Z�[�u�f�[�^�擾�̂��߂̊֐�
//----------------------------------------------------------
extern ZUKAN_WORK * SaveData_GetZukanWork(SAVEDATA * sv);


//----------------------------------------------------------
//	�f�o�b�O�p
//----------------------------------------------------------
extern void Debug_ZukanWork_Make(ZUKAN_WORK * zw, int start, int end, BOOL see_flg);
extern void Debug_ZukanWork_DeokisisuBuckUp( ZUKAN_WORK * zw );

#ifdef CREATE_INDEX
extern void *Index_Get_Zukan_Offset(ZUKAN_WORK *zw);
extern void *Index_Get_Zenkoku_Zukan_Offset(ZUKAN_WORK *zw);
extern void *Index_Get_Get_Flag_Offset(ZUKAN_WORK *zw);
extern void *Index_Get_See_Flag_Offset(ZUKAN_WORK *zw);
extern void *Index_Get_Sex_Flag_Offset(ZUKAN_WORK *zw);
#endif

#endif	// __ZUKANWORK_H__
