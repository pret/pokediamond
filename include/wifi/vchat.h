#ifndef __VHCAT_H_
#define __VHCAT_H_
// �{�C�X�`���b�g�֌W�B
// dwc_rap.c ��vchat.c����̂݌Ăяo�����B
// �{�C�X�`���b�g���Ăԏꍇ�́Adwc_rap.h�o�R�ŌĂԁB

extern void myvct_init( int heapID, int codec );
extern void myvct_setCodec( int codec );
extern void myvct_main( );
extern BOOL myvct_checkData( int aid, void *data, int size );

extern void* mydwc_AllocFunc( DWCAllocType name, u32   size, int align );
extern void mydwc_FreeFunc( DWCAllocType name, void* ptr,  u32 size  );

//==============================================================================
/**
 * ��b�I�����������R�[���o�b�N��ݒ肵�܂��B
 * ���肩��؂�ꂽ�ꍇ���Ăяo����܂��B
 * ���̊֐����Ăяo����钼�O�ɁAvchat.c�p�̃��[�N���������܂��B
 * @param   none
 * @retval  none
 */
//==============================================================================
extern void myvct_setDisconnectCallback( void (*disconnectCallback)() );

//==============================================================================
/**
 * ��b�I���v���������܂��B�܂��ʘb�ł��Ă��Ȃ��Ƃ��͑����ɏI�����܂��B
 * myvct_setDisconnectCallback�Őݒ肳�ꂽ�R�[���o�b�N���Ăяo����܂��B
 * @param   none
 * @retval  none
 */
//==============================================================================
extern void myvct_endConnection();

//==============================================================================
/**
 * ���C�u�����I�������B���̒������b�I�����������R�[���o�b�N���Ă΂�܂��B
 * �ʏ�I�����͂��̊֐��́A��b�I���v������Ăяo����܂��B
 * @param   none
 * @retval  none
 */
//==============================================================================
extern void myvct_free();

//==============================================================================
/**
 * �����̃m�C�Y�J�b�g���x���𒲐����܂��i�O������A�N�Z�X�������̂ŁA������Ɂj
 * @param   d �c �����臒l�������邩�A�グ�邩�i������قǏE���₷���Ȃ�j
 * @retval  none
 */
//==============================================================================
extern void myvct_changeVADLevel(int d);


// ���M�������ǂ�����Ԃ��܂�
extern BOOL myvct_IsSendVoiceAndInc(void);

// �{�C�X�`���b�g���I�t�ɂ��܂��B
extern void myvct_offVchat();

// �{�C�X�`���b�g���I���ɂ��܂��B
extern void myvct_onVchat();

// �{�C�X�`���b�g���I������Ԃ��܂��B
extern BOOL myvct_isVchatOn();

#endif

