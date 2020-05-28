//=============================================================================
/**
 * @file	comm_command_field.h
 * @brief	�ʐM�̃R�}���h�ꗗ  �t�B�[���h�p
 * @author	Katsumi Ohno
 * @date    2005.11.07
 */
//=============================================================================

#ifndef __COMM_COMMAND_FIELD_H__
#define __COMM_COMMAND_FIELD_H__

#include "communication/comm_command.h"






/// �t�B�[���h��p�ʐM�R�}���h�̒�`�B
enum CommCommandField_e {
  CF_PLAYER_POS = CS_COMMAND_MAX,              ///< �v���[���[�̍��W�𑗂�
  CF_PLAYER_POS_ID,           ///< �w��̃v���[���[�̍��W�𑗂�
  CF_NPC_TALK,                  ///<  NPC�Ƃ̉�b
  CF_OTHER_TALK,              ///< NPC�Ɖ�b
  CF_OTHER_TALK_SERVER_SIDE,  ///< NPC�Ɖ�b�T�[�o�[��
  CF_CHECK_FIELDMENU_OPEN,    ///< �t�B�[���h���j���[���J���Ă������₢���킹
  CF_CHECK_ABUTTON_ACTION,    ///< �`�{�^���ŉ�����������̂��₢���킹
  CF_RESULT_FIELDMENU_OPEN,   ///< �t�B�[���h���j���[���J���Ă��������ʂ�Ԃ�
  CF_RESULT_UGMENU_OPEN,      ///< �Y�z���j���[���J���Ă��������ʂ�Ԃ�
  CF_PLAYER_INIT_END,      ///< �������]�����I�����ꍇ
  CF_TRAP_DATA,               ///< �P��㩃f�[�^�ݒu
  CF_TRAP_DATA_DEL,           ///< 㩃f�[�^�̍폜
  CF_TRAP_DATA_RESULT,        ///< 㩃f�[�^�̌��ʂ�Ԃ�
  CF_TRAP_ARRAY_DATA,         ///< �A�������f�[�^�̂P��㩃f�[�^
  CF_TRAP_ARRAY_RESULT,       ///< 㩃f�[�^���󂯎�������ʂ�Ԃ�
  CF_TRAP_START,      ///< 㩂ɂ�����B㩂��N������
  CF_TRAP_SECOND_START,      ///< 2��ڂ̃X�^�[�g  㩂����s�����
  CF_TRAP_SECOND_START_RET,      ///< 2��ڂ̃X�^�[�g  㩂����s�����
  CF_TRAP_PRIEND,     ///< ���I�����q�@�ɂ�����  �{���̏I���͂��Ȃ�
  CF_TRAP_END,        ///< �q�@����㩂��Ǘ����Ă��ďI�������ꍇ�e�@�ɂ����`����
  CF_TRAP_END_RESULT, ///< �e�ɗ���㩉������q�@�ɍē]��
  CF_TRAP_END_FORCE,  ///< �����I��
  CF_TRAP_RELEASE,    ///< 㩉���
  CF_TRAP_NOWARRAY,   ///< ��㩂ɂ������Ă���l�𑗐M
  CF_TRAP_RADAR_REQ,   ///< �V�R���[�_�[�\��REQ
  CF_TRAP_RADAR_ANS,   ///< �V�R���[�_�[�\��ANS
  CF_TOUCH_GROUND,    ///< �n�ʂ��^�b�`����
  CF_TOUCH_RESULT1,    ///< �n�ʂ��^�b�`�������ʂ�Ԃ�1
  CF_TOUCH_RESULT2,    ///< �n�ʂ��^�b�`�������ʂ�Ԃ�2
  CF_TRAP_DEFUSE,     ///< 㩉���
  CF_PLAYER_DELETE,   ///< �v���[���[�̏���
  CF_SECRETBASE_DATA,             ///< �閧��n�f�[�^�ЂƂ�
  CF_SECRETBASE_DATA_SERVER,             ///< �閧��n�f�[�^�ЂƂ��i�T�[�o�[���瑗�M�j-
  CF_SECRETBASE_POS,        ///< �閧��n������ʒu
  CF_SECRETBASE_JUMP_END,  ///< �閧��n�ړ����I���������Ƃ�Ԃ�
  CF_SECRETBASE_RETJUMP,  ///< �閧��n����A��ړ����s��
  CF_SECRETBASE_EVENT_START,  ///< �閧��n�ɓ���A�܂��͔�����C�x���g�J�nS->C
  CF_SECRETBASE_EVENT_RES,  ///< �閧��n�ɓ���A�܂��͔�����C�x���g����C->S
  CF_SECRETBASE_GOODS_CHECK, ///< A�{�^���ŃO�b�Y�̃`�F�b�N��������
  CF_SECRETBASE_MOVE_FAILED,  ///< �ړ��Ɏ��s����
  CF_MOVE_CONTROL,        ///< �ړ��R���g���[����Ԃ𑗐M����
  CF_DIG_STONE_PICKUP,      ///< �΂��E����������Ȃ��i�N���C�A���g�Ŋm�F���Ă��炤�ׂ̗v���R�}���h�j
  CF_FIND_FOSSIL,             ///< ���Δ���
  CF_DIG_FOSSIL_START_REQ,       ///< ���Δ��@�J�n���N�G�X�g
  CF_DIG_FOSSIL_START,       ///< ���Δ��@�J�n
  CF_DIG_FOSSIL_END_REQ,     ///< ���Δ��@�I�����N�G�X�g
  CF_DIG_FOSSIL_POS,    ///< �@�����ꏊ��e�ɑ���
  CF_DIG_FOSSIL_POS_RETURN,    ///< �@�����ꏊ���q�ɑ���
  CF_DIG_FOSSIL_INIT,       ///< ���΂��@���Ă��邱�Ƃ�e�ɒʒm
  CF_DIG_FOSSIL_PCRADAR,      ///< �p�\�R�����΃��[�_�[�N��
  CF_DIG_FOSSIL_PCRADAR_ANS,  ///< �p�\�R�����΃��[�_�[�̓���
  CF_ASKSEQ_SET,           ///< ��b��Ԃ�ύX����
  CF_TALKSEQ_SET,          ///< �b����������Ԃ�ύX����
  CF_ASKSEQ_SET_CALL,           ///< ��b��Ԃ�ύX����(SERVER����߂�)
  CF_TALKSEQ_SET_CALL,          ///< �b����������Ԃ�ύX����(SERVER����߂�)
  CF_SEND_ITEM,             ///< �A�C�e���𑗂�
  CF_SEND_ITEM_CALL,        ///< �A�C�e���𑗂�R�}���h�̖߂�(SERVER����߂�)
  CF_SECRET_QUESTION,       ///< �閧�̎���
  CF_SECRET_QUESTION_CALL,  ///< �閧�̎��� (SERVER����߂�)
  CF_TARGET_RECORD,         ///< �b������̃��R�[�h���𑗂�
  CF_TARGET_RECORD_CALL,    ///< �b������̃��R�[�h���𑗂�
  CF_PC_ACCESS,            ///< �p�\�R���̑O��A�{�^�����������ꍇ(SERVER����߂�)
  CF_FLAG_STATE,           ///< ����Ԃ��ω��������Ƃ��T�[�o�[�ɑ��M
  CF_FLAG_STATE_RET,       ///< ����Ԃ̕ω����T�[�o�[�����đ��M
  CF_DRILL_START,          ///< �閧��n���@��
  CF_DRILL_START_RESULT,   ///< �閧��n���ق�邩�ǂ�����Ԃ�
  CF_TRAINER_CARD,         ///< �g���[�i�[�J�[�h�𑗂�
  CF_GET_FLAG,            ///< �p�\�R������n�^�����邩�ǂ����ēx�m�F
  CF_GET_FLAG_RET,        ///< �p�\�R������n�^����ꂽ��ԐM
  CF_FLAG_NOWARRAY_REQ,   ///< ����̃n�^���v��
  CF_FLAG_NOWARRAY,       ///< ����̃n�^���𑗂�
  CF_FLAG_NOWARRAY_END,   ///< ����̃n�^���I���
  CF_DIRECT_START_SET,    ///< �_�C���N�g�R�[�i�[�X�^�[�g�ʒu�Z�b�g
  CF_DIRECT_STARTPOS,     ///< �_�C���N�g�R�[�i�[�X�^�[�g�ʒu
  CF_LVUP_FLAG,           ///< �p�\�R��LVUP
  CF_LVUP_FLAG_RET,       ///< �p�\�R��LVUP
  
  //------------------------------------------------�������烆�j�I�����[���p�R�}���h

  CU_PLAYER_STATUS,		///< �X�e�[�^�X�̑��M
  CU_PLAYER_SELECT,		///< �I����e�̑��M�i��������E�`���b�g�E�J�[�h�E��������E��߂����j
  CU_TALK_TALK,			///< ��b�f�[�^�̑��M
  CU_BATTLE_PLIST_RET,	///< �퓬�O�|�P�������X�g�̑I�����ʁi�I�������E�L�����Z�������j
  CU_TALK_NO,			///< ������
  CU_START_NEXT,		///< �����E�퓬�E�`���b�g�E�J�[�h�ւ̈ړ��J�n
  CU_END_CONNECT_SERVER,///< �e�@���ʐM�ؒf��ʒm		
  CU_TRAINER_CARD,		///< �g���[�i�[�J�[�h�f�[�^����M

  //------------------------------------------------��������~�b�N�X�o�g���p�R�}���h

  CF_MIXBATTLE,			///< �~�b�N�X�o�g���i���胁���o�[�������Ă���j
  CF_MIXBATTLE_TRADE,	///< �~�b�N�X�o�g���i�����|�P�����̃C���f�b�N�X�������Ă���j


  //------------------------------------------------�����܂�

  //------------------------------------------------�������烌�R�[�h�R�[�i�[�p

  CR_RECORD_YES,							///< �͂�
  CR_RECORD_NO,								///< ������
  CR_RECORD_STOP,							///< �����҂������̂ň�U�X�g�b�v
  CR_RECORD_RESTART,						///< �����ҏ������I������̂ōĉ�
  CR_RECORD_END_CHILD,						///< �q�@�����E
  CR_RECORD_END,							///< �I��
  CR_RECORD_CHILD_JOIN,						///< �q�@��������錾
  CR_RECORD_START,							///< �e�@�����R�[�h�J�n��ʒB
  CR_RECORD_DATA,  							///< ���R�[�h�f�[�^���M
  CR_RECORD_BAN,							///< ���E�֎~�E����
  //------------------------------------------------�����܂�

  //------------------------------------------------�������炨�G�����{�[�h��p�ʐM�R�}���h

  CO_OEKAKI_GRAPHICDATA, 					///< �݂�Ȃŕ`���Ă����摜�f�[�^
  CO_OEKAKI_LINEPOS,						///< �^�b�`�p�l���Ŏ擾�����|�W�V�����f�[�^
  CO_OEKAKI_LINEPOSSERVER,					///< �^�b�`�p�l���Ŏ擾�����|�W�V�����f�[�^
  CO_OEKAKI_YES,							///< �͂�
  CO_OEKAKI_NO,								///< ������
  CO_OEKAKI_STOP,							///< �����҂������̂ň�U�X�g�b�v
  CO_OEKAKI_RESTART,						///< �����ҏ������I������̂ōĉ�
  CO_OEKAKI_END_QUESTION,					///< �I��
  CO_OEKAKI_END_CHILD,						///< �q�@�����E
  CO_OEKAKI_END,							///< �I��
  CO_OEKAKI_CHILD_JOIN,						///< �q�@��������錾
  CO_OEKAKI_OUT_CONTROL,				    ///< ���E�֎~�M��
  
  //------------------------------------------------�����܂�


  CF_COMMAND_MAX   // �I�[--------------����͈ړ������Ȃ��ł�������
};

extern void CommCommandFieldInitialize(void* pWork);
extern int _getRecordSize(void);
extern int _getPictureSize(void);
extern int _getLinePosSize(void);
extern int _getLinePosServerSize(void);
extern void CommDummyCallBack( int netID, int size, void* pBuff, void* pWork );













#endif// __COMM_COMMAND_FIELD_H__

