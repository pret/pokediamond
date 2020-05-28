#ifndef __BEACONDOWNLOAD__
#define __BEACONDOWNLOAD__
/**
 * @version "$Id: beacondownload.h,v 1.3 2006/07/05 13:50:25 mitsuhara Exp $"
 *
 * @file beacondownload.h
 * @brief �r�[�R�����g�p�����f�[�^�_�E�����[�h����
 * 
 */
 
#ifndef BEACONDOWNLOAD
#define DEBUG_BEACONDOWNLOAD	1
#endif

// �R�[���o�b�N�^
typedef void (*BSDOWN_CALLBACK)( int code );

// �ȉ��̏����������Ȃ�ꂽ�Ƃ��ɃR�[���o�b�N���Ԃ�܂��B
enum
{
	BSDOWNCALLBACK_STARTSCAN,	// �X�L�����J�n��
	BSDOWNCALLBACK_START,		// �e�@���݂����Ƃ�
	BSDOWNCALLBACK_SUCCESS,		// �f�[�^�����S�Ɏ󂯎�����Ƃ�
	BSDOWNCALLBACK_FINISH,		// �����̏I�������i�L�����Z�����A�f�[�^�����S�Ɏ󂯎�����Ƃ����ʁj
	BSDOWNCALLBACK_ERROR,		// �G���[������
	BSDOWNCALLBACK_RESTART,		// ��M���ɐe�@������ύX�����ꍇ�ȂǁA�f�[�^�ɐH���Ⴂ���������ꍇ�B
								//�@���̏ꍇ�A�����I�ɍă_�E�����[�h���J�n����܂��B
	BSDOWNCALLBACK_FILEINFO		// �t�@�C���̃^�C�g�������擾�ł����Ƃ��ɃR�[���o�b�N�Ƃ��Ă�����܂��B
};

/* ======================================================================
   �֐��Q
   ====================================================================== */

// ��ƂɕK�v�ȃo�b�t�@�̃T�C�Y��Ԃ��܂��B
extern int bsdown_c_worksize();

/*---------------------------------------------------------------------------*
  Name:         bsdown_c_init
  Description:  
	  �q�@�p�������B
	  ������WM_INIT���Ăяo���A�X�L�����J�n�܂ň�C�ɐi�߂܂��B
  Arguments:    
  				target �@�c �f�[�^���i�[�����̃|�C���^�B
  						�@�@�S�o�C�g�̈�ɂ��킹�ĉ������B
  				callback �c �R�[���o�b�N�֐�]
  				buffer   �c ��Ɨ̈�B

  Returns:      ��������ΐ^�B
 *---------------------------------------------------------------------------*/
extern BOOL bsdown_c_init( void *target, BSDOWN_CALLBACK callback, void *buffer );

// ���݂܂łɎ�M�����p�P�b�g�ʂ��擾
extern int bsdown_c_received(void);

// ��M���ׂ��p�P�b�g�̗�
extern int bsdown_c_total(void);

// ��M���Ă���f�[�^�̃T�C�Y�B�܂���M���J�n����Ă��Ȃ���΂O��Ԃ��B
extern int bsdown_c_size(void);

// �I������B����������R�[���o�b�N��BSDOWNCALLBACK_ERROR2���Ԃ��Ă���B
extern BOOL bsdown_end( void );

// �Ō�Ɏ�M�����p�P�b�g�̃C���f�b�N�X
extern int bsdown_c_lastreceive(void);
// ���݂܂Ŏ󂯎�����p�P�b�g�̕\
extern u8 *bsdown_c_downloadpacket(void);

// ��M�ς݂̂b�q�b�����������`�F�b�N�B
// ���̊֐����Ăяo���Ȃ�����A�b�q�b�̃`�F�b�N�͍s���܂���B
// BSDOWNCALLBACK_SUCCESS �̃R�[���o�b�N����������ɁA�Ăяo���Ă��������B
extern int bsdown_c_checkcrc(void);

// �Ō�ɂ����Ƃ����r�[�R���̋��x���擾�B�i�A���e�i�A�C�R���̕\�����ɂ����p���������j
extern int bsdown_c_linklevel(void);

// �^�C�g���ȂǁA�_�E�����[�h���Ă���t�@�C���̏����擾���܂��B
// �܂���M�ł��Ă��Ȃ��Ƃ��́ANULL��Ԃ��܂��B
extern void* bsdown_c_fileheader(void);

// ����A���ňႤ��ނ̃p�P�b�g���󂯎�����ꍇ�A�^�C���A�E�g�Ɣ��肷�邩�H
#define BSDOWN_TIMEOUT 16

/* ======================================================================
   �ȉ��͎q�@�e�@���ʂ̐ݒ�ɂ���K�v������B
   ====================================================================== */

// GGID�͒萔�Œ�`�B�r�[�R���z�M�͐�p�̂��̂������Ă��������B
#if 0
#define BDOWN_GGID 0x003fff20
#else
#define BDOWN_GGID 0x00000345
#endif

// ��M/���M����\���̂���t�@�C���̍ő�l
#define BSOWN_MAXSIZE (128*1024)

#define BSDOWN_SCANTIME 220



#endif	// __BEACONDOWNLOAD__
