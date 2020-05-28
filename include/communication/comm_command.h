//=============================================================================
/**
 * @file	comm_command.h
 * @brief	�f�[�^���L���s���ꍇ�̒ʐM�V�X�e��
 *          �g�p����ꍇ�ɏ������ޕK�v��������̂��܂Ƃ߂��w�b�_�[
 * @author	Katsumi Ohno
 * @date    2005.07.26
 */
//=============================================================================

#ifndef __COMM_COMMAND_H__
#define __COMM_COMMAND_H__


//==============================================================================
//	��`
//==============================================================================

//==============================================================================
//	�^�錾
//==============================================================================
// �R�[���o�b�N�֐��̏���
typedef void (*PTRCommRecvFunc)(int netID, int size, void* pData, void* pWork);
// �T�C�Y���Œ�̏ꍇ�T�C�Y���֐��ŕԂ�
typedef int (*PTRCommRecvSizeFunc)(void);
// ��M�o�b�t�@�������Ă���ꍇ���̃|�C���^
typedef u8* (*PTRCommRecvBuffAddr)(int netID, void* pWork, int size);


typedef struct {
    PTRCommRecvFunc callbackFunc;    ///< �R�}���h���������ɌĂ΂��R�[���o�b�N�֐�
    PTRCommRecvSizeFunc getSizeFunc; ///< �R�}���h�̑��M�f�[�^�T�C�Y���Œ�Ȃ珑���Ă�������
    PTRCommRecvBuffAddr getAddrFunc;
} CommPacketTbl;

#define   _SET(callfunc, getSize, name)       {callfunc,  getSize},

/// �ėp�ʐM�R�}���h�̒�`
enum CommCommand_e {
  CS_NONE = 0xee,                ///< �Ȃɂ����Ȃ�
  CS_FREE = 0,                   ///< ��R�}���h
  CS_COMMAND_MIN = 1,             ///< �ŏ��l
  CS_EXIT = CS_COMMAND_MIN,            ///< �I��
  CS_AUTO_EXIT,            ///< �����I��
  CS_COMM_INFO,       ///< info���
  CS_COMM_INFO_ARRAY,  ///< info���𓊂��Ԃ�
  CS_COMM_INFO_END,   ///< info��񑗐M�I��
  CS_COMM_NEGOTIATION,  ///< ���������̃l�S�V�G�[�V����
  CS_COMM_NEGOTIATION_RETURN,
  CS_DEBUG_VARIABLE,         ///< �f�o�b�O�p�i�{�ԂŃR�}���h�ԍ����ς��Ȃ��悤�ɂ��̂܂܂����Ă����j
  CS_DEBUG_START,            ///< �f�o�b�O�p �o�g���X�^�[�g
  CS_DSMP_CHANGE,            ///< DS���[�h�ʐM��MP���[�h�ʐM���ɐ؂�ւ��鋖�𓾂�
  CS_DSMP_CHANGE_REQ,        ///< DS���[�h�ʐM��MP���[�h�ʐM���ɐ؂�ւ���w�����o��
  CS_DSMP_CHANGE_END,        ///< DS���[�h�ʐM��MP���[�h�ʐM���ɐ؂�ւ������������Ƃ�ʒm
  CS_COMMAND_THROWOUT,       ///< �R�}���h��j�����鋖�𓾂�
  CS_COMMAND_THROWOUT_REQ,   ///< �R�}���h��j������w�����o��
  CS_COMMAND_THROWOUT_END,   ///< �R�}���h�j�������������Ƃ�ʒm-----
  CS_TIMING_SYNC,            ///< ���������R�}���h
  CS_TIMING_SYNC_END,        ///< ��������ꂽ���Ƃ�Ԃ��R�}���h
  CS_TIMING_SYNC_INFO,       ///< �����̏󋵂��q�@�ɕԂ��R�}���h
  CS_LIST_NO,                ///< DS��p �I��ԍ��𑗂肠��
  CS_TOOL_TEMP,              ///< DS��p �ėp�f�[�^�]��
  CS_WIFI_EXIT,
  //------------------------------------------------�����܂�----------
  CS_COMMAND_MAX   // �I�[--------------����͈ړ������Ȃ��ł�������     21
};

#define COMM_VARIABLE_SIZE (0xffff)   ///< �σf�[�^���M�ł��邱�Ƃ������Ă���


/// �R�}���h�e�[�u���̏�����������
extern void CommCommandInitialize(const CommPacketTbl* pCommPacketLocal,int listNum,void* pWork);
/// �R�}���h�e�[�u���̊J������
extern void CommCommandFinalize( void );
/// �f�[�^�̃T�C�Y�𓾂�
extern int CommCommandGetPacketSize(int command);
///  �R�}���h�e�[�u����j�����鎞�̖���
extern BOOL CommCommandThrowOut(void);
///  �R�}���h�e�[�u�����j�����I��������ǂ�������
extern BOOL CommCommandIsThrowOuted(void);
///  �R�[���o�b�N���Ă�
extern void CommCommandCallBack(int netID, int command, int size, void* pData);
/// �v�����g
extern void CommCommandDebugPrint(int command);

// �T�C�Y�w��p�ȈՊ֐�  �e�ʍ팸�̈�extern�錾  06.03.29
extern int _getVariable(void);
extern int _getZero(void);
extern int _getOne(void);

extern void* CommCommandCreateBuffStart(int command, int netID, int size);
extern BOOL CommCommandCreateBuffCheck(int command);


#endif// __COMM_COMMAND_H__

