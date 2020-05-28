//============================================================================================
/**
 * @file	field_skill.h
 * @brief	�t�B�[���h�Z�����i��`�Z�Ȃǁj
 * @author	Hiroyuki Nakamura
 * @date	2005.12.01
 */
//============================================================================================
#ifndef FIELD_SKILL_H
#define FIELD_SKILL_H
#undef GLOBAL
#ifdef FIELD_SKILL_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif


//============================================================================================
//	�萔��`
//============================================================================================
// �Z�C���f�b�N�X�i�|�P�������X�g�Ɠ������тɂ��邱�ƁI�j
#define	FLD_SKILL_IAIGIRI		( 0 )		// ����������
#define	FLD_SKILL_SORAWOTOBU	( 1 )		// ������Ƃ�
#define	FLD_SKILL_NAMINORI		( 2 )		// �Ȃ݂̂�
#define	FLD_SKILL_KAIRIKI		( 3 )		// �����肫
#define	FLD_SKILL_KIRIBARAI		( 4 )		// ����΂炢
#define	FLD_SKILL_IWAKUDAKI		( 5 )		// ���킭����
#define	FLD_SKILL_TAKINOBORI	( 6 )		// �����̂ڂ�
#define	FLD_SKILL_ROCKCLIMB		( 7 )		// ���b�N�N���C��
#define	FLD_SKILL_FLASH			( 8 )		// �t���b�V��
#define	FLD_SKILL_TELEPORT		( 9 )		// �e���|�[�g
#define	FLD_SKILL_ANAWOHORU		( 10 )		// ���Ȃ��ق�
#define	FLD_SKILL_AMAIKAORI		( 11 )		// ���܂�������
#define	FLD_SKILL_OSYABERI		( 12 )		// ������ׂ�

// �Z�g�p���[�N�ւ̕s���S�^�|�C���^
typedef struct SKILLUSE_WORK SKILLUSE_WORK;

// �Z�g�p�`�F�b�N���[�N�ւ̕s���S�^�|�C���^
typedef struct SKILLCHECK_WORK SKILLCHECK_WORK;

typedef int (*SKILLCHECK_FUNC)(const SKILLCHECK_WORK*);	// �Z�g�p�`�F�b�N�֐�

typedef void (*SKILLUSE_FUNC)(SKILLUSE_WORK*, const SKILLCHECK_WORK *);	// �Z�g�p�֐�

// �Z�g�p�֐��擾�p�����[�^
enum {
	FIELDSKILL_PRM_USEFUNC = 0,	// �g�p�֐�
	FIELDSKILL_PRM_CHECKFUNC	// �`�F�b�N�֐�
};

// �g�p�`�F�b�N�̖߂�l
enum {
	FIELDSKILL_USE_TRUE = 0,	// �g�p�\
	FIELDSKILL_USE_FALSE,		// �g�p�s�i�����ł͎g���܂���j
	FIELDSKILL_NO_BADGE,		// �g�p�s�E�o�b�W�Ȃ�
	FIELDSKILL_COMPANION,		// �g�p�s�E�A�����
	FIELDSKILL_PLAYER_SWIM,		// �g�p�s�E�Ȃ݂̂蒆
};


//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �g�p�֐��擾
 *
 * @param	prm		�擾�p�����[�^
 * @param	id		�֐�ID
 *
 * @return	�g�p�֐�
 */
//--------------------------------------------------------------------------------------------
GLOBAL u32 FieldSkill_FuncGet( u16 prm, u16 id );

//--------------------------------------------------------------------------------------------
/**
 * �g�p�`�F�b�N���[�N�쐬
 *
 * @param	fsys	�t�B�[���h���[�N
 * @param	id		�`�F�b�N���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void FieldSkill_CheckWorkMake( FIELDSYS_WORK * fsys, SKILLCHECK_WORK * scwk );




#undef GLOBAL
#endif	/* FIELD_SKILL_H */
