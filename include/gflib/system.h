
#ifndef __SYSTEM_H__
#define __SYSTEM_H__

///#define DEBUG_PRINT	//�f�o�b�O����\���������ꍇ�́A�R�����g���͂���
#include <nitro.h>
#include <nnsys.h>

#include "gflib\heapsys.h"
#include "gflib\tcb.h"
#include "system\heapdefine.h"
#include "system\tcbman.h"


/*---------------------------------------------------------------------------*
  File:     system.h
 *---------------------------------------------------------------------------*/
#undef GLOBAL
#ifdef __SYSTEM_H_GLOBAL__
#define GLOBAL /*	*/
#else
#define GLOBAL extern
#endif



#define XtOffset(p_type,field)     ((unsigned int)&(((p_type )NULL)->field))
#define	NELEMS(array)	( sizeof(array) / sizeof(array[0]) )
#define	ALIGN4 __attribute__((aligned(4)))
#define ROUND_UP(value, alignment) \
    (((u32)(value) + (alignment-1)) & ~(alignment-1))
#define ROUND_DOWN(value, alignment) \
    ((u32)(value) & ~(alignment-1))


#ifdef PM_DEBUG
#define TPRINTF(fmt, ...) \
	OS_TPrintf("%s:%d: " fmt, __FILE__, __LINE__, __VA_ARGS__)
#else
#define TPRINTF(fmt, ...) \
	((void)0)
#endif


/*
 * @brief	���荞�݊֐��p�|�C���^�^
 */
typedef void (*INTR_FUNC)(void *);

typedef void (*pFunc)(void);	// �֐��|�C���^�^
typedef int (*appFunc)(int command, void* set_up, void* rep);	// �A�v���֐��|�C���^�^
enum {
	APP_ON = 0,
	APP_BUSY = 1,
	APP_END = -1,
};
enum {
	APP_INIT_REQ = 0,
	APP_ON_REQ = 1,
	APP_PAUSE_REQ = 2,
	APP_END_REQ = -1,
};

enum {
	DISP_3D_TO_MAIN = 0,
	DISP_3D_TO_SUB = 1,
};

enum {
	KEYCONTROL_NORMAL = 0,
	KEYCONTROL_PATTERN1 = 1,
	KEYCONTROL_PATTERN2 = 2,
	KEYCONTROL_PATTERN3 = 3,
};

enum {  //�X���[�v��Ԃɂ��Ă͂����Ȃ���`
  SLEEPTYPE_SAVELOAD = 0x01,
  SLEEPTYPE_AGBROM = 0x02,
  SLEEPTYPE_COMM = 0x04,
};

enum {  //�\�t�g�E�G�A���Z�b�g���������Ȃ���Ԃ̒�`
  SOFTRESET_TYPE_WIFI = 0x01,   // WIFI�ʐM��
  SOFTRESET_TYPE_TRADE = 0x02,  // �|�P����������
  SOFTRESET_TYPE_SAVELOAD = 0x04, // �Z�[�u���[�h������
};


//------------------- ��` -----------------------------------------
typedef	struct {
//	pFunc	pMainProc;		// ���C����ʃv���Z�X�Ăяo���֐��|�C���^
//	pFunc	pReturnProc;	// ���菈����ɕ��A�����̊֐��|�C���^
//	appFunc pSubProc;		// �A�v���P�[�V�����Ăяo���֐��|�C���^

	INTR_FUNC pVBlank;		// �u�u�����N�����ݓ��Ăяo���֐��|�C���^
	void * pVBlankWork;		// �u�u�����N�����ݓ��Ăяo���֐��p���[�N�ւ̃|�C���^
	INTR_FUNC pHBlank;		// �g�u�����N�����ݓ��Ăяo���֐��|�C���^
	void * pHBlankWork;		// �g�u�����N�����ݓ��Ăяo���֐��p���[�N�ւ̃|�C���^
	pFunc pVCount;			// �u�J�E���g�����ݓ��Ăяo���֐��|�C���^
	pFunc pSio;				// �r�h�n�����ݓ��Ăяo���֐��|�C���^

	TCBSYS*  mainTCBSys;	// ���C�����[�v�pTCB(30fps)
	TCBSYS*  vintrTCBSys;	// Vblank���荞�ݗpTCB
	TCBSYS*  vwaitTCBSys;	// VBlank�Q��I�����30fps�����pTCB
	TCBSYS*  printTCBSys;	// �����o�͏����p��,VBlank�҂��O�ɉғ�����TCB

	u32* main_timer;			// �^�C�}�[(�\�t�g)�p�J�E���^�|�C���^
	u32 vsync_counter;			// �u�u�����N�p�J�E���^
	u32 vsync_flame_counter;	// �t���[������p�J�E���^

	int key_control_mode;	// �L�[�擾���[�h(0��default)
	int cont_org;			// �L�[���
	int trg_org;			// �L�[�g���K
	int repeat_org;			// �L�[���s�[�g
	int cont;				// �L�[���(�Q�[���ݒ�ɂ��ϊ�����������)
	int trg;				// �L�[�g���K(�Q�[���ݒ�ɂ��ϊ�����������)
	int repeat;				// �L�[���s�[�g(�Q�[���ݒ�ɂ��ϊ�����������)
	int repeatWait_Count;	// �L�[���s�[�g�J�E���^
	int repeatSpeed;		// �L�[���s�[�g�X�s�[�h
	int repeatWait;			// �L�[���s�[�g�E�F�C�g

	u16		tp_x;			// �^�b�`�p�l��X���W
	u16		tp_y;			// �^�b�`�p�l��Y���W
	u16		tp_trg;			// �^�b�`�p�l���ڐG����g���K
	u16		tp_cont;		// �^�b�`�p�l���ڐG������

	u8		tp_auto_samp;	// �^�b�`�p�l���I�[�g�T���v�����O�t���O(0:�T���v�����O���Ă��Ȃ��@1:�T���v�����O��)
	u8 		disp3DSW;			// �R�c�\���f�B�X�v���C�X�C�b�`
	u8  	AgbCasetteVersion;	// �������܂�Ă���Agb�J�[�b�g���b�W�̃o�[�W�����iGBA�|�P�������������܂�Ă��鎞�̂݁j
	u8 		DontSleep;          //�X���[�v��Ԃɂ��Ă͂����Ȃ��ꍇBIT�������Ă��� ���v�ȏꍇ0
	u8 		DontSoftReset;      //�\�t�g���Z�b�g�������Ȃ��ꍇBIT�������Ă��� ���v�ȏꍇ0

	BOOL 	DS_Boot_Flag;		// 

}SystemArea;


//==================================================================
//	�O���[�o���ϐ�
//==================================================================
GLOBAL SystemArea sys;						// �V�X�e�����\�[�X

//==================================================================
//	�������֐�
//==================================================================
GLOBAL void sys_InitSystem(void);
GLOBAL void sys_InitVRAM(void);
GLOBAL void sys_InitKeyRead(void);
GLOBAL void sys_InitAgbCasetteVer(int version);

//==================================================================
//	�f�t�H���g���荞�݊֐�
//==================================================================
GLOBAL void sys_VBlankIntr(void);

// HBlank�ݒ�
GLOBAL void sys_HBlankIntrStop( void );
GLOBAL BOOL sys_HBlankIntrSet( INTR_FUNC func, void * work );

//==================================================================
//	���[�e�B���e�B�[�֐�
//==================================================================


//V�u�����N���Ăяo���֐��̓o�^
GLOBAL void sys_VBlankFuncChange(INTR_FUNC func, void * work);

//	�t�@�C�����[�h�֐�
GLOBAL void* sys_LoadFile( int mode, const char *path);
GLOBAL void * sys_LoadFileEx( int mode, const char * path, u32 * siz );
GLOBAL void* sys_LoadGraphFile(const char *path, const u8 inMode);
GLOBAL void sys_LoadFileNoMem(const char *path,void **mem);
/*---------------------------------------------------------------------------*
  Name:         sys_LoadFileDiv

  Description:  �ʏ�t�@�C���̓ǂݍ��ݕ��� 
  
  Arguments:    mode	�w��q�[�v�̈��`
				path	�t�@�C���ւ̃p�X
				memory	�t�@�C���ǂݍ��ݐ�A�h���X�i�[�|�C���^
				offset	�ǂݍ��݃I�t�Z�b�g�i�[�|�C���^
				divsiz	�ǂݍ��ݕ����T�C�Y
Returns:		0:�p���A1=�I��
 *---------------------------------------------------------------------------*/
GLOBAL int sys_LoadFileDiv( int mode, const char * path, void** memory, u32* offset, u16 divsiz );

/*---------------------------------------------------------------------------*
  Name:         sys_LoadFileDivNoMem

  Description:  �ʏ�t�@�C���̓ǂݍ��ݕ���(�������m�ۂ��Ȃ�)
  
  Arguments:    path	�t�@�C���ւ̃p�X
				memory	�t�@�C���ǂݍ��ݐ�A�h���X�i�[�|�C���^
				offset	�ǂݍ��݃I�t�Z�b�g�i�[�|�C���^
				divsiz	�ǂݍ��ݕ����T�C�Y
Returns:		0:�p���A1=�I��
 *---------------------------------------------------------------------------*/
GLOBAL int sys_LoadFileDivNoMem( const char * path, void** memory, u32* offset, u16 divsiz );
#if 0
/*---------------------------------------------------------------------------*
  @brief	�O���t�B�b�N�p�t�@�C�����\�[�X�̉��

  @param	addr	(void*)������郊�\�[�X�A�h���X
  @param	free	TRUE�Ȃ�΁A�L���b�V���o�^����Ă��郊�\�[�X�ł��������
					FALSE�̏ꍇ�A�L���b�V���o�^����Ă���Ή�����Ȃ�
  @retval	0		������
  @retval	1		�L���b�V��������
  @retval	2		�L���b�V���o�^����Ă���̂Ŕ���
  @retval	0xFF	�p�����[�^���s��
 *---------------------------------------------------------------------------*/
GLOBAL s8 sys_FreeGraphFile(void* addr,u8 free);
#endif
	//	�L�[���擾�֐�
GLOBAL void sys_MainKeyRead(void);

// �L�[���s�[�g�̑��x�ƃE�F�C�g���Z�b�g
GLOBAL void sys_KeyRepeatSpeedSet( int speed, int wait );

/**
 * @brief	�t�@�C��������t�@�C���L���b�V���p�̃n�b�V���l���擾����
 * @param   path	�t�@�C����������
 * @retval  u32		
 */
GLOBAL u32 CreateFileHash(const char *path);

//==============================================================================
/**
 * ���ɃL���b�V���Ƃ��đ��݂��Ă��邢�邩��������
 * @param   hash	�t�@�C��������擾�����n�b�V���l
 * @retval  int		0�`:���������z��̗v�f	-1:������Ȃ�����
 */
//==============================================================================
GLOBAL int SearchFileCache(u32 hash);

//==============================================================================
/**
 * �V�����ǂݍ��񂾃t�@�C�����L���b�V�����Ƃ��ēo�^����
 *
 * @param   memory		�V�����m�ۂ����������̃A�h���X
 * @param   hash		�t�@�C��������擾�����n�b�V���l
 *
 * @retval  int			�o�^�����ԍ�
 */
//==============================================================================
GLOBAL int SetBlankCache(void* memory, u32 hash);

//==============================================================================
/**
 * �L���b�V���̑S����E�n�b�V�����̃N���A
 * @param   none		
 * @retval  none		
 */
//==============================================================================
GLOBAL void ClearFileCache(void);

//==============================================================================
/**
 * @brief	�n�b�V���z���NULL����������
 */
//==============================================================================
GLOBAL void InitFileCache(void);

//==============================================================================
/**
 * @brief	����̃n�b�V�����N���A����(�L�[�w��)
 *
 * @param   hash	�t�@�C��������擾�����n�b�V���l
 *
 * @retval  int		0�`:�폜�����v�fIndex	-1:�폜���Ȃ�����
 */
//==============================================================================
GLOBAL int ClearFileCacheKey(u32 hash);

//==============================================================================
/**
 * @brief	����̃n�b�V�����N���A����(�A�h���X�w��)
 *
 * @param   addr	���\�[�X�̃A�h���X
 *
 * @retval  int		0�`:�폜�����v�fIndex	-1:�폜���Ȃ�����
 */
//==============================================================================
GLOBAL int ClearFileCacheAddr(void* addr);

/*---------------------------------------------------------------------------*
  @brief	�X���[�v��Ԃ��֎~����
 *---------------------------------------------------------------------------*/
GLOBAL void sys_SleepNG(u8 sleepTypeBit);

/*---------------------------------------------------------------------------*
  @brief	�X���[�v��Ԃ�������
 *---------------------------------------------------------------------------*/
GLOBAL void sys_SleepOK(u8 sleepTypeBit);

/*---------------------------------------------------------------------------*
  @brief	�\�t�g�E�G�A���Z�b�g��Ԃ��֎~����
 *---------------------------------------------------------------------------*/
GLOBAL void sys_SoftResetNG(u8 sleepTypeBit);

/*---------------------------------------------------------------------------*
  @brief	�\�t�g�E�G�A���Z�b�g��Ԃ�������
 *---------------------------------------------------------------------------*/
GLOBAL void sys_SoftResetOK(u8 sleepTypeBit);




#undef GLOBAL


#endif
