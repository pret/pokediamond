#ifndef _AGB_ACCESS_H
#define _AGB_ACCESS_H

#include "pokeparam.h"
#include "pm_version.h"

#define SOFTTYPE_RS	0	// ���r�[�A�T�t�@�C�A
#define SOFTTYPE_FL	1	// �t�@�C�A���b�h�A���[�t�O���[��
#define SOFTTYPE_EM 2	// �G�������h

#if 0
#define LANGTYPE_JP 0
#define LANGTYPE_US 1
#define LANGTYPE_FR 2
#define LANGTYPE_GE 3
#define LANGTYPE_SP 4
#define LANGTYPE_IT 5
#else
#define LANGTYPE_JP LANG_JAPAN
#define LANGTYPE_US LANG_ENGLISH
#define LANGTYPE_FR LANG_FRANCE
#define LANGTYPE_GE LANG_GERMANY
#define LANGTYPE_SP LANG_SPAIN
#define LANGTYPE_IT LANG_ITALY
#endif

enum {
  CASTYPE_RUBY = 0,
  CASTYPE_SAPPHIRE,
  CASTYPE_GREEN,
  CASTYPE_RED,
  CASTYPE_EMERALD,
  CASTYPE_MAX
};


#define	SVLD_RET_NG			(0xff)		//�Z�[�u���ʁi�������ݏo���Ȃ������j
#define	SVLD_RET_NULL		(0x0)		//�Z�[�u���ʁi�o�b�N�A�b�v�Ȃ��j
#define	SVLD_RET_OK			(0x1)		//�Z�[�u���ʁi����ɏI���j
#define	SVLD_RET_DESTROY	(0x2)		//�Z�[�u���ʁi���S�j��F���A�s�\�j
#define	SVLD_RET_FULL		(0x3)		//�Z�[�u���ʁi����ȏ㏑�����ݏo���Ȃ��j
#define	SVLD_RET_HARDERROR	(0x4)		//�n�[�h�G���[�i��ՂȂ��j
#define	SVLD_RET_ERROR		(0x5)		//�ǂݍ��݂Ɏ��s�@�i�d���������āA�J�[�g���b�W���������肳�����Ƃ𑣂��j

#define	SVLD_HEADER_SIZE	(4+2+4+2)	//�w�b�_�T�C�Y
#define	SVLD_SECTOR_SIZE	(0x1000)	//�Z�N�^�T�C�Y
#define	SVLD_DATA_SIZE		(SVLD_SECTOR_SIZE - SVLD_HEADER_SIZE)	//���f�[�^�T�C�Y





typedef struct
{
	u32 buffer[SVLD_SECTOR_SIZE / 4];
	u8 MyData[SVLD_SECTOR_SIZE];
	u8 Fld[SVLD_SECTOR_SIZE*4];
	POKEBOX_SAVE_DATA pc_data;
} AGBPOKE_SAVEDATA;

#define AGBPOKE_BUFFERSIZE (sizeof(AGBPOKE_SAVEDATA)) 

enum
{
	AGBPOKE_ERROR_OK,
	AGBPOKE_ERROR_NOROM,
	AGBPOKE_ERROR_NOTPOKEMON,
	AGBPOKE_ERROR_NOFLASH,
	AGBPOKE_ERROR_READ,
	AGBPOKE_ERROR_NG,
	AGBPOKE_ERROR_DESTROY,
	AGBPOKE_ERROR_NULL,	
	AGBPOKE_ERROR_WRITE,
	AGBPOKE_ERROR_WRITING,
	AGBPOKE_ERROR_CONTINUE,	
	AGBPOKE_ERROR_LAST,
	AGBPOKE_ERROR_OTHER			
};

//==============================================================================
/**
 * agbpoke_*���Ăяo�����O�ɁA���̊֐����R�[�����Ă��������B
 * @param   buffer�c�o�b�t�@��n���B�K�v�ȗʂ�AGBPOKE_BUFFERSIZE
 * @retval  �G���[�R�[�h
 */
//==============================================================================
extern int agbpoke_init( void *buffer );
extern void agbpoke_preinit(void);

//==============================================================================
/**
 * �������Ă���\�t�g�̃C�j�V�����R�[�h���擾���܂��B
 * @retval  TRUE�c�����������@FALSE�c���������s
 */
//==============================================================================
extern u32 agbpoke_getInitialCode();

//==============================================================================
/**
 * �������Ă���\�t�g�̃Q�[����ނ�Ԃ��܂��B
 * @retval  �J�Z�b�g�̃|�P�����^�C�v
 */
//==============================================================================
extern int agbpoke_getPokemonType();

//==============================================================================
/**
 * �������Ă���|�P�����\�t�g�̌����Ԃ��B
 * @retval  �J�Z�b�g�̌���
 */
//==============================================================================
extern int agbpoke_getPokemonLanguage();

//==============================================================================
/**
 * �f�[�^�����[�h����B
 * @param   newsector�c�V�����Z�N�^�[�̔ԍ��������Ă���(0��1)
 * @param   buffer   �cSVLD_SECTOR_SIZE �K�v
 * @retval  ���ʁB
 */
//==============================================================================
extern int agbpoke_LoadDATA();

//==============================================================================
/**
 * �p�\�R���f�[�^�ւ̃|�C���^���擾����B
 * @param   newsector�c�V�����Z�N�^�[�̔ԍ��������Ă���(0��1)
 * @param   buffer   �cSVLD_SECTOR_SIZE �K�v
 * @retval  ���ʁB
 */
//==============================================================================
extern POKEBOX_SAVE_DATA *agbpoke_getPCdata();

//==============================================================================
/**
 * �}�ӂ������Ă��邩����B
 * @retval  ���ʁB
 */
//==============================================================================
extern BOOL gbapoke_hasZukan();

//==============================================================================
/**
 * �|�P�����Z���^�[���ŃZ�[�u���Ă��邩�ǂ���
 * @retval  ���ʁB
 */
//==============================================================================
extern BOOL gbapoke_inPokemonCenter();

//==============================================================================
/**
 * �f�[�^��񓯊��ŃZ�[�u����B
 * @retval  ���ʁB
 */
//==============================================================================
extern BOOL agbpoke_saveEdit_Async();
//==============================================================================
/**
 * �f�[�^��񓯊��ŃZ�[�u�����Ƃ��A�I�����������`�F�b�N����֐��B
 * @retval  ���ʁB
 */
//==============================================================================
extern int agbpoke_saveEdit_check();
extern int agbpoke_check_status(void);

//==============================================================================
/**
 * �f�[�^���Z�[�u����BAGBPOKE_ERROR_CONTINUE�ȊO�̒l���Ԃ��܂ŌĂяo���ĉ������B
 * @retval  ���ʁB
 */
//==============================================================================
extern int agbpoke_saveEdit( );
extern void *agbpoke_GetMyDataPtr(void);

#endif
